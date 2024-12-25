; ----------------------------------------------------------------------
; Copyright (c) 2024 Devon Artmeier
;
; Permission to use, copy, modify, and/or distribute this software
; for any purpose with or without fee is hereby granted.
;
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
; WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIE
; WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
; AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
; DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
; PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER 
; TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
; PERFORMANCE OF THIS SOFTWARE.
; ----------------------------------------------------------------------

; ----------------------------------------------------------------------
; Initialize the Mega CD
; ----------------------------------------------------------------------
; PARAMETERS:
;	a0.l  - Pointer to Sub CPU program
;	d0.l  - Size of Sub CPU program
; RETURNS:
;	d0.b  - Error code
;	        0 - Success
;	        1 - No BIOS found
;	        2 - Program load failed
;	        3 - Hardware failure
;	eq/ne - Success/Failure
; ----------------------------------------------------------------------

InitMcd:
	movem.l	d0-d1/a0-a1,-(sp)			; Save registers
	
	bsr.w	CheckMcdBios				; Check for a BIOS
	bne.s	NoMcdBiosFound				; If no BIOS was found, branch
	
	bsr.w	ResetMcdGateArray			; Reset the Gate Array
	bsr.w	ClearMcdCommRegisters			; Clear communication registers
	
	move.l	#$100,d0				; Hold reset
	bsr.w	HoldMcdResetTimed
	bne.s	McdHardwareFail				; If it failed, branch
	
	bsr.w	RequestMcdBusTimed			; Request bus access
	bne.s	McdHardwareFail				; If it failed, branch
	
	move.b	#0,$A12002				; Disable write protection
	
	lea	$420000,a1				; Decompress Sub CPU BIOS
	jsr	McdKosDec
	
	movem.l (sp),d0-d1/a0-a1			; Load Sub CPU program
	move.l	#$6000,d1
	bsr.w	CopyMcdPrgRamData
	bne.s	McdProgramLoadFail			; If it failed, branch
	
	move.b	#$2A,$A12002				; Enable write protection	

	move.l	#$100,d0				; Release reset
	bsr.w	ReleaseMcdResetTimed
	bne.s	McdHardwareFail				; If it failed, branch
	
	bsr.w	ReleaseMcdBusTimed			; Release bus
	bne.s	McdHardwareFail				; If it failed, branch
	
	movem.l (sp)+,d0-d1/a0-a1			; Success
	moveq	#0,d0
	rts

NoMcdBiosFound:
	movem.l (sp)+,d0-d1/a0-a1			; No BIOS found
	moveq	#1,d0
	rts

McdProgramLoadFail:
	movem.l (sp)+,d0-d1/a0-a1			; Program load failed
	moveq	#2,d0
	rts

McdHardwareFail:
	move.b	#%00000010,$A12001			; Halt
	
	movem.l (sp)+,d0-d1/a0-a1			; Hardware failure
	moveq	#3,d0
	rts

; ----------------------------------------------------------------------
; Check if there's a Mega CD BIOS available
; ----------------------------------------------------------------------
; RETURNS:
;	eq/ne - Found/Not found
;	a0.l  - Pointer to compressed Sub CPU BIOS, if found
; ----------------------------------------------------------------------

CheckMcdBios:
	movem.l	d0/a1-a3,-(sp)				; Save registers
	
	cmpi.l	#"SEGA",$400100				; Is the "SEGA" signature present?
	bne.s	McdBiosCheckEnd				; If not, branch
	cmpi.w	#"BR",$400180				; Is the "Boot ROM" software type present?
	bne.s	McdBiosCheckEnd				; If not, branch
	
	lea	McdBiosSignatures(pc),a1		; Get known signature location list

FindMcdBiosLoop:
	move.l	(a1)+,d0				; Get pointer to signature data to check
	movea.l	d0,a2
	beq.s	McdBiosNotFound				; If we are at the end of the list, branch
	
	movea.l	(a2)+,a0				; Get pointer to Sub CPU BIOS
	movea.l	(a2)+,a3				; Get pointer to signature

CheckMcdBiosSignature:
	move.b	(a2)+,d0				; Get character
	beq.s	McdBiosCheckEnd				; If we are done checking, branch
	cmp.b	(a3)+,d0				; Does the signature match so far?
	bne.s	FindMcdBiosLoop				; If not, check the next BIOS
	bra.s	CheckMcdBiosSignature			; Loop until signature is fully checked

McdBiosNotFound:
	andi	#%11111011,ccr				; BIOS not found

McdBiosCheckEnd:
	movem.l	(sp)+,d0/a1-a3				; Restore registers
	rts

; ----------------------------------------------------------------------

McdBiosSignatures:
	dc.l	McdBiosSega15800
	dc.l	McdBiosSega16000
	dc.l	McdBiosSega1AD00
	dc.l	McdBiosWonder16000
	dc.l	0
	
McdBiosSega15800:
	dc.l	$415800
	dc.l	$41586D
	dc.b	"SEGA", 0
	even
	
McdBiosSega16000:
	dc.l	$416000
	dc.l	$41606D
	dc.b	"SEGA", 0
	even
	
McdBiosSega1AD00:
	dc.l	$41AD00
	dc.l	$41AD6D
	dc.b	"SEGA", 0
	even
	
McdBiosWonder16000:
	dc.l	$416000
	dc.l	$41606D
	dc.b	"WONDER", 0
	even

; ----------------------------------------------------------------------
; Mega CD initialization IRQ2 trigger and delay
; ----------------------------------------------------------------------
; Use this when waiting for the Sub CPU to initialize after loading
; the BIOS and system program and booting. If this doesn't fit your
; needs, then you can manually call TriggerMcdIrq2 however you please.
; ----------------------------------------------------------------------

McdInitIrq2:
	move.w	d0,-(sp)				; Save d0
	move	sr,-(sp)				; Save interrupt settings
	move	#$2700,sr				; Disable interrupts

	bsr.s	TriggerMcdIrq2				; Trigger IRQ2

	move.w	#$2DCE-1,d0				; Delay for a while

WaitMcdInitIrq2:
	dbf	d0,WaitMcdInitIrq2

	move	(sp)+,sr				; Restore interrupt settings
	move.w	(sp)+,d0				; Restore d0
	rts

; ----------------------------------------------------------------------
; Reset the Gate Array
; ----------------------------------------------------------------------

ResetMcdGateArray:
	move.l	d0,-(sp)				; Save d0
	
	move.w	#$FF00,$A12002				; Reset sequence
	move.b	#3,$A12001
	move.b	#2,$A12001
	move.b	#0,$A12001

	moveq	#$80-1,d0				; Wait for a bit to process

WaitMcdGateArrayReset:
	dbf	d0,WaitMcdGateArrayReset
	
	move.l	(sp)+,d0				; Restore d0
	rts
	
; ----------------------------------------------------------------------
; Trigger IRQ2
; ----------------------------------------------------------------------

TriggerMcdIrq2:
	bset	#0,$A12000				; Trigger IRQ2
	rts

; ----------------------------------------------------------------------
; Hold reset
; ----------------------------------------------------------------------

HoldMcdReset:
	bclr	#0,$A12001				; Hold reset
	bne.s	HoldMcdReset
	rts

; ----------------------------------------------------------------------
; Release reset
; ----------------------------------------------------------------------

ReleaseMcdReset:
	bset	#0,$A12001				; Release reset
	beq.s	ReleaseMcdReset
	rts

; ----------------------------------------------------------------------
; Hold reset (timed)
; ----------------------------------------------------------------------
; PARAMETERS:
;	d0.l  - Time to wait
; RETURNS:
;	eq/ne - Success/Failure
; ----------------------------------------------------------------------

HoldMcdResetTimed:
	move.l	d0,-(sp)				; Save d0

WaitMcdResetHold:
	bclr	#0,$A12001				; Hold reset
	beq.s	McdResetHoldDone			; If it was successful, branch
	subq.l	#1,d0					; Decrement time left
	bne.s	WaitMcdResetHold			; Loop if we should try again
	
	move.l	(sp)+,d0				; Restore d0
	andi	#%11111011,ccr				; Failure
	rts
	
McdResetHoldDone:
	move.l	(sp)+,d0				; Restore d0
	ori	#%00000100,ccr				; Success
	rts

; ----------------------------------------------------------------------
; Release reset (timed)
; ----------------------------------------------------------------------
; PARAMETERS:
;	d0.l  - Time to wait
; RETURNS:
;	eq/ne - Success/Failure
; ----------------------------------------------------------------------

ReleaseMcdResetTimed:
	move.l	d0,-(sp)				; Save d0

WaitMcdResetRelease:
	bset	#0,$A12001				; Release reset
	bne.s	McdResetReleaseDone			; If it was successful, branch
	subq.l	#1,d0					; Decrement time left
	bne.s	WaitMcdResetRelease			; Loop if we should try again
	
	move.l	(sp)+,d0				; Restore d0
	andi	#%11111011,ccr				; Failure
	rts
	
McdResetReleaseDone:
	move.l	(sp)+,d0				; Restore d0
	ori	#%00000100,ccr				; Success
	rts

; ----------------------------------------------------------------------
; Request access to the bus
; ----------------------------------------------------------------------

RequestMcdBus:
	bset	#1,$A12001				; Request bus access
	beq.s	RequestMcdBus
	rts

; ----------------------------------------------------------------------
; Release the bus
; ----------------------------------------------------------------------

ReleaseMcdBus:
	bclr	#1,$A12001				; Release bus
	bne.s	ReleaseMcdBus
	rts

; ----------------------------------------------------------------------
; Request access to the bus (timed)
; ----------------------------------------------------------------------
; PARAMETERS:
;	d0.l  - Time to wait
; RETURNS:
;	eq/ne - Success/Failure
; ----------------------------------------------------------------------

RequestMcdBusTimed:
	move.l	d0,-(sp)				; Save d0

WaitMcdBusRequest:
	bset	#1,$A12001				; Request bus access
	bne.s	McdBusRequestDone			; If it was successful, branch
	subq.l	#1,d0					; Decrement time left
	bne.s	WaitMcdBusRequest			; Loop if we should try again
	
	move.l	(sp)+,d0				; Restore d0
	andi	#%11111011,ccr				; Failure
	rts
	
McdBusRequestDone:
	move.l	(sp)+,d0				; Restore d0
	ori	#%00000100,ccr				; Success
	rts

; ----------------------------------------------------------------------
; Release the bus (timed)
; ----------------------------------------------------------------------
; PARAMETERS:
;	d0.l  - Time to wait
; RETURNS:
;	eq/ne - Success/Failure
; ----------------------------------------------------------------------

ReleaseMcdBusTimed:
	move.l	d0,-(sp)				; Save d0

WaitMcdBusRelease:
	bclr	#1,$A12001				; Release bus
	beq.s	McdBusReleaseDone			; If it was successful, branch
	subq.l	#1,d0					; Decrement time left
	bne.s	WaitMcdBusRelease			; Loop if we should try again
	
	move.l	(sp)+,d0				; Restore d0
	andi	#%11111011,ccr				; Failure
	rts
	
McdBusReleaseDone:
	move.l	(sp)+,d0				; Restore d0
	ori	#%00000100,ccr				; Success
	rts
	
; ----------------------------------------------------------------------
; Copy data to Program RAM
; ----------------------------------------------------------------------
; You should get access to the bus before calling this.
; ----------------------------------------------------------------------
; PARAMETERS:
;	a0.l  - Pointer to data to copy
;	d0.l  - Length of data to copy
;	d1.l  - Program RAM offset
; RETURNS:
;	eq/ne - Success/Failure
;	d1.l  - Advanced Program RAM offset
;	a0.l  - End of data
; ----------------------------------------------------------------------

CopyMcdPrgRamData:
	movem.l	d0/d2/a1,-(sp)				; Save registers	

	move.l	d1,d2					; Set Program RAM bank ID
	swap	d2
	ror.b	#3,d2
	andi.b	#%11000000,d2
	andi.b	#%00111111,$A12003
	or.b	d2,$A12003
	
	lea	$420000,a1				; Get initial copy destination
	move.l	d1,d2
	andi.l	#$1FFFF,d2
	adda.l	d2,a1
	
	add.l	d0,d1					; Advance Program RAM offset
	
CopyMcdPrgRamDataLoop:
	move.b	(a0),(a1)				; Copy byte
	cmpm.b	(a0)+,(a1)+				; Did it copy correctly?
	bne.s	McdPrgRamDataCopyFail			; If not, branch
	
	subq.l	#1,d0					; Decrement number of bytes left to copy
	beq.s	McdPrgRamDataCopyDone			; If we are finished, branch
	
	cmpa.l	#$440000,a1				; Have we reached the end of the bank?
	bcs.s	CopyMcdPrgRamDataLoop			; If not, branch

	addi.b	#$40,$A12003				; Go to next bank
	lea	$420000,a1
	bra.s	CopyMcdPrgRamDataLoop

McdPrgRamDataCopyFail:
	movem.l	(sp)+,d0/d2/a1				; Restore registers
	andi	#%11111011,ccr				; Failure
	rts
	
McdPrgRamDataCopyDone:
	movem.l	(sp)+,d0/d2/a1				; Restore registers
	ori	#%00000100,ccr				; Success
	rts

; ----------------------------------------------------------------------
; Clear communication registers
; ----------------------------------------------------------------------

ClearMcdCommRegisters:
	clr.b	$A1200E					; Clear communication registers
	clr.l	$A12010
	clr.l	$A12014
	clr.l	$A12018
	clr.l	$A1201C
	rts

; ----------------------------------------------------------------------
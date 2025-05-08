; ------------------------------------------------------------------------------
; Copyright (c) 2025 Devon Artmeier
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
; ------------------------------------------------------------------------------

	include	"mcd_main.inc"
	
	section code

; ------------------------------------------------------------------------------
; Check if the Sub CPU's IRQ2 is enabled
; ------------------------------------------------------------------------------
; PARAMETERS:
;	eq/ne - Disabled/Enabled
; ------------------------------------------------------------------------------

	xdef CheckSubCpuIrq2
CheckSubCpuIrq2:
	btst	#7,MCD_IRQ2					; Check if IRQ2 is enabled
	rts

; ------------------------------------------------------------------------------
; Trigger Sub CPU IRQ2
; ------------------------------------------------------------------------------

	xdef TriggerSubCpuIrq2
TriggerSubCpuIrq2:
	bset	#0,MCD_IRQ2					; Trigger IRQ2
	rts
	
; ------------------------------------------------------------------------------
; Hold Sub CPU reset
; ------------------------------------------------------------------------------

	xdef HoldSubCpuReset
HoldSubCpuReset:
	bclr	#0,MCD_SUB_CTRL					; Hold reset
	bne.s	HoldSubCpuReset					; If it hasn't been held, wait
	rts

; ------------------------------------------------------------------------------
; Release Sub CPU reset
; ------------------------------------------------------------------------------

	xdef ReleaseSubCpuReset
ReleaseSubCpuReset:
	bset	#0,MCD_SUB_CTRL					; Release reset
	beq.s	ReleaseSubCpuReset				; If it hasn't been released, wait
	rts

; ------------------------------------------------------------------------------
; Request access to the Sub CPU's bus
; ------------------------------------------------------------------------------

	xdef RequestSubCpuBus
RequestSubCpuBus:
	bset	#1,MCD_SUB_CTRL					; Request bus access
	beq.s	RequestSubCpuBus				; If it hasn't been given, wait
	rts

; ------------------------------------------------------------------------------
; Release the Sub CPU's bus
; ------------------------------------------------------------------------------

	xdef ReleaseSubCpuBus
ReleaseSubCpuBus:
	bclr	#1,MCD_SUB_CTRL					; Release bus
	bne.s	ReleaseSubCpuBus				; If it hasn't been released, wait
	rts

; ------------------------------------------------------------------------------
; Check if we have access to Word RAM
; ------------------------------------------------------------------------------
; PARAMETERS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRam
CheckWordRam:
	btst	#0,MCD_MEM_MODE					; Check if we have access
	rts

; ------------------------------------------------------------------------------
; Give Word RAM access to the Sub CPU
; ------------------------------------------------------------------------------

	xdef GiveWordRam
GiveWordRam:
	bset	#1,MCD_MEM_MODE					; Give Word RAM access to the Sub CPU
	beq.s	GiveWordRam					; If it hasn't been given, wait
	rts

; ------------------------------------------------------------------------------
; Wait for Word RAM access
; ------------------------------------------------------------------------------

	xdef WaitWordRam
WaitWordRam:
	btst	#0,MCD_MEM_MODE					; Do we have Word RAM access?
	beq.s	WaitWordRam					; If not, wait
	rts

; ------------------------------------------------------------------------------
; Copy data to Program RAM
; ------------------------------------------------------------------------------
; You need to have access to the Sub CPU's bus before calling this.
; ------------------------------------------------------------------------------
; PARAMETERS:
;	a0.l - Data address
;	d0.l - Data length
;	d1.l - Program RAM offset
; RETURNS:
;	d1.l - Advanced Program RAM offset
;	a0.l - End of data address
; ------------------------------------------------------------------------------

	xdef CopyPrgRamData
CopyPrgRamData:
	movem.l	d0/d2/a1,-(sp)					; Save registers	

	move.l	d1,d2						; Set Program RAM bank ID
	swap	d2
	ror.b	#3,d2
	andi.b	#$C0,d2
	andi.b	#$3F,MCD_MEM_MODE
	or.b	d2,MCD_MEM_MODE
	
	lea	PRG_RAM_BANK,a1					; Get initial copy destination
	move.l	d1,d2
	andi.l	#PRG_RAM_BANK_SIZE-1,d2
	adda.l	d2,a1
	
	add.l	d0,d1						; Advance Program RAM offset
	
.Copy:
	move.b	(a0)+,(a1)+					; Copy byte
	subq.l	#1,d0						; Decrement number of bytes left to copy
	beq.s	.Done						; If we are finished, branch
	
	cmpa.l	#PRG_RAM_BANK_END,a1				; Have we reached the end of the bank?
	bls.s	.Copy						; If not, branch

	addi.b	#1<<6,MCD_MEM_MODE				; Go to next bank
	lea	PRG_RAM_BANK,a1
	bra.s	.Copy

.Done:
	movem.l	(sp)+,d0/d2/a1					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Initialize CD drive
; ------------------------------------------------------------------------------

	xdef InitCdDrive
InitCdDrive:
	move.b	#1,-(sp)					; Initialize CD drive
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Open CD drive
; ------------------------------------------------------------------------------

	xdef OpenCdDrive
OpenCdDrive:
	move.b	#2,-(sp)					; Open CD drive
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Get CD drive status
; ------------------------------------------------------------------------------
; RETURNS:
;	d0.w - CD drive status
; ------------------------------------------------------------------------------

	xdef GetCdDriveStatus
GetCdDriveStatus:
	move.b	#3,-(sp)					; Get CD drive status
	bsr.w	SubCpuCommand2
	addq.w	#2,sp
	move.w	MCD_SUB_COMM_0,d0
	rts

; ------------------------------------------------------------------------------
; Play all CDDA tracks
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Starting track ID
; ------------------------------------------------------------------------------

	xdef PlayAllCdda
PlayAllCdda:
	move.w	d0,MCD_MAIN_COMM_0				; Play all CDDA tracks
	move.b	#4,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Play CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef PlayCdda
PlayCdda:
	move.w	d0,MCD_MAIN_COMM_0				; Play CDDA track
	move.b	#5,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Loop CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef LoopCdda
LoopCdda:
	move.w	d0,MCD_MAIN_COMM_0				; Loop CDDA track
	move.b	#6,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Play CDDA at time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.l - Timecode
; ------------------------------------------------------------------------------

	xdef PlayCddaTime
PlayCddaTime:
	move.l	d0,MCD_MAIN_COMM_0				; Play CDDA at time
	move.b	#7,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Stop CDDA
; ------------------------------------------------------------------------------

	xdef StopCdda
StopCdda:
	move.b	#8,-(sp)					; Stop CDDA
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Pause CDDA
; ------------------------------------------------------------------------------

	xdef PauseCdda
PauseCdda:
	move.b	#9,-(sp)					; Pause CDDA
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Unpause CDDA
; ------------------------------------------------------------------------------

	xdef UnpauseCdda
UnpauseCdda:
	move.b	#$A,-(sp)					; Unpause CDDA
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Seek to CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef SeekCdda
SeekCdda:
	move.w	d0,MCD_MAIN_COMM_0				; Seek to CDDA track
	move.b	#$B,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Seek to CDDA time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.l - Timecode
; ------------------------------------------------------------------------------

	xdef SeekCddaTime
SeekCddaTime:
	move.l	d0,MCD_MAIN_COMM_0				; Seek to CDDA time
	move.b	#$C,-(sp)
	bra.s	SubCpuCommand

; ------------------------------------------------------------------------------
; Start Sub CPU module
; ------------------------------------------------------------------------------

	xdef StartSubCpuModule
StartSubCpuModule:
	move.b	#$D,-(sp)					; Start module

; ------------------------------------------------------------------------------
; Send command to the Sub CPU
; ------------------------------------------------------------------------------
; PARAMETERS:
;	(sp).b - Command ID
; ------------------------------------------------------------------------------

SubCpuCommand:
	move.b	(sp)+,MCD_MAIN_FLAG				; Set command ID

WaitSubCpuCmd:
	cmpi.b	#"C",MCD_SUB_FLAG				; Has the Sub CPU acknowledged it?
	bne.s	WaitSubCpuCmd					; If not, wait
	clr.b	MCD_MAIN_FLAG					; Reset command ID

.WaitSubFinish:
	tst.b	MCD_SUB_FLAG					; Has the Sub CPU finished?
	bne.s	.WaitSubFinish					; If not, wait
	rts

; ------------------------------------------------------------------------------

SubCpuCommand2:
	move.b	4(sp),MCD_MAIN_FLAG				; Set command ID
	bra.s	WaitSubCpuCmd					; Process command

; ------------------------------------------------------------------------------
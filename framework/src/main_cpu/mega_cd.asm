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
; RETURNS:
;	eq/ne - Disabled/Enabled
; ------------------------------------------------------------------------------

	xdef CheckSubCpuIrq2
CheckSubCpuIrq2:
	btst	#7,MCD_IRQ2					; Check if IRQ2 is enabled
	rts

; ------------------------------------------------------------------------------
; Request Sub CPU IRQ2
; ------------------------------------------------------------------------------

	xdef RequestSubCpuIrq2
RequestSubCpuIrq2:
	bset	#0,MCD_IRQ2					; Request IRQ2
	rts

; ------------------------------------------------------------------------------
; Check if the Sub CPU is running
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Not running/Running
; ------------------------------------------------------------------------------

	xdef CheckSubCpuRun
CheckSubCpuRun:
	btst	#0,MCD_SUB_CTRL					; Check if the Sub CPU is running
	rts

; ------------------------------------------------------------------------------
; Check if Sub CPU reset is held
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Not held/Held
; ------------------------------------------------------------------------------

	xdef CheckSubCpuReset
CheckSubCpuReset:
	bsr.s	CheckSubCpuRun					; Check if reset is held
	eori	#4,sr
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
; Check if we have access to the Sub CPU's bus
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckSubCpuBus
CheckSubCpuBus:
	btst	#1,MCD_SUB_CTRL					; Check if we have access
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
; Check if we have access to Word RAM bank 0
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRamBank0
CheckWordRamBank0:
	bsr.s	CheckWordRamBank1				; Check if we have access
	eori	#4,sr
	rts

; ------------------------------------------------------------------------------
; Check if we have access to Word RAM or if we have access to Word RAM bank 1
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - No access/Access
; ------------------------------------------------------------------------------

	xdef CheckWordRam
	xdef CheckWordRamBank1
CheckWordRam:
CheckWordRamBank1:
	btst	#0,MCD_MEM_MODE					; Check if we have access
	rts

; ------------------------------------------------------------------------------
; Give Word RAM access to the Sub CPU
; ------------------------------------------------------------------------------

	xdef GiveWordRam
GiveWordRam:
	bset	#1,MCD_MEM_MODE					; Give access to the Sub CPU
	beq.s	GiveWordRam					; If it hasn't been given, wait
	rts

; ------------------------------------------------------------------------------
; Wait for Word RAM bank 0 access
; ------------------------------------------------------------------------------

	xdef WaitWordRamBank0
WaitWordRamBank0:
	bsr.s	CheckWordRamBank1				; Do we have access?
	bne.s	WaitWordRamBank0				; If not, wait
	rts

; ------------------------------------------------------------------------------
; Wait for Word RAM access or Word RAM bank 1 access
; ------------------------------------------------------------------------------

	xdef WaitWordRam
	xdef WaitWordRamBank1
WaitWordRam:
WaitWordRamBank1:
	bsr.s	CheckWordRam					; Do we have access?
	beq.s	WaitWordRam					; If not, wait
	rts

; ------------------------------------------------------------------------------
; Check if we are in Word RAM 1M/1M mode
; ------------------------------------------------------------------------------

	xdef CheckWordRam1M
CheckWordRam1M:
	btst	#2,MCD_MEM_MODE					; Check if we are in 1M/1M mode
	rts

; ------------------------------------------------------------------------------
; Check if we are in Word RAM 2M mode
; ------------------------------------------------------------------------------

	xdef CheckWordRam2M
CheckWordRam2M:
	bsr.s	CheckWordRam1M					; Check if we are in 2M mode
	eori	#4,sr
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

	addi.b	#$40,MCD_MEM_MODE				; Go to next bank
	lea	PRG_RAM_BANK,a1
	bra.s	.Copy

.Done:
	movem.l	(sp)+,d0/d2/a1					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Send command to the Sub CPU
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Command ID
; ------------------------------------------------------------------------------

SubCpuCommand:
	move	sr,-(sp)					; Save status register
	move	#$2700,sr					; Disable interrupts

	move.b	d0,MCD_MAIN_FLAG				; Set command ID
	bsr.w	RequestSubCpuIrq2				; Request IRQ2

.WaitSubAck:
	cmpi.b	#"C",MCD_SUB_FLAG				; Has the Sub CPU acknowledged it?
	bne.s	.WaitSubAck					; If not, wait
	clr.b	MCD_MAIN_FLAG					; Reset command ID

.WaitSubFinish:
	tst.b	MCD_SUB_FLAG					; Has the Sub CPU finished?
	bne.s	.WaitSubFinish					; If not, wait

	move	(sp)+,sr					; Restore interrupts
	rts

; ------------------------------------------------------------------------------
; Initialize CD drive
; ------------------------------------------------------------------------------

	xdef InitCdDrive
InitCdDrive:
	move.l	d0,-(sp)					; Save registers

	moveq	#1,d0						; Initialize CD drive
	bsr.s	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Open CD drive
; ------------------------------------------------------------------------------

	xdef OpenCdDrive
OpenCdDrive:
	move.l	d0,-(sp)					; Save registers

	moveq	#2,d0						; Open CD drive
	bsr.s	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Get CD drive status
; ------------------------------------------------------------------------------
; RETURNS:
;	d0.w - CD drive status
; ------------------------------------------------------------------------------

	xdef GetCdDriveStatus
GetCdDriveStatus:
	moveq	#3,d0						; Get CD drive status
	bsr.s	SubCpuCommand
	move.w	MCD_SUB_COMM_0,d0
	rts

; ------------------------------------------------------------------------------
; Check if the CD drive is ready
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Not ready/Ready
; ------------------------------------------------------------------------------

	xdef CheckCdDriveReady
CheckCdDriveReady:
	move.l	d0,-(sp)					; Save registers

	bsr.s	GetCdDriveStatus				; Get CD drive ready status
	andi.w	#$F000,d0
	eori	#4,sr

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Wait for the CD drive to be ready
; ------------------------------------------------------------------------------

	xdef WaitCdDriveReady
WaitCdDriveReady:
	move	sr,-(sp)					; Save status register
	move	#$2700,sr					; Disable interrupts

.Wait:
	bsr.s	CheckCdDriveReady				; Is the CD drive ready?
	beq.s	.Wait						; If not, wait

	move	(sp)+,sr					; Restore interrupts
	rts

; ------------------------------------------------------------------------------
; Play all CDDA tracks
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Starting track ID
; ------------------------------------------------------------------------------

	xdef PlayAllCdda
PlayAllCdda:
	move.l	d0,-(sp)					; Save registers

	move.w	d0,MCD_MAIN_COMM_0				; Play all tracks
	moveq	#4,d0
	bsr.s	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Play CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef PlayCdda
PlayCdda:
	move.l	d0,-(sp)					; Save registers

	move.w	d0,MCD_MAIN_COMM_0				; Play track
	moveq	#5,d0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Loop CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef LoopCdda
LoopCdda:
	move.l	d0,-(sp)					; Save registers

	move.w	d0,MCD_MAIN_COMM_0				; Loop track
	moveq	#6,d0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Play CDDA at time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.l - Timecode
; ------------------------------------------------------------------------------

	xdef PlayCddaTime
PlayCddaTime:
	move.l	d0,-(sp)					; Save registers

	move.l	d0,MCD_MAIN_COMM_0				; Play at time
	moveq	#7,d0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Stop CDDA
; ------------------------------------------------------------------------------

	xdef StopCdda
StopCdda:
	move.l	d0,-(sp)					; Save registers

	moveq	#8,d0						; Stop CDDA
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Pause CDDA
; ------------------------------------------------------------------------------

	xdef PauseCdda
PauseCdda:
	move.l	d0,-(sp)					; Save registers

	moveq	#9,d0						; Pause CDDA
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Unpause CDDA
; ------------------------------------------------------------------------------

	xdef UnpauseCdda
UnpauseCdda:
	move.l	d0,-(sp)					; Save registers

	moveq	#$A,d0						; Unpause CDDA
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set CDDA speed
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Speed setting
;	       0 - Normal
;	       1 - Fast forward
;	       2 - Fast reverse
; ------------------------------------------------------------------------------

	xdef SetCddaSpeed
SetCddaSpeed:
	move.l	d0,-(sp)					; Save registers

	moveq	#$B,d0						; Set speed
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Seek to CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Track ID
; ------------------------------------------------------------------------------

	xdef SeekCdda
SeekCdda:
	move.l	d0,-(sp)					; Save registers

	move.w	d0,MCD_MAIN_COMM_0				; Seek to track
	moveq	#$C,d0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Seek to CDDA time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.l - Timecode
; ------------------------------------------------------------------------------

	xdef SeekCddaTime
SeekCddaTime:
	move.l	d0,-(sp)					; Save registers

	move.l	d0,MCD_MAIN_COMM_0				; Seek to time
	moveq	#$D,d0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Swap Word RAM banks
; ------------------------------------------------------------------------------

	xdef SwapWordRamBanks
SwapWordRamBanks:
	move.l	d0,-(sp)					; Save registers

	moveq	#$E,d0						; Swap banks
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Access Word RAM bank 0
; ------------------------------------------------------------------------------

	xdef SetWordRamBank0
SetWordRamBank0:
	move.l	d0,-(sp)					; Save registers

	moveq	#$F,d0						; Access bank 0
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Access Word RAM bank 1
; ------------------------------------------------------------------------------

	xdef SetWordRamBank1
SetWordRamBank1:
	move.l	d0,-(sp)					; Save registers

	moveq	#$10,d0						; Access bank 1
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Unload Sub CPU module
; ------------------------------------------------------------------------------

	xdef UnloadSubCpuModule
UnloadSubCpuModule:
	move.l	d0,-(sp)					; Save registers
	
	move.b	#$11,d0						; Unload module
	bsr.w	SubCpuCommand

	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
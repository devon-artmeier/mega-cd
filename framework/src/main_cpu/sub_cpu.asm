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
; Trigger Sub CPU IRQ2
; ------------------------------------------------------------------------------

	xdef TrigerSubCpuIrq2
TrigerSubCpuIrq2:
	bset	#0,MCD_IRQ2					; Trigger IRQ2
	rts
	
; ------------------------------------------------------------------------------
; Hold Sub CPU reset
; ------------------------------------------------------------------------------

	xdef HoldSubCpuReset
HoldSubCpuReset:
	bclr	#0,MCD_SUB_CTRL					; Hold reset
	bne.s	HoldSubCpuReset
	rts

; ------------------------------------------------------------------------------
; Release Sub CPU reset
; ------------------------------------------------------------------------------

	xdef ReleaseSubCpuReset
ReleaseSubCpuReset:
	bset	#0,MCD_SUB_CTRL					; Release reset
	beq.s	ReleaseSubCpuReset
	rts

; ------------------------------------------------------------------------------
; Request access to the Sub CPU's bus
; ------------------------------------------------------------------------------

	xdef RequestSubCpuBus
RequestSubCpuBus:
	bset	#1,MCD_SUB_CTRL					; Request bus access
	beq.s	RequestSubCpuBus
	rts

; ------------------------------------------------------------------------------
; Release the Sub CPU's bus
; ------------------------------------------------------------------------------

	xdef ReleaseSubCpuBus
ReleaseSubCpuBus:
	bclr	#1,MCD_SUB_CTRL					; Release bus
	bne.s	ReleaseSubCpuBus
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
	andi.l	#$1FFFF,d2
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
; Send command to the Sub CPU
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Command ID
; ------------------------------------------------------------------------------

	xdef SubCpuCommand
SubCpuCommand:
	move.b	d0,MCD_MAIN_FLAG				; Set command ID

.WaitSubAck:
	cmpi.b	#"C",MCD_SUB_FLAG				; Has the Sub CPU acknowledged it?
	bne.s	.WaitSubAck					; If not, wait

	clr.b	MCD_MAIN_FLAG					; Reset command ID

.WaitSubFinish:
	tst.b	MCD_SUB_FLAG					; Has the Sub CPU finished?
	bne.s	.WaitSubFinish					; If not, wait
	rts

; ------------------------------------------------------------------------------
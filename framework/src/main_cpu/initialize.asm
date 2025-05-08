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
; Wait for the Sub CPU program to initialize
; ------------------------------------------------------------------------------

	xdef WaitSubCpuInit
WaitSubCpuInit:
	movem.l	d0/a0,-(sp)					; Save registers

	lea	MCD_MAIN_COMMS,a0				; Clear communication registers
	moveq	#0,d0
	move.b	d0,MCD_MAIN_FLAG-MCD_MAIN_COMMS(a0)
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+

.WaitSubInit:
	if USE_MCD_MODE_1<>0
		bsr.w	TriggerSubCpuIrq2			; Trigger IRQ2
		move.w	#$3000-1,d0				; Delay for a while
		dbf	d0,*
	endif

	cmpi.b	#"I",MCD_SUB_FLAG				; Has the Sub CPU initialized?
	bne.s	.WaitSubInit					; If not, wait
	move.b	#"I",MCD_MAIN_FLAG				; Mark as initialized

.WaitSubAck:
	tst.b	MCD_SUB_FLAG					; Has the Sub CPU acknowledged us?
	bne.s	.WaitSubAck					; If not, wait
	clr.b	MCD_MAIN_FLAG					; Reset command ID
	
	bsr.w	GiveWordRam					; Wait for Word RAM access

	movem.l	(sp)+,d0/a0					; Restore registers
	rts

; ------------------------------------------------------------------------------
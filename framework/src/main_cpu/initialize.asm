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
	movem.l	d0-d1/a0,-(sp)					; Save registers

	lea	MCD_MAIN_COMMS,a0				; Clear communication registers
	moveq	#0,d0
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+
	move.l	d0,(a0)+

	lea	MCD_SUB_FLAG-(MCD_MAIN_COMMS+$10)(a0),a0	; Get communication flags
	moveq	#"S",d0						; Initialization flag

.WaitSubInit:
	if USE_MCD_MODE_1<>0
		bsr.s	.RequestIrq2				; Request IRQ2
	endif
	cmp.b	(a0),d0						; Has the Sub CPU initialized?
	bne.s	.WaitSubInit					; If not, wait
	move.b	d0,MCD_MAIN_FLAG-MCD_SUB_FLAG(a0)		; Acknowledge the Sub CPU

.WaitSubAck:
	cmpi.b	#"I",(a0)					; Has the Sub CPU acknowledged us?
	bne.s	.WaitSubAck					; If not, wait

	bsr.w	GiveWordRam					; Give Word RAM access to the Sub CPU
	
	clr.b	MCD_MAIN_FLAG-MCD_SUB_FLAG(a0)			; Mark as ready for commands

.WaitSubAck2:
	if USE_MCD_MODE_1<>0
		bsr.s	.RequestIrq2				; Request IRQ2
	endif
	tst.b	(a0)						; Has the Sub CPU started?
	bne.s	.WaitSubAck2					; If not, wait
	
	movem.l	(sp)+,d0-d1/a0					; Restore registers
	rts

; ------------------------------------------------------------------------------

	if USE_MCD_MODE_1<>0
.RequestIrq2:
		move.w	#$3000-1,d1				; Request IRQ2
		dbf	d1,*
		bra.w	RequestSubCpuIrq2
	endif

; ------------------------------------------------------------------------------
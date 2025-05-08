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
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

	include	"mcd_sub.inc"

	section code

; ------------------------------------------------------------------------------

MODULE_START		equ $10000				; Module start

; ------------------------------------------------------------------------------
; Start module
; ------------------------------------------------------------------------------

	xdef INT_StartModuleCmd
INT_StartModuleCmd:
	bclr	#2,MCD_IRQ_MASK					; Disable Mega Drive interrupt

	move.l	MODULE_START,d0					; Get module initialization function
	beq.s	.SetUpdate					; If it's not set, branch
	movea.l	d0,a0						; Initialize module
	jsr	(a0)

.SetUpdate:
	move.l	MODULE_START+4,module_update.w			; Set module update function
	bset	#2,MCD_IRQ_MASK					; Enable Mega Drive interrupt
	rts

; ------------------------------------------------------------------------------
; Unload module
; ------------------------------------------------------------------------------

	xdef INT_UnloadModuleCmd
INT_UnloadModuleCmd:
	bclr	#2,MCD_IRQ_MASK					; Disable Mega Drive interrupt
	clr.l	module_update.w					; Unset module update function
	bset	#2,MCD_IRQ_MASK					; Enable Mega Drive interrupt
	rts

; ------------------------------------------------------------------------------
; Update module
; ------------------------------------------------------------------------------

	xdef INT_UpdateModule
INT_UpdateModule:
	move.l	module_update.w,d0				; Get module update function
	beq.s	.End						; If it's not set, branch
	movea.l	d0,a0						; Update module
	jmp	(a0)

.End:
	rts

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------

	section bss

module_update		ds.l 1					; Module update

; ------------------------------------------------------------------------------
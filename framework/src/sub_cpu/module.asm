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

	xdef MODULE_ENTRY
MODULE_ENTRY		equ $10000				; Module start

; ------------------------------------------------------------------------------
; Run module
; ------------------------------------------------------------------------------

	xdef RunModule
RunModule:
	tst.b	run_module					; Should we run the module?
	beq.s	.End						; If not, branch
	clr.b	run_module					; Mark module as run

	jmp	MODULE_ENTRY					; Run module

.End:
	rts

; ------------------------------------------------------------------------------
; Set to run module
; ------------------------------------------------------------------------------

	xdef SetModuleRun
	xdef XREF_SetModuleRunCmd

SetModuleRun:
XREF_SetModuleRunCmd:
	st.b	run_module					; Set to run module
	rts

; ------------------------------------------------------------------------------
; Unload module
; ------------------------------------------------------------------------------

	xdef UnloadModule
	xdef XREF_UnloadModuleCmd
UnloadModule:
XREF_UnloadModuleCmd:
	move.w	#$4E75,MODULE_ENTRY				; Unset module update function
	rts

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------
	
run_module:
	dc.b 0							; Run module flag
	even

; ------------------------------------------------------------------------------
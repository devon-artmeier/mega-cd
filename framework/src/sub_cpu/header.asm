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
	
	section header

; ------------------------------------------------------------------------------
; Module header
; ------------------------------------------------------------------------------

ModuleHeader:
	dc.b	"MAIN       ", 0				; Name and flag
	dc.w	$100						; Version
	dc.w	0						; Type
	dc.l	0						; Link module
	dc.l	0						; Module size
	dc.l	ModuleStart-ModuleHeader			; Start address
	dc.l	0						; Work RAM size

; ------------------------------------------------------------------------------
; Module offsets
; ------------------------------------------------------------------------------

ModuleStart:
	dc.l	INT_Initialize-ModuleStart			; Initialization
	dc.l	INT_Main-ModuleStart				; Main
	dc.l	INT_MegaDriveIrq-ModuleStart			; Mega Drive interrupt
	dc.l	INT_UserCall3-ModuleStart			; User call 3
	dc.w	0

; ------------------------------------------------------------------------------
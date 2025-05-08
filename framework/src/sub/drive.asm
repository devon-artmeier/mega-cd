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
; Initialize CD drive
; ------------------------------------------------------------------------------

	xdef INT_InitCdDriveCmd
INT_InitCdDriveCmd:
	lea	bios_params.w,a0				; Initialize CD drive
	move.w	#(1<<8)|$FF,(a0)
	moveq	#DRVINIT,d0
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Open CD drive
; ------------------------------------------------------------------------------

	xdef INT_OpenCdDriveCmd
INT_OpenCdDriveCmd:
	moveq	#DRVOPEN,d0					; Open CD drive
	jmp	_CDBIOS

; ------------------------------------------------------------------------------
; Get CD drive status
; ------------------------------------------------------------------------------
; RETURNS:
;	$00.w - CD drive status
; ------------------------------------------------------------------------------

	xdef INT_GetCdDriveStatusCmd
INT_GetCdDriveStatusCmd:
	move.w	#CDBSTAT,d0					; Get CD drive status
	jsr	_CDBIOS
	move.w	(a0),MCD_SUB_COMM_0
	rts

; ------------------------------------------------------------------------------
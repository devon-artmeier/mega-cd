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

	xdef InitCdDrive
	xdef XREF_InitCdDriveCmd
InitCdDrive:
XREF_InitCdDriveCmd:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	lea	XREF_bios_params.w,a0				; Initialize CD drive
	move.w	#(1<<8)|$FF,(a0)
	moveq	#DRVINIT,d0
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Open CD drive
; ------------------------------------------------------------------------------

	xdef OpenCdDrive
	xdef XREF_OpenCdDriveCmd
OpenCdDrive:
XREF_OpenCdDriveCmd:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	moveq	#DRVOPEN,d0					; Open CD drive
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Get CD drive status
; ------------------------------------------------------------------------------
; RETURNS:
;	Comm 14.w - CD drive status
; ------------------------------------------------------------------------------

	xdef GetCdDriveStatus
GetCdDriveStatus:
	movem.l d0-d1/a0-a1,-(sp)				; Save registers
	
	move.w	#CDBSTAT,d0					; Get status
	jsr	_CDBIOS
	move.w	(a0),MCD_SUB_COMM_14
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers

.End:
	rts

; ------------------------------------------------------------------------------
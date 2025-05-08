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
	xdef INT_InitCdDriveCmd
InitCdDrive:
INT_InitCdDriveCmd:
	move.w	#(1<<8)|$FF,d0					; Initialize CD drive
	move.w	#DRVINIT,-(sp)
	bra.w	BasicBiosFunctionW

; ------------------------------------------------------------------------------
; Open CD drive
; ------------------------------------------------------------------------------

	xdef OpenCdDrive
	xdef INT_OpenCdDriveCmd
OpenCdDrive:
INT_OpenCdDriveCmd:
	move.w	#DRVOPEN,-(sp)					; Open CD drive
	bra.w	BasicBiosFunction

; ------------------------------------------------------------------------------
; Get CD drive status
; ------------------------------------------------------------------------------
; RETURNS:
;	d0.w - CD drive status
; ------------------------------------------------------------------------------

	xdef INT_GetCdDriveStatusCmd
INT_GetCdDriveStatusCmd:
	bsr.s	GetCdDriveStatus				; Get CD drive status
	move.w	d0,MCD_SUB_COMM_0
	rts

; ------------------------------------------------------------------------------

	xdef GetCdDriveStatus
GetCdDriveStatus:
	movem.l d1/a0-a1,-(sp)					; Save registers

	move.w	#CDBSTAT,d0					; Get CD drive status
	jsr	_CDBIOS
	move.w	(a0),d0
	
	movem.l	(sp)+,d1/a0-a1					; Restore registers
	rts

; ------------------------------------------------------------------------------
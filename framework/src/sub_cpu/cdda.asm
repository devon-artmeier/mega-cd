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
; Play all CDDA tracks
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.w - Starting track ID
; ------------------------------------------------------------------------------

	xdef XREF_PlayAllCddaCmd
XREF_PlayAllCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef PlayAllCdda
PlayAllCdda:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Play all CDDA tracks
	move.w	d0,(a0)
	moveq	#MSCPLAY,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Play CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.w - Track ID
; ------------------------------------------------------------------------------

	xdef XREF_PlayCddaCmd
XREF_PlayCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef PlayCdda
PlayCdda:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Play CDDA track
	move.w	d0,(a0)
	moveq	#MSCPLAY1,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Loop CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.w - Track ID
; ------------------------------------------------------------------------------

	xdef XREF_LoopCddaCmd
XREF_LoopCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef LoopCdda
LoopCdda:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Loop CDDA track
	move.w	d0,(a0)
	moveq	#MSCPLAYR,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Play CDDA at time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.l - Timecode
; ------------------------------------------------------------------------------

	xdef XREF_PlayCddaTimeCmd
XREF_PlayCddaTimeCmd:
	move.l	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef PlayCddaTime
PlayCddaTime:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Play CDDA at time
	move.l	d0,(a0)
	moveq	#MSCPLAYT,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Stop CDDA
; ------------------------------------------------------------------------------

	xdef StopCdda
	xdef XREF_StopCddaCmd
StopCdda:
XREF_StopCddaCmd:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	moveq	#MSCSTOP,d0					; Stop CDDA
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Pause CDDA
; ------------------------------------------------------------------------------

	xdef PauseCdda
	xdef XREF_PauseCddaCmd
PauseCdda:
XREF_PauseCddaCmd:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	moveq	#MSCPAUSEON,d0					; Pause CDDA
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Unpause CDDA
; ------------------------------------------------------------------------------

	xdef UnpauseCdda
	xdef XREF_UnpauseCddaCmd
UnpauseCdda:
XREF_UnpauseCddaCmd:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	moveq	#MSCPAUSEOFF,d0					; Unpause CDDA
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set CDDA speed
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.w - Speed setting
;	              0 - Normal
;	              1 - Fast forward
;	              2 - Fast reverse
; ------------------------------------------------------------------------------

	xdef XREF_SetCddaSpeedCmd
XREF_SetCddaSpeedCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get speed setting

; ------------------------------------------------------------------------------

	xdef SetCddaSpeed
SetCddaSpeed:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers

	add.w	d0,d0						; Set CDDA speed
	move.w	.FunctionIds(pc,d0.w),d0
	jsr	_CDBIOS

	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------

.FunctionIds:
	dc.w	MSCSCANOFF, MSCSCANFF, MSCSCANFR

; ------------------------------------------------------------------------------
; Seek to CDDA track
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.w - Track ID
; ------------------------------------------------------------------------------

	xdef XREF_SeekCddaCmd
XREF_SeekCddaCmd:
	move.w	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef SeekCdda
SeekCdda:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Seek to CDDA track
	move.w	d0,(a0)
	moveq	#MSCSEEK,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Seek to CDDA time
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0/Comm 0.l - Timecode
; ------------------------------------------------------------------------------

	xdef XREF_SeekCddaTimeCmd
XREF_SeekCddaTimeCmd:
	move.l	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef SeekCddaTime
SeekCddaTime:
	movem.l	d0-d1/a0-a1,-(sp)				; Save registers
	
	lea	XREF_bios_params.w,a0				; Seek to CDDA time
	move.l	d0,(a0)
	moveq	#MSCSEEKT,d0
	jsr	_CDBIOS
	
	movem.l	(sp)+,d0-d1/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
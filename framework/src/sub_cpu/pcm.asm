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
; Delay a bit to let the PCM chip process
; ------------------------------------------------------------------------------
; PARAMETERS:
;	\1 - Data register
; ------------------------------------------------------------------------------

pcmDelay macro
	moveq	#$20-1,\1
	dbf	\1,*
	endm

; ------------------------------------------------------------------------------
; Initialize PCM
; ------------------------------------------------------------------------------

	xdef InitPcm
	xdef XREF_InitPcmCmd
InitPcm:
XREF_InitPcmCmd:
	movem.l	d0-d4/a0-a2,-(sp)				; Save registers

	lea	PCM_REGS,a0					; Registers
	moveq	#0,d0						; Zero
	moveq	#$FFFFFFFF,d1					; All bits

; ------------------------------------------------------------------------------

	moveq	#$FFFFFF80,d2					; Initial Wave RAM bank
	moveq	#16-1,d3					; Number of banks

.BankLoop:
	move.b	d2,PCM_CTRL-PCM_REGS(a0)			; Select bank

	lea	WAVE_RAM_BANK,a1				; Fill wave bank with loop flags
	move.w	#WAVE_RAM_BANK_SIZE-1,d4

.FillBank:
	move.b	d1,(a1)+
	addq.w	#1,a1
	dbf	d4,.FillBank

	addq.b	#1,d2						; Next bank
	dbf	d3,.BankLoop					; Loop until all banks are filled

; ------------------------------------------------------------------------------

	lea	pcm_volumes.w,a1				; Volumes
	lea	pcm_frequencies.w,a2				; Frequencies

	moveq	#$FFFFFFC0,d2					; Initial channel selection
	moveq	#8-1,d3						; Number of channels

.InitChannels:
	move.b	d2,PCM_CTRL-PCM_REGS(a0)			; Select channel

	move.b	d0,(a1)+					; Mute channel
	move.b	d0,PCM_VOLUME-PCM_REGS(a0)
	
	move.b	d1,PCM_PAN-PCM_REGS(a0)				; Set panning

	move.w	d0,(a2)+					; Reset frequency
	move.b	d0,PCM_FREQ_L-PCM_REGS(a0)
	move.b	d0,PCM_FREQ_H-PCM_REGS(a0)

	move.b	d0,PCM_LOOP_L-PCM_REGS(a0)			; Reset loop address
	move.b	d0,PCM_LOOP_H-PCM_REGS(a0)
	
	move.b	d0,PCM_START-PCM_REGS(a0)			; Reset start address

	addq.b	#1,d2						; Next channel
	dbf	d3,.InitChannels				; Loop until all channels are set up

	move.b	d1,PCM_ENABLE-PCM_REGS(a0)			; Disable PCM channels
	move.b	d1,pcm_on_off.w

; ------------------------------------------------------------------------------

	movem.l	(sp)+,d0-d4/a0-a2				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set PCM channel volume
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID
;	d1.b - Volume
; ------------------------------------------------------------------------------

	xdef XREF_SetPcmVolumeCmd
XREF_SetPcmVolumeCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters
	move.b	MCD_MAIN_COMM_1,d1

; ------------------------------------------------------------------------------

	xdef SetPcmVolume
SetPcmVolume:
	movem.l	d0/a0,-(sp)					; Save registers
	
	ori.b	#$C0,d0						; Set channel
	move.b	d0,PCM_CTRL
	
	lea	pcm_volumes.w,a0				; Set volume
	andi.w	#7,d0
	move.b	d1,(a0,d0.w)
	move.b	d1,PCM_VOLUME
	pcmDelay d0
	
	movem.l	(sp)+,d0/a0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set PCM channel panning
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID
;	d1.b - Panning
; ------------------------------------------------------------------------------

	xdef XREF_SetPcmPanningCmd
XREF_SetPcmPanningCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters
	move.b	MCD_MAIN_COMM_1,d1

; ------------------------------------------------------------------------------

	xdef SetPcmPanning
SetPcmPanning:
	move.l	d0,-(sp)					; Save registers
	
	ori.b	#$C0,d0						; Set channel
	move.b	d0,PCM_CTRL

	move.b	d1,PCM_PAN					; Set panning
	pcmDelay d0
	
	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set PCM channel frequency
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID
;	d1.w - Frequency
; ------------------------------------------------------------------------------

	xdef XREF_SetPcmFrequencyCmd
XREF_SetPcmFrequencyCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters
	move.w	MCD_MAIN_COMM_2,d1

; ------------------------------------------------------------------------------

	xdef SetPcmFrequency
SetPcmFrequency:
	movem.l	d0/a0,-(sp)					; Save registers
	
	ori.b	#$C0,d0						; Set channel
	move.b	d0,PCM_CTRL

	lea	pcm_frequencies.w,a0				; Set frequency
	andi.w	#7,d0
	add.w	d0,d0
	move.w	d1,(a0,d0.w)
	move.b	d1,PCM_FREQ_L
	move.w	d1,-(sp)
	move.b	(sp)+,PCM_FREQ_H
	pcmDelay d0
	
	movem.l	(sp)+,d0/a0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set PCM channel Wave RAM start address
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID
;	d1.b - Start address
; ------------------------------------------------------------------------------

	xdef XREF_SetPcmWaveStartCmd
XREF_SetPcmWaveStartCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters
	move.b	MCD_MAIN_COMM_1,d1

; ------------------------------------------------------------------------------

	xdef SetPcmWaveStart
SetPcmWaveStart:
	move.l	d0,-(sp)					; Save registers
	
	ori.b	#$C0,d0						; Set channel
	move.b	d0,PCM_CTRL

	move.b	d1,PCM_START					; Set start address
	pcmDelay d0
	
	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Set PCM channel Wave RAM loop address
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID
;	d1.w - Loop address
; ------------------------------------------------------------------------------

	xdef XREF_SetPcmWaveLoopCmd
XREF_SetPcmWaveLoopCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters
	move.w	MCD_MAIN_COMM_2,d1

; ------------------------------------------------------------------------------

	xdef SetPcmWaveLoop
SetPcmWaveLoop:
	move.l	d0,-(sp)					; Save registers
	
	ori.b	#$C0,d0						; Set channel
	move.b	d0,PCM_CTRL
	
	move.b	d1,PCM_LOOP_L					; Set loop address
	move.w	d1,-(sp)
	move.b	(sp)+,PCM_LOOP_H
	pcmDelay d0
	
	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Play PCM channels
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID bit array
; ------------------------------------------------------------------------------

	xdef XREF_PlayPcmCmd
XREF_PlayPcmCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef PlayPcm
PlayPcm:
	movem.l	d0-d1,-(sp)					; Save registers
	
	or.b	d0,pcm_on_off.w					; Stop channels
	move.b	pcm_on_off.w,PCM_ENABLE
	pcmDelay d1
	
	not.b	d0						; Play channels
	and.b	d0,pcm_on_off.w
	pcmDelay d1
	
	movem.l	(sp)+,d0-d1					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Stop PCM channels
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID bit array
; ------------------------------------------------------------------------------

	xdef XREF_StopPcmCmd
XREF_StopPcmCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef StopPcm
StopPcm:
	move.l	d0,-(sp)					; Save registers
	
	or.b	d0,pcm_on_off.w					; Stop channels
	move.b	pcm_on_off.w,PCM_ENABLE
	pcmDelay d0
	
	move.l	(sp)+,d0					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Pause PCM channels
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID bit array
; ------------------------------------------------------------------------------

	xdef XREF_PausePcmCmd
XREF_PausePcmCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef PausePcm
PausePcm:
	movem.l	d0-d4,-(sp)					; Save registers
	
	moveq	#$FFFFFFC0,d1					; Initial channel selection
	moveq	#8-1,d2						; Number of channels
	moveq	#0,d3						; Zero
	
.PauseLoop:
	lsr.b	#1,d0						; Is this channel selected?
	bcc.s	.NextChannel					; If not, branch	

	move.b	d1,PCM_CTRL					; Set channel
	
	move.b	d3,PCM_VOLUME					; Pause channel
	move.b	d3,PCM_FREQ_L
	move.b	d3,PCM_FREQ_H
	pcmDelay d4

.NextChannel:
	addq.b	#1,d1						; Next channel
	dbf	d2,.PauseLoop					; Loop until finished

	movem.l	(sp)+,d0-d4					; Restore registers
	rts

; ------------------------------------------------------------------------------
; Unpause PCM channels
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.b - Channel ID bit array
; ------------------------------------------------------------------------------

	xdef XREF_UnpausePcmCmd
XREF_UnpausePcmCmd:
	move.b	MCD_MAIN_COMM_0,d0				; Get parameters

; ------------------------------------------------------------------------------

	xdef UnpausePcm
UnpausePcm:
	movem.l	d0-d3/a0-a1,-(sp)				; Save registers
	
	moveq	#$FFFFFFC0,d1					; Initial channel selection
	moveq	#8-1,d2						; Number of channels
	
	lea	pcm_volumes.w,a0				; Volumes
	lea	pcm_frequencies.w,a1				; Frequencies
	
.UnpauseLoop:
	lsr.b	#1,d0						; Is this channel selected?
	bcc.s	.NextChannel					; If not, branch	

	move.b	d1,PCM_CTRL					; Set channel
	
	move.b	(a0),PCM_VOLUME					; Restore volume

	move.b	1(a1),PCM_FREQ_L				; Restore frequency
	move.b	(a1),PCM_FREQ_H
	pcmDelay d3

.NextChannel:
	addq.b	#1,d1						; Next channel
	addq.w	#1,a0
	addq.w	#2,a1
	dbf	d2,.UnpauseLoop					; Loop until finished

	movem.l	(sp)+,d0-d3/a0-a1				; Restore registers
	rts

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------

pcm_on_off:
	dc.b	%11111111					; Channel on/off array
	even
pcm_volumes:
	dcb.b	8, 0						; Volumes
pcm_frequencies:
	dcb.w	8, 0						; Frequencies

; ------------------------------------------------------------------------------
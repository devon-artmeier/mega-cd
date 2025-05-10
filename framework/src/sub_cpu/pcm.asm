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
; Initialize PCM
; ------------------------------------------------------------------------------

	xdef InitPcm
InitPcm:
	rts
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

	moveq	#$FFFFFFC0,d2					; Initial PCM channel
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
; Set channel ID (fast)
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef SetPcmChannelFast
SetPcmChannelFast:
	move.w	d0,-(sp)					; Set channel
	ori.b	#$C0,d0
	move.b	d0,PCM_CTRL
	move.w	(sp)+,d0
	rts

; ------------------------------------------------------------------------------
; Set channel ID
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef SetPcmChannel
SetPcmChannel:
	bsr.s	SetPcmChannelFast				; Set channel

; ------------------------------------------------------------------------------
; Handle PCM register delay
; ------------------------------------------------------------------------------

	xdef PcmDelay
PcmDelay:
	move.w	d0,-(sp)					; Delay for a bit
	move.w	#$80-1,d0
	dbf	d0,*
	move.w	(sp)+,d0
	rts

; ------------------------------------------------------------------------------
; Set PCM channel volume
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
;	d1.b - Volume
; ------------------------------------------------------------------------------

	xdef SetPcmVolume
SetPcmVolume:
	bsr.s	SetPcmChannelFast				; Set channel
	
	move.l	a0,-(sp)					; Save volume
	lea	pcm_volumes.w,a0
	move.b	d1,(a0,d0.w)
	move.l	(sp)+,a0
	
	move.b	d1,PCM_VOLUME					; Set volume
	bra.s	PcmDelay

; ------------------------------------------------------------------------------
; Set PCM channel panning
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
;	d1.b - Panning
; ------------------------------------------------------------------------------

	xdef SetPcmPanning
SetPcmPanning:
	bsr.s	SetPcmChannelFast				; Set channel

	move.b	d1,PCM_PAN					; Set panning
	bra.s	PcmDelay

; ------------------------------------------------------------------------------
; Set PCM channel frequency
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
;	d1.w - Frequency
; ------------------------------------------------------------------------------

	xdef SetPcmFrequency
SetPcmFrequency:
	bsr.s	SetPcmChannelFast				; Set channel

	movem.l	d0/a0,-(sp)					; Save frequency
	lea	pcm_frequencies.w,a0
	add.w	d0,d0
	move.w	d1,(a0,d0.w)
	movem.l	(sp)+,d0/a0
	
	move.b	d1,PCM_FREQ_L					; Set frequency
	move.w	d1,-(sp)
	move.b	(sp)+,PCM_FREQ_H
	bra.s	PcmDelay

; ------------------------------------------------------------------------------
; Set PCM Wave RAM start address
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
;	d1.b - Start address
; ------------------------------------------------------------------------------

	xdef SetPcmWaveStart
SetPcmWaveStart:
	bsr.s	SetPcmChannelFast				; Set channel

	move.b	d1,PCM_START					; Set start address
	bra.s	PcmDelay

; ------------------------------------------------------------------------------
; Set PCM Wave RAM loop address
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
;	d1.b - Start address
; ------------------------------------------------------------------------------

	xdef SetPcmWaveLoop
SetPcmWaveLoop:
	bsr.s	SetPcmChannelFast				; Set channel
	
	move.b	d1,PCM_LOOP_L					; Set loop address
	move.w	d1,-(sp)
	move.b	(sp)+,PCM_LOOP_H
	bra.s	PcmDelay

; ------------------------------------------------------------------------------
; Play PCM channel
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef PlayPcm
PlayPcm:
	bsr.s	StopPcm						; Stop channel

	bclr	d0,pcm_on_off					; Play channel
	move.b	pcm_on_off.w,PCM_ENABLE
	bra.w	PcmDelay

; ------------------------------------------------------------------------------
; Stop PCM channel
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef StopPcm
StopPcm:
	bsr.w	SetPcmChannelFast				; Set channel

	bset	d0,pcm_on_off.w					; Stop channel
	move.b	pcm_on_off.w,PCM_ENABLE
	bra.w	PcmDelay

; ------------------------------------------------------------------------------
; Stop all PCM channels
; ------------------------------------------------------------------------------

	xdef StopAllPcm
StopAllPcm:
	st	pcm_on_off.w					; Stop all channels
	move.b	pcm_on_off.w,PCM_ENABLE
	bra.w	PcmDelay

; ------------------------------------------------------------------------------
; Pause PCM channel
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef PausePcm
PausePcm:
	bsr.w	SetPcmChannelFast				; Set channel

	move.l	d0,-(sp)					; Pause channel
	moveq	#0,d0
	move.b	d0,PCM_VOLUME
	move.b	d0,PCM_FREQ_L
	move.b	d0,PCM_FREQ_H
	move.l	(sp)+,d0
	bra.w	PcmDelay

; ------------------------------------------------------------------------------
; Unpause PCM channel
; ------------------------------------------------------------------------------
; PARAMETERS:
;	d0.w - Channel ID
; ------------------------------------------------------------------------------

	xdef UnpausePcm
UnpausePcm:
	bsr.w	SetPcmChannelFast				; Set channel

	lea	pcm_volumes.w,a0				; Restore volume
	move.b	(a0,d0.w),PCM_VOLUME
	bsr.w	PcmDelay

	movem.l	d0/a0,-(sp)					; Restore frequency
	lea	pcm_frequencies.w,a0
	add.w	d0,d0
	move.b	1(a0,d0.w),PCM_FREQ_L
	move.b	(a0,d0.w),PCM_FREQ_H
	movem.l	(sp)+,d0/a0
	bra.w	PcmDelay

; ------------------------------------------------------------------------------
; Variables
; ------------------------------------------------------------------------------

	section bss

pcm_on_off		ds.b 1					; Channel on/off array
			ds.b 1
pcm_volumes		ds.b 8					; Volumes
pcm_frequencies		ds.w 8					; Frequencies

; ------------------------------------------------------------------------------
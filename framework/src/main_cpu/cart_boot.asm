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

	if USE_MCD_MODE_1<>0

; ------------------------------------------------------------------------------
; Initialize the Sub CPU
; ------------------------------------------------------------------------------
; PARAMETERS:
;	a0.l  - Sub CPU program address
;	d0.l  - Sub CPU program size
; RETURNS:
;	eq/ne - Success/Failure
; ------------------------------------------------------------------------------

	xdef InitSubCpu
InitSubCpu:
	movem.l	d0-d1/a0-a2,-(sp)				; Save registers

	bsr.w	FindBios					; Find BIOS
	bne.s	.Fail						; If no BIOS was found, branch

	lea	MCD_MAIN_COMMS,a2				; Clear communication registers
	moveq	#0,d1
	move.b	d1,MCD_MAIN_FLAG-MCD_MAIN_COMMS(a2)
	move.l	d1,(a2)+
	move.l	d1,(a2)+
	move.l	d1,(a2)+
	move.l	d1,(a2)+

	lea	MCD_SUB_CTRL-MCD_SUB_COMMS(a2),a2		; Reset sequence
	move.w	#$FF00,1(a2)
	move.b	#3,(a2)
	move.b	#2,(a2)
	move.b	d1,(a2)

	moveq	#$80-1,d1					; Wait for a bit to process
	dbf	d1,*

	bsr.w	HoldSubCpuReset					; Hold Sub CPU reset
	bsr.w	RequestSubCpuBus				; Request Sub CPU bus access
	
	move.b	#0,MCD_PROTECT					; Disable write protection
	
	lea	PRG_RAM_BANK,a2					; Decompress Sub CPU BIOS
	jsr	DecompKosinski
	
	move.l	#$6000,d1					; Load Sub CPU program
	bsr.w	CopyPrgRamData
	
	move.b	#$5400/$200,MCD_PROTECT				; Enable write protection	

	bsr.w	ReleaseSubCpuReset				; Release Sub CPU reset
	bsr.w	ReleaseSubCpuBus				; Release Sub CPU bus

	movem.l (sp)+,d0-d1/a0-a2				; Success
	ori	#4,ccr
	rts

.Fail:
	movem.l (sp)+,d0-d1/a0-a2				; Failure
	andi	#~4,ccr
	rts

; ------------------------------------------------------------------------------
; Check if there's a BIOS available
; ------------------------------------------------------------------------------
; RETURNS:
;	eq/ne - Found/Not found
;	a1.l  - Pointer to compressed Sub CPU BIOS, if found
; ------------------------------------------------------------------------------

FindBios:
	movem.l	d0/a2-a4,-(sp)					; Save registers
	
	lea	BIOS+$100,a2					; Get BIOS header
	cmpi.l	#"SEGA",(a2)					; Is the "SEGA" signature present?
	bne.s	.NotFound					; If not, branch
	cmpi.w	#"BR",$80(a2)					; Is the "Boot ROM" software type present?
	bne.s	.NotFound					; If not, branch
	
	lea	.Signatures(pc),a2				; Get known signature location list

.FindLoop:
	moveq	#0,d0						; Get next index of signature to check
	move.w	(a2)+,d0
	beq.s	.NotFound					; If we are at the end of the list, branch
	
	add.l	a2,d0						; Get pointer to signature data to check
	movea.l	d0,a3
	
	movea.l	(a3)+,a1					; Get pointer to Sub CPU BIOS
	movea.l	(a3)+,a4					; Get pointer to signature

.CheckSignature:
	move.b	(a3)+,d0					; Get character
	beq.s	.End						; If we are done checking, branch
	cmp.b	(a4)+,d0					; Does the signature match so far?
	bne.s	.FindLoop					; If not, check the next BIOS
	bra.s	.CheckSignature					; Loop until signature is fully checked

.NotFound:
	andi	#~4,ccr						; BIOS not found

.End:
	movem.l	(sp)+,d0/a2-a4					; Restore registers
	rts

; ------------------------------------------------------------------------------

.Signatures:
	dc.w	.Sega15800-*+2
	dc.w	.Sega16000-*+2
	dc.w	.Sega1AD00-*+2
	dc.w	.Wonder16000-*+2
	dc.w	0
	
.Sega15800:
	dc.l	BIOS+$15800
	dc.l	BIOS+$1586D
	dc.b	"SEGA", 0
	even
	
.Sega16000:
	dc.l	BIOS+$16000
	dc.l	BIOS+$1606D
	dc.b	"SEGA", 0
	even
	
.Sega1AD00:
	dc.l	BIOS+$1AD00
	dc.l	BIOS+$1AD6D
	dc.b	"SEGA", 0
	even
	
.Wonder16000:
	dc.l	BIOS+$16000
	dc.l	BIOS+$1606D
	dc.b	"WONDER", 0
	even

; ------------------------------------------------------------------------------
; Decompress Kosinski data
; Format details: https://segaretro.org/Kosinski_compression
; ------------------------------------------------------------------------------
; PARAMETERS:
;	a1.l - Pointer to source data
;	a2.l - Pointer to destination buffer
; ------------------------------------------------------------------------------
; RETURNS:
;	a1.l - Pointer to end of source data
;	a2.l - Pointer to end of destination buffer
; ------------------------------------------------------------------------------

DecompKosinski:
	movem.l	d0-d3/a3,-(sp)					; Save registers
	
	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

; ------------------------------------------------------------------------------

GetKosCode:
	lsr.w	#1,d1						; Get code
	bcc.s	KosCode0x					; If it's 0, branch

; ------------------------------------------------------------------------------

KosCode1:
	dbf	d0,.NoNewDesc					; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.NoNewDesc:
	move.b	(a1)+,(a2)+					; Copy uncompressed byte
	bra.s	GetKosCode					; Process next code

; ------------------------------------------------------------------------------

KosCode0x:
	dbf	d0,.NoNewDesc					; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.NoNewDesc:
	moveq	#$FFFFFFFF,d2					; Copy offsets are always negative
	moveq	#0,d3						; Reset copy counter

	lsr.w	#1,d1						; Get 2nd code bit
	bcs.s	KosCode01					; If the full code is 01, branch

; ------------------------------------------------------------------------------

KosCode00:
	dbf	d0,.GetCopyLength1				; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.GetCopyLength1:
	lsr.w	#1,d1						; Get number of bytes to copy (first bit)
	addx.w	d3,d3
	dbf	d0,.GetCopyLength2				; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.GetCopyLength2:
	lsr.w	#1,d1						; Get number of bytes to copy (second bit)
	addx.w	d3,d3
	dbf	d0,.GetCopyOffset				; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.GetCopyOffset:
	move.b	(a1)+,d2					; Get copy offset

; ------------------------------------------------------------------------------

KosDecCopy:
	lea	(a2,d2.w),a3					; Get copy address
	move.b	(a3)+,(a2)+					; Copy a byte

.Copy:
	move.b	(a3)+,(a2)+					; Copy a byte
	dbf	d3,.Copy					; Loop until bytes are copied

	bra.w	GetKosCode					; Process next code

; ------------------------------------------------------------------------------

KosCode01:
	dbf	d0,.NoNewDesc					; Decrement bits left to process

	move.b	(a1)+,-(sp)					; Read from data stream
	move.b	(a1)+,-(sp)
	move.w	(sp)+,d1
	move.b	(sp)+,d1
	moveq	#16-1,d0					; 16 bits to process

.NoNewDesc:
	move.b	(a1)+,-(sp)					; Get copy offset
	move.b	(a1)+,d2
	move.b	d2,d3
	lsl.w	#5,d2
	move.b	(sp)+,d2

	andi.w	#7,d3						; Get 3-bit copy count
	bne.s	KosDecCopy					; If this is a 3-bit copy count, branch

	move.b	(a1)+,d3					; Get 8-bit copy count
	beq.s	.End						; If it's 0, we are done decompressing
	subq.b	#1,d3						; Is it 1?
	bne.s	KosDecCopy					; If not, start copying
	
	bra.w	GetKosCode					; Process next code

.End:
	movem.l	(sp)+,d0-d3/a3					; Restore registers
	rts

; ------------------------------------------------------------------------------

	endif

; ------------------------------------------------------------------------------
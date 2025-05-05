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

	include	"mcd_common.inc"

; ------------------------------------------------------------------------------
; Cartridge
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
CARTRIDGE		equ 0					; Cartridge start
	elseif CONFIG_MCD_MODE=USE_MCD_MODE_2
CARTRIDGE		equ $400000				; Cartridge start
	endif
CARTRIDGE_END		equ CARTRIDGE+CARTRIDGE_SIZE-1		; Cartridge end

; ------------------------------------------------------------------------------
; SRAM (mode 1)
; ------------------------------------------------------------------------------

	if (CONFIG_MCD_MODE=USE_MCD_MODE_1)&(CONFIG_SRAM<>NO_SRAM)
SRAM			equ CARTRIDGE+$200001			; SRAM start
SRAM_END		equ SRAM+((SRAM_SIZE-1)*2)		; SRAM end

SRAM_CTRL		equ $A130F1				; SRAM control
	endif
	
; ------------------------------------------------------------------------------
; Mapper (mode 1)
; ------------------------------------------------------------------------------

	if (CONFIG_MCD_MODE=USE_MCD_MODE_1)&(CONFIG_MAPPER=USE_MAPPER)
MAPPER_REGS		equ $A130F3				; Mapper registers
MAPPER_BANK_1		equ MAPPER_REGS				; Mapper bank 1
MAPPER_BANK_2		equ MAPPER_REGS+2			; Mapper bank 2
MAPPER_BANK_3		equ MAPPER_REGS+4			; Mapper bank 3
MAPPER_BANK_4		equ MAPPER_REGS+6			; Mapper bank 4
MAPPER_BANK_5		equ MAPPER_REGS+8			; Mapper bank 5
MAPPER_BANK_6		equ MAPPER_REGS+$A			; Mapper bank 6
MAPPER_BANK_7		equ MAPPER_REGS+$C			; Mapper bank 7

CART_BANK_0		equ CARTRIDGE+(0*CART_BANK_SIZE)	; Cartridge bank 0
CART_BANK_0_END		equ CART_BANK_0+CART_BANK_SIZE-1	; Cartridge bank 0 end
CART_BANK_1		equ CARTRIDGE+(1*CART_BANK_SIZE)	; Cartridge bank 1
CART_BANK_1_END		equ CART_BANK_1+CART_BANK_SIZE-1	; Cartridge bank 1 end
CART_BANK_2		equ CARTRIDGE+(2*CART_BANK_SIZE)	; Cartridge bank 2
CART_BANK_2_END		equ CART_BANK_2+CART_BANK_SIZE-1	; Cartridge bank 2 end
CART_BANK_3		equ CARTRIDGE+(3*CART_BANK_SIZE)	; Cartridge bank 3
CART_BANK_3_END		equ CART_BANK_3+CART_BANK_SIZE-1	; Cartridge bank 3 end
CART_BANK_4		equ CARTRIDGE+(4*CART_BANK_SIZE)	; Cartridge bank 4
CART_BANK_4_END		equ CART_BANK_4+CART_BANK_SIZE-1	; Cartridge bank 4 end
CART_BANK_5		equ CARTRIDGE+(5*CART_BANK_SIZE)	; Cartridge bank 5
CART_BANK_5_END		equ CART_BANK_5+CART_BANK_SIZE-1	; Cartridge bank 5 end
CART_BANK_6		equ CARTRIDGE+(6*CART_BANK_SIZE)	; Cartridge bank 6
CART_BANK_6_END		equ CART_BANK_6+CART_BANK_SIZE-1	; Cartridge bank 6 end
CART_BANK_7		equ CARTRIDGE+(7*CART_BANK_SIZE)	; Cartridge bank 7
CART_BANK_7_END		equ CART_BANK_7+CART_BANK_SIZE-1	; Cartridge bank 7 end
	endif

; ------------------------------------------------------------------------------
; RAM cartridge (mode 2)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
RAM_CART_ID		equ CARTRIDGE+1				; RAM cartridge ID
RAM_CART		equ CARTRIDGE+$200001			; RAM cartridge data start
RAM_CART_END		equ RAM_CART+((RAM_CART_SIZE-1)*2)	; RAM cartridge data end

RAM_CART_CTRL		equ CARTRIDGE+$3FFFFF			; RAM cartridge control

SPECIAL_CART_ID		equ CARTRIDGE+$10			; Special cartridge ID
SPECIAL_CART_ENTRY	equ CARTRIDGE+$20			; Special cartridge entry point
	endif
	
; ------------------------------------------------------------------------------
; Expansion
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
EXPANSION		equ $400000				; Expansion start
	elseif CONFIG_MCD_MODE=USE_MCD_MODE_2
EXPANSION		equ 0					; Expansion start
	endif
EXPANSION_END		equ EXPANSION+EXPANSION_SIZE-1		; Expansion end

; ------------------------------------------------------------------------------
; Work RAM
; ------------------------------------------------------------------------------

WORK_RAM		equ $FFFF0000				; Work RAM start
WORK_RAM_END		equ WORK_RAM+WORK_RAM_SIZE-1		; Work RAM end
	
; ------------------------------------------------------------------------------
; VDP
; ------------------------------------------------------------------------------

VDP_PORTS		equ $C00000				; Ports
VDP_DATA		equ VDP_PORTS+0				; Data port
VDP_CTRL		equ VDP_PORTS+4				; Control port
VDP_HV			equ VDP_PORTS+8				; H/V counter
VDP_DEBUG		equ VDP_PORTS+$C			; Debug register

; ------------------------------------------------------------------------------
; YM2612
; ------------------------------------------------------------------------------

YM_PORTS		equ $A00000				; Ports
YM_ADDR_0		equ YM_PORTS+0				; Register address (bank 0)
YM_DATA_0		equ YM_PORTS+1				; Register data (bank 0)
YM_ADDR_1		equ YM_PORTS+2				; Register address (bank 1)
YM_DATA_1		equ YM_PORTS+3				; Register data (bank 1)

; ------------------------------------------------------------------------------
; PSG
; ------------------------------------------------------------------------------

PSG_CTRL		equ VDP_PORTS+$11			; Control port

; ------------------------------------------------------------------------------
; I/O
; ------------------------------------------------------------------------------

IO_REGS			equ $A10001				; I/O registers
IO_VERSION		equ IO_REGS				; Hardware version
IO_DATA_1		equ IO_REGS+2				; Port 1 data
IO_DATA_2		equ IO_REGS+4				; Port 2 data
IO_DATA_3		equ IO_REGS+6				; Port 3 data
IO_CTRL_1		equ IO_REGS+8				; Port 1 control
IO_CTRL_2		equ IO_REGS+$A				; Port 2 control
IO_CTRL_3		equ IO_REGS+$C				; Port 3 control
IO_SERIAL_TX_1		equ IO_REGS+$E				; Port serial Tx data 1
IO_SERIAL_RX_1		equ IO_REGS+$10				; Port serial Rx data 1
IO_SERIAL_CTRL_1	equ IO_REGS+$12				; Port serial control 1
IO_SERIAL_TX_2		equ IO_REGS+$14				; Port serial Tx data 2
IO_SERIAL_RX_2		equ IO_REGS+$16				; Port serial Rx data 2
IO_SERIAL_CTRL_2	equ IO_REGS+$18				; Port serial control 2
IO_SERIAL_TX_3		equ IO_REGS+$1A				; Port serial Tx data 3
IO_SERIAL_RX_3		equ IO_REGS+$1C				; Port serial Rx data 3
IO_SERIAL_CTRL_3	equ IO_REGS+$1E				; Port serial control 3
	
; ------------------------------------------------------------------------------
; TMSS
; ------------------------------------------------------------------------------

TMSS_SEGA		equ $A14000				; TMSS "SEGA" register
	
; ------------------------------------------------------------------------------
; Z80
; ------------------------------------------------------------------------------

Z80_RAM			equ $A00000				; Z80 RAM start
Z80_RAM_END		equ Z80_RAM+Z80_RAM_SIZE-1		; Z80 RAM end

Z80_REGS		equ $A11100				; Z80 registers
Z80_BUS			equ Z80_REGS				; Z80 bus request
Z80_RESET		equ Z80_REGS+$200			; Z80 reset

; ------------------------------------------------------------------------------
; BIOS
; ------------------------------------------------------------------------------

BIOS			equ EXPANSION				; BIOS start
BIOS_END		equ BIOS+BIOS_SIZE-1			; BIOS end

; ------------------------------------------------------------------------------
; Program RAM
; ------------------------------------------------------------------------------

PRG_RAM_BANK		equ EXPANSION+$20000			; Program RAM bank
PRG_RAM_BANK_END	equ PRG_RAM_BANK+PRG_RAM_BANK_SIZE-1	; Program RAM bank end

; ------------------------------------------------------------------------------
; Word RAM
; ------------------------------------------------------------------------------

WORD_RAM_1M		equ EXPANSION+$200000			; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ WORD_RAM_1M+WORD_RAM_1M_SIZE-1	; Word RAM end (1M/1M)
WORD_RAM_2M		equ EXPANSION+$200000			; Word RAM start (2M)
WORD_RAM_2M_END		equ WORD_RAM_2M+WORD_RAM_2M_SIZE-1	; Word RAM end (2M)
WORD_RAM_VRAM		equ EXPANSION+$220000			; Word RAM VRAM image start (1M/1M)
WORD_RAM_VRAM_END	equ WORD_RAM_VRAM+WORD_RAM_VRAM_SIZE-1	; Word RAM VRAM image end (1M/1M)

; ------------------------------------------------------------------------------
; Mega CD
; ------------------------------------------------------------------------------

MCD_REGS		equ $A12000				; Mega CD registers
MCD_IRQ2		equ MCD_REGS				; Mega Drive interrupt request
MCD_SUB_CTRL		equ MCD_REGS+1				; Sub CPU control
MCD_PROTECT		equ MCD_REGS+2				; Program RAM write protection
MCD_MEM_MODE		equ MCD_REGS+3				; Memory mode
MCD_CDC_MODE		equ MCD_REGS+4				; CDC mode
MCD_HBLANK		equ MCD_REGS+6				; H-BLANK interrupt address (mode 2)
MCD_CDC_HOST		equ MCD_REGS+8				; CDC host data
MCD_STOPWATCH		equ MCD_REGS+$C				; Stopwatch
MCD_COMM_FLAGS		equ MCD_REGS+$E				; Communication flags
MCD_MAIN_FLAG		equ MCD_COMM_FLAGS			; Main CPU communication flag
MCD_SUB_FLAG		equ MCD_COMM_FLAGS+1			; Sub CPU communication flag
MCD_MAIN_COMMS		equ MCD_REGS+$10			; Main CPU communication registers
MCD_MAIN_COMM_0		equ MCD_MAIN_COMMS+0			; Main CPU communication register 0
MCD_MAIN_COMM_1		equ MCD_MAIN_COMMS+1			; Main CPU communication register 1
MCD_MAIN_COMM_2		equ MCD_MAIN_COMMS+2			; Main CPU communication register 2
MCD_MAIN_COMM_3		equ MCD_MAIN_COMMS+3			; Main CPU communication register 3
MCD_MAIN_COMM_4		equ MCD_MAIN_COMMS+4			; Main CPU communication register 4
MCD_MAIN_COMM_5		equ MCD_MAIN_COMMS+5			; Main CPU communication register 5
MCD_MAIN_COMM_6		equ MCD_MAIN_COMMS+6			; Main CPU communication register 6
MCD_MAIN_COMM_7		equ MCD_MAIN_COMMS+7			; Main CPU communication register 7
MCD_MAIN_COMM_8		equ MCD_MAIN_COMMS+8			; Main CPU communication register 8
MCD_MAIN_COMM_9		equ MCD_MAIN_COMMS+9			; Main CPU communication register 9
MCD_MAIN_COMM_10	equ MCD_MAIN_COMMS+$A			; Main CPU communication register 10
MCD_MAIN_COMM_11	equ MCD_MAIN_COMMS+$B			; Main CPU communication register 11
MCD_MAIN_COMM_12	equ MCD_MAIN_COMMS+$C			; Main CPU communication register 12
MCD_MAIN_COMM_13	equ MCD_MAIN_COMMS+$D			; Main CPU communication register 13
MCD_MAIN_COMM_14	equ MCD_MAIN_COMMS+$E			; Main CPU communication register 14
MCD_MAIN_COMM_15	equ MCD_MAIN_COMMS+$F			; Main CPU communication register 15
MCD_SUB_COMMS		equ MCD_REGS+$20			; Sub CPU communication registers
MCD_SUB_COMM_0		equ MCD_SUB_COMMS+0			; Sub CPU communication register 0
MCD_SUB_COMM_1		equ MCD_SUB_COMMS+1			; Sub CPU communication register 1
MCD_SUB_COMM_2		equ MCD_SUB_COMMS+2			; Sub CPU communication register 2
MCD_SUB_COMM_3		equ MCD_SUB_COMMS+3			; Sub CPU communication register 3
MCD_SUB_COMM_4		equ MCD_SUB_COMMS+4			; Sub CPU communication register 4
MCD_SUB_COMM_5		equ MCD_SUB_COMMS+5			; Sub CPU communication register 5
MCD_SUB_COMM_6		equ MCD_SUB_COMMS+6			; Sub CPU communication register 6
MCD_SUB_COMM_7		equ MCD_SUB_COMMS+7			; Sub CPU communication register 7
MCD_SUB_COMM_8		equ MCD_SUB_COMMS+8			; Sub CPU communication register 8
MCD_SUB_COMM_9		equ MCD_SUB_COMMS+9			; Sub CPU communication register 9
MCD_SUB_COMM_10		equ MCD_SUB_COMMS+$A			; Sub CPU communication register 10
MCD_SUB_COMM_11		equ MCD_SUB_COMMS+$B			; Sub CPU communication register 11
MCD_SUB_COMM_12		equ MCD_SUB_COMMS+$C			; Sub CPU communication register 12
MCD_SUB_COMM_13		equ MCD_SUB_COMMS+$D			; Sub CPU communication register 13
MCD_SUB_COMM_14		equ MCD_SUB_COMMS+$E			; Sub CPU communication register 14
MCD_SUB_COMM_15		equ MCD_SUB_COMMS+$F			; Sub CPU communication register 15

_EXCPT			equ WORK_RAM+$FD00			; Exception
_LEVEL6			equ WORK_RAM+$FD06			; V-BLANK interrupt
_LEVEL4			equ WORK_RAM+$FD0C			; H-BLANK interrupt
_LEVEL2			equ WORK_RAM+$FD12			; External interrupt
_TRAP00			equ WORK_RAM+$FD18			; TRAP #00
_TRAP01			equ WORK_RAM+$FD1E			; TRAP #01
_TRAP02			equ WORK_RAM+$FD24			; TRAP #02
_TRAP03			equ WORK_RAM+$FD2A			; TRAP #03
_TRAP04			equ WORK_RAM+$FD30			; TRAP #04
_TRAP05			equ WORK_RAM+$FD36			; TRAP #05
_TRAP06			equ WORK_RAM+$FD3C			; TRAP #06
_TRAP07			equ WORK_RAM+$FD42			; TRAP #07
_TRAP08			equ WORK_RAM+$FD48			; TRAP #08
_TRAP09			equ WORK_RAM+$FD4E			; TRAP #09
_TRAP10			equ WORK_RAM+$FD54			; TRAP #10
_TRAP11			equ WORK_RAM+$FD5A			; TRAP #11
_TRAP12			equ WORK_RAM+$FD60			; TRAP #12
_TRAP13			equ WORK_RAM+$FD66			; TRAP #13
_TRAP14			equ WORK_RAM+$FD6C			; TRAP #14
_TRAP15			equ WORK_RAM+$FD72			; TRAP #15
_CHKERR			equ WORK_RAM+$FD78			; CHK exception
_ADRERR			equ WORK_RAM+$FD7E			; Address error
_CODERR			equ WORK_RAM+$FD7E			; Illegal instruction
_DIVERR			equ WORK_RAM+$FD84			; Division by zero
_TRPERR			equ WORK_RAM+$FD8A			; TRAPV exception
_NOCOD0			equ WORK_RAM+$FD90			; Line A emulator
_NOCOD1			equ WORK_RAM+$FD96			; Line F emulator
_SPVERR			equ WORK_RAM+$FD9C			; Privilege violation
_TRACE			equ WORK_RAM+$FDA2			; TRACE exception
_BURAM			equ WORK_RAM+$FDAE			; RAM cartridge function

; ------------------------------------------------------------------------------
; Wait for a VDP DMA to finish
; ------------------------------------------------------------------------------
; PARAMETERS:
;	ctrl - VDP control port (optional)
; ------------------------------------------------------------------------------

waitDma macro ctrl
.Wait\@:
	if narg>0
		move	\ctrl,ccr
	else
		move	VDP_CTRL,ccr
	endif
	bvs.s	.Wait\@
	endm
	
; ------------------------------------------------------------------------------
; VDP DMA from 68000 memory to VDP memory
; ------------------------------------------------------------------------------
; PARAMETERS:
;	src  - Source address in 68000 memory
;	dest - Destination address in VDP memory
;	len  - Length of data in bytes
;	type - Type of VDP memory
;	ctrl - VDP control port (optional)
; ------------------------------------------------------------------------------

dma68k macro src, dest, len, type, ctrl
	__vdp_len: = (VDP_DMA_LEN_H<<16)|VDP_DMA_LEN_L
	__vdp_src: = (VDP_DMA_SRC_M<<16)|VDP_DMA_SRC_L
	
	if narg>4
		move.l	#__vdp_len|((((\len)/2)&$FF00)<<8)|(((\len)/2)&$FF),\ctrl
		move.l	#__vdp_src|((((\src)/2)&$FF00)<<8)|(((\src)/2)&$FF),\ctrl
		move.w	#VDP_DMA_SRC_H|(((\src)>>17)&$7F),\ctrl
		vdpCmdHi move.w,\dest,\type,DMA,\ctrl
		vdpCmdLo move.w,\dest,\type,DMA,-(sp)
		move.w	(sp)+,\ctrl
	else
		move.l	#__vdp_len|((((\len)/2)&$FF00)<<8)|(((\len)/2)&$FF),VDP_CTRL
		move.l	#__vdp_src|((((\src)/2)&$FF00)<<8)|(((\src)/2)&$FF),VDP_CTRL
		move.w	#VDP_DMA_SRC_H|(((\src)>>17)&$7F),VDP_CTRL
		vdpCmdHi move.w,\dest,\type,DMA,VDP_CTRL
		vdpCmdLo move.w,\dest,\type,DMA,-(sp)
		move.w	(sp)+,VDP_CTRL
	endif
	endm

; ------------------------------------------------------------------------------
; Fill VRAM with byte
; (Auto-increment should be set to 1 beforehand)
; ------------------------------------------------------------------------------
; PARAMETERS:
;	addr - Address in VRAM
;	len  - Length of fill in bytes
;	byte - Byte to fill VRAM with
;	ctrl - VDP control port (optional)
;	data - VDP data port (optional)
; ------------------------------------------------------------------------------

vramFill macro addr, len, byte, ctrl, data
	__vdp_len: = (VDP_DMA_LEN_H<<16)|VDP_DMA_LEN_L
	
	if narg>3
		move.l	#__vdp_len|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),\ctrl
		move.w	#VDP_DMA_SRC_H|VDPR_DMD_FILL,\ctrl
		vdpCmd move.l,\addr,VRAM,DMA,\ctrl
		move.w	#((\byte)<<8)|(\byte),\data
		waitDma \ctrl
	else
		move.l	#$94009300|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),VDP_CTRL
		move.w	#VDP_DMA_SRC_H|VDPR_DMD_FILL,VDP_CTRL
		vdpCmd move.l,\addr,VRAM,DMA,VDP_CTRL
		move.w	#((\byte)<<8)|(\byte),VDP_DATA
		waitDma
	endif
	endm

; ------------------------------------------------------------------------------
; Copy a region of VRAM to a location in VRAM
; (Auto-increment should be set to 1 beforehand)
; ------------------------------------------------------------------------------
; PARAMETERS:
;	src  - Source address in VRAM
;	dest - Destination address in VRAM
;	len  - Length of copy in bytes
;	ctrl - VDP control port (optional)
; ------------------------------------------------------------------------------

vramCopy macro src, dest, len, ctrl
	__vdp_len: = (VDP_DMA_LEN_H<<16)|VDP_DMA_LEN_L
	__vdp_src: = (VDP_DMA_SRC_M<<16)|VDP_DMA_SRC_L

	if narg>3
		move.l	#__vdp_len|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),\ctrl
		move.l	#__vdp_src|(((\src)&$FF00)<<8)|((\src)&$FF),\ctrl
		move.w	#VDP_DMA_SRC_H|VDPR_DMD_COPY,\ctrl
		vdpCmd move.l,\dest,VRAM,COPY,\ctrl
		waitDma \ctrl
	else
		move.l	#__vdp_len|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),VDP_CTRL
		move.l	#__vdp_src|(((\src)&$FF00)<<8)|((\src)&$FF),VDP_CTRL
		move.w	#VDP_DMA_SRC_H|VDPR_DMD_COPY,VDP_CTRL
		vdpCmd move.l,\dest,VRAM,COPY,VDP_CTRL
		waitDma
	endif
	endm

; ------------------------------------------------------------------------------
; Reqeust Z80 bus access
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 control port (optional)
; ------------------------------------------------------------------------------

requestZ80 macro reg
	if narg>0
		move.w	#$100,\reg
	else
		move.w	#$100,Z80_BUS
	endif
	endm

; ------------------------------------------------------------------------------
; Wait for Z80 bus acknowledgement
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 control port (optional)
; ------------------------------------------------------------------------------

waitZ80 macro reg
.Wait\@:
	if narg>0
		btst	#0,\reg
	else
		btst	#0,Z80_BUS
	endif
	bne.s	.Wait\@
	endm

; ------------------------------------------------------------------------------
; Stop the Z80 and get bus access
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 control port (optional)
; ------------------------------------------------------------------------------

stopZ80 macro reg
	if narg>0
		requestZ80 \reg
		waitZ80 \reg
	else
		requestZ80
		waitZ80
	endif
	endm

; ------------------------------------------------------------------------------
; Start the Z80 and release bus access
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 bus port (optional)
; ------------------------------------------------------------------------------

startZ80 macro reg
	if narg>0
		move.w	#0,\reg
	else
		move.w	#0,Z80_BUS
	endif
	endm

; ------------------------------------------------------------------------------
; Start Z80 reset
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 reset port (optional)
; ------------------------------------------------------------------------------

resetZ80On macro reg
	if narg>0
		move.w	#0,\reg
	else
		move.w	#0,Z80_RESET
	endif
	ror.b	#8,d0
	endm

; ------------------------------------------------------------------------------
; Stop Z80 reset
; ------------------------------------------------------------------------------
; PARAMETERS:
;	reg - Z80 reset port (optional)
; ------------------------------------------------------------------------------

resetZ80Off macro reg
	if narg>0
		move.w	#$100,\reg
	else
		move.w	#$100,Z80_RESET
	endif
	endm

; ------------------------------------------------------------------------------
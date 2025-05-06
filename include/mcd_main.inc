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
CARTRIDGE_END		equ $3FFFFF				; Cartridge end
	elseif CONFIG_MCD_MODE=USE_MCD_MODE_2
CARTRIDGE		equ $400000				; Cartridge start
CARTRIDGE_END		equ $7FFFFF				; Cartridge end
	endif
CARTRIDGE_SIZE		equ $400000				; Cartridge size

; ------------------------------------------------------------------------------
; SRAM (mode 1)
; ------------------------------------------------------------------------------

	if (CONFIG_MCD_MODE=USE_MCD_MODE_1)&(CONFIG_SRAM<>NO_SRAM)
	if CONFIG_SRAM=USE_SRAM_8K
SRAM_SIZE		equ $2000				; SRAM size (8K)
	elseif CONFIG_SRAM=USE_SRAM_16K
SRAM_SIZE		equ $4000				; SRAM size (16K)
	elseif CONFIG_SRAM=USE_SRAM_32K
SRAM_SIZE		equ $8000				; SRAM size (32K)
	endif
SRAM			equ $200001				; SRAM start
SRAM_END		equ $200001+((SRAM_SIZE-1)*2)		; SRAM end

SRAM_CTRL		equ $A130F1				; SRAM control
	endif
	
; ------------------------------------------------------------------------------
; Mapper (mode 1)
; ------------------------------------------------------------------------------

	if (CONFIG_MCD_MODE=USE_MCD_MODE_1)&(CONFIG_MAPPER=USE_MAPPER)
CART_BANK_0		equ 0					; Cartridge bank 0
CART_BANK_0_END		equ $7FFFF				; Cartridge bank 0 end
CART_BANK_1		equ $80000				; Cartridge bank 1
CART_BANK_1_END		equ $FFFFF				; Cartridge bank 1 end
CART_BANK_2		equ $100000				; Cartridge bank 2
CART_BANK_2_END		equ $17FFFF				; Cartridge bank 2 end
CART_BANK_3		equ $180000				; Cartridge bank 3
CART_BANK_3_END		equ $1FFFFF				; Cartridge bank 3 end
CART_BANK_4		equ $200000				; Cartridge bank 4
CART_BANK_4_END		equ $27FFFF				; Cartridge bank 4 end
CART_BANK_5		equ $280000				; Cartridge bank 5
CART_BANK_5_END		equ $2FFFFF				; Cartridge bank 5 end
CART_BANK_6		equ $300000				; Cartridge bank 6
CART_BANK_6_END		equ $37FFFF				; Cartridge bank 6 end
CART_BANK_7		equ $380000				; Cartridge bank 7
CART_BANK_7_END		equ $3FFFFF				; Cartridge bank 7 end
CART_BANK_SIZE		equ $80000				; Cartridge bank size

MAPPER_REGS		equ $A130F3				; Mapper registers
MAPPER_BANK_1		equ $A130F3				; Mapper bank 1
MAPPER_BANK_2		equ $A130F5				; Mapper bank 2
MAPPER_BANK_3		equ $A130F7				; Mapper bank 3
MAPPER_BANK_4		equ $A130F9				; Mapper bank 4
MAPPER_BANK_5		equ $A130FB				; Mapper bank 5
MAPPER_BANK_6		equ $A130FD				; Mapper bank 6
MAPPER_BANK_7		equ $A130FF				; Mapper bank 7
	endif

; ------------------------------------------------------------------------------
; RAM cartridge (mode 2)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
RAM_CART_ID		equ $400001				; RAM cartridge ID
RAM_CART		equ $600001				; RAM cartridge data start
RAM_CART_END		equ $6FFFFF				; RAM cartridge data end
RAM_CART_SIZE		equ $80000				; RAM cartridge data size

RAM_CART_CTRL		equ $7FFFFF				; RAM cartridge control

SPECIAL_CART_ID		equ $400010				; Special cartridge ID
SPECIAL_CART_ENTRY	equ $400020				; Special cartridge entry point
	endif
	
; ------------------------------------------------------------------------------
; Expansion
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
EXPANSION		equ $400000				; Expansion start
EXPANSION_END		equ $7FFFFF				; Expansion end
	elseif CONFIG_MCD_MODE=USE_MCD_MODE_2
EXPANSION		equ 0					; Expansion start
EXPANSION_END		equ $3FFFFF				; Expansion end
	endif
EXPANSION_SIZE		equ $400000				; Expansion size

; ------------------------------------------------------------------------------
; Work RAM
; ------------------------------------------------------------------------------

WORK_RAM		equ $FFFF0000				; Work RAM start
WORK_RAM_END		equ $FFFFFFFF				; Work RAM end
WORK_RAM_SIZE		equ $10000				; Work RAM size

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
_EXCPT			equ $FFFFFD00				; Exception
_LEVEL6			equ $FFFFFD06				; V-BLANK interrupt
_LEVEL4			equ $FFFFFD0C				; H-BLANK interrupt
_LEVEL2			equ $FFFFFD12				; External interrupt
_TRAP00			equ $FFFFFD18				; TRAP #00
_TRAP01			equ $FFFFFD1E				; TRAP #01
_TRAP02			equ $FFFFFD24				; TRAP #02
_TRAP03			equ $FFFFFD2A				; TRAP #03
_TRAP04			equ $FFFFFD30				; TRAP #04
_TRAP05			equ $FFFFFD36				; TRAP #05
_TRAP06			equ $FFFFFD3C				; TRAP #06
_TRAP07			equ $FFFFFD42				; TRAP #07
_TRAP08			equ $FFFFFD48				; TRAP #08
_TRAP09			equ $FFFFFD4E				; TRAP #09
_TRAP10			equ $FFFFFD54				; TRAP #10
_TRAP11			equ $FFFFFD5A				; TRAP #11
_TRAP12			equ $FFFFFD60				; TRAP #12
_TRAP13			equ $FFFFFD66				; TRAP #13
_TRAP14			equ $FFFFFD6C				; TRAP #14
_TRAP15			equ $FFFFFD72				; TRAP #15
_CHKERR			equ $FFFFFD78				; CHK exception
_ADRERR			equ $FFFFFD7E				; Address error
_CODERR			equ $FFFFFD7E				; Illegal instruction
_DIVERR			equ $FFFFFD84				; Division by zero
_TRPERR			equ $FFFFFD8A				; TRAPV exception
_NOCOD0			equ $FFFFFD90				; Line A emulator
_NOCOD1			equ $FFFFFD96				; Line F emulator
_SPVERR			equ $FFFFFD9C				; Privilege violation
_TRACE			equ $FFFFFDA2				; TRACE exception
_BURAM			equ $FFFFFDAE				; RAM cartridge function
	endif
	
; ------------------------------------------------------------------------------
; VDP
; ------------------------------------------------------------------------------

VDP_PORTS		equ $C00000				; Ports
VDP_DATA		equ $C00000				; Data port
VDP_CTRL		equ $C00004				; Control port
VDP_HV			equ $C00008				; H/V counter
VDP_DEBUG		equ $C0000C				; Debug register

; ------------------------------------------------------------------------------
; YM2612
; ------------------------------------------------------------------------------

YM_PORTS		equ $A00000				; Ports
YM_ADDR_0		equ $A00000				; Register address (bank 0)
YM_DATA_0		equ $A00001				; Register data (bank 0)
YM_ADDR_1		equ $A00002				; Register address (bank 1)
YM_DATA_1		equ $A00003				; Register data (bank 1)

; ------------------------------------------------------------------------------
; PSG
; ------------------------------------------------------------------------------

PSG_CTRL		equ $C00011				; Control port

; ------------------------------------------------------------------------------
; I/O
; ------------------------------------------------------------------------------

IO_REGS			equ $A10001				; I/O registers
IO_VERSION		equ $A10001				; Hardware version
IO_DATA_1		equ $A10003				; Port 1 data
IO_DATA_2		equ $A10005				; Port 2 data
IO_DATA_3		equ $A10007				; Port 3 data
IO_CTRL_1		equ $A10009				; Port 1 control
IO_CTRL_2		equ $A1000B				; Port 2 control
IO_CTRL_3		equ $A1000D				; Port 3 control
IO_SERIAL_TX_1		equ $A1000F				; Port serial Tx data 1
IO_SERIAL_RX_1		equ $A10011				; Port serial Rx data 1
IO_SERIAL_CTRL_1	equ $A10013				; Port serial control 1
IO_SERIAL_TX_2		equ $A10015				; Port serial Tx data 2
IO_SERIAL_RX_2		equ $A10017				; Port serial Rx data 2
IO_SERIAL_CTRL_2	equ $A10019				; Port serial control 2
IO_SERIAL_TX_3		equ $A1001B				; Port serial Tx data 3
IO_SERIAL_RX_3		equ $A1001D				; Port serial Rx data 3
IO_SERIAL_CTRL_3	equ $A1001F				; Port serial control 3
	
; ------------------------------------------------------------------------------
; TMSS
; ------------------------------------------------------------------------------

TMSS_SEGA		equ $A14000				; TMSS "SEGA" register
	
; ------------------------------------------------------------------------------
; Z80
; ------------------------------------------------------------------------------

Z80_RAM			equ $A00000				; Z80 RAM start
Z80_RAM_END		equ $A01FFF				; Z80 RAM end
Z80_RAM_SIZE		equ $2000				; Z80 RAM size

Z80_REGS		equ $A11100				; Z80 registers
Z80_BUS			equ $A11100				; Z80 bus request
Z80_RESET		equ $A11200				; Z80 reset

; ------------------------------------------------------------------------------
; BIOS
; ------------------------------------------------------------------------------

BIOS			equ EXPANSION				; BIOS start
BIOS_END		equ EXPANSION+$1FFFF			; BIOS end
BIOS_SIZE		equ $20000				; BIOS size

; ------------------------------------------------------------------------------
; Program RAM
; ------------------------------------------------------------------------------

PRG_RAM_BANK		equ EXPANSION+$20000			; Program RAM bank
PRG_RAM_BANK_END	equ EXPANSION+$3FFFF			; Program RAM bank end
PRG_RAM_BANK_SIZE	equ $20000				; Program RAM bank size

; ------------------------------------------------------------------------------
; Word RAM
; ------------------------------------------------------------------------------

WORD_RAM_1M		equ EXPANSION+$200000			; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ EXPANSION+$21FFFF			; Word RAM end (1M/1M)
WORD_RAM_1M_SIZE	equ $20000				; Word RAM size (1M/1M)
WORD_RAM_2M		equ EXPANSION+$200000			; Word RAM start (2M)
WORD_RAM_2M_END		equ EXPANSION+$23FFFF			; Word RAM end (2M)
WORD_RAM_2M_SIZE	equ $40000				; Word RAM size (2M)
WORD_RAM_VRAM		equ EXPANSION+$220000			; Word RAM VRAM image start (1M/1M)
WORD_RAM_VRAM_END	equ EXPANSION+$23FFFF			; Word RAM VRAM image end (1M/1M)
WORD_RAM_VRAM_SIZE	equ $20000				; Word RAM VRAM image size (1M/1M)

; ------------------------------------------------------------------------------
; Gate array
; ------------------------------------------------------------------------------

MCD_REGS		equ $A12000				; Mega CD registers
MCD_IRQ2		equ $A12000				; Mega Drive interrupt request
MCD_SUB_CTRL		equ $A12001				; Sub CPU control
MCD_PROTECT		equ $A12002				; Program RAM write protection
MCD_MEM_MODE		equ $A12003				; Memory mode
MCD_CDC_MODE		equ $A12004				; CDC mode
MCD_HBLANK		equ $A12006				; H-BLANK interrupt address (mode 2)
MCD_CDC_HOST		equ $A12008				; CDC host data
MCD_STOPWATCH		equ $A1200C				; Stopwatch
MCD_COMM_FLAGS		equ $A1200E				; Communication flags
MCD_MAIN_FLAG		equ $A1200E				; Main CPU communication flag
MCD_SUB_FLAG		equ $A1200F				; Sub CPU communication flag
MCD_MAIN_COMMS		equ $A12010				; Main CPU communication registers
MCD_MAIN_COMM_0		equ $A12010				; Main CPU communication register 0
MCD_MAIN_COMM_1		equ $A12011				; Main CPU communication register 1
MCD_MAIN_COMM_2		equ $A12012				; Main CPU communication register 2
MCD_MAIN_COMM_3		equ $A12013				; Main CPU communication register 3
MCD_MAIN_COMM_4		equ $A12014				; Main CPU communication register 4
MCD_MAIN_COMM_5		equ $A12015				; Main CPU communication register 5
MCD_MAIN_COMM_6		equ $A12016				; Main CPU communication register 6
MCD_MAIN_COMM_7		equ $A12017				; Main CPU communication register 7
MCD_MAIN_COMM_8		equ $A12018				; Main CPU communication register 8
MCD_MAIN_COMM_9		equ $A12019				; Main CPU communication register 9
MCD_MAIN_COMM_10	equ $A1201A				; Main CPU communication register 10
MCD_MAIN_COMM_11	equ $A1201B				; Main CPU communication register 11
MCD_MAIN_COMM_12	equ $A1201C				; Main CPU communication register 12
MCD_MAIN_COMM_13	equ $A1201D				; Main CPU communication register 13
MCD_MAIN_COMM_14	equ $A1201E				; Main CPU communication register 14
MCD_MAIN_COMM_15	equ $A1201F				; Main CPU communication register 15
MCD_SUB_COMMS		equ $A12020				; Sub CPU communication registers
MCD_SUB_COMM_0		equ $A12020				; Sub CPU communication register 0
MCD_SUB_COMM_1		equ $A12021				; Sub CPU communication register 1
MCD_SUB_COMM_2		equ $A12022				; Sub CPU communication register 2
MCD_SUB_COMM_3		equ $A12023				; Sub CPU communication register 3
MCD_SUB_COMM_4		equ $A12024				; Sub CPU communication register 4
MCD_SUB_COMM_5		equ $A12025				; Sub CPU communication register 5
MCD_SUB_COMM_6		equ $A12026				; Sub CPU communication register 6
MCD_SUB_COMM_7		equ $A12027				; Sub CPU communication register 7
MCD_SUB_COMM_8		equ $A12028				; Sub CPU communication register 8
MCD_SUB_COMM_9		equ $A12029				; Sub CPU communication register 9
MCD_SUB_COMM_10		equ $A1202A				; Sub CPU communication register 10
MCD_SUB_COMM_11		equ $A1202B				; Sub CPU communication register 11
MCD_SUB_COMM_12		equ $A1202C				; Sub CPU communication register 12
MCD_SUB_COMM_13		equ $A1202D				; Sub CPU communication register 13
MCD_SUB_COMM_14		equ $A1202E				; Sub CPU communication register 14
MCD_SUB_COMM_15		equ $A1202F				; Sub CPU communication register 15

; ------------------------------------------------------------------------------
; Backup RAM function codes
; ------------------------------------------------------------------------------

BRMINIT			equ 0					; Initialize Backup RAM interaction
BRMSTAT			equ 1					; Get Backup RAM status
BRMSERCH		equ 2					; Search Backup RAM
BRMREAD			equ 3					; Read Backup RAM data
BRMWRITE		equ 4					; Write Backup RAM data
BRMDEL			equ 5					; Delete Backup RAM data
BRMFORMAT		equ 6					; Format Backup RAM
BRMDIR			equ 7					; Get Backup RAM directory
BRMVERIFY		equ 8					; Verify written Backup RAM data

; ------------------------------------------------------------------------------
; VDP command instruction
; ------------------------------------------------------------------------------
; PARAMETERS:
;	ins  - Instruction
;	addr - Address in VDP memory
;	type - Type of VDP memory
;	rwd  - VDP command
;	dest - Destination (optional)
; ------------------------------------------------------------------------------

VRAM_WRITE_CMD		equ $40000000				; VRAM write
CRAM_WRITE_CMD		equ $C0000000				; CRAM write
VSRAM_WRITE_CMD		equ $40000010				; VSRAM write
VRAM_READ_CMD		equ $00000000				; VRAM read
CRAM_READ_CMD		equ $00000020				; CRAM read
VSRAM_READ_CMD		equ $00000010				; VSRAM read
VRAM_DMA_CMD		equ $40000080				; VRAM DMA
CRAM_DMA_CMD		equ $C0000080				; CRAM DMA
VSRAM_DMA_CMD		equ $40000090				; VSRAM DMA
VRAM_COPY_CMD		equ $000000C0				; VRAM DMA copy

; ------------------------------------------------------------------------------

vdpCmd macro ins, addr, type, rwd, dest
	local cmd
	cmd: = (\type\_\rwd\_CMD)|(((\addr)&$3FFF)<<16)|((\addr)/$4000)
	if narg=5
		\ins	#\#cmd,\dest
	else
		\ins	cmd
	endif
	endm

; ------------------------------------------------------------------------------
; VDP command instruction (low word)
; ------------------------------------------------------------------------------
; PARAMETERS:
;	ins  - Instruction
;	addr - Address in VDP memory
;	type - Type of VDP memory
;	rwd  - VDP command
;	dest - Destination (optional)
; ------------------------------------------------------------------------------

vdpCmdLo macro ins, addr, type, rwd, dest
	local cmd
	cmd: = ((\type\_\rwd\_CMD)&$FFFF)|((\addr)/$4000)
	if narg=5
		\ins	#\#cmd,\dest
	else
		\ins	cmd
	endif
	endm

; ------------------------------------------------------------------------------
; VDP command instruction (high word)
; ------------------------------------------------------------------------------
; PARAMETERS:
;	ins  - Instruction
;	addr - Address in VDP memory
;	type - Type of VDP memory
;	rwd  - VDP command
;	dest - Destination (optional)
; ------------------------------------------------------------------------------

vdpCmdHi macro ins, addr, type, rwd, dest
	local cmd
	cmd: = ((\type\_\rwd\_CMD)>>16)|((\addr)&$3FFF)
	if narg=5
		\ins	#\#cmd,\dest
	else
		\ins	cmd
	endif
	endm
	
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
	if narg>4
		move.l	#$94009300|((((\len)/2)&$FF00)<<8)|(((\len)/2)&$FF),\ctrl
		move.l	#$96009500|((((\src)/2)&$FF00)<<8)|(((\src)/2)&$FF),\ctrl
		move.w	#$9700|(((\src)>>17)&$7F),\ctrl
		vdpCmdHi move.w,\dest,\type,DMA,\ctrl
		vdpCmdLo move.w,\dest,\type,DMA,-(sp)
		move.w	(sp)+,\ctrl
	else
		move.l	#$94009300|((((\len)/2)&$FF00)<<8)|(((\len)/2)&$FF),VDP_CTRL
		move.l	#$96009500|((((\src)/2)&$FF00)<<8)|(((\src)/2)&$FF),VDP_CTRL
		move.w	#$9700|(((\src)>>17)&$7F),VDP_CTRL
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
	if narg>3
		move.l	#$94009300|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),\ctrl
		move.w	#$9780,\ctrl
		vdpCmd move.l,\addr,VRAM,DMA,\ctrl
		move.w	#((\byte)<<8)|(\byte),\data
		waitDma \ctrl
	else
		move.l	#$94009300|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),VDP_CTRL
		move.w	#$9780,VDP_CTRL
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
	if narg>3
		move.l	#$94009300|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),\ctrl
		move.l	#$96009500|(((\src)&$FF00)<<8)|((\src)&$FF),\ctrl
		move.w	#$97C0,\ctrl
		vdpCmd move.l,\dest,VRAM,COPY,\ctrl
		waitDma \ctrl
	else
		move.l	#$94009300|((((\len)-1)&$FF00)<<8)|(((\len)-1)&$FF),VDP_CTRL
		move.l	#$96009500|(((\src)&$FF00)<<8)|((\src)&$FF),VDP_CTRL
		move.w	#$97C0,VDP_CTRL
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
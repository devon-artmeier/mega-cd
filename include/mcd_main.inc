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

; ------------------------------------------------------------------------------
; Configuration
; ------------------------------------------------------------------------------

USE_MCD_MODE_1		equ 0					; Mega CD mode 1
USE_MCD_MODE_2		equ 1					; Mega CD mode 2

NO_SRAM			equ 0					; No SRAM
USE_SRAM_8K		equ 1					; 8 KiB SRAM
USE_SRAM_16K		equ 2					; 16 KiB SRAM
USE_SRAM_32K		equ 3					; 32 KiB SRAM

NO_MAPPER		equ 0					; No mapper
USE_MAPPER		equ 1					; Use mapper

; ------------------------------------------------------------------------------
; Cartridge
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
CARTRIDGE		equ $400000				; Cartridge memory start
CARTRIDGE_END		equ $7FFFFF				; Cartridge memory end
	else
CARTRIDGE		equ 0					; Cartridge memory start
CARTRIDGE_END		equ $3FFFFF				; Cartridge memory end
	endif
CARTRIDGE_LEN		equ $400000				; Cartridge memory length

; ------------------------------------------------------------------------------
; Expansion
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
EXPANSION		equ 0					; Expansion memory start
EXPANSION_END		equ $3FFFFF				; Expansion memory end
	else
EXPANSION		equ $400000				; Expansion memory start
EXPANSION_END		equ $7FFFFF				; Expansion memory end
	endif
EXPANSION_LEN		equ $400000				; Expansion memory length

; ------------------------------------------------------------------------------
; SRAM/mapper (Mode 1)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
	if CONFIG_SRAM<>NO_SRAM
SRAM			equ CARTRIDGE+$200001			; SRAM start
	if CONFIG_SRAM=USE_SRAM_8K
SRAM_END		equ CARTRIDGE+$203FFF			; SRAM end
SRAM_SIZE		equ $2000				; SRAM size
	elseif CONFIG_SRAM=USE_SRAM_16K
SRAM_END		equ CARTRIDGE+$207FFF			; SRAM end
SRAM_SIZE		equ $4000				; SRAM size
	elseif CONFIG_SRAM=USE_SRAM_32K
SRAM_END		equ CARTRIDGE+$20FFFF			; SRAM end
SRAM_SIZE		equ $8000				; SRAM size
	endif

SRAM_CTRL		equ $A130F1				; SRAM control
	endif
	endif

	if CONFIG_MAPPER=USE_MAPPER
MAPPER_BANK_0		equ CARTRIDGE				; Mapper bank 0
MAPPER_BANK_0_END	equ CARTRIDGE+$7FFFF			; Mapper bank 0 end
MAPPER_BANK_1		equ CARTRIDGE+$80000			; Mapper bank 1
MAPPER_BANK_1_END	equ CARTRIDGE+$FFFFF			; Mapper bank 1 end
MAPPER_BANK_2		equ CARTRIDGE+$100000			; Mapper bank 2
MAPPER_BANK_2_END	equ CARTRIDGE+$17FFFF			; Mapper bank 2 end
MAPPER_BANK_3		equ CARTRIDGE+$180000			; Mapper bank 3
MAPPER_BANK_3_END	equ CARTRIDGE+$1FFFFF			; Mapper bank 3 end
MAPPER_BANK_4		equ CARTRIDGE+$200000			; Mapper bank 4
MAPPER_BANK_4_END	equ CARTRIDGE+$27FFFF			; Mapper bank 4 end
MAPPER_BANK_5		equ CARTRIDGE+$280000			; Mapper bank 5
MAPPER_BANK_5_END	equ CARTRIDGE+$2FFFFF			; Mapper bank 5 end
MAPPER_BANK_6		equ CARTRIDGE+$300000			; Mapper bank 6
MAPPER_BANK_6_END	equ CARTRIDGE+$37FFFF			; Mapper bank 6 end
MAPPER_BANK_7		equ CARTRIDGE+$380000			; Mapper bank 7
MAPPER_BANK_7_END	equ CARTRIDGE+$3FFFFF			; Mapper bank 7 end
MAPPER_BANK_LEN		equ $80000				; ROM bank length

MAPPER_REGS		equ $A130F1				; Mapper registers
MAPPER_CTRL		equ $A130F1				; Mapper control
MAPPER_BANK_SETS	equ $A130F3				; Mapper bank sets
MAPPER_BANK_SET_1	equ $A130F3				; Mapper bank set 1
MAPPER_BANK_SET_2	equ $A130F5				; Mapper bank set 2
MAPPER_BANK_SET_3	equ $A130F7				; Mapper bank set 3
MAPPER_BANK_SET_4	equ $A130F9				; Mapper bank set 4
MAPPER_BANK_SET_5	equ $A130FB				; Mapper bank set 5
MAPPER_BANK_SET_6	equ $A130FD				; Mapper bank set 6
MAPPER_BANK_SET_7	equ $A130FF				; Mapper bank set 7
	endif
	endif

; ------------------------------------------------------------------------------
; RAM cartridge (Mode 2)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
RAM_CART_ID		equ CARTRIDGE+1				; RAM cartridge ID
RAM_CART_DATA		equ CARTRIDGE+$200001			; RAM cartridge data start
RAM_CART_DATA_END	equ CARTRIDGE+$2FFFFF			; RAM cartridge data end
RAM_CART_DATA_LEN	equ $80000				; RAM cartridge data length

RAM_CART_CTRL		equ CARTRIDGE+$3FFFFF			; RAM cartridge control

SPECIAL_CART_ID		equ CARTRIDGE+$10			; Special cartridge ID
SPECIAL_CART_ENTRY	equ CARTRIDGE+$20			; Special cartridge entry point
	endif

; ------------------------------------------------------------------------------
; Mega CD
; ------------------------------------------------------------------------------

BIOS			equ EXPANSION				; BIOS start
BIOS_END		equ EXPANSION+$1FFFF			; BIOS end
BIOS_LEN		equ $20000				; BIOS length

PRG_RAM_BANK		equ EXPANSION+$20000			; Program RAM bank
PRG_RAM_BANK_END	equ EXPANSION+$3FFFF			; Program RAM bank end
PRG_RAM_BANK_LEN	equ $20000				; Program RAM bank length

WORD_RAM_1M		equ EXPANSION+$200000			; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ EXPANSION+$21FFFF			; Word RAM end (1M/1M)
WORD_RAM_1M_LEN		equ $20000				; Word RAM length (1M/1M)
WORD_RAM_VRAM		equ EXPANSION+$220000			; Word RAM VRAM image start (1M/1M)
WORD_RAM_VRAM_END	equ EXPANSION+$23FFFF			; Word RAM VRAM image end (1M/1M)
WORD_RAM_VRAM_LEN	equ $20000				; Word RAM VRAM image length (1M/1M)
WORD_RAM_2M		equ EXPANSION+$200000			; Word RAM start (2M)
WORD_RAM_2M_END		equ EXPANSION+$23FFFF			; Word RAM end (2M)
WORD_RAM_2M_LEN		equ $40000				; Word RAM length (2M)

MCD_REGS		equ $A12000				; Mega CD registers
MCD_IRQ2		equ $A12000				; IRQ2 request
MCD_RESET		equ $A12001				; Reset
MCD_PROTECT		equ $A12002				; Program RAM write protection
MCD_MEM_MODE		equ $A12003				; Memory mode
MCD_CDC_MODE		equ $A12004				; CDC mode
	if CONFIG_MCD_MODE=USE_MCD_MODE_1
MCD_HBLANK		equ $A12006				; H-BLANK interrupt address (Mode 2 only)
	endif
MCD_CDC_HOST		equ $A12008				; CDC data
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
; Z80
; ------------------------------------------------------------------------------

Z80_RAM			equ $A00000				; Z80 RAM start
Z80_RAM_END		equ $A01FFF				; Z80 RAM end
Z80_RAM_LEN		equ $2000				; Z80 RAM length

Z80_REGS		equ $A11100				; Z80 registers
Z80_BUS			equ $A11100				; Z80 bus request
Z80_RESET		equ $A11200				; Z80 reset

Z80R_BREQ_BIT		equ 0					; Z80 bus request
Z80R_BREQ		equ %00000001

Z80R_RREQ_BIT		equ 0					; Z80 reset request
Z80R_RREQ		equ %00000001

; ------------------------------------------------------------------------------
; YM2612
; ------------------------------------------------------------------------------

YM_PORTS		equ $A10000				; YM2612 ports
YM_ADDR_0		equ $A10000				; YM2612 register address 0
YM_DATA_0		equ $A10001				; YM2612 register data 0
YM_ADDR_1		equ $A10002				; YM2612 register address 1
YM_DATA_1		equ $A10003				; YM2612 register data 1

; ------------------------------------------------------------------------------
; I/O
; ------------------------------------------------------------------------------

IO_REGS			equ $A10001				; I/O registers
IO_VERSION		equ $A10001				; Hardware version
IO_DATA_1		equ $A10003				; Controller port 1 data
IO_DATA_2		equ $A10005				; Controller port 2 data
IO_DATA_3		equ $A10007				; Controller port 3 data
IO_CTRL_1		equ $A10009				; Controller port 1 control
IO_CTRL_2		equ $A1000B				; Controller port 2 control
IO_CTRL_3		equ $A1000D				; Controller port 3 control
IO_SERIAL_TX_1		equ $A1000F				; Controller port serial Tx data 1
IO_SERIAL_RX_1		equ $A10011				; Controller port serial Rx data 1
IO_SERIAL_CTRL_1	equ $A10013				; Controller port serial control 1
IO_SERIAL_TX_2		equ $A10015				; Controller port serial Tx data 2
IO_SERIAL_RX_2		equ $A10017				; Controller port serial Rx data 2
IO_SERIAL_CTRL_2	equ $A10019				; Controller port serial control 2
IO_SERIAL_TX_3		equ $A1001B				; Controller port serial Tx data 3
IO_SERIAL_RX_3		equ $A1001D				; Controller port serial Rx data 3
IO_SERIAL_CTRL_3	equ $A1001F				; Controller port serial control 3

IOR_VER_BIT		equ 0					; Hardware version
IOR_VER			equ %00001111
IOR_DISK_BIT		equ 5					; Expansion connected
IOR_DISK		equ %00100000
IOR_VMOD_BIT		equ 6					; CPU clock speed
IOR_VMOD		equ %01000000
IOR_VMOD_NTSC		equ %00000000				; NTSC clock speed
IOR_VMOD_PAL		equ %01000000				; PAL clock speed
IOR_MODE_BIT		equ 7					; Hardware model type
IOR_MODE		equ %10000000
IOR_VMOD_DOMESTIC	equ %00000000				; Domestic model
IOR_VMOD_OVERSEAS	equ %10000000				; Overseas model

IOR_PD0_BIT		equ 0					; Controller port data bit 0
IOR_PD0			equ %00000001
IOR_UP_BIT		equ 0					; Controller port up bit
IOR_UP			equ %00000001
IOR_PD1_BIT		equ 1					; Controller port data bit 1
IOR_PD1			equ %00000010
IOR_DOWN_BIT		equ 1					; Controller port down bit
IOR_DOWN		equ %00000010
IOR_PD2_BIT		equ 2					; Controller port data bit 2
IOR_PD2			equ %00000100
IOR_LEFT_BIT		equ 2					; Controller port left bit
IOR_LEFT		equ %00000100
IOR_PD3_BIT		equ 3					; Controller port data bit 3
IOR_PD3			equ %00001000
IOR_RIGHT_BIT		equ 3					; Controller port right bit
IOR_RIGHT		equ %00001000
IOR_PD4_BIT		equ 4					; Controller port data bit 4
IOR_PD4			equ %00010000
IOR_TL_BIT		equ 4					; Controller port TL bit
IOR_TL			equ %00010000
IOR_PD5_BIT		equ 5					; Controller port data bit 5
IOR_PD5			equ %00100000
IOR_TR_BIT		equ 5					; Controller port TR bit
IOR_TR			equ %00100000
IOR_PD6_BIT		equ 6					; Controller port data bit 6
IOR_PD6			equ %01000000
IOR_TH_BIT		equ 6					; Controller port TH bit
IOR_TH			equ %01000000
IOR_PD7_BIT		equ 7					; Controller port data bit 7
IOR_PD7			equ %10000000

IOR_PC0_BIT		equ 0					; Controller port PD0 (up) mode
IOR_PC0			equ %00000001
IOR_PC1_BIT		equ 1					; Controller port PD1 (down) mode
IOR_PC1			equ %00000010
IOR_PC2_BIT		equ 2					; Controller port PD2 (left) mode
IOR_PC2			equ %00000100
IOR_PC3_BIT		equ 3					; Controller port PD3 (right) mode
IOR_PC3			equ %00001000
IOR_PC4_BIT		equ 4					; Controller port PD4 (TL) mode
IOR_PC4			equ %00010000
IOR_PC5_BIT		equ 5					; Controller port PD5 (TH) mode
IOR_PC5			equ %00100000
IOR_PC6_BIT		equ 6					; Controller port PD6 (TR) mode
IOR_PC6			equ %01000000
IOR_PC7_BIT		equ 7					; Controller port PD7 mode
IOR_PC7			equ %10000000

IOR_TFUL_BIT		equ 0					; Tx data full
IOR_TFUL		equ %00000001
IOR_RRDY_BIT		equ 1					; TL serial output mode
IOR_RRDY		equ %00000010
IOR_RERR_BIT		equ 2					; Rx data ready
IOR_RERR		equ %00000100
IOR_RINT_BIT		equ 3					; Rx data error
IOR_RINT		equ %00001000
IOR_SOUT_BIT		equ 4					; TL serial output mode
IOR_SOUT		equ %00010000
IOR_SIN_BIT		equ 5					; TR serial input mode
IOR_SIN			equ %00100000
IOR_BPS_BIT		equ 6					; Serial speed
IOR_BPS			equ %11000000
IOR_BPS_4800		equ %00000000				; 4800bps
IOR_BPS_2400		equ %01000000				; 2400bps
IOR_BPS_1200		equ %10000000				; 1200bps
IOR_BPS_300		equ %11000000				; 300bps

; ------------------------------------------------------------------------------
; TMSS
; ------------------------------------------------------------------------------

TMSS_SEGA		equ $A14000				; TMSS "SEGA" register

; ------------------------------------------------------------------------------
; VDP
; ------------------------------------------------------------------------------

VRAM_LEN		equ $10000				; VRAM length
CRAM_LEN		equ $80					; CRAM length
VSRAM_LEN		equ $50					; VSRAM length

VDP_PORTS		equ $C00000				; VDP ports
VDP_DATA		equ $C00000				; VDP data port
VDP_CTRL		equ $C00004				; VDP control port
VDP_HV			equ $C00008				; VDP H/V counter
VDP_DEBUG		equ $C0000C				; VDP debug

VDPR_M3_BIT		equ 1					; H/V counter latch
VDPR_M3			equ %00000010
VDPR_IE1_BIT		equ 4					; H-BLANK interrupt enable
VDPR_IE1		equ %00010000
VDPR_LCB_BIT		equ 5					; Blank leftmost 8 pixels
VDPR_LCB		equ %00010000

VDPR_M5_BIT		equ 2					; Genesis/Mega Drive mode
VDPR_M5			equ %00000100
VDPR_M2_BIT		equ 3					; V30 mode
VDPR_M2			equ %00001000
VDPR_M1_BIT		equ 4					; DMA enable
VDPR_M1			equ %00010000
VDPR_IE0_BIT		equ 5					; V-BLANK interrupt enable
VDPR_IE0		equ %00100000
VDPR_DISP_BIT		equ 6					; Display enable
VDPR_DISP		equ %01000000

VDPR_SA_BIT		equ 3					; Plane A address
VDPR_SA			equ %00111000
VDPR_SA_SHIFT		equ $A

VDPR_WD_BIT		equ 1					; Window plane address
VDPR_WD			equ %00111110
VDPR_WD_SHIFT		equ $A

VDPR_SB_BIT		equ 0					; Plane B address
VDPR_SB			equ %00000111
VDPR_SB_SHIFT		equ $D

VDPR_AT_BIT		equ 0					; Sprite table aaddress
VDPR_AT			equ %01111111
VDPR_AT_SHIFT		equ 9

VDPR_COL_BIT		equ 0					; Background color index
VDPR_COL		equ %00001111
VDPR_CPT_BIT		equ 4					; Background color index
VDPR_CPT		equ %00110000

VDPR_HIT_BIT		equ 0					; H-BLANK interrupt counter
VDPR_HIT		equ %11111111

VDPR_HSCR_BIT		equ 0					; Horizontal scroll mode
VDPR_HSCR		equ %00000011
VDPR_HSCR_FULL		equ %00000000				; Horizontal full screen scroll mode
VDPR_HSCR_TILE		equ %00000010				; Horizontal tile scroll mode
VDPR_HSCR_LINE		equ %00000011				; Horizontal line scroll mode
VDPR_VSCR_BIT		equ 2					; Vertical scroll mode
VDPR_VSCR		equ %00000100
VDPR_VSCR_FULL		equ %00000000				; Vertical full screen scroll mode
VDPR_VSCR_TILE		equ %00000100				; Vertical tile scroll mode
VDPR_IE2_BIT		equ 3					; External interrupt enable
VDPR_IE2		equ %00001000

VDPR_RS1_BIT		equ 0					; H40 mode (low bit)
VDPR_RS1		equ %00000001
VDPR_LSM_BIT		equ 1					; Interlace mode
VDPR_LSM		equ %00000110
VDPR_LSM_OFF		equ %00000000				; Interlace mode off
VDPR_LSM_ON		equ %00000010				; Interlace mode on
VDPR_LSM_DOUBLE		equ %00000110				; Interlace mode on (double)
VDPR_STE_BIT		equ 3					; Shadow/highlight mode
VDPR_STE		equ %00001000
VDPR_RS0_BIT		equ 7					; H40 mode (high bit)
VDPR_RS0		equ %10000000
VDPR_RS			equ %10000001				; H40 mode (bits combined)

VDPR_HS_BIT		equ 0					; Horizontal scroll table address
VDPR_HS			equ %00111111
VDPR_HS_SHIFT		equ $A

VDPR_INC_BIT		equ 0					; Auto-increment
VDPR_INC		equ %11111111

VDPR_HSZ_BIT		equ 0					; Horizontal plane size
VDPR_HSZ		equ %00000011
VDPR_HSZ_32		equ %00000000				; 32 tile horizontal plane size
VDPR_HSZ_64		equ %00000001				; 64 tile horizontal plane size
VDPR_HSZ_128		equ %00000011				; 128 tile horizontal plane size
VDPR_VSZ_BIT		equ 4					; Vertical plane size
VDPR_VSZ		equ %00110000
VDPR_VSZ_32		equ %00000000				; 32 tile vertical plane size
VDPR_VSZ_64		equ %00010000				; 64 tile vertical plane size
VDPR_VSZ_128		equ %00110000				; 128 tile vertical plane size

VDPR_WHP_BIT		equ 0					; Window plane horizontal position
VDPR_WHP		equ %00011111
VDPR_RIGT_BIT		equ 7					; Window plane right direction
VDPR_RIGT		equ %10000000

VDPR_WVP_BIT		equ 0					; Window plane vertical position
VDPR_WVP		equ %00011111
VDPR_DOWN_BIT		equ 7					; Window plane down direction
VDPR_DOWN		equ %10000000

VDPR_LGL_BIT		equ 0					; DMA length (low)
VDPR_LGL		equ %11111111

VDPR_LGH_BIT		equ 0					; DMA length (high)
VDPR_LGH		equ %11111111
VDPR_LGH_SHIFT		equ 8

VDPR_SAL_BIT		equ 0					; DMA source address (low)
VDPR_SAL		equ %11111111

VDPR_SAM_BIT		equ 0					; DMA source address (middle)
VDPR_SAM		equ %11111111
VDPR_SAM_SHIFT		equ 8

VDPR_SAH_BIT		equ 0					; DMA source address (high)
VDPR_SAH		equ %01111111
VDPR_SAH_SHIFT		equ 16
VDPR_DMD_BIT		equ 6					; DMA mode
VDPR_DMD		equ %11000000
VDPR_DMD_68K		equ %00000000				; DMA from 68000 memory mode
VDPR_DMD_FILL		equ %10000000				; VRAM fill mode
VDPR_DMD_COPY		equ %11000000				; VRAM copy mode

; ------------------------------------------------------------------------------
; PSG
; ------------------------------------------------------------------------------

PSG_CTRL		equ $C00011				; PSG control port

; ------------------------------------------------------------------------------
; Work RAM
; ------------------------------------------------------------------------------

WORK_RAM		equ $FFFF0000				; Work RAM start
WORK_RAM_LEN		equ $10000				; Work RAM length
WORK_RAM_END		equ $FFFFFFFF				; Work RAM end

; ------------------------------------------------------------------------------
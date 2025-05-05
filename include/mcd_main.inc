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

ALLOW_DOMESTIC_NTSC	equ %00000001				; Allow domestic NTSC models (Japan/South Korea/Taiwan)
ALLOW_DOMESTIC_PAL	equ %00000010				; Allow domestic PAL models
ALLOW_DOMESTIC		equ %00000011				; Allow domestic models
ALLOW_OVERSEAS_NTSC	equ %00000100				; Allow overseas NTSC models (USA/Canada/Brazil)
ALLOW_OVERSEAS_PAL	equ %00001000				; Allow overseas PAL models (Europe/Hong Kong)
ALLOW_OVERSEAS		equ %00001100				; Allow overseas models
ALLOW_NTSC		equ %00000101				; Allow NTSC models
ALLOW_PAL		equ %00001010				; Allow PAL models
ALLOW_ALL_MODELS	equ %00001111				; Allow all models
ALLOW_JAPAN		equ %00000001				; Allow Japan/South Korea/Taiwan models
ALLOW_USA		equ %00000100				; Allow USA/Canada/Brazil models
ALLOW_EUROPE		equ %00001000				; Allow Europe/Hong Kong models

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
CARTRIDGE_SIZE		equ $400000				; Cartridge memory size

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
EXPANSION_SIZE		equ $400000				; Expansion memory size

; ------------------------------------------------------------------------------
; SRAM/mapper (mode 1)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
	if CONFIG_SRAM<>NO_SRAM
SRAM			equ $200001				; SRAM start
	if CONFIG_SRAM=USE_SRAM_8K
SRAM_END		equ $203FFF				; SRAM end
SRAM_SIZE		equ $2000				; SRAM size
	elseif CONFIG_SRAM=USE_SRAM_16K
SRAM_END		equ $207FFF				; SRAM end
SRAM_SIZE		equ $4000				; SRAM size
	elseif CONFIG_SRAM=USE_SRAM_32K
SRAM_END		equ $20FFFF				; SRAM end
SRAM_SIZE		equ $8000				; SRAM size
	endif

SRAM_CTRL		equ $A130F1				; SRAM control

SRAMR_ENABLE_BIT	equ 0					; SRAM enable
SRAMR_ENABLE		equ %00000001
SRAMR_PROTECT_BIT	equ 1					; SRAM write protection
SRAMR_PROTECT		equ %00000010
	endif

	if CONFIG_MAPPER=USE_MAPPER
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
	endif

; ------------------------------------------------------------------------------
; RAM cartridge (mode 2)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
RAM_CART_ID		equ $200001				; RAM cartridge ID
RAM_CART_DATA		equ $600001				; RAM cartridge data start
RAM_CART_DATA_END	equ $6FFFFF				; RAM cartridge data end
RAM_CART_DATA_SIZE	equ $80000				; RAM cartridge data size

SPECIAL_CART_ID		equ $400010				; Special cartridge ID
SPECIAL_CART_ENTRY	equ $400020				; Special cartridge entry point

RAM_CART_CTRL		equ $7FFFFF				; RAM cartridge control
	endif

; ------------------------------------------------------------------------------
; Mega CD
; ------------------------------------------------------------------------------

BIOS			equ EXPANSION				; BIOS start
BIOS_END		equ EXPANSION+$1FFFF			; BIOS end
BIOS_SIZE		equ $20000				; BIOS size

PRG_RAM_BANK		equ EXPANSION+$20000			; Program RAM bank
PRG_RAM_BANK_END	equ EXPANSION+$3FFFF			; Program RAM bank end
PRG_RAM_BANK_SIZE	equ $20000				; Program RAM bank size

WORD_RAM_1M		equ EXPANSION+$200000			; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ EXPANSION+$21FFFF			; Word RAM end (1M/1M)
WORD_RAM_1M_SIZE	equ $20000				; Word RAM size (1M/1M)
WORD_RAM_VRAM		equ EXPANSION+$220000			; Word RAM VRAM image start (1M/1M)
WORD_RAM_VRAM_END	equ EXPANSION+$23FFFF			; Word RAM VRAM image end (1M/1M)
WORD_RAM_VRAM_SIZE	equ $20000				; Word RAM VRAM image size (1M/1M)
WORD_RAM_2M		equ EXPANSION+$200000			; Word RAM start (2M)
WORD_RAM_2M_END		equ EXPANSION+$23FFFF			; Word RAM end (2M)
WORD_RAM_2M_SIZE	equ $40000				; Word RAM size (2M)

MCD_REGS		equ $A12000				; Mega CD registers
MCD_IRQ2		equ $A12000				; IRQ2 request
MCD_SUB_CTRL		equ $A12001				; Sub CPU control
MCD_PROTECT		equ $A12002				; Program RAM write protection
MCD_MEM_MODE		equ $A12003				; Memory mode
MCD_CDC_MODE		equ $A12004				; CDC mode
	if CONFIG_MCD_MODE=USE_MCD_MODE_1
MCD_HBLANK		equ $A12006				; H-BLANK interrupt address (mode 2 only)
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

MCDR_IFL2_BIT		equ 0					; Sub CPU IRQ2 request
MCDR_IFL2		equ %00000001
MCDR_IEN2_BIT		equ 7					; Sub CPU IRQ2 enabled
MCDR_IEN2		equ %10000000

MCDR_SRES_BIT		equ 0					; Sub CPU reset
MCDR_SRES		equ %00000001
MCDR_SBRQ_BIT		equ 1					; Sub CPU bus request
MCDR_SBRQ		equ %00000010

MCDR_WP_BIT		equ 0					; Program RAM write protection range
MCDR_WP			equ %11111111
MCDR_WP_SHIFT		equ 9

MCDR_RET_BIT		equ 0					; Word RAM Main CPU access
MCDR_RET		equ %00000001
MCDR_DMNA_BIT		equ 1					; Word RAM Sub CPU access
MCDR_DMNA		equ %00000010
MCDR_MODE_BIT		equ 2					; Word RAM mode
MCDR_MODE		equ %00000100
MCDR_MODE_2M		equ %00000000				; Word RAM 2M mode
MCDR_MODE_1M		equ %00000100				; Word RAM 1M/1M mode

	if CONFIG_MCD_MODE=USE_MCD_MODE_1
MCDR_HIB_BIT		equ 0					; H-BLANK interrupt address (mode 2 only)
MCDR_HIB		equ %11111111
	endif
	
MCDR_DD_BIT		equ 0					; CDC device destination
MCDR_DD			equ %00000111
MCDR_DD_HOST_MAIN	equ %00000010				; Host register (Main CPU read)
MCDR_DD_HOST_SUB	equ %00000011				; Host register (Sub CPU read)
MCDR_DD_WAVE_RAM	equ %00000100				; Wave RAM (DMA)
MCDR_DD_PRG_RAM		equ %00000101				; Program RAM (DMA)
MCDR_DD_WORD_RAM	equ %00000111				; Word RAM (DMA)
MCDR_DSR_BIT		equ 6					; Data set ready
MCDR_DSR		equ %01000000
MCDR_EDT_BIT		equ 7					; End of data transfer
MCDR_EDT		equ %10000000

MCDR_HD_BIT		equ 0					; CDC host data
MCDR_HD			equ %1111111111111111

MCDR_TD_BIT		equ 0					; Stopwatch value
MCDR_TD			equ %0000111111111111

MCDR_CFM_BIT		equ 0					; Main CPU communication flag
MCDR_CFM		equ %11111111

MCDR_CFS_BIT		equ 0					; Sub CPU communication flag
MCDR_CFS		equ %11111111

MCDR_CCM_BIT		equ 0					; Main CPU communication value
MCDR_CCM		equ %11111111

MCDR_CST_BIT		equ 0					; Sub CPU communication value
MCDR_CST		equ %11111111

; ------------------------------------------------------------------------------
; Z80
; ------------------------------------------------------------------------------

Z80_RAM			equ $A00000				; Z80 RAM start
Z80_RAM_END		equ $A01FFF				; Z80 RAM end
Z80_RAM_SIZE		equ $2000				; Z80 RAM size

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

YM_PORTS		equ $A10000				; Ports
YM_ADDR_0		equ $A10000				; Register address (bank 0)
YM_DATA_0		equ $A10001				; Register data (bank 0)
YM_ADDR_1		equ $A10002				; Register address (bank 1)
YM_DATA_1		equ $A10003				; Register data (bank 1)

YMR_BUSY_BIT		equ 7					; Busy
YMR_BUSY		equ %10000000

YM_CH_BIT		equ 0					; Channel ID
YM_CH			equ %00000011
YM_CH14			equ %00000000				; Channel 1/4
YM_CH25			equ %00000001				; Channel 2/5
YM_CH36			equ %00000010				; Channel 3/6
YM_BANK_BIT		equ 2					; Channel bank
YM_BANK			equ %00000100
YM_BANK_0		equ %00000000				; Channel bank 0
YM_BANK_1		equ %00000100				; Channel bank 1
YM_CH1			equ %00000000				; Channel 1
YM_CH2			equ %00000001				; Channel 2
YM_CH3			equ %00000010				; Channel 3
YM_CH4			equ %00000100				; Channel 4
YM_CH5			equ %00000101				; Channel 5
YM_CH6			equ %00000110				; Channel 6
YM_OP_1			equ %00000000				; OP1
YM_OP_14_1		equ %00000000				; CH1/4 OP1
YM_OP_25_1		equ %00000001				; CH2/5 OP1
YM_OP_36_1		equ %00000010				; CH3/6 OP1
YM_OP_1_1		equ %00000000				; CH1 OP1
YM_OP_4_1		equ %00000000				; CH4 OP1
YM_OP_2_1		equ %00000001				; CH2 OP1
YM_OP_5_1		equ %00000001				; CH5 OP1
YM_OP_3_1		equ %00000010				; CH3 OP1
YM_OP_6_1		equ %00000010				; CH6 OP1
YM_OP_2			equ %00001000				; OP2
YM_OP_14_2		equ %00001000				; CH1/4 OP2
YM_OP_25_2		equ %00001001				; CH2/5 OP2
YM_OP_36_2		equ %00001010				; CH3/6 OP2
YM_OP_1_2		equ %00001000				; CH1 OP2
YM_OP_4_2		equ %00001000				; CH4 OP2
YM_OP_2_2		equ %00001001				; CH2 OP2
YM_OP_5_2		equ %00001001				; CH5 OP2
YM_OP_3_2		equ %00001010				; CH3 OP2
YM_OP_6_2		equ %00001010				; CH6 OP2
YM_OP_3			equ %00000100				; OP3
YM_OP_14_3		equ %00000100				; CH1/4 OP3
YM_OP_25_3		equ %00000101				; CH2/5 OP3
YM_OP_36_3		equ %00000110				; CH3/6 OP3
YM_OP_1_3		equ %00000100				; CH1 OP3
YM_OP_4_3		equ %00000100				; CH4 OP3
YM_OP_2_3		equ %00000101				; CH2 OP3
YM_OP_5_3		equ %00000101				; CH5 OP3
YM_OP_3_3		equ %00000110				; CH3 OP3
YM_OP_6_3		equ %00000110				; CH6 OP3
YM_OP_4			equ %00001100				; OP4
YM_OP_14_4		equ %00001100				; CH1/4 OP4
YM_OP_25_4		equ %00001101				; CH2/5 OP4
YM_OP_36_4		equ %00001110				; CH3/6 OP4
YM_OP_1_4		equ %00001100				; CH1 OP4
YM_OP_4_4		equ %00001100				; CH4 OP4
YM_OP_2_4		equ %00001101				; CH2 OP4
YM_OP_5_4		equ %00001101				; CH5 OP4
YM_OP_3_4		equ %00001110				; CH3 OP4
YM_OP_6_4		equ %00001110				; CH6 OP4

YM_LFO			equ $22					; LFO
YM_TIMER_A_H		equ $24					; Timer A (high)
YM_TIMER_A_L		equ $25					; Timer A (low)
YM_TIMER_B		equ $26					; Timer B
YM_CH3_TIMERS		equ $27					; Channel 3 mode and timer control
YM_KEY_ON		equ $28					; Key on/off
YM_DAC_OUT		equ $2A					; DAC output
YM_DAC_ENABLE		equ $2B					; DAC enable
YM_MUL_DT		equ $30					; Multiply and detune
YM_MUL_DT_1_1		equ $30					; Multiply and detune (CH1/4 OP1)
YM_MUL_DT_2_1		equ $31					; Multiply and detune (CH2/5 OP1)
YM_MUL_DT_3_1		equ $32					; Multiply and detune (CH3/6 OP1)
YM_MUL_DT_1_3		equ $34					; Multiply and detune (CH1/4 OP3)
YM_MUL_DT_2_3		equ $35					; Multiply and detune (CH2/5 OP3)
YM_MUL_DT_3_3		equ $36					; Multiply and detune (CH3/6 OP3)
YM_MUL_DT_1_2		equ $38					; Multiply and detune (CH1/4 OP2)
YM_MUL_DT_2_2		equ $39					; Multiply and detune (CH2/5 OP2)
YM_MUL_DT_3_2		equ $3A					; Multiply and detune (CH3/6 OP2)
YM_MUL_DT_1_4		equ $3C					; Multiply and detune (CH1/4 OP4)
YM_MUL_DT_2_4		equ $3D					; Multiply and detune (CH2/5 OP4)
YM_MUL_DT_3_4		equ $3E					; Multiply and detune (CH3/6 OP4)
YM_TL			equ $40					; Total level
YM_TL_1_1		equ $40					; Total level (CH1/4 OP1)
YM_TL_2_1		equ $41					; Total level (CH2/5 OP1)
YM_TL_3_1		equ $42					; Total level (CH3/6 OP1)
YM_TL_1_3		equ $44					; Total level (CH1/4 OP3)
YM_TL_2_3		equ $45					; Total level (CH2/5 OP3)
YM_TL_3_3		equ $46					; Total level (CH3/6 OP3)
YM_TL_1_2		equ $48					; Total level (CH1/4 OP2)
YM_TL_2_2		equ $49					; Total level (CH2/5 OP2)
YM_TL_3_2		equ $4A					; Total level (CH3/6 OP2)
YM_TL_1_4		equ $4C					; Total level (CH1/4 OP4)
YM_TL_2_4		equ $4D					; Total level (CH2/5 OP4)
YM_TL_3_4		equ $4E					; Total level (CH3/6 OP4)
YM_AR_RS		equ $50					; Attack rate and rate scaling
YM_AR_RS_1_1		equ $50					; Attack rate and rate scaling (CH1/4 OP1)
YM_AR_RS_2_1		equ $51					; Attack rate and rate scaling (CH2/5 OP1)
YM_AR_RS_3_1		equ $52					; Attack rate and rate scaling (CH3/6 OP1)
YM_AR_RS_1_3		equ $54					; Attack rate and rate scaling (CH1/4 OP3)
YM_AR_RS_2_3		equ $55					; Attack rate and rate scaling (CH2/5 OP3)
YM_AR_RS_3_3		equ $56					; Attack rate and rate scaling (CH3/6 OP3)
YM_AR_RS_1_2		equ $58					; Attack rate and rate scaling (CH1/4 OP2)
YM_AR_RS_2_2		equ $59					; Attack rate and rate scaling (CH2/5 OP2)
YM_AR_RS_3_2		equ $5A					; Attack rate and rate scaling (CH3/6 OP2)
YM_AR_RS_1_4		equ $5C					; Attack rate and rate scaling (CH1/4 OP4)
YM_AR_RS_2_4		equ $5D					; Attack rate and rate scaling (CH2/5 OP4)
YM_AR_RS_3_4		equ $5E					; Attack rate and rate scaling (CH3/6 OP4)
YM_DR_AM		equ $60					; Decay rate and AM enable
YM_DR_AM_1_1		equ $60					; Decay rate and AM enable (CH1/4 OP1)
YM_DR_AM_2_1		equ $61					; Decay rate and AM enable (CH2/5 OP1)
YM_DR_AM_3_1		equ $62					; Decay rate and AM enable (CH3/6 OP1)
YM_DR_AM_1_3		equ $64					; Decay rate and AM enable (CH1/4 OP3)
YM_DR_AM_2_3		equ $65					; Decay rate and AM enable (CH2/5 OP3)
YM_DR_AM_3_3		equ $66					; Decay rate and AM enable (CH3/6 OP3)
YM_DR_AM_1_2		equ $68					; Decay rate and AM enable (CH1/4 OP2)
YM_DR_AM_2_2		equ $69					; Decay rate and AM enable (CH2/5 OP2)
YM_DR_AM_3_2		equ $6A					; Decay rate and AM enable (CH3/6 OP2)
YM_DR_AM_1_4		equ $6C					; Decay rate and AM enable (CH1/4 OP4)
YM_DR_AM_2_4		equ $6D					; Decay rate and AM enable (CH2/5 OP4)
YM_DR_AM_3_4		equ $6E					; Decay rate and AM enable (CH3/6 OP4)
YM_SR			equ $70					; Sustain rate
YM_SR_1_1		equ $70					; Sustain rate (CH1/4 OP1)
YM_SR_2_1		equ $71					; Sustain rate (CH2/5 OP1)
YM_SR_3_1		equ $72					; Sustain rate (CH3/6 OP1)
YM_SR_1_3		equ $74					; Sustain rate (CH1/4 OP3)
YM_SR_2_3		equ $75					; Sustain rate (CH2/5 OP3)
YM_SR_3_3		equ $76					; Sustain rate (CH3/6 OP3)
YM_SR_1_2		equ $78					; Sustain rate (CH1/4 OP2)
YM_SR_2_2		equ $79					; Sustain rate (CH2/5 OP2)
YM_SR_3_2		equ $7A					; Sustain rate (CH3/6 OP2)
YM_SR_1_4		equ $7C					; Sustain rate (CH1/4 OP4)
YM_SR_2_4		equ $7D					; Sustain rate (CH2/5 OP4)
YM_SR_3_4		equ $7E					; Sustain rate (CH3/6 OP4)
YM_RR_SL		equ $80					; Release rate and sustain level
YM_RR_SL_1_1		equ $80					; Release rate and sustain level (CH1/4 OP1)
YM_RR_SL_2_1		equ $81					; Release rate and sustain level (CH2/5 OP1)
YM_RR_SL_3_1		equ $82					; Release rate and sustain level (CH3/6 OP1)
YM_RR_SL_1_3		equ $84					; Release rate and sustain level (CH1/4 OP3)
YM_RR_SL_2_3		equ $85					; Release rate and sustain level (CH2/5 OP3)
YM_RR_SL_3_3		equ $86					; Release rate and sustain level (CH3/6 OP3)
YM_RR_SL_1_2		equ $88					; Release rate and sustain level (CH1/4 OP2)
YM_RR_SL_2_2		equ $89					; Release rate and sustain level (CH2/5 OP2)
YM_RR_SL_3_2		equ $8A					; Release rate and sustain level (CH3/6 OP2)
YM_RR_SL_1_4		equ $8C					; Release rate and sustain level (CH1/4 OP4)
YM_RR_SL_2_4		equ $8D					; Release rate and sustain level (CH2/5 OP4)
YM_RR_SL_3_4		equ $8E					; Release rate and sustain level (CH3/6 OP4)
YM_SSGEG		equ $90					; SSG-EG
YM_SSGEG_1_1		equ $90					; SSG-EG (CH1/4 OP1)
YM_SSGEG_2_1		equ $91					; SSG-EG (CH2/5 OP1)
YM_SSGEG_3_1		equ $92					; SSG-EG (CH3/6 OP1)
YM_SSGEG_1_3		equ $94					; SSG-EG (CH1/4 OP3)
YM_SSGEG_2_3		equ $95					; SSG-EG (CH2/5 OP3)
YM_SSGEG_3_3		equ $96					; SSG-EG (CH3/6 OP3)
YM_SSGEG_1_2		equ $98					; SSG-EG (CH1/4 OP2)
YM_SSGEG_2_2		equ $99					; SSG-EG (CH2/5 OP2)
YM_SSGEG_3_2		equ $9A					; SSG-EG (CH3/6 OP2)
YM_SSGEG_1_4		equ $9C					; SSG-EG (CH1/4 OP4)
YM_SSGEG_2_4		equ $9D					; SSG-EG (CH2/5 OP4)
YM_SSGEG_3_4		equ $9E					; SSG-EG (CH3/6 OP4)
YM_FREQ_L		equ $A0					; Frequency (low)
YM_FREQ_L_1		equ $A0					; Frequency (low, CH1/4)
YM_FREQ_L_2		equ $A1					; Frequency (low, CH2/5)
YM_FREQ_L_3		equ $A2					; Frequency (low, CH3/6)
YM_FREQ_L_3_4		equ $A2					; Frequency (low, CH3 OP4)
YM_FREQ_H		equ $A4					; Frequency (high)
YM_FREQ_H_1		equ $A4					; Frequency (high, CH1/4)
YM_FREQ_H_2		equ $A5					; Frequency (high, CH2/5)
YM_FREQ_H_3		equ $A6					; Frequency (high, CH3/6)
YM_FREQ_H_3_4		equ $A2					; Frequency (high, CH3 OP4)
YM_FREQ_L_3_3		equ $A8					; Frequency (low, CH3 OP3)
YM_FREQ_L_3_1		equ $A9					; Frequency (low, CH3 OP1)
YM_FREQ_L_3_2		equ $AA					; Frequency (low, CH3 OP2)
YM_FREQ_H_3_3		equ $AC					; Frequency (high, CH3 OP3)
YM_FREQ_H_3_1		equ $AD					; Frequency (high, CH3 OP1)
YM_FREQ_H_3_2		equ $AE					; Frequency (high, CH3 OP2)
YM_ALG_FB		equ $B0					; Algorithm and feedback
YM_ALG_FB_1		equ $B0					; Algorithm and feedback (CH1/4)
YM_ALG_FB_2		equ $B1					; Algorithm and feedback (CH2/5)
YM_ALG_FB_3		equ $B2					; Algorithm and feedback (CH3/6)
YM_PAN_MOD		equ $B4					; Panning and modulation
YM_PAN_MOD_1		equ $B4					; Panning and modulation (CH1/4)
YM_PAN_MOD_2		equ $B5					; Panning and modulation (CH2/5)
YM_PAN_MOD_3		equ $B6					; Panning and modulation (CH3/6)

YMR_LFO_BIT		equ 0					; LFO frequency
YMR_LFO			equ %00000111
YMR_LFO_3_82		equ %00000000				; 3.82 Hz LFO
YMR_LFO_5_33		equ %00000001				; 5.33 Hz LFO
YMR_LFO_5_77		equ %00000010				; 5.77 Hz LFO
YMR_LFO_6_11		equ %00000011				; 6.11 Hz LFO
YMR_LFO_6_60		equ %00000100				; 6.60 Hz LFO
YMR_LFO_9_23		equ %00000101				; 9.23 Hz LFO
YMR_LFO_46_11		equ %00000110				; 46.11 Hz LFO
YMR_LFO_69_22		equ %00000111				; 69.22 Hz LFO
YMR_LFOEN_BIT		equ 3					; LFO enable
YMR_LFOEN		equ %00001000

YMR_TMA_H_BIT		equ 0					; Timer A (high)
YMR_TMA_H		equ %11111111
YMR_TMA_H_SHIFT		equ 2

YMR_TMA_L_BIT		equ 0					; Timer A (low)
YMR_TMA_L		equ %11

YMR_TMB_BIT		equ 0					; Timer B
YMR_TMB			equ %11111111

YMR_RUN_A_BIT		equ 0					; Timer A running
YMR_RUN_A		equ %00000001
YMR_RUN_B_BIT		equ 1					; Timer B running
YMR_RUN_B		equ %00000010
YMR_FLG_A_BIT		equ 2					; Timer A overflow flag enable
YMR_FLG_A		equ %00000100
YMR_FLG_B_BIT		equ 3					; Timer B overflow flag enable
YMR_FLG_B		equ %00001000
YMR_RST_A_BIT		equ 4					; Timer A overflow flag enable
YMR_RST_A		equ %00010000
YMR_RST_B_BIT		equ 5					; Timer B overflow flag enable
YMR_RST_B		equ %00100000
YMR_CH3_BIT		equ 6					; Channel 3 mode
YMR_CH3			equ %11000000
YMR_CH3_NORMAL		equ %00000000				; Normal channel 3 mode
YMR_CH3_SPECIAL		equ %01000000				; Special channel 3 mode
YMR_CH3_CSM		equ %10000000				; CSM channel 3 mode

YMR_CH_BIT		equ 0					; Key on/off channel ID
YMR_CH			equ %00000111
YMR_OP0_BIT		equ 4					; OP1 key on/off
YMR_OP0			equ %00010000
YMR_OP1_BIT		equ 5					; OP2 key on/off
YMR_OP1			equ %00100000
YMR_OP2_BIT		equ 6					; OP3 key on/off
YMR_OP2			equ %01000000
YMR_OP3_BIT		equ 7					; OP4 key on/off
YMR_OP3			equ %10000000
YMR_OP_ALL		equ %11110000				; All operator key on/off

YMR_DAC_BIT		equ 0					; DAC output data
YMR_DAC			equ %11111111

YMR_DACEN_BIT		equ 7					; DAC enable
YMR_DACEN		equ %10000000

YMR_MUL_BIT		equ 0					; Multiply
YMR_MUL			equ %00001111
YMR_DT_BIT		equ 4					; Detune
YMR_DT			equ %01110000
YMR_DT_OFFSET		equ %00110000				; Detune offset
YMR_DT_SIGN		equ %01000000				; Detune sign
YMR_DT_SIGN_P		equ %00000000				; Positive detune
YMR_DT_SIGN_N		equ %01000000				; Negative detune

YMR_TL_BIT		equ 0					; Total level
YMR_TL			equ %01111111

YMR_AR_BIT		equ 0					; Attack rate
YMR_AR			equ %00011111
YMR_RS_BIT		equ 6					; Rate scaling
YMR_RS			equ %11000000

YMR_DR_BIT		equ 0					; Decay rate
YMR_DR			equ %00011111
YMR_AM_BIT		equ 7					; AM enable
YMR_AM			equ %10000000

YMR_SR_BIT		equ 0					; Sustain rate
YMR_SR			equ %00011111

YMR_RR_BIT		equ 0					; Release rate
YMR_RR			equ %00001111
YMR_SL_BIT		equ 4					; Sustain level
YMR_SL			equ %11110000

YMR_SSGEG_BIT		equ 0					; SSG-EG envelope
YMR_SSGEG		equ %00000111
YMR_SSGEG_REPEAT	equ %00000000				; SSG-EG repeat
YMR_SSGEG_HOLD		equ %00000001				; SSG-EG hold
YMR_SSGEG_INVERT	equ %00000010				; SSG-EG invert
YMR_SSGEG_LEFT		equ %00000000				; SSG-EG left direction
YMR_SSGEG_RIGHT		equ %00000100				; SSG-EG right direction
YMR_SSGEG_EN_BIT	equ 3					; SSG-EG enable
YMR_SSGEG_EN		equ %00001000

YMR_FREQ_H_BIT		equ 0					; Frequency (high)
YMR_FREQ_H		equ %00000111
YMR_FREQ_H_SHIFT	equ 8
YMR_BLK_BIT		equ 3					; Frequency block
YMR_BLK			equ %00111000

YMR_FREQ_L_BIT		equ 0					; Frequency (low)
YMR_FREQ_L		equ %11111111

YMR_ALG_BIT		equ 0					; Algorithm
YMR_ALG			equ %00000111
YMR_FB_BIT		equ 3					; Feedback
YMR_FB			equ %00111000

YMR_FMS_BIT		equ 0					; FMS
YMR_FMS			equ %00000111
YMR_FMS_NONE		equ %00000000				; No FMS
YMR_FMS_034		equ %00000001				; -/+0.034 semitone FMS
YMR_FMS_067		equ %00000010				; -/+0.067 semitone FMS
YMR_FMS_100		equ %00000011				; -/+0.100 semitone FMS
YMR_FMS_140		equ %00000100				; -/+0.140 semitone FMS
YMR_FMS_200		equ %00000101				; -/+0.200 semitone FMS
YMR_FMS_400		equ %00000110				; -/+0.400 semitone FMS
YMR_FMS_800		equ %00000111				; -/+0.800 semitone FMS
YMR_AMS_BIT		equ 4					; AMS
YMR_AMS			equ %00110000
YMR_AMS_NONE		equ %00000000				; No AMS
YMR_AMS_14		equ %00010000				; -/+1.4 dB AMS
YMR_AMS_5_9		equ %00100000				; -/+5.9 dB AMS
YMR_AMS_11_8		equ %00110000				; -/+11.8 dB AMS
YMR_R_BIT		equ 6					; Right output
YMR_R			equ %01000000
YMR_L_BIT		equ 7					; Left output
YMR_R			equ %10000000
YMR_LR			equ %11000000				; Left and right output

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
IOR_MODE_DOMESTIC	equ %00000000				; Domestic model
IOR_MODE_OVERSEAS	equ %10000000				; Overseas model
IOR_DOMESTIC_NSTC	equ %00000000				; Domestic NTSC model
IOR_DOMESTIC_PAL	equ %01000000				; Domestic PAL model
IOR_OVERSEAS_NSTC	equ %10000000				; Overseas NTSC model
IOR_OVERSEAS_PAL	equ %11000000				; Overseas PAL model
IOR_JAPAN		equ %00000000				; Japan/South Korea/Taiwan model
IOR_USA			equ %10000000				; USA/Canada/Brazil model
IOR_EUROPE		equ %11000000				; Europe/Hong Kong model

IOR_PD0_BIT		equ 0					; Port data bit 0
IOR_PD0			equ %00000001
IOR_UP_BIT		equ 0					; Port up bit
IOR_UP			equ %00000001
IOR_PD1_BIT		equ 1					; Port data bit 1
IOR_PD1			equ %00000010
IOR_DOWN_BIT		equ 1					; Port down bit
IOR_DOWN		equ %00000010
IOR_PD2_BIT		equ 2					; Port data bit 2
IOR_PD2			equ %00000100
IOR_LEFT_BIT		equ 2					; Port left bit
IOR_LEFT		equ %00000100
IOR_PD3_BIT		equ 3					; Port data bit 3
IOR_PD3			equ %00001000
IOR_RIGHT_BIT		equ 3					; Port right bit
IOR_RIGHT		equ %00001000
IOR_PD4_BIT		equ 4					; Port data bit 4
IOR_PD4			equ %00010000
IOR_TL_BIT		equ 4					; Port TL bit
IOR_TL			equ %00010000
IOR_PD5_BIT		equ 5					; Port data bit 5
IOR_PD5			equ %00100000
IOR_TR_BIT		equ 5					; Port TR bit
IOR_TR			equ %00100000
IOR_PD6_BIT		equ 6					; Port data bit 6
IOR_PD6			equ %01000000
IOR_TH_BIT		equ 6					; Port TH bit
IOR_TH			equ %01000000
IOR_PD7_BIT		equ 7					; Port data bit 7
IOR_PD7			equ %10000000

IOR_PC0_BIT		equ 0					; Port PD0 (up) mode
IOR_PC0			equ %00000001
IOR_PC1_BIT		equ 1					; Port PD1 (down) mode
IOR_PC1			equ %00000010
IOR_PC2_BIT		equ 2					; Port PD2 (left) mode
IOR_PC2			equ %00000100
IOR_PC3_BIT		equ 3					; Port PD3 (right) mode
IOR_PC3			equ %00001000
IOR_PC4_BIT		equ 4					; Port PD4 (TL) mode
IOR_PC4			equ %00010000
IOR_PC5_BIT		equ 5					; Port PD5 (TH) mode
IOR_PC5			equ %00100000
IOR_PC6_BIT		equ 6					; Port PD6 (TR) mode
IOR_PC6			equ %01000000
IOR_PC7_BIT		equ 7					; Port PD7 mode
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
IOR_BPS_4800		equ %00000000				; 4800 bps serial speed
IOR_BPS_2400		equ %01000000				; 2400 bps serial speed
IOR_BPS_1200		equ %10000000				; 1200 bps serial speed
IOR_BPS_300		equ %11000000				; 300 bps serial speed

; ------------------------------------------------------------------------------
; TMSS
; ------------------------------------------------------------------------------

TMSS_SEGA		equ $A14000				; TMSS "SEGA" register

; ------------------------------------------------------------------------------
; VDP
; ------------------------------------------------------------------------------

VRAM_SIZE		equ $10000				; VRAM size
CRAM_SIZE		equ $80					; CRAM size
VSRAM_SIZE		equ $50					; VSRAM size

VDP_PORTS		equ $C00000				; Ports
VDP_DATA		equ $C00000				; Data port
VDP_CTRL		equ $C00004				; Control port
VDP_HV			equ $C00008				; H/V counter
VDP_DEBUG		equ $C0000C				; Debug register

VDP_REGS		equ $8000				; Registers
VDP_MODE_SET_1		equ $8000				; Mode set 1
VDP_MODE_SET_2		equ $8100				; Mode set 2
VDP_PLANE_A_ADDR	equ $8200				; Plane A address
VDP_WINDOW_ADDR		equ $8300				; Window plane address
VDP_PLANE_B_ADDR	equ $8400				; Plane B address
VDP_SPRITES_ADDR	equ $8500				; Sprite table address
VDP_BG_COLOR		equ $8700				; Background color
VDP_HBLANK		equ $8A00				; H-BLANK interrupt counter
VDP_MODE_SET_3		equ $8B00				; Mode set 3
VDP_MODE_SET_4		equ $8C00				; Mode set 4
VDP_HSCROLL_ADDR	equ $8D00				; Horizontal scroll table address
VDP_AUTO_INC		equ $8F00				; Auto-increment
VDP_PLANE_SIZE		equ $9000				; Plane size
VDP_WINDOW_H		equ $9100				; Horizontal window position
VDP_WINDOW_B		equ $9200				; Vertical window position
VDP_DMA_LEN_L		equ $9300				; DMA length (low)
VDP_DMA_LEN_H		equ $9400				; DMA length (high)
VDP_DMA_SRC_L		equ $9500				; DMA source address (low)
VDP_DMA_SRC_M		equ $9600				; DMA source address (middle)
VDP_DMA_SRC_H		equ $9700				; DMA source address (high)

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
VDPR_SZ_32_32		equ %00000000				; 32x32 tile plane size
VDPR_SZ_64_32		equ %00000001				; 64x32 tile plane size
VDPR_SZ_128_32		equ %00000011				; 128x32 tile plane size
VDPR_SZ_32_64		equ %00010000				; 32x64 tile plane size
VDPR_SZ_64_64		equ %00010001				; 64x64 tile plane size
VDPR_SZ_32_128		equ %00110000				; 32x128 tile plane size

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
VDPR_LGL_68K_SHIFT	equ 1

VDPR_LGH_BIT		equ 0					; DMA length (high)
VDPR_LGH		equ %11111111
VDPR_LGH_SHIFT		equ 8
VDPR_LGH_68K_SHIFT	equ 9

VDPR_SAL_BIT		equ 0					; DMA source address (low)
VDPR_SAL		equ %11111111
VDPR_SAL_68K_SHIFT	equ 1

VDPR_SAM_BIT		equ 0					; DMA source address (middle)
VDPR_SAM		equ %11111111
VDPR_SAM_SHIFT		equ 8
VDPR_SAM_68K_SHIFT	equ 9

VDPR_SAH_BIT		equ 0					; DMA source address (high)
VDPR_SAH		equ %00111111
VDPR_SAH_SHIFT		equ 16
VDPR_SAH_68K		equ %01111111
VDPR_SAH_68K_SHIFT	equ 17
VDPR_DMD_BIT		equ 6					; DMA mode
VDPR_DMD		equ %11000000
VDPR_DMD_68K		equ %00000000				; DMA from 68000 memory mode
VDPR_DMD_FILL		equ %10000000				; VRAM fill mode
VDPR_DMD_COPY		equ %11000000				; VRAM copy mode

; ------------------------------------------------------------------------------
; PSG
; ------------------------------------------------------------------------------

PSG_CTRL		equ $C00011				; Control port

PSG_CH_BIT		equ 5					; Channel ID
PSG_CH			equ %01100000
PSG_CH1			equ %00000000				; Channel 1
PSG_CH2			equ %00100000				; Channel 2
PSG_CH3			equ %01000000				; Channel 3
PSG_CH4			equ %01100000				; Channel 4

PSGR_ATTEN_BIT		equ 0					; Attenuation
PSGR_ATTEN		equ %00001111
PSGR_ATTEN_SET		equ %10010000				; Attenuation set
PSGR_ATTEN_SET_1	equ %10010000				; Channel 1 attenuation set
PSGR_ATTEN_SET_2	equ %10110000				; Channel 2 attenuation set
PSGR_ATTEN_SET_3	equ %11010000				; Channel 3 attenuation set
PSGR_ATTEN_SET_4	equ %11110000				; Channel 4 attenuation set

PSGR_FREQ_L_BIT		equ 0					; Frequency (low)
PSGR_FREQ_L		equ %00001111
PSGR_FREQ_SET		equ %10000000				; Frequency set
PSGR_FREQ_SET_1		equ %10000000				; Channel 1 frequency set
PSGR_FREQ_SET_2		equ %10100000				; Channel 2 frequency set
PSGR_FREQ_SET_3		equ %11000000				; Channel 3 frequency set

PSGR_FREQ_H_BIT		equ 0					; Frequency (high)
PSGR_FREQ_H		equ %00111111
PSGR_FREQ_H_SHIFT	equ 4

PSGR_NOISE_SET		equ %11100000				; Noise set
PSGR_NF_BIT		equ 0					; Noise frequency
PSGR_NF			equ %00000011
PSGR_NF_CLOCK_2		equ %00000000				; Clock/2 noise frequency
PSGR_NF_CLOCK_4		equ %00000001				; Clock/2 noise frequency
PSGR_NF_CLOCK_8		equ %00000010				; Clock/2 noise frequency
PSGR_NF_CH3		equ %00000011				; Channel 3 frequency
PSGR_FB_BIT		equ 2					; Noise type
PSGR_FB			equ %00000100
PSGR_FB_PERIODIC	equ %00000000				; Periodic noise
PSGR_FB_WHITE		equ %00000100				; White noise

; ------------------------------------------------------------------------------
; Work RAM
; ------------------------------------------------------------------------------

WORK_RAM		equ $FFFF0000				; Work RAM start
WORK_RAM_SIZE		equ $10000				; Work RAM size
WORK_RAM_END		equ $FFFFFFFF				; Work RAM end

; ------------------------------------------------------------------------------
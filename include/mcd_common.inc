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

SRAMR_ENABLE_BIT	equ 0					; SRAM enable
SRAMR_ENABLE		equ %00000001
SRAMR_PROTECT_BIT	equ 1					; SRAM write protection
SRAMR_PROTECT		equ %00000010
	endif
	
; ------------------------------------------------------------------------------
; Mapper (mode 1)
; ------------------------------------------------------------------------------

	if (CONFIG_MCD_MODE=USE_MCD_MODE_1)&(CONFIG_MAPPER=USE_MAPPER)
CART_BANK_SIZE		equ $80000				; Cartridge bank size

CART_BANK_COUNT		equ 8					; Cartridge bank count
CART_FIXED_COUNT	equ 1					; Fixed cartridge bank count
CART_SWAP_COUNT		equ 7					; Swappable cartridge bank count
	endif

; ------------------------------------------------------------------------------
; RAM cartridge (mode 2)
; ------------------------------------------------------------------------------

	if CONFIG_MCD_MODE=USE_MCD_MODE_2
RAM_CART_SIZE		equ $80000				; RAM cartridge data size
	endif
	
; ------------------------------------------------------------------------------
; Expansion
; ------------------------------------------------------------------------------

EXPANSION_SIZE		equ $400000				; Expansion size

; ------------------------------------------------------------------------------
; Work RAM
; ------------------------------------------------------------------------------

WORK_RAM_SIZE		equ $10000				; Work RAM size

; ------------------------------------------------------------------------------
; VDP
; ------------------------------------------------------------------------------

VRAM_SIZE		equ $10000				; VRAM size
CRAM_SIZE		equ $80					; CRAM size
VSRAM_SIZE		equ $50					; VSRAM size

VDP_REGS		equ $8000				; Registers
VDP_MODE_SET_1		equ $8000|%00000100			; Mode set 1 (with required bit set)
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

VDPR_PAL_BIT		equ 0					; PAL mode
VDPR_PAL		equ %0000000000000001
VDPR_DMA_BIT		equ 1					; DMA busy
VDPR_DMA		equ %0000000000000010
VDPR_HB_BIT		equ 2					; H-BLANK period
VDPR_HB			equ %0000000000000100
VDPR_VB_BIT		equ 3					; V-BLANK period
VDPR_VB			equ %0000000000001000
VDPR_ODD_BIT		equ 4					; Odd interlaced frame
VDPR_ODD		equ %0000000000010000
VDPR_C_BIT		equ 5					; Sprite collision
VDPR_C			equ %0000000000100000
VDPR_SOVR_BIT		equ 6					; Sprite overflow
VDPR_SOVR		equ %0000000001000000
VDPR_F_BIT		equ 7					; V-BLANK interrupt occurrence
VDPR_F			equ %0000000010000000
VDPR_FULL_BIT		equ 8					; FIFO full
VDPR_FULL		equ %0000000100000000
VDPR_EMPT_BIT		equ 9					; FIFO empty
VDPR_EMPT		equ %0000001000000000

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
; YM2612
; ------------------------------------------------------------------------------

YM_CHANNEL_COUNT	equ 6					; Channel count
YM_OP_COUNT		equ 4					; Operator count
YM_FM_COUNT		equ 5					; FM channel count
YM_DAC_COUNT		equ 1					; DAC channel count
YM_BANK_COUNT		equ 2					; Bank count

YM_CH_BIT		equ 0					; Channel ID
YM_CH			equ %00000011
YM_CH14			equ %00000000				; Channel 1/4
YM_CH25			equ %00000001				; Channel 2/5
YM_CH36			equ %00000010				; Channel 3/6
YM_BK_BIT		equ 2					; Channel bank
YM_BK			equ %00000100
YM_BK_0			equ %00000000				; Channel bank 0
YM_BK_1			equ %00000100				; Channel bank 1
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

YMR_BUSY_BIT		equ 7					; Busy
YMR_BUSY		equ %10000000

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
; PSG
; ------------------------------------------------------------------------------

PSG_CHANNEL_COUNT	equ 4					; Channel count
PSG_PULSE_COUNT		equ 3					; Pulse channel count
PSG_NOISE_COUNT		equ 1					; Noise channel count

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
; I/O
; ------------------------------------------------------------------------------

IO_PORT_COUNT		equ 3					; I/O port count

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
; Z80
; ------------------------------------------------------------------------------

Z80_RAM_SIZE		equ $2000				; Z80 RAM size

Z80R_BREQ_BIT		equ 0					; Z80 bus request
Z80R_BREQ		equ %00000001

Z80R_RREQ_BIT		equ 0					; Z80 reset request
Z80R_RREQ		equ %00000001

; ------------------------------------------------------------------------------
; BIOS
; ------------------------------------------------------------------------------

BIOS_SIZE		equ $20000				; BIOS size

; ------------------------------------------------------------------------------
; Program RAM
; ------------------------------------------------------------------------------

PRG_RAM_SIZE		equ $80000				; Program RAM size
PRG_RAM_BANK_SIZE	equ $20000				; Program RAM bank size

PRG_RAM_BANK_COUNT	equ 4					; Program RAM bank count

; ------------------------------------------------------------------------------
; Word RAM
; ------------------------------------------------------------------------------

WORD_RAM_1M_SIZE	equ $20000				; Word RAM size (1M/1M)
WORD_RAM_2M_SIZE	equ $40000				; Word RAM size (2M)
WORD_RAM_VRAM_SIZE	equ $20000				; Word RAM VRAM image size (1M/1M)
WORD_RAM_PIXEL_SIZE	equ $40000				; Word RAM pixel image size (1M/1M)

; ------------------------------------------------------------------------------
; PCM
; ------------------------------------------------------------------------------

PCM_CHANNEL_COUNT	equ 8					; Channel count

PCM_CH_BIT		equ 0					; Channel ID
PCM_CH			equ %00000111
PCM_CH1			equ %00000000				; Channel 1
PCM_CH2			equ %00000001				; Channel 2
PCM_CH3			equ %00000010				; Channel 3
PCM_CH4			equ %00000011				; Channel 4
PCM_CH5			equ %00000100				; Channel 5
PCM_CH6			equ %00000101				; Channel 6
PCM_CH7			equ %00000110				; Channel 7
PCM_CH8			equ %00000111				; Channel 8

PCMR_WB_BIT		equ 0					; Wave RAM bank ID
PCMR_WB			equ %00001111
PCMR_CB_BIT		equ 0					; Channel ID
PCMR_CB			equ %00000111
PCMR_MOD_BIT		equ 6					; Control selection
PCMR_MOD		equ %01000000
PCMR_MOD_WAVE		equ %00000000				; Wave RAM bank selection mode
PCMR_MOD_CHAN		equ %01000000				; Channel selection mode
PCMR_ON_OFF_BIT		equ 7					; Chip on/off
PCMR_ON_OFF		equ %10000000
PCMR_OFF		equ %00000000				; Chip off
PCMR_ON			equ %10000000				; Chip on

PCMR_ST_BIT		equ 0					; Start address
PCMR_ST			equ %11111111
PCMR_ST_SHIFT		equ 8

PCMR_LSH_BIT		equ 0					; Loop address (high)
PCMR_LSH		equ %11111111
PCMR_LSH_SHIFT		equ 8

PCMR_LSL_BIT		equ 0					; Loop address (low)
PCMR_LSL		equ %11111111

PCMR_FDH_BIT		equ 0					; Frequency (high)
PCMR_FDH		equ %11111111
PCMR_FDH_SHIFT		equ 8

PCMR_FDL_BIT		equ 0					; Frequency (low)
PCMR_FDL		equ %11111111

PCMR_L_BIT		equ 0					; Panning (left)
PCMR_L			equ %00001111
PCMR_R_BIT		equ 4					; Panning (right)
PCMR_R			equ %00001111

PCMR_EN1_BIT		equ 0					; Channel 1 enable
PCMR_EN1		equ %00000001
PCMR_EN2_BIT		equ 1					; Channel 2 enable
PCMR_EN2		equ %00000010
PCMR_EN3_BIT		equ 2					; Channel 3 enable
PCMR_EN3		equ %00000100
PCMR_EN4_BIT		equ 3					; Channel 4 enable
PCMR_EN4		equ %00001000
PCMR_EN5_BIT		equ 4					; Channel 5 enable
PCMR_EN5		equ %00010000
PCMR_EN6_BIT		equ 5					; Channel 6 enable
PCMR_EN6		equ %00100000
PCMR_EN7_BIT		equ 6					; Channel 7 enable
PCMR_EN7		equ %01000000
PCMR_EN8_BIT		equ 7					; Channel 8 enable
PCMR_EN8		equ %10000000

; ------------------------------------------------------------------------------
; Wave RAM
; ------------------------------------------------------------------------------

WAVE_RAM_SIZE		equ $10000				; Wave RAM size
WAVE_RAM_BANK_SIZE	equ $1000				; Wave RAM bank size

WAVE_RAM_BANK_COUNT	equ 16					; Wave RAM bank count

WAVE_BK_BIT		equ 0					; Wave RAM bank ID
WAVE_BK			equ %00001111
WAVE_BK_0		equ %00000000				; Wave RAM bank 0
WAVE_BK_1		equ %00000001				; Wave RAM bank 1
WAVE_BK_2		equ %00000010				; Wave RAM bank 2
WAVE_BK_3		equ %00000011				; Wave RAM bank 3
WAVE_BK_4		equ %00000100				; Wave RAM bank 4
WAVE_BK_5		equ %00000101				; Wave RAM bank 5
WAVE_BK_6		equ %00000110				; Wave RAM bank 6
WAVE_BK_7		equ %00000111				; Wave RAM bank 7
WAVE_BK_8		equ %00001000				; Wave RAM bank 8
WAVE_BK_9		equ %00001001				; Wave RAM bank 9
WAVE_BK_10		equ %00001010				; Wave RAM bank 10
WAVE_BK_11		equ %00001011				; Wave RAM bank 11
WAVE_BK_12		equ %00001100				; Wave RAM bank 12
WAVE_BK_13		equ %00001101				; Wave RAM bank 13
WAVE_BK_14		equ %00001110				; Wave RAM bank 14
WAVE_BK_15		equ %00001111				; Wave RAM bank 15

; ------------------------------------------------------------------------------
; Mega CD
; ------------------------------------------------------------------------------

MSCSTOP			equ 2					; Stop CD audio
MSCPAUSEON		equ 3					; Pause CD audio
MSCPAUSEOFF		equ 4					; Unpause CD audio
MSCSCANFF		equ 5					; Fast forward CD audio
MSCSCANFR		equ 6					; Fast reverse CD audio
MSCSCANOFF		equ 7					; Stop CD audio scan
ROMPAUSEON		equ 8					; Pause CD data read
ROMPAUSEOFF		equ 9					; Unpause CD data read
DRVOPEN			equ $A					; Open CD tray
DRVINIT			equ $10					; Close CD tray and initialize
MSCPLAY			equ $11					; Play CD audio
MSCPLAY1		equ $12					; Play CD audio track once
MSCPLAYR		equ $13					; Loop CD audio track
MSCPLAYT		equ $14					; Play CD audio at time
MSCSEEK			equ $15					; Seek to CD audio track
MSCSEEKT		equ $16					; Seek to CD audio time
ROMREAD			equ $17					; Start reading CD data
ROMSEEK			equ $18					; Seek to CD sector
MSCSEEK1		equ $19					; Seek to CD audio track and play once
ROMREADN		equ $20					; Read number of CD sectors
ROMREADE		equ $21					; Read range of CD sectors
CDBCHK			equ $80					; Check if command has been received
CDBSTAT			equ $81					; Check status
CDBTOCWRITE		equ $82					; Write TOC
CDBTOCREAD		equ $83					; Read TOC
CDBPAUSE		equ $84					; Set pause to standby timer
FDRSET			equ $85					; Set CD audio volume
FDRCHG			equ $86					; Fade CD audio
CDCSTART		equ $87					; Start CD data read from current sector
CDCSTOP			equ $89					; Stop CD data read
CDCSTAT			equ $8A					; Check if CD data is ready
CDCREAD			equ $8B					; Prepare CD data transfer
CDCTRN			equ $8C					; Transfer CD data (SUB CPU read mode only)
CDCACK			equ $8D					; Finish CD data transfer
SCDINIT			equ $8E					; Initialize subcode read
SCDSTART		equ $8F					; Start subcode read
SCDSTOP			equ $90					; Stop subcode read
SCDSTAT			equ $91					; Check if subcode is ready
SCDREAD			equ $92					; Read subcode
SCDPQ			equ $93					; Get P/Q code from subcode
SCDPQL			equ $94					; Get last P/Q code from subcode
LEDSET			equ $95					; Set LED mode

CBTINIT			equ 0					; Initialize boot system
CBTINT			equ 1					; Manage boot interrupt
CBTOPENDISC		equ 2					; Request disc tray open
CBTOPENSTAT		equ 3					; Check if disc tray open was completed
CBTCHKDISC		equ 4					; Check if disc is bootable
CBTCHKSTAT		equ 5					; Check boot and get disc type

BRMINIT			equ 0					; Initialize Backup RAM interaction
BRMSTAT			equ 1					; Get Backup RAM status
BRMSERCH		equ 2					; Search Backup RAM
BRMREAD			equ 3					; Read Backup RAM data
BRMWRITE		equ 4					; Write Backup RAM data
BRMDEL			equ 5					; Delete Backup RAM data
BRMFORMAT		equ 6					; Format Backup RAM
BRMDIR			equ 7					; Get Backup RAM directory
BRMVERIFY		equ 8					; Verify written Backup RAM data

STAMP_SNO_BIT		equ 0					; Stamp ID
STAMP_SNO		equ %0000011111111111
STAMP_SNO_16		equ %0000011111111111			; Stamp ID (16x16 stamps)
STAMP_SNO_32		equ %0000011111111100			; Stamp ID (32x32 stamps)
STAMP_RT_BIT		equ $D					; Rotation
STAMP_RT		equ %0110000000000000
STAMP_RT_0		equ %0000000000000000			; 0 degree rotation
STAMP_RT_90		equ %0010000000000000			; 90 degree rotation
STAMP_RT_180		equ %0100000000000000			; 180 degree rotation
STAMP_RT_270		equ %0110000000000000			; 270 degree rotation
STAMP_HFLP_BIT		equ $F					; Horizontal flip
STAMP_HFLP		equ %1000000000000000

TRACE_PX_BIT		equ 0					; X start fractional part
TRACE_PX		equ %0000000000000111
TRACE_X_BIT		equ 3					; X start integer part
TRACE_X			equ %1111111111111000
TRACE_X_SHIFT		equ 5
TRACE_PY_BIT		equ 0					; Y start fractional part
TRACE_PY		equ %0000000000000111
TRACE_Y_BIT		equ 3					; Y start integer part
TRACE_Y			equ %1111111111111000
TRACE_Y_SHIFT		equ 5
TRACE_DPX_BIT		equ 0					; X delta fractional part
TRACE_DPX		equ %0000011111111111
TRACE_DX_BIT		equ 0					; X delta integer part
TRACE_DX		equ %1111100000000000
TRACE_DX_SHIFT		equ 3
TRACE_DY_BIT		equ 0					; Y delta integer part
TRACE_DY		equ %1111100000000000
TRACE_DY_SHIFT		equ 3

MCDR_IFL2_BIT		equ 0					; Mega Drive interrupt request
MCDR_IFL2		equ %00000001
MCDR_MIE2_BIT		equ 7					; Mega Drive interrupt enabled
MCDR_MIE2		equ %10000000

MCDR_LEDR_BIT		equ 0					; Red LED
MCDR_LEDR		equ %00000001
MCDR_LEDG_BIT		equ 1					; Green LED
MCDR_LEDG		equ %00000010

MCDR_SRES_BIT		equ 0					; Sub CPU reset
MCDR_SRES		equ %00000001
MCDR_SBRQ_BIT		equ 1					; Sub CPU bus request
MCDR_SBRQ		equ %00000010

MCDR_RES0_BIT		equ 0					; Reset
MCDR_RES0		equ %00000001
MCDR_VER_BIT		equ 4					; Version
MCDR_VER		equ %11110000

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
MCDR_PM_BIT		equ 3					; Word RAM priority mode
MCDR_PM			equ %00011000
MCDR_PM_OFF		equ %00000000				; Word RAM priority off
MCDR_PM_UNDER		equ %00001000				; Word RAM underwrite mode
MCDR_PM_OVER		equ %00010000				; Word RAM overwrite mode

MCDR_DD_BIT		equ 0					; CDC device destination
MCDR_DD			equ %00000111
MCDR_DD_HOST_MAIN	equ %00000010				; Host register (Main CPU read)
MCDR_DD_HOST_SUB	equ %00000011				; Host register (Sub CPU read)
MCDR_DD_WAVE_RAM	equ %00000100				; Wave RAM (DMA)
MCDR_DD_PRG_RAM		equ %00000101				; Program RAM (DMA)
MCDR_DD_WORD_RAM	equ %00000111				; Word RAM (DMA)
MCDR_UBR_BIT		equ 5					; Upper byte ready
MCDR_UBR		equ %00100000
MCDR_DSR_BIT		equ 6					; Data set ready
MCDR_DSR		equ %01000000
MCDR_EDT_BIT		equ 7					; End of data transfer
MCDR_EDT		equ %10000000

MCDR_HIB_BIT		equ 0					; H-BLANK interrupt address (Main CPU, mode 2)
MCDR_HIB		equ %1111111111111111

MCDR_CA_BIT		equ 0					; CDC register address
MCDR_CA			equ %00001111

MCDR_CD_BIT		equ 0					; CDC register data
MCDR_CD			equ %11111111

MCDR_HD_BIT		equ 0					; CDC host data
MCDR_HD			equ %1111111111111111

MCDR_DMA_BIT		equ 0					; CDC DMA address
MCDR_DMA		equ %1111111111111111
MCDR_DMA_SHIFT		equ 3

MCDR_SW_BIT		equ 0					; Stopwatch value
MCDR_SW			equ %0000111111111111

MCDR_CFM_BIT		equ 0					; Main CPU communication flag
MCDR_CFM		equ %11111111

MCDR_CFS_BIT		equ 0					; Sub CPU communication flag
MCDR_CFS		equ %11111111

MCDR_CCM_BIT		equ 0					; Main CPU communication value
MCDR_CCM		equ %11111111

MCDR_CST_BIT		equ 0					; Sub CPU communication value
MCDR_CST		equ %11111111

MCDR_TD_BIT		equ 0					; Timer interrupt timer
MCDR_TD			equ %11111111

MCDR_IEN1_BIT		equ 1					; Graphics interrupt enable
MCDR_IEN1		equ %00000010
MCDR_IEN2_BIT		equ 2					; Mega Drive interrupt enable
MCDR_IEN2		equ %00000100
MCDR_IEN3_BIT		equ 3					; Timer interrupt enable
MCDR_IEN3		equ %00001000
MCDR_IEN4_BIT		equ 4					; CDD interrupt enable
MCDR_IEN4		equ %00010000
MCDR_IEN5_BIT		equ 5					; CDC interrupt enable
MCDR_IEN5		equ %00100000
MCDR_IEN6_BIT		equ 6					; Subcode interrupt enable
MCDR_IEN6		equ %01000000

MCDR_DEF_BIT		equ 2					; De-emphasis
MCDR_DEF		equ %0000000000001100
MCDR_DEF_OFF		equ %0000000000000000			; De-emphasis off
MCDR_DEF_44		equ %0000000000000100			; 44.1 kHz de-emphasis
MCDR_DEF_32		equ %0000000000001000			; 32 kHz de-emphasis
MCDR_DEF_48		equ %0000000000001100			; 48 kHz de-emphasis
MCDR_FD_BIT		equ 4					; Fader volume
MCDR_FD			equ %0111111111110000
MCDR_EFDT_BIT		equ 15					; End of fade data transfer
MCDR_EFDT		equ %1000000000000000

MCDR_DM_BIT		equ 0					; CDC data type
MCDR_DM			equ %00000001
MCDR_DM_MUSIC		equ %00000000				; Music data type
MCDR_DM_ROM		equ %00000001				; CD-ROM data type

MCDR_DTS_BIT		equ 0					; Data transmission status
MCDR_DTS		equ %00000001
MCDR_DRS_BIT		equ 1					; Data receive status
MCDR_DRS		equ %00000010
MCDR_HOCK_BIT		equ 2					; Host clock
MCDR_HOCK		equ %00000100

MCDR_CDST_BIT		equ 0					; CDD status value
MCDR_CDST		equ %00001111

MCDR_CDCM_BIT		equ 0					; CDD command value
MCDR_CDCM		equ %00001111

MCDR_SC0_BIT		equ 0					; 1BPP conversion color (0)
MCDR_SC0		equ %00001111
MCDR_SC1_BIT		equ 4					; 1BPP conversion color (1)
MCDR_SC1		equ %11110000

MCDR_IDT_BIT		equ 0					; 1BPP conversion input data
MCDR_IDT		equ %1111111111111111

MCDR_ODT_BIT		equ 0					; 1BPP conversion output data
MCDR_ODT		equ %1111111111111111

MCDR_GRON_BIT		equ 7					; Image rendering (2M)
MCDR_GRON		equ %10000000

MCDR_RPT_BIT		equ 0					; Stamp map repeating (2M)
MCDR_RPT		equ %00000001
MCDR_STS_BIT		equ 1					; Stamp size (2M)
MCDR_STS		equ %00000010
MCDR_STS_16		equ %00000000				; 16x16 stamps (2M)
MCDR_STS_32		equ %00000010				; 32x32 stamps (2M)
MCDR_SMS_BIT		equ 2					; Stamp size (2M)
MCDR_SMS		equ %00000100
MCDR_SMS_256		equ %00000000				; 256x2456 stamp map (2M)
MCDR_SMS_4096		equ %00000100				; 4096x4096 stamp map (2M)

MCDR_SMA_BIT		equ 0					; Stamp map address (2M)
MCDR_SMA		equ %1111111111100000
MCDR_SMA_SHIFT		equ 2
MCDR_SMA_16_256		equ %1111111110000000			; Stamp map address (16x16 stamps, 256x256 map) (2M)
MCDR_SMA_32_256		equ %1111111111100000			; Stamp map address (32x32 stamps, 256x256 map) (2M)
MCDR_SMA_16_4096	equ %1000000000000000			; Stamp map address (16x16 stamps, 4096x4096 map) (2M)
MCDR_SMA_32_4096	equ %1110000000000000			; Stamp map address (32x32 stamps, 4096x4096 map) (2M)

MCDR_VCS_BIT		equ 0					; Image buffer stride (2M)
MCDR_VCS		equ %00011111

MCDR_IMA_BIT		equ 0					; Image buffer address (2M)
MCDR_IMA		equ %1111111111111000
MCDR_IMA_SHIFT		equ 2

MCDR_DOT_BIT		equ 0					; Image buffer X offset (2M)
MCDR_DOT		equ %00000111
MCDR_LN_BIT		equ 3					; Image buffer Y offset (2M)
MCDR_LN			equ %00111000

MCDR_HW_BIT		equ 0					; Image buffer width (2M)
MCDR_HW			equ %0000000111111111

MCDR_VW_BIT		equ 0					; Image buffer height (2M)
MCDR_VW			equ %0000000011111111

MCDR_TVA_BIT		equ 0					; Trace vector address (2M)
MCDR_TVA		equ %1111111111111110
MCDR_TVA_SHIFT		equ 2

MCDR_STA_BIT		equ 1					; Subcode top address
MCDR_STA		equ %01111110
MCDR_SAOR_BIT		equ 7					; Subcode address overrun
MCDR_SAOR		equ %10000000

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
vramCopy_CMD		equ $000000C0				; VRAM DMA copy

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
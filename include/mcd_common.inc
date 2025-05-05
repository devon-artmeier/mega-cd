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

USE_DOMESTIC_NTSC	equ %0001				; Allow domestic NTSC models
USE_DOMESTIC_PAL	equ %0010				; Allow domestic PAL models
USE_OVERSEAS_NTSC	equ %0100				; Allow overseas NTSC models
USE_OVERSEAS_PAL	equ %1000				; Allow overseas PAL models
USE_DOMESTIC		equ USE_DOMESTIC_NTSC|USE_DOMESTIC_PAL	; Allow domestic models
USE_OVERSEAS		equ USE_OVERSEAS_NTSC|USE_OVERSEAS_PAL	; Allow overseas models
USE_NTSC		equ USE_DOMESTIC_NTSC|USE_OVERSEAS_NTSC	; Allow NTSC models
USE_PAL			equ USE_DOMESTIC_PAL|USE_OVERSEAS_PAL	; Allow PAL models
USE_ALL_MODELS		equ USE_NTSC|USE_PAL			; Allow all models
USE_JAPAN		equ USE_DOMESTIC_NTSC			; Allow Japan models
USE_USA			equ USE_OVERSEAS_NTSC			; Allow USA models
USE_EUROPE		equ USE_OVERSEAS_PAL			; Allow Europe models

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

SRMR_ON_BIT		equ 0					; SRAM enable
SRMR_ON			equ 1<<SRMR_ON_BIT
SRMR_WPR_BIT		equ 1					; SRAM write protection
SRMR_WPR		equ 1<<SRMR_WPR_BIT
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
VDP_REG_BIT		equ 8
VDP_MODE_SET_1		equ VDP_REGS|%100			; Mode set 1 (with required bit set)
VDP_MODE_SET_2		equ VDP_REGS+(1<<VDP_REG_BIT)		; Mode set 2
VDP_PLANE_A_ADDR	equ VDP_REGS+(2<<VDP_REG_BIT)		; Plane A address
VDP_WINDOW_ADDR		equ VDP_REGS+(3<<VDP_REG_BIT)		; Window plane address
VDP_PLANE_B_ADDR	equ VDP_REGS+(4<<VDP_REG_BIT)		; Plane B address
VDP_SPRITES_ADDR	equ VDP_REGS+(5<<VDP_REG_BIT)		; Sprite table address
VDP_BG_COLOR		equ VDP_REGS+(7<<VDP_REG_BIT)		; Background color
VDP_HBLANK		equ VDP_REGS+($A<<VDP_REG_BIT)		; H-BLANK interrupt counter
VDP_MODE_SET_3		equ VDP_REGS+($B<<VDP_REG_BIT)		; Mode set 3
VDP_MODE_SET_4		equ VDP_REGS+($C<<VDP_REG_BIT)		; Mode set 4
VDP_HSCROLL_ADDR	equ VDP_REGS+($D<<VDP_REG_BIT)		; Horizontal scroll table address
VDP_AUTO_INC		equ VDP_REGS+($F<<VDP_REG_BIT)		; Auto-increment
VDP_PLANE_SIZE		equ VDP_REGS+($10<<VDP_REG_BIT)		; Plane size
VDP_WINDOW_H		equ VDP_REGS+($11<<VDP_REG_BIT)		; Horizontal window position
VDP_WINDOW_B		equ VDP_REGS+($12<<VDP_REG_BIT)		; Vertical window position
VDP_DMA_LEN_L		equ VDP_REGS+($13<<VDP_REG_BIT)		; DMA length (low)
VDP_DMA_LEN_H		equ VDP_REGS+($14<<VDP_REG_BIT)		; DMA length (high)
VDP_DMA_SRC_L		equ VDP_REGS+($15<<VDP_REG_BIT)		; DMA source address (low)
VDP_DMA_SRC_M		equ VDP_REGS+($16<<VDP_REG_BIT)		; DMA source address (middle)
VDP_DMA_SRC_H		equ VDP_REGS+($17<<VDP_REG_BIT)		; DMA source address (high)

VDPR_PAL_BIT		equ 0					; PAL mode
VDPR_PAL		equ %1<<VDPR_PAL_BIT
VDPR_DMA_BIT		equ 1					; DMA busy
VDPR_DMA		equ %1<<VDPR_DMA_BIT
VDPR_HB_BIT		equ 2					; H-BLANK period
VDPR_HB			equ %1<<VDPR_HB_BIT
VDPR_VB_BIT		equ 3					; V-BLANK period
VDPR_VB			equ %1<<VDPR_VB_BIT
VDPR_ODD_BIT		equ 4					; Odd interlaced frame
VDPR_ODD		equ %1<<VDPR_ODD_BIT
VDPR_C_BIT		equ 5					; Sprite collision
VDPR_C			equ %1<<VDPR_C_BIT
VDPR_SOVR_BIT		equ 6					; Sprite overflow
VDPR_SOVR		equ %1<<VDPR_SOVR_BIT
VDPR_F_BIT		equ 7					; V-BLANK interrupt occurrence
VDPR_F			equ %1<<VDPR_F_BIT
VDPR_FULL_BIT		equ 8					; FIFO full
VDPR_FULL		equ %1<<VDPR_FULL_BIT
VDPR_EMPT_BIT		equ 9					; FIFO empty
VDPR_EMPT		equ %1<<VDPR_EMPT_BIT

VDPR_M3_BIT		equ 1					; H/V counter latch
VDPR_M3			equ %1<<VDPR_M3_BIT
VDPR_IE1_BIT		equ 4					; H-BLANK interrupt enable
VDPR_IE1		equ %1<<VDPR_IE1_BIT
VDPR_LCB_BIT		equ 5					; Blank leftmost 8 pixels
VDPR_LCB		equ %1<<VDPR_LCB_BIT

VDPR_M5_BIT		equ 2					; Genesis/Mega Drive mode
VDPR_M5			equ %1<<VDPR_M5_BIT
VDPR_M2_BIT		equ 3					; V30 mode
VDPR_M2			equ %1<<VDPR_M2_BIT
VDPR_M1_BIT		equ 4					; DMA enable
VDPR_M1			equ %1<<VDPR_M1_BIT
VDPR_IE0_BIT		equ 5					; V-BLANK interrupt enable
VDPR_IE0		equ %1<<VDPR_IE0_BIT
VDPR_DISP_BIT		equ 6					; Display enable
VDPR_DISP		equ %1<<VDPR_DISP_BIT

VDPR_SA_BIT		equ 0					; Plane A address
VDPR_SA			equ %111000<<VDPR_SA_BIT
VDPR_SA_SHIFT		equ $A

VDPR_WD_BIT		equ 0					; Window plane address
VDPR_WD			equ %111110<<VDPR_WD_BIT
VDPR_WD_SHIFT		equ $A

VDPR_SB_BIT		equ 0					; Plane B address
VDPR_SB			equ %111<<VDPR_SB_BIT
VDPR_SB_SHIFT		equ $D

VDPR_AT_BIT		equ 0					; Sprite table aaddress
VDPR_AT			equ %1111111<<VDPR_AT_BIT
VDPR_AT_SHIFT		equ 9

VDPR_COL_BIT		equ 0					; Background color index
VDPR_COL		equ %1111<<VDPR_COL_BIT
VDPR_CPT_BIT		equ 4					; Background color index
VDPR_CPT		equ %11<<VDPR_CPT_BIT

VDPR_HIT_BIT		equ 0					; H-BLANK interrupt counter
VDPR_HIT		equ %11111111<<VDPR_HIT_BIT

VDPR_HSCR_BIT		equ 0					; Horizontal scroll mode
VDPR_HSCR		equ %11<<VDPR_HSCR_BIT
VDPR_HSCR_FULL		equ %00<<VDPR_HSCR_BIT			; Horizontal full screen scroll mode
VDPR_HSCR_TILE		equ %10<<VDPR_HSCR_BIT			; Horizontal tile scroll mode
VDPR_HSCR_LINE		equ %11<<VDPR_HSCR_BIT			; Horizontal line scroll mode
VDPR_VSCR_BIT		equ 2					; Vertical scroll mode
VDPR_VSCR		equ %1<<VDPR_VSCR_BIT
VDPR_VSCR_FULL		equ %0<<VDPR_VSCR_BIT			; Vertical full screen scroll mode
VDPR_VSCR_TILE		equ %1<<VDPR_VSCR_BIT			; Vertical tile scroll mode
VDPR_IE2_BIT		equ 3					; External interrupt enable
VDPR_IE2		equ %1<<VDPR_IE2_BIT

VDPR_RS1_BIT		equ 0					; H40 mode (low bit)
VDPR_RS1		equ %1<<VDPR_RS1_BIT
VDPR_LSM_BIT		equ 1					; Interlace mode
VDPR_LSM		equ %11<<VDPR_LSM_BIT
VDPR_LSM_OFF		equ %00<<VDPR_LSM_BIT			; Interlace mode off
VDPR_LSM_ON		equ %01<<VDPR_LSM_BIT			; Interlace mode on
VDPR_LSM_DOUBLE		equ %11<<VDPR_LSM_BIT			; Interlace mode on (double)
VDPR_STE_BIT		equ 3					; Shadow/highlight mode
VDPR_STE		equ %1<<VDPR_STE_BIT
VDPR_RS0_BIT		equ 7					; H40 mode (high bit)
VDPR_RS0		equ %1<<VDPR_RS0_BIT
VDPR_RS			equ VDPR_RS0|VDPR_RS1			; H40 mode (bits combined)

VDPR_HS_BIT		equ 0					; Horizontal scroll table address
VDPR_HS			equ %111111<<VDPR_HS_BIT
VDPR_HS_SHIFT		equ $A

VDPR_INC_BIT		equ 0					; Auto-increment
VDPR_INC		equ %11111111<<VDPR_INC_BIT

VDPR_HSZ_BIT		equ 0					; Horizontal plane size
VDPR_HSZ		equ %11<<VDPR_HSZ_BIT
VDPR_HSZ_32		equ %00<<VDPR_HSZ_BIT			; 32 tile horizontal plane size
VDPR_HSZ_64		equ %01<<VDPR_HSZ_BIT			; 64 tile horizontal plane size
VDPR_HSZ_128		equ %11<<VDPR_HSZ_BIT			; 128 tile horizontal plane size
VDPR_VSZ_BIT		equ 4					; Vertical plane size
VDPR_VSZ		equ %11<<VDPR_VSZ_BIT
VDPR_VSZ_32		equ %00<<VDPR_VSZ_BIT			; 32 tile vertical plane size
VDPR_VSZ_64		equ %01<<VDPR_VSZ_BIT			; 64 tile vertical plane size
VDPR_VSZ_128		equ %11<<VDPR_VSZ_BIT			; 128 tile vertical plane size
VDPR_SZ_32_32		equ VDPR_HSZ_32|VDPR_VSZ_32		; 32x32 tile plane size
VDPR_SZ_64_32		equ VDPR_HSZ_64|VDPR_VSZ_32		; 64x32 tile plane size
VDPR_SZ_128_32		equ VDPR_HSZ_128|VDPR_VSZ_32		; 128x32 tile plane size
VDPR_SZ_32_64		equ VDPR_HSZ_32|VDPR_VSZ_64		; 32x64 tile plane size
VDPR_SZ_64_64		equ VDPR_HSZ_64|VDPR_VSZ_64		; 64x64 tile plane size
VDPR_SZ_32_128		equ VDPR_HSZ_32|VDPR_VSZ_128		; 32x128 tile plane size

VDPR_WHP_BIT		equ 0					; Window plane horizontal position
VDPR_WHP		equ %11111<<VDPR_WHP_BIT
VDPR_RIGT_BIT		equ 7					; Window plane right direction
VDPR_RIGT		equ %1<<VDPR_RIGT_BIT

VDPR_WVP_BIT		equ 0					; Window plane vertical position
VDPR_WVP		equ %11111<<VDPR_WVP_BIT
VDPR_DOWN_BIT		equ 7					; Window plane down direction
VDPR_DOWN		equ %1<<VDPR_DOWN_BIT

VDPR_LGL_BIT		equ 0					; DMA length (low)
VDPR_LGL		equ %11111111<<VDPR_LGL_BIT
VDPR_LGL_68K_SHIFT	equ 1

VDPR_LGH_BIT		equ 0					; DMA length (high)
VDPR_LGH		equ %11111111<<VDPR_LGH_BIT
VDPR_LGH_SHIFT		equ 8
VDPR_LGH_68K_SHIFT	equ 9

VDPR_SAL_BIT		equ 0					; DMA source address (low)
VDPR_SAL		equ %11111111<<VDPR_SAL_BIT
VDPR_SAL_68K_SHIFT	equ 1

VDPR_SAM_BIT		equ 0					; DMA source address (middle)
VDPR_SAM		equ %11111111<<VDPR_SAM_BIT
VDPR_SAM_SHIFT		equ 8
VDPR_SAM_68K_SHIFT	equ 9

VDPR_SAH_BIT		equ 0					; DMA source address (high)
VDPR_SAH		equ %0111111<<VDPR_SAH_BIT
VDPR_SAH_SHIFT		equ 16
VDPR_SAH_68K		equ %1111111<<VDPR_SAH_BIT
VDPR_SAH_68K_SHIFT	equ 17
VDPR_DMD_BIT		equ 6					; DMA mode
VDPR_DMD		equ %11<<VDPR_DMD_BIT
VDPR_DMD_68K		equ %00<<VDPR_DMD_BIT			; DMA from 68000 memory mode
VDPR_DMD_FILL		equ %10<<VDPR_DMD_BIT			; VRAM fill mode
VDPR_DMD_COPY		equ %11<<VDPR_DMD_BIT			; VRAM copy mode

; ------------------------------------------------------------------------------
; YM2612
; ------------------------------------------------------------------------------

YM_CHANNEL_COUNT	equ 6					; Channel count
YM_OPERATOR_COUNT	equ 4					; Operator count
YM_FM_COUNT		equ 5					; FM channel count
YM_DAC_COUNT		equ 1					; DAC channel count
YM_BANK_COUNT		equ 2					; Bank count

YM_CH_BIT		equ 0					; Channel ID
YM_CH			equ %11<<YM_CH_BIT
YM_CH14			equ %00<<YM_CH_BIT			; Channel 1/4
YM_CH25			equ %01<<YM_CH_BIT			; Channel 2/5
YM_CH36			equ %10<<YM_CH_BIT			; Channel 3/6
YM_BK_BIT		equ 2					; Channel bank
YM_BK			equ %1<<YM_BK_BIT
YM_BK_0			equ %0<<YM_BK_BIT			; Channel bank 0
YM_BK_1			equ %1<<YM_BK_BIT			; Channel bank 1
YM_CH1			equ YM_CH14|YM_BK_0			; Channel 1
YM_CH2			equ YM_CH25|YM_BK_0			; Channel 2
YM_CH3			equ YM_CH36|YM_BK_0			; Channel 3
YM_CH4			equ YM_CH14|YM_BK_1			; Channel 4
YM_CH5			equ YM_CH25|YM_BK_1			; Channel 5
YM_CH6			equ YM_CH36|YM_BK_1			; Channel 6
YM_OP1			equ 0					; OP1
YM_CH14_OP1		equ YM_OP1|YM_CH14			; CH1/4 OP1
YM_CH25_OP1		equ YM_OP1|YM_CH25			; CH2/5 OP1
YM_CH36_OP1		equ YM_OP1|YM_CH36			; CH3/6 OP1
YM_OP3			equ 4					; OP3
YM_CH14_OP3		equ YM_OP3|YM_CH14			; CH1/4 OP3
YM_CH25_OP3		equ YM_OP3|YM_CH25			; CH2/5 OP3
YM_CH36_OP3		equ YM_OP3|YM_CH36			; CH3/6 OP3
YM_OP2			equ 8					; OP2
YM_CH14_OP2		equ YM_OP2|YM_CH14			; CH1/4 OP2
YM_CH25_OP2		equ YM_OP2|YM_CH25			; CH2/5 OP2
YM_CH36_OP2		equ YM_OP2|YM_CH36			; CH3/6 OP2
YM_OP4			equ $C					; OP4
YM_CH14_OP4		equ YM_OP4|YM_CH14			; CH1/4 OP4
YM_CH25_OP4		equ YM_OP4|YM_CH25			; CH2/5 OP4
YM_CH36_OP4		equ YM_OP4|YM_CH36			; CH3/6 OP4

YM_LFO			equ $22					; LFO
YM_TIMER_A_H		equ $24					; Timer A (high)
YM_TIMER_A_L		equ $25					; Timer A (low)
YM_TIMER_B		equ $26					; Timer B
YM_CH3_TIMERS		equ $27					; Channel 3 mode and timer control
YM_KEY_ON		equ $28					; Key on/off
YM_DAC_OUT		equ $2A					; DAC output
YM_DAC_ENABLE		equ $2B					; DAC enable
YM_MUL_DT		equ $30					; Multiply and detune
YM_MUL_DT_OP1		equ YM_MUL_DT|YM_OP1			; Multiply and detune (OP1)
YM_MUL_DT_CH14_OP1	equ YM_MUL_DT|YM_CH14_OP1		; Multiply and detune (CH1/4 OP1)
YM_MUL_DT_CH25_OP1	equ YM_MUL_DT|YM_CH25_OP1		; Multiply and detune (CH2/5 OP1)
YM_MUL_DT_CH36_OP1	equ YM_MUL_DT|YM_CH36_OP1		; Multiply and detune (CH3/6 OP1)
YM_MUL_DT_OP3		equ YM_MUL_DT|YM_OP3			; Multiply and detune (OP3)
YM_MUL_DT_CH14_OP3	equ YM_MUL_DT|YM_CH14_OP3		; Multiply and detune (CH1/4 OP3)
YM_MUL_DT_CH25_OP3	equ YM_MUL_DT|YM_CH25_OP3		; Multiply and detune (CH2/5 OP3)
YM_MUL_DT_CH36_OP3	equ YM_MUL_DT|YM_CH36_OP3		; Multiply and detune (CH3/6 OP3)
YM_MUL_DT_OP2		equ YM_MUL_DT|YM_OP2			; Multiply and detune (OP2)
YM_MUL_DT_CH14_OP2	equ YM_MUL_DT|YM_CH14_OP2		; Multiply and detune (CH1/4 OP2)
YM_MUL_DT_CH25_OP2	equ YM_MUL_DT|YM_CH25_OP2		; Multiply and detune (CH2/5 OP2)
YM_MUL_DT_CH36_OP2	equ YM_MUL_DT|YM_CH36_OP2		; Multiply and detune (CH3/6 OP2)
YM_MUL_DT_OP4		equ YM_MUL_DT|YM_OP4			; Multiply and detune (OP4)
YM_MUL_DT_CH14_OP4	equ YM_MUL_DT|YM_CH14_OP4		; Multiply and detune (CH1/4 OP4)
YM_MUL_DT_CH25_OP4	equ YM_MUL_DT|YM_CH25_OP4		; Multiply and detune (CH2/5 OP4)
YM_MUL_DT_CH36_OP4	equ YM_MUL_DT|YM_CH36_OP4		; Multiply and detune (CH3/6 OP4)
YM_TL			equ $40					; Total level
YM_TL_OP1		equ YM_TL|YM_OP1			; Total level (OP1)
YM_TL_CH14_OP1		equ YM_TL|YM_CH14_OP1			; Total level (CH1/4 OP1)
YM_TL_CH25_OP1		equ YM_TL|YM_CH25_OP1			; Total level (CH2/5 OP1)
YM_TL_CH36_OP1		equ YM_TL|YM_CH36_OP1			; Total level (CH3/6 OP1)
YM_TL_OP3		equ YM_TL|YM_OP3			; Total level (OP3)
YM_TL_CH14_OP3		equ YM_TL|YM_CH14_OP3			; Total level (CH1/4 OP3)
YM_TL_CH25_OP3		equ YM_TL|YM_CH25_OP3			; Total level (CH2/5 OP3)
YM_TL_CH36_OP3		equ YM_TL|YM_CH36_OP3			; Total level (CH3/6 OP3)
YM_TL_OP2		equ YM_TL|YM_OP2			; Total level (OP2)
YM_TL_CH14_OP2		equ YM_TL|YM_CH14_OP2			; Total level (CH1/4 OP2)
YM_TL_CH25_OP2		equ YM_TL|YM_CH25_OP2			; Total level (CH2/5 OP2)
YM_TL_CH36_OP2		equ YM_TL|YM_CH36_OP2			; Total level (CH3/6 OP2)
YM_TL_OP4		equ YM_TL|YM_OP4			; Total level (OP4)
YM_TL_CH14_OP4		equ YM_TL|YM_CH14_OP4			; Total level (CH1/4 OP4)
YM_TL_CH25_OP4		equ YM_TL|YM_CH25_OP4			; Total level (CH2/5 OP4)
YM_TL_CH36_OP4		equ YM_TL|YM_CH36_OP4			; Total level (CH3/6 OP4)
YM_AR_RS		equ $50					; Attack rate and rate scaling
YM_AR_RS_OP1		equ YM_AR_RS|YM_OP1			; Attack rate and rate scaling (OP1)
YM_AR_RS_CH14_OP1	equ YM_AR_RS|YM_CH14_OP1		; Attack rate and rate scaling (CH1/4 OP1)
YM_AR_RS_CH25_OP1	equ YM_AR_RS|YM_CH25_OP1		; Attack rate and rate scaling (CH2/5 OP1)
YM_AR_RS_CH36_OP1	equ YM_AR_RS|YM_CH36_OP1		; Attack rate and rate scaling (CH3/6 OP1)
YM_AR_RS_OP3		equ YM_AR_RS|YM_OP3			; Attack rate and rate scaling (OP3)
YM_AR_RS_CH14_OP3	equ YM_AR_RS|YM_CH14_OP3		; Attack rate and rate scaling (CH1/4 OP3)
YM_AR_RS_CH25_OP3	equ YM_AR_RS|YM_CH25_OP3		; Attack rate and rate scaling (CH2/5 OP3)
YM_AR_RS_CH36_OP3	equ YM_AR_RS|YM_CH36_OP3		; Attack rate and rate scaling (CH3/6 OP3)
YM_AR_RS_OP2		equ YM_AR_RS|YM_OP2			; Attack rate and rate scaling (OP2)
YM_AR_RS_CH14_OP2	equ YM_AR_RS|YM_CH14_OP2		; Attack rate and rate scaling (CH1/4 OP2)
YM_AR_RS_CH25_OP2	equ YM_AR_RS|YM_CH25_OP2		; Attack rate and rate scaling (CH2/5 OP2)
YM_AR_RS_CH36_OP2	equ YM_AR_RS|YM_CH36_OP2		; Attack rate and rate scaling (CH3/6 OP2)
YM_AR_RS_OP4		equ YM_AR_RS|YM_OP4			; Attack rate and rate scaling (OP4)
YM_AR_RS_CH14_OP4	equ YM_AR_RS|YM_CH14_OP4		; Attack rate and rate scaling (CH1/4 OP4)
YM_AR_RS_CH25_OP4	equ YM_AR_RS|YM_CH25_OP4		; Attack rate and rate scaling (CH2/5 OP4)
YM_AR_RS_CH36_OP4	equ YM_AR_RS|YM_CH36_OP4		; Attack rate and rate scaling (CH3/6 OP4)
YM_DR_AM		equ $60					; Decay rate and AM enable
YM_DR_AM_OP1		equ YM_DR_AM|YM_OP1			; Decay rate and AM enable (OP1)
YM_DR_AM_CH14_OP1	equ YM_DR_AM|YM_CH14_OP1		; Decay rate and AM enable (CH1/4 OP1)
YM_DR_AM_CH25_OP1	equ YM_DR_AM|YM_CH25_OP1		; Decay rate and AM enable (CH2/5 OP1)
YM_DR_AM_CH36_OP1	equ YM_DR_AM|YM_CH36_OP1		; Decay rate and AM enable (CH3/6 OP1)
YM_DR_AM_OP3		equ YM_DR_AM|YM_OP3			; Decay rate and AM enable (OP3)
YM_DR_AM_CH14_OP3	equ YM_DR_AM|YM_CH14_OP3		; Decay rate and AM enable (CH1/4 OP3)
YM_DR_AM_CH25_OP3	equ YM_DR_AM|YM_CH25_OP3		; Decay rate and AM enable (CH2/5 OP3)
YM_DR_AM_CH36_OP3	equ YM_DR_AM|YM_CH36_OP3		; Decay rate and AM enable (CH3/6 OP3)
YM_DR_AM_OP2		equ YM_DR_AM|YM_OP2			; Decay rate and AM enable (OP2)
YM_DR_AM_CH14_OP2	equ YM_DR_AM|YM_CH14_OP2		; Decay rate and AM enable (CH1/4 OP2)
YM_DR_AM_CH25_OP2	equ YM_DR_AM|YM_CH25_OP2		; Decay rate and AM enable (CH2/5 OP2)
YM_DR_AM_CH36_OP2	equ YM_DR_AM|YM_CH36_OP2		; Decay rate and AM enable (CH3/6 OP2)
YM_DR_AM_OP4		equ YM_DR_AM|YM_OP4			; Decay rate and AM enable (OP4)
YM_DR_AM_CH14_OP4	equ YM_DR_AM|YM_CH14_OP4		; Decay rate and AM enable (CH1/4 OP4)
YM_DR_AM_CH25_OP4	equ YM_DR_AM|YM_CH25_OP4		; Decay rate and AM enable (CH2/5 OP4)
YM_DR_AM_CH36_OP4	equ YM_DR_AM|YM_CH36_OP4		; Decay rate and AM enable (CH3/6 OP4)
YM_SR			equ $70					; Sustain rate
YM_SR_OP1		equ YM_SR|YM_OP1			; Sustain rate (OP1)
YM_SR_CH14_OP1		equ YM_SR|YM_CH14_OP1			; Sustain rate (CH1/4 OP1)
YM_SR_CH25_OP1		equ YM_SR|YM_CH25_OP1			; Sustain rate (CH2/5 OP1)
YM_SR_CH36_OP1		equ YM_SR|YM_CH36_OP1			; Sustain rate (CH3/6 OP1)
YM_SR_OP3		equ YM_SR|YM_OP1			; Sustain rate (OP3)
YM_SR_CH14_OP3		equ YM_SR|YM_CH14_OP3			; Sustain rate (CH1/4 OP3)
YM_SR_CH25_OP3		equ YM_SR|YM_CH25_OP3			; Sustain rate (CH2/5 OP3)
YM_SR_CH36_OP3		equ YM_SR|YM_CH36_OP3			; Sustain rate (CH3/6 OP3)
YM_SR_OP2		equ YM_SR|YM_OP1			; Sustain rate (OP2)
YM_SR_CH14_OP2		equ YM_SR|YM_CH14_OP2			; Sustain rate (CH1/4 OP2)
YM_SR_CH25_OP2		equ YM_SR|YM_CH25_OP2			; Sustain rate (CH2/5 OP2)
YM_SR_CH36_OP2		equ YM_SR|YM_CH36_OP2			; Sustain rate (CH3/6 OP2)
YM_SR_OP4		equ YM_SR|YM_OP1			; Sustain rate (OP4)
YM_SR_CH14_OP4		equ YM_SR|YM_CH14_OP4			; Sustain rate (CH1/4 OP4)
YM_SR_CH25_OP4		equ YM_SR|YM_CH25_OP4			; Sustain rate (CH2/5 OP4)
YM_SR_CH36_OP4		equ YM_SR|YM_CH36_OP4			; Sustain rate (CH3/6 OP4)
YM_RR_SL		equ $80					; Release rate and sustain level
YM_RR_SL_OP1		equ YM_RR_SL|YM_OP1			; Release rate and sustain level (OP1)
YM_RR_SL_CH14_OP1	equ YM_RR_SL|YM_CH14_OP1		; Release rate and sustain level (CH1/4 OP1)
YM_RR_SL_CH25_OP1	equ YM_RR_SL|YM_CH25_OP1		; Release rate and sustain level (CH2/5 OP1)
YM_RR_SL_CH36_OP1	equ YM_RR_SL|YM_CH36_OP1		; Release rate and sustain level (CH3/6 OP1)
YM_RR_SL_OP3		equ YM_RR_SL|YM_OP3			; Release rate and sustain level (OP3)
YM_RR_SL_CH14_OP3	equ YM_RR_SL|YM_CH14_OP3		; Release rate and sustain level (CH1/4 OP3)
YM_RR_SL_CH25_OP3	equ YM_RR_SL|YM_CH25_OP3		; Release rate and sustain level (CH2/5 OP3)
YM_RR_SL_CH36_OP3	equ YM_RR_SL|YM_CH36_OP3		; Release rate and sustain level (CH3/6 OP3)
YM_RR_SL_OP2		equ YM_RR_SL|YM_OP2			; Release rate and sustain level (OP2)
YM_RR_SL_CH14_OP2	equ YM_RR_SL|YM_CH14_OP2		; Release rate and sustain level (CH1/4 OP2)
YM_RR_SL_CH25_OP2	equ YM_RR_SL|YM_CH25_OP2		; Release rate and sustain level (CH2/5 OP2)
YM_RR_SL_CH36_OP2	equ YM_RR_SL|YM_CH36_OP2		; Release rate and sustain level (CH3/6 OP2)
YM_RR_SL_OP4		equ YM_RR_SL|YM_OP4			; Release rate and sustain level (OP4)
YM_RR_SL_CH14_OP4	equ YM_RR_SL|YM_CH14_OP4		; Release rate and sustain level (CH1/4 OP4)
YM_RR_SL_CH25_OP4	equ YM_RR_SL|YM_CH25_OP4		; Release rate and sustain level (CH2/5 OP4)
YM_RR_SL_CH36_OP4	equ YM_RR_SL|YM_CH36_OP4		; Release rate and sustain level (CH3/6 OP4)
YM_SSGEG		equ $90					; SSG-EG
YM_SSGEG_OP1		equ YM_SSGEG|YM_OP1			; SSG-EG (OP1)
YM_SSGEG_CH14_OP1	equ YM_SSGEG|YM_CH14_OP1		; SSG-EG (CH1/4 OP1)
YM_SSGEG_CH25_OP1	equ YM_SSGEG|YM_CH25_OP1		; SSG-EG (CH2/5 OP1)
YM_SSGEG_CH36_OP1	equ YM_SSGEG|YM_CH36_OP1		; SSG-EG (CH3/6 OP1)
YM_SSGEG_OP3		equ YM_SSGEG|YM_OP3			; SSG-EG (OP3)
YM_SSGEG_CH14_OP3	equ YM_SSGEG|YM_CH14_OP3		; SSG-EG (CH1/4 OP3)
YM_SSGEG_CH25_OP3	equ YM_SSGEG|YM_CH25_OP3		; SSG-EG (CH2/5 OP3)
YM_SSGEG_CH36_OP3	equ YM_SSGEG|YM_CH36_OP3		; SSG-EG (CH3/6 OP3)
YM_SSGEG_OP2		equ YM_SSGEG|YM_OP2			; SSG-EG (OP2)
YM_SSGEG_CH14_OP2	equ YM_SSGEG|YM_CH14_OP2		; SSG-EG (CH1/4 OP2)
YM_SSGEG_CH25_OP2	equ YM_SSGEG|YM_CH25_OP2		; SSG-EG (CH2/5 OP2)
YM_SSGEG_CH36_OP2	equ YM_SSGEG|YM_CH36_OP2		; SSG-EG (CH3/6 OP2)
YM_SSGEG_OP4		equ YM_SSGEG|YM_OP4			; SSG-EG (OP4)
YM_SSGEG_CH14_OP4	equ YM_SSGEG|YM_CH14_OP4		; SSG-EG (CH1/4 OP4)
YM_SSGEG_CH25_OP4	equ YM_SSGEG|YM_CH25_OP4		; SSG-EG (CH2/5 OP4)
YM_SSGEG_CH36_OP4	equ YM_SSGEG|YM_CH36_OP4		; SSG-EG (CH3/6 OP4)
YM_FREQ_L		equ $A0					; Frequency (low)
YM_FREQ_L_CH14		equ YM_FREQ_L|YM_CH14			; Frequency (low, CH1/4)
YM_FREQ_L_CH25		equ YM_FREQ_L|YM_CH25			; Frequency (low, CH2/5)
YM_FREQ_L_CH36		equ YM_FREQ_L|YM_CH36			; Frequency (low, CH3/6)
YM_FREQ_L_CH3_OP4	equ YM_FREQ_L_CH36			; Frequency (low, CH3 OP4)
YM_FREQ_H		equ $A4					; Frequency (high)
YM_FREQ_H_CH14		equ YM_FREQ_H|YM_CH14			; Frequency (high, CH1/4)
YM_FREQ_H_CH25		equ YM_FREQ_H|YM_CH25			; Frequency (high, CH2/5)
YM_FREQ_H_CH36		equ YM_FREQ_H|YM_CH36			; Frequency (high, CH3/6)
YM_FREQ_H_CH3_OP4	equ YM_FREQ_H_CH36			; Frequency (high, CH3 OP4)
YM_FREQ_L_CH3_OP3	equ $A8					; Frequency (low, CH3 OP3)
YM_FREQ_L_CH3_OP1	equ $A9					; Frequency (low, CH3 OP1)
YM_FREQ_L_CH3_OP2	equ $AA					; Frequency (low, CH3 OP2)
YM_FREQ_H_CH3_OP3	equ $AC					; Frequency (high, CH3 OP3)
YM_FREQ_H_CH3_OP1	equ $AD					; Frequency (high, CH3 OP1)
YM_FREQ_H_CH3_OP2	equ $AE					; Frequency (high, CH3 OP2)
YM_ALG_FB		equ $B0					; Algorithm and feedback
YM_ALG_FB_CH14		equ YM_ALG_FB|YM_CH14			; Algorithm and feedback (CH1/4)
YM_ALG_FB_CH25		equ YM_ALG_FB|YM_CH25			; Algorithm and feedback (CH2/5)
YM_ALG_FB_CH36		equ YM_ALG_FB|YM_CH36			; Algorithm and feedback (CH3/6)
YM_PAN_MOD		equ $B4					; Panning and modulation
YM_PAN_MOD_CH14		equ YM_PAN_MOD|YM_CH14			; Panning and modulation (CH1/4)
YM_PAN_MOD_CH25		equ YM_PAN_MOD|YM_CH25			; Panning and modulation (CH2/5)
YM_PAN_MOD_CH36		equ YM_PAN_MOD|YM_CH36			; Panning and modulation (CH3/6)

YMR_BUSY_BIT		equ 7					; Busy
YMR_BUSY		equ %1<<YMR_BUSY_BIT

YMR_LFO_BIT		equ 0					; LFO frequency
YMR_LFO			equ %111<<YMR_LFO_BIT
YMR_LFO_3_82		equ %000<<YMR_LFO_BIT			; 3.82 Hz LFO
YMR_LFO_5_33		equ %001<<YMR_LFO_BIT			; 5.33 Hz LFO
YMR_LFO_5_77		equ %010<<YMR_LFO_BIT			; 5.77 Hz LFO
YMR_LFO_6_11		equ %011<<YMR_LFO_BIT			; 6.11 Hz LFO
YMR_LFO_6_60		equ %100<<YMR_LFO_BIT			; 6.60 Hz LFO
YMR_LFO_9_23		equ %101<<YMR_LFO_BIT			; 9.23 Hz LFO
YMR_LFO_46_11		equ %110<<YMR_LFO_BIT			; 46.11 Hz LFO
YMR_LFO_69_22		equ %111<<YMR_LFO_BIT			; 69.22 Hz LFO
YMR_LFOEN_BIT		equ 3					; LFO enable
YMR_LFOEN		equ %1<<YMR_LFOEN_BIT

YMR_TMA_H_BIT		equ 0					; Timer A (high)
YMR_TMA_H		equ %11111111<<YMR_TMA_H_BIT
YMR_TMA_H_SHIFT		equ 2

YMR_TMA_L_BIT		equ 0					; Timer A (low)
YMR_TMA_L		equ %11<<YMR_TMA_L_BIT

YMR_TMB_BIT		equ 0					; Timer B
YMR_TMB			equ %11111111<<YMR_TMB_BIT

YMR_RUN_A_BIT		equ 0					; Timer A running
YMR_RUN_A		equ %1<<YMR_RUN_A_BIT
YMR_RUN_B_BIT		equ 1					; Timer B running
YMR_RUN_B		equ %1<<YMR_RUN_B_BIT
YMR_FLG_A_BIT		equ 2					; Timer A overflow flag enable
YMR_FLG_A		equ %1<<YMR_FLG_A_BIT
YMR_FLG_B_BIT		equ 3					; Timer B overflow flag enable
YMR_FLG_B		equ %1<<YMR_FLG_B_BIT
YMR_RST_A_BIT		equ 4					; Timer A overflow flag enable
YMR_RST_A		equ %1<<YMR_RST_A_BIT
YMR_RST_B_BIT		equ 5					; Timer B overflow flag enable
YMR_RST_B		equ %1<<YMR_RST_B_BIT
YMR_CH3_BIT		equ 6					; Channel 3 mode
YMR_CH3			equ %11<<YMR_CH3_BIT
YMR_CH3_NORMAL		equ %00<<YMR_CH3_BIT			; Normal channel 3 mode
YMR_CH3_SPECIAL		equ %01<<YMR_CH3_BIT			; Special channel 3 mode
YMR_CH3_CSM		equ %10<<YMR_CH3_BIT			; CSM channel 3 mode

YMR_CH_BIT		equ 0					; Key on/off channel ID
YMR_CH			equ %111<<YMR_CH_BIT
YMR_OP1_BIT		equ 4					; OP1 key on/off
YMR_OP1			equ %1<<YMR_OP1_BIT
YMR_OP2_BIT		equ 5					; OP2 key on/off
YMR_OP2			equ %1<<YMR_OP2_BIT
YMR_OP3_BIT		equ 6					; OP3 key on/off
YMR_OP3			equ %1<<YMR_OP3_BIT
YMR_OP4_BIT		equ 7					; OP4 key on/off
YMR_OP4			equ %1<<YMR_OP4_BIT
YMR_OP_ALL		equ YMR_OP1|YMR_OP2|YMR_OP3|YMR_OP4	; All operator key on/off

YMR_DAC_BIT		equ 0					; DAC output data
YMR_DAC			equ %11111111<<YMR_DAC_BIT

YMR_DACEN_BIT		equ 7					; DAC enable
YMR_DACEN		equ %1<<YMR_DACEN_BIT

YMR_MUL_BIT		equ 0					; Multiply
YMR_MUL			equ %1111<<YMR_MUL_BIT
YMR_DT_BIT		equ 4					; Detune
YMR_DT			equ %111<<YMR_DT_BIT
YMR_DT_OFFSET		equ %011<<YMR_DT_BIT			; Detune offset
YMR_DT_SIGN		equ %100<<YMR_DT_BIT			; Detune sign
YMR_DT_SIGN_P		equ %000<<YMR_DT_BIT			; Positive detune
YMR_DT_SIGN_N		equ %100<<YMR_DT_BIT			; Negative detune

YMR_TL_BIT		equ 0					; Total level
YMR_TL			equ %1111111<<YMR_TL_BIT

YMR_AR_BIT		equ 0					; Attack rate
YMR_AR			equ %11111<<YMR_AR_BIT
YMR_RS_BIT		equ 6					; Rate scaling
YMR_RS			equ %11<<YMR_RS_BIT

YMR_DR_BIT		equ 0					; Decay rate
YMR_DR			equ %11111<<YMR_DR_BIT
YMR_AM_BIT		equ 7					; AM enable
YMR_AM			equ %1<<YMR_AM_BIT

YMR_SR_BIT		equ 0					; Sustain rate
YMR_SR			equ %11111<<YMR_SR_BIT

YMR_RR_BIT		equ 0					; Release rate
YMR_RR			equ %1111<<YMR_RR_BIT
YMR_SL_BIT		equ 4					; Sustain level
YMR_SL			equ %1111<<YMR_SL_BIT

YMR_SSG_BIT		equ 0					; SSG-EG envelope
YMR_SSG			equ %111<<YMR_SSG_BIT
YMR_SSG_REPEAT		equ %000<<YMR_SSG_BIT			; SSG-EG repeat
YMR_SSG_HOLD		equ %001<<YMR_SSG_BIT			; SSG-EG hold
YMR_SSG_INVERT		equ %010<<YMR_SSG_BIT			; SSG-EG invert
YMR_SSG_LEFT		equ %000<<YMR_SSG_BIT			; SSG-EG left direction
YMR_SSG_RIGHT		equ %100<<YMR_SSG_BIT			; SSG-EG right direction
YMR_SSGEN_BIT		equ 3					; SSG-EG enable
YMR_SSGEN		equ %1<<YMR_SSGEN_BIT

YMR_FREQ_H_BIT		equ 0					; Frequency (high)
YMR_FREQ_H		equ %111<<YMR_FREQ_H_BIT
YMR_FREQ_H_SHIFT	equ 8
YMR_BLK_BIT		equ 3					; Frequency block
YMR_BLK			equ %111<<YMR_BLK_BIT

YMR_FREQ_L_BIT		equ 0					; Frequency (low)
YMR_FREQ_L		equ %11111111<<YMR_FREQ_L_BIT

YMR_ALG_BIT		equ 0					; Algorithm
YMR_ALG			equ %111<<YMR_ALG_BIT
YMR_FB_BIT		equ 3					; Feedback
YMR_FB			equ %111<<YMR_FB_BIT

YMR_FMS_BIT		equ 0					; FMS
YMR_FMS			equ %111<<YMR_FMS_BIT
YMR_FMS_NONE		equ %000<<YMR_FMS_BIT			; No FMS
YMR_FMS_034		equ %001<<YMR_FMS_BIT			; -/+0.034 semitone FMS
YMR_FMS_067		equ %010<<YMR_FMS_BIT			; -/+0.067 semitone FMS
YMR_FMS_100		equ %011<<YMR_FMS_BIT			; -/+0.100 semitone FMS
YMR_FMS_140		equ %100<<YMR_FMS_BIT			; -/+0.140 semitone FMS
YMR_FMS_200		equ %101<<YMR_FMS_BIT			; -/+0.200 semitone FMS
YMR_FMS_400		equ %110<<YMR_FMS_BIT			; -/+0.400 semitone FMS
YMR_FMS_800		equ %111<<YMR_FMS_BIT			; -/+0.800 semitone FMS
YMR_AMS_BIT		equ 4					; AMS
YMR_AMS			equ %11<<YMR_AMS_BIT
YMR_AMS_NONE		equ %00<<YMR_AMS_BIT			; No AMS
YMR_AMS_14		equ %01<<YMR_AMS_BIT			; -/+1.4 dB AMS
YMR_AMS_5_9		equ %10<<YMR_AMS_BIT			; -/+5.9 dB AMS
YMR_AMS_11_8		equ %11<<YMR_AMS_BIT			; -/+11.8 dB AMS
YMR_R_BIT		equ 6					; Right output
YMR_R			equ %1<<YMR_R_BIT
YMR_L_BIT		equ 7					; Left output
YMR_R			equ %1<<YMR_L_BIT
YMR_LR			equ YMR_L|YMR_R				; Left and right output

; ------------------------------------------------------------------------------
; PSG
; ------------------------------------------------------------------------------

PSG_CHANNEL_COUNT	equ 4					; Channel count
PSG_PULSE_COUNT		equ 3					; Pulse channel count
PSG_NOISE_COUNT		equ 1					; Noise channel count

PSG_CH_BIT		equ 5					; Channel ID
PSG_CH			equ %11<<PSG_CH_BIT
PSG_CH1			equ %00<<PSG_CH_BIT			; Channel 1
PSG_CH2			equ %01<<PSG_CH_BIT			; Channel 2
PSG_CH3			equ %10<<PSG_CH_BIT			; Channel 3
PSG_CH4			equ %11<<PSG_CH_BIT			; Channel 4

PSGR_ATTEN_BIT		equ 0					; Attenuation
PSGR_ATTEN		equ %1111<<PSGR_ATTEN_BIT
PSGR_ATTEN_SET		equ %10010000				; Attenuation set
PSGR_ATTEN_SET_CH1	equ PSGR_ATTEN_SET|PSG_CH1		; Channel 1 attenuation set
PSGR_ATTEN_SET_CH2	equ PSGR_ATTEN_SET|PSG_CH2		; Channel 2 attenuation set
PSGR_ATTEN_SET_CH3	equ PSGR_ATTEN_SET|PSG_CH3		; Channel 3 attenuation set
PSGR_ATTEN_SET_CH4	equ PSGR_ATTEN_SET|PSG_CH4		; Channel 4 attenuation set

PSGR_FREQ_L_BIT		equ 0					; Frequency (low)
PSGR_FREQ_L		equ %1111<<PSGR_FREQ_L_BIT
PSGR_FREQ_SET		equ %10000000				; Frequency set
PSGR_FREQ_SET_CH1	equ PSGR_FREQ_SET|PSG_CH1		; Channel 1 frequency set
PSGR_FREQ_SET_CH2	equ PSGR_FREQ_SET|PSG_CH2		; Channel 2 frequency set
PSGR_FREQ_SET_CH3	equ PSGR_FREQ_SET|PSG_CH3		; Channel 3 frequency set

PSGR_FREQ_H_BIT		equ 0					; Frequency (high)
PSGR_FREQ_H		equ %111111<<PSGR_FREQ_H_BIT
PSGR_FREQ_H_SHIFT	equ 4

PSGR_NOISE_SET		equ PSGR_FREQ_SET|PSG_CH4		; Noise set
PSGR_NF_BIT		equ 0					; Noise frequency
PSGR_NF			equ %11<<PSGR_NF_BIT
PSGR_NF_CLOCK_2		equ %00<<PSGR_NF_BIT			; Clock/2 noise frequency
PSGR_NF_CLOCK_4		equ %01<<PSGR_NF_BIT			; Clock/2 noise frequency
PSGR_NF_CLOCK_8		equ %10<<PSGR_NF_BIT			; Clock/2 noise frequency
PSGR_NF_CH3		equ %11<<PSGR_NF_BIT			; Channel 3 frequency
PSGR_FB_BIT		equ 2					; Noise type
PSGR_FB			equ %1<<PSGR_FB_BIT
PSGR_FB_PERIODIC	equ %0<<PSGR_FB_BIT			; Periodic noise
PSGR_FB_WHITE		equ %1<<PSGR_FB_BIT			; White noise

; ------------------------------------------------------------------------------
; I/O
; ------------------------------------------------------------------------------

IO_PORT_COUNT		equ 3					; I/O port count

IOR_VER_BIT		equ 0					; Hardware version
IOR_VER			equ %1111<<IOR_VER_BIT
IOR_DISK_BIT		equ 5					; Expansion connected
IOR_DISK		equ %1<<IOR_DISK_BIT
IOR_VMOD_BIT		equ 6					; CPU clock speed
IOR_VMOD		equ %1<<IOR_VMOD_BIT
IOR_VMOD_NTSC		equ %0<<IOR_VMOD_BIT			; NTSC clock speed
IOR_VMOD_PAL		equ %1<<IOR_VMOD_BIT			; PAL clock speed
IOR_MODE_BIT		equ 7					; Hardware model type
IOR_MODE		equ %1<<IOR_MODE_BIT
IOR_MODE_DOMESTIC	equ %0<<IOR_MODE_BIT			; Domestic model
IOR_MODE_OVERSEAS	equ %1<<IOR_MODE_BIT			; Overseas model
IOR_DOMESTIC_NTSC	equ IOR_MODE_DOMESTIC|IOR_VMOD_NTSC	; Domestic NTSC model
IOR_DOMESTIC_PAL	equ IOR_MODE_DOMESTIC|IOR_VMOD_PAL	; Domestic PAL model
IOR_OVERSEAS_NTSC	equ IOR_MODE_OVERSEAS|IOR_VMOD_NTSC	; Overseas NTSC model
IOR_OVERSEAS_PAL	equ IOR_MODE_OVERSEAS|IOR_VMOD_PAL	; Overseas PAL model
IOR_JAPAN		equ IOR_DOMESTIC_NTSC			; Japan/South Korea/Taiwan model
IOR_USA			equ IOR_OVERSEAS_NTSC			; USA/Canada/Brazil model
IOR_EUROPE		equ IOR_OVERSEAS_PAL			; Europe/Hong Kong model

IOR_PD0_BIT		equ 0					; Port data bit 0
IOR_PD0			equ %1<<IOR_PD0_BIT
IOR_UP_BIT		equ IOR_PD0_BIT				; Port up bit
IOR_UP			equ IOR_PD0
IOR_PD1_BIT		equ 1					; Port data bit 1
IOR_PD1			equ %1<<IOR_PD1_BIT
IOR_DOWN_BIT		equ IOR_PD1_BIT				; Port down bit
IOR_DOWN		equ IOR_PD1
IOR_PD2_BIT		equ 2					; Port data bit 2
IOR_PD2			equ %1<<IOR_PD2_BIT
IOR_LEFT_BIT		equ IOR_PD2_BIT				; Port left bit
IOR_LEFT		equ IOR_PD2
IOR_PD3_BIT		equ 3					; Port data bit 3
IOR_PD3			equ %1<<IOR_PD3_BIT
IOR_RIGHT_BIT		equ IOR_PD3_BIT				; Port right bit
IOR_RIGHT		equ IOR_PD3
IOR_PD4_BIT		equ 4					; Port data bit 4
IOR_PD4			equ %1<<IOR_PD4_BIT
IOR_TL_BIT		equ IOR_PD4_BIT				; Port TL bit
IOR_TL			equ IOR_PD4
IOR_PD5_BIT		equ 5					; Port data bit 5
IOR_PD5			equ %1<<IOR_PD5_BIT
IOR_TR_BIT		equ IOR_PD5_BIT				; Port TR bit
IOR_TR			equ IOR_PD5
IOR_PD6_BIT		equ 6					; Port data bit 6
IOR_PD6			equ %1<<IOR_PD6_BIT
IOR_TH_BIT		equ IOR_PD6_BIT				; Port TH bit
IOR_TH			equ IOR_PD6
IOR_PD7_BIT		equ 7					; Port data bit 7
IOR_PD7			equ %1<<IOR_PD7_BIT

IOR_PC0_BIT		equ 0					; Port PD0 (up) mode
IOR_PC0			equ %1<<IOR_PC0_BIT
IOR_PC1_BIT		equ 1					; Port PD1 (down) mode
IOR_PC1			equ %1<<IOR_PC1_BIT
IOR_PC2_BIT		equ 2					; Port PD2 (left) mode
IOR_PC2			equ %1<<IOR_PC2_BIT
IOR_PC3_BIT		equ 3					; Port PD3 (right) mode
IOR_PC3			equ %1<<IOR_PC3_BIT
IOR_PC4_BIT		equ 4					; Port PD4 (TL) mode
IOR_PC4			equ %1<<IOR_PC4_BIT
IOR_PC5_BIT		equ 5					; Port PD5 (TH) mode
IOR_PC5			equ %1<<IOR_PC5_BIT
IOR_PC6_BIT		equ 6					; Port PD6 (TR) mode
IOR_PC6			equ %1<<IOR_PC6_BIT
IOR_PC7_BIT		equ 7					; Port PD7 mode
IOR_PC7			equ %1<<IOR_PC7_BIT

IOR_TFUL_BIT		equ 0					; Tx data full
IOR_TFUL		equ %1<<IOR_TFUL_BIT
IOR_RRDY_BIT		equ 1					; TL serial output mode
IOR_RRDY		equ %1<<IOR_RRDY_BIT
IOR_RERR_BIT		equ 2					; Rx data ready
IOR_RERR		equ %1<<IOR_RERR_BIT
IOR_RINT_BIT		equ 3					; Rx data error
IOR_RINT		equ %1<<IOR_RINT_BIT
IOR_SOUT_BIT		equ 4					; TL serial output mode
IOR_SOUT		equ %1<<IOR_SOUT_BIT
IOR_SIN_BIT		equ 5					; TR serial input mode
IOR_SIN			equ %1<<IOR_SIN_BIT
IOR_BPS_BIT		equ 6					; Serial speed
IOR_BPS			equ %11<<IOR_BPS_BIT
IOR_BPS_4800		equ %00<<IOR_BPS_BIT			; 4800 bps serial speed
IOR_BPS_2400		equ %01<<IOR_BPS_BIT			; 2400 bps serial speed
IOR_BPS_1200		equ %10<<IOR_BPS_BIT			; 1200 bps serial speed
IOR_BPS_300		equ %11<<IOR_BPS_BIT			; 300 bps serial speed

; ------------------------------------------------------------------------------
; Z80
; ------------------------------------------------------------------------------

Z80_RAM_SIZE		equ $2000				; Z80 RAM size

Z80R_BREQ_BIT		equ 0					; Z80 bus request
Z80R_BREQ		equ %1<<Z80R_BREQ_BIT

Z80R_RREQ_BIT		equ 0					; Z80 reset request
Z80R_RREQ		equ %1<<Z80R_RREQ_BIT

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

PCM_CH1			equ 0					; Channel 1
PCM_CH2			equ 1					; Channel 2
PCM_CH3			equ 2					; Channel 3
PCM_CH4			equ 3					; Channel 4
PCM_CH5			equ 4					; Channel 5
PCM_CH6			equ 5					; Channel 6
PCM_CH7			equ 6					; Channel 7
PCM_CH8			equ 7					; Channel 8

PCMR_WB_BIT		equ 0					; Wave RAM bank ID
PCMR_WB			equ %1111<<PCMR_WB_BIT
PCMR_CB_BIT		equ 0					; Channel ID
PCMR_CB			equ %111<<PCMR_CB_BIT
PCMR_MOD_BIT		equ 6					; Control selection
PCMR_MOD		equ %1<<PCMR_MOD_BIT
PCMR_MOD_WAVE		equ %0<<PCMR_MOD_BIT			; Wave RAM bank selection mode
PCMR_MOD_CHAN		equ %1<<PCMR_MOD_BIT			; Channel selection mode
PCMR_ON_OFF_BIT		equ 7					; Chip on/off
PCMR_ON_OFF		equ %1<<PCMR_ON_OFF_BIT
PCMR_OFF		equ %0<<PCMR_ON_OFF_BIT			; Chip off
PCMR_ON			equ %1<<PCMR_ON_OFF_BIT			; Chip on

PCMR_ST_BIT		equ 0					; Start address
PCMR_ST			equ %11111111<<PCMR_ST_BIT
PCMR_ST_SHIFT		equ 8

PCMR_LSH_BIT		equ 0					; Loop address (high)
PCMR_LSH		equ %11111111<<PCMR_LSH_BIT
PCMR_LSH_SHIFT		equ 8

PCMR_LSL_BIT		equ 0					; Loop address (low)
PCMR_LSL		equ %11111111<<PCMR_LSL_BIT

PCMR_FDH_BIT		equ 0					; Frequency (high)
PCMR_FDH		equ %11111111<<PCMR_FDH_BIT
PCMR_FDH_SHIFT		equ 8

PCMR_FDL_BIT		equ 0					; Frequency (low)
PCMR_FDL		equ %11111111<<PCMR_FDL_BIT

PCMR_L_BIT		equ 0					; Panning (left)
PCMR_L			equ %1111<<PCMR_L_BIT
PCMR_R_BIT		equ 4					; Panning (right)
PCMR_R			equ %1111<<PCMR_R_BIT

PCMR_ON1_BIT		equ 0					; Channel 1 enable
PCMR_ON1		equ %1<<PCMR_ON1_BIT
PCMR_ON2_BIT		equ 1					; Channel 2 enable
PCMR_ON2		equ %1<<PCMR_ON2_BIT
PCMR_ON3_BIT		equ 2					; Channel 3 enable
PCMR_ON3		equ %1<<PCMR_ON3_BIT
PCMR_ON4_BIT		equ 3					; Channel 4 enable
PCMR_ON4		equ %1<<PCMR_ON4_BIT
PCMR_ON5_BIT		equ 4					; Channel 5 enable
PCMR_ON5		equ %1<<PCMR_ON5_BIT
PCMR_ON6_BIT		equ 5					; Channel 6 enable
PCMR_ON6		equ %1<<PCMR_ON6_BIT
PCMR_ON7_BIT		equ 6					; Channel 7 enable
PCMR_ON7		equ %1<<PCMR_ON7_BIT
PCMR_ON8_BIT		equ 7					; Channel 8 enable
PCMR_ON8		equ %1<<PCMR_ON8_BIT

; ------------------------------------------------------------------------------
; Wave RAM
; ------------------------------------------------------------------------------

WAVE_RAM_SIZE		equ $10000				; Wave RAM size
WAVE_RAM_BANK_SIZE	equ $1000				; Wave RAM bank size

WAVE_RAM_BANK_COUNT	equ 16					; Wave RAM bank count

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
STAMP_SNO		equ %11111111111<<STAMP_SNO_BIT
STAMP_SNO_16		equ %11111111111<<STAMP_SNO_BIT		; Stamp ID (16x16 stamps)
STAMP_SNO_32		equ %11111111100<<STAMP_SNO_BIT		; Stamp ID (32x32 stamps)
STAMP_RT_BIT		equ $D					; Rotation
STAMP_RT		equ %11<<STAMP_RT_BIT
STAMP_RT_0		equ %00<<STAMP_RT_BIT			; 0 degree rotation
STAMP_RT_90		equ %01<<STAMP_RT_BIT			; 90 degree rotation
STAMP_RT_180		equ %10<<STAMP_RT_BIT			; 180 degree rotation
STAMP_RT_270		equ %11<<STAMP_RT_BIT			; 270 degree rotation
STAMP_HFLP_BIT		equ $F					; Horizontal flip
STAMP_HFLP		equ %1<<STAMP_HFLP_BIT

TRACE_PX_BIT		equ 0					; X start fractional part
TRACE_PX		equ %111<<TRACE_PX_BIT
TRACE_X_BIT		equ 3					; X start integer part
TRACE_X			equ %1111111111111<<TRACE_X_BIT
TRACE_X_SHIFT		equ 5
TRACE_PY_BIT		equ 0					; Y start fractional part
TRACE_PY		equ %111<<TRACE_PY_BIT
TRACE_Y_BIT		equ 3					; Y start integer part
TRACE_Y			equ %1111111111111<<TRACE_Y_BIT
TRACE_Y_SHIFT		equ 5
TRACE_DPX_BIT		equ 0					; X delta fractional part
TRACE_DPX		equ %11111111111<<TRACE_DPX_BIT
TRACE_DX_BIT		equ 11					; X delta integer part
TRACE_DX		equ %11111<<TRACE_DX_BIT
TRACE_DX_SHIFT		equ 3
TRACE_DY_BIT		equ 11					; Y delta integer part
TRACE_DY		equ %11111<<TRACE_DY_BIT
TRACE_DY_SHIFT		equ 3

MCDR_IFL2_BIT		equ 0					; Mega Drive interrupt request
MCDR_IFL2		equ %1<<MCDR_IFL2_BIT
MCDR_MIE2_BIT		equ 7					; Mega Drive interrupt enabled
MCDR_MIE2		equ %1<<MCDR_MIE2_BIT

MCDR_LEDR_BIT		equ 0					; Red LED
MCDR_LEDR		equ %1<<MCDR_LEDR_BIT
MCDR_LEDG_BIT		equ 1					; Green LED
MCDR_LEDG		equ %1<<MCDR_LEDG_BIT

MCDR_SRES_BIT		equ 0					; Sub CPU reset
MCDR_SRES		equ %1<<MCDR_SRES_BIT
MCDR_SBRQ_BIT		equ 1					; Sub CPU bus request
MCDR_SBRQ		equ %1<<MCDR_SBRQ_BIT

MCDR_RES0_BIT		equ 0					; Reset
MCDR_RES0		equ %1<<MCDR_RES0_BIT
MCDR_VER_BIT		equ 4					; Version
MCDR_VER		equ %1111<<MCDR_VER_BIT

MCDR_WP_BIT		equ 0					; Program RAM write protection range
MCDR_WP			equ %11111111<<MCDR_WP_BIT
MCDR_WP_SHIFT		equ 9

MCDR_RET_BIT		equ 0					; Word RAM Main CPU access
MCDR_RET		equ %1<<MCDR_RET_BIT
MCDR_DMNA_BIT		equ 1					; Word RAM Sub CPU access
MCDR_DMNA		equ %1<<MCDR_DMNA_BIT
MCDR_MODE_BIT		equ 2					; Word RAM mode
MCDR_MODE		equ %1<<MCDR_MODE_BIT
MCDR_MODE_2M		equ %0<<MCDR_MODE_BIT			; Word RAM 2M mode
MCDR_MODE_1M		equ %1<<MCDR_MODE_BIT			; Word RAM 1M/1M mode
MCDR_PM_BIT		equ 3					; Word RAM priority mode
MCDR_PM			equ %11<<MCDR_PM_BIT
MCDR_PM_OFF		equ %00<<MCDR_PM_BIT			; Word RAM priority off
MCDR_PM_UNDER		equ %01<<MCDR_PM_BIT			; Word RAM underwrite mode
MCDR_PM_OVER		equ %10<<MCDR_PM_BIT			; Word RAM overwrite mode

MCDR_DD_BIT		equ 0					; CDC device destination
MCDR_DD			equ %111<<MCDR_DD_BIT
MCDR_DD_HOST_MAIN	equ %010<<MCDR_DD_BIT			; Host register (Main CPU read)
MCDR_DD_HOST_SUB	equ %011<<MCDR_DD_BIT			; Host register (Sub CPU read)
MCDR_DD_WAVE_RAM	equ %100<<MCDR_DD_BIT			; Wave RAM (DMA)
MCDR_DD_PRG_RAM		equ %101<<MCDR_DD_BIT			; Program RAM (DMA)
MCDR_DD_WORD_RAM	equ %111<<MCDR_DD_BIT			; Word RAM (DMA)
MCDR_UBR_BIT		equ 5					; Upper byte ready
MCDR_UBR		equ %1<<MCDR_UBR_BIT
MCDR_DSR_BIT		equ 6					; Data set ready
MCDR_DSR		equ %1<<MCDR_DSR_BIT
MCDR_EDT_BIT		equ 7					; End of data transfer
MCDR_EDT		equ %1<<MCDR_EDT_BIT

MCDR_HIB_BIT		equ 0					; H-BLANK interrupt address (Main CPU, mode 2)
MCDR_HIB		equ %1111111111111111<<MCDR_HIB_BIT

MCDR_CA_BIT		equ 0					; CDC register address
MCDR_CA			equ %1111<<MCDR_CA_BIT

MCDR_CD_BIT		equ 0					; CDC register data
MCDR_CD			equ %11111111<<MCDR_CD_BIT

MCDR_HD_BIT		equ 0					; CDC host data
MCDR_HD			equ %1111111111111111<<MCDR_HD_BIT

MCDR_DMA_BIT		equ 0					; CDC DMA address
MCDR_DMA		equ %1111111111111111<<MCDR_DMA_BIT
MCDR_DMA_SHIFT		equ 3

MCDR_SW_BIT		equ 0					; Stopwatch value
MCDR_SW			equ %111111111111<<MCDR_SW_BIT

MCDR_CFM_BIT		equ 0					; Main CPU communication flag
MCDR_CFM		equ %11111111<<MCDR_CFM_BIT

MCDR_CFS_BIT		equ 0					; Sub CPU communication flag
MCDR_CFS		equ %11111111<<MCDR_CFS_BIT

MCDR_CCM_BIT		equ 0					; Main CPU communication value
MCDR_CCM		equ %11111111<<MCDR_CCM_BIT

MCDR_CST_BIT		equ 0					; Sub CPU communication value
MCDR_CST		equ %11111111<<MCDR_CST_BIT

MCDR_TD_BIT		equ 0					; Timer interrupt timer
MCDR_TD			equ %11111111<<MCDR_TD_BIT

MCDR_IEN1_BIT		equ 1					; Graphics interrupt enable
MCDR_IEN1		equ %1<<MCDR_IEN1_BIT
MCDR_IEN2_BIT		equ 2					; Mega Drive interrupt enable
MCDR_IEN2		equ %1<<MCDR_IEN2_BIT
MCDR_IEN3_BIT		equ 3					; Timer interrupt enable
MCDR_IEN3		equ %1<<MCDR_IEN3_BIT
MCDR_IEN4_BIT		equ 4					; CDD interrupt enable
MCDR_IEN4		equ %1<<MCDR_IEN4_BIT
MCDR_IEN5_BIT		equ 5					; CDC interrupt enable
MCDR_IEN5		equ %1<<MCDR_IEN5_BIT
MCDR_IEN6_BIT		equ 6					; Subcode interrupt enable
MCDR_IEN6		equ %1<<MCDR_IEN6_BIT

MCDR_DEF_BIT		equ 2					; De-emphasis
MCDR_DEF		equ %11<<MCDR_DEF_BIT
MCDR_DEF_OFF		equ %00<<MCDR_DEF_BIT			; De-emphasis off
MCDR_DEF_44		equ %01<<MCDR_DEF_BIT			; 44.1 kHz de-emphasis
MCDR_DEF_32		equ %10<<MCDR_DEF_BIT			; 32 kHz de-emphasis
MCDR_DEF_48		equ %11<<MCDR_DEF_BIT			; 48 kHz de-emphasis
MCDR_FD_BIT		equ 4					; Fader volume
MCDR_FD			equ %11111111111<<MCDR_FD_BIT
MCDR_EFDT_BIT		equ 15					; End of fade data transfer
MCDR_EFDT		equ %1<<MCDR_EFDT_BIT

MCDR_DM_BIT		equ 0					; CDC data type
MCDR_DM			equ %1<<MCDR_DM_BIT
MCDR_DM_MUSIC		equ %0<<MCDR_DM_BIT			; Music data type
MCDR_DM_ROM		equ %1<<MCDR_DM_BIT			; CD-ROM data type

MCDR_DTS_BIT		equ 0					; Data transmission status
MCDR_DTS		equ %1<<MCDR_DTS_BIT
MCDR_DRS_BIT		equ 1					; Data receive status
MCDR_DRS		equ %1<<MCDR_DRS_BIT
MCDR_HOCK_BIT		equ 2					; Host clock
MCDR_HOCK		equ %1<<MCDR_HOCK_BIT

MCDR_CDST_BIT		equ 0					; CDD status value
MCDR_CDST		equ %1111<<MCDR_CDST_BIT

MCDR_CDCM_BIT		equ 0					; CDD command value
MCDR_CDCM		equ %1111<<MCDR_CDCM_BIT

MCDR_SC0_BIT		equ 0					; 1BPP conversion color (0)
MCDR_SC0		equ %1111<<MCDR_SC0_BIT
MCDR_SC1_BIT		equ 4					; 1BPP conversion color (1)
MCDR_SC1		equ %1111<<MCDR_SC1_BIT

MCDR_IDT_BIT		equ 0					; 1BPP conversion input data
MCDR_IDT		equ %1111111111111111<<MCDR_IDT_BIT

MCDR_ODT_BIT		equ 0					; 1BPP conversion output data
MCDR_ODT		equ %1111111111111111<<MCDR_ODT_BIT

MCDR_GRON_BIT		equ 7					; Image rendering (2M)
MCDR_GRON		equ %1<<MCDR_GRON_BIT

MCDR_RPT_BIT		equ 0					; Stamp map repeating (2M)
MCDR_RPT		equ %1<<MCDR_RPT_BIT
MCDR_STS_BIT		equ 1					; Stamp size (2M)
MCDR_STS		equ %1<<MCDR_STS_BIT
MCDR_STS_16		equ %0<<MCDR_STS_BIT			; 16x16 stamps (2M)
MCDR_STS_32		equ %1<<MCDR_STS_BIT			; 32x32 stamps (2M)
MCDR_SMS_BIT		equ 2					; Stamp size (2M)
MCDR_SMS		equ %1<<MCDR_SMS_BIT
MCDR_SMS_256		equ %0<<MCDR_SMS_BIT			; 256x2456 stamp map (2M)
MCDR_SMS_4096		equ %1<<MCDR_SMS_BIT			; 4096x4096 stamp map (2M)

MCDR_SMA_BIT		equ 0					; Stamp map address (2M)
MCDR_SMA		equ %1111111111100000<<MCDR_SMA_BIT
MCDR_SMA_SHIFT		equ 2
MCDR_SMA_16_256		equ %1111111110000000<<MCDR_SMA_BIT	; Stamp map address (16x16 stamps, 256x256 map) (2M)
MCDR_SMA_32_256		equ %1111111111100000<<MCDR_SMA_BIT	; Stamp map address (32x32 stamps, 256x256 map) (2M)
MCDR_SMA_16_4096	equ %1000000000000000<<MCDR_SMA_BIT	; Stamp map address (16x16 stamps, 4096x4096 map) (2M)
MCDR_SMA_32_4096	equ %1110000000000000<<MCDR_SMA_BIT	; Stamp map address (32x32 stamps, 4096x4096 map) (2M)

MCDR_VCS_BIT		equ 0					; Image buffer stride (2M)
MCDR_VCS		equ %11111<<MCDR_VCS_BIT

MCDR_IMA_BIT		equ 0					; Image buffer address (2M)
MCDR_IMA		equ %1111111111111000<<MCDR_IMA_BIT
MCDR_IMA_SHIFT		equ 2

MCDR_DOT_BIT		equ 0					; Image buffer X offset (2M)
MCDR_DOT		equ %111<<MCDR_DOT_BIT
MCDR_LN_BIT		equ 3					; Image buffer Y offset (2M)
MCDR_LN			equ %111<<MCDR_LN_BIT

MCDR_HW_BIT		equ 0					; Image buffer width (2M)
MCDR_HW			equ %111111111<<MCDR_HW_BIT

MCDR_VW_BIT		equ 0					; Image buffer height (2M)
MCDR_VW			equ %11111111<<MCDR_VW_BIT

MCDR_TVA_BIT		equ 0					; Trace vector address (2M)
MCDR_TVA		equ %1111111111111110<<MCDR_TVA_BIT
MCDR_TVA_SHIFT		equ 2

MCDR_STA_BIT		equ 1					; Subcode top address
MCDR_STA		equ %111111<<MCDR_STA_BIT
MCDR_SAOR_BIT		equ 7					; Subcode address overrun
MCDR_SAOR		equ %1<<MCDR_SAOR_BIT

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
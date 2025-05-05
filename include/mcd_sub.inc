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
; Program RAM
; ------------------------------------------------------------------------------

PRG_RAM			equ 0					; Program RAM
PRG_RAM_END		equ PRG_RAM+PRG_RAM_SIZE-1		; Program RAM end

SP_START		equ PRG_RAM+$6000			; System program start

; ------------------------------------------------------------------------------
; Word RAM
; ------------------------------------------------------------------------------

WORD_RAM_PIXEL		equ $80000				; Word RAM pixel image start (1M/1M)
WORD_RAM_PIXEL_END	equ WORD_RAM_PIXEL+WORD_RAM_PIXEL_SIZE-1; Word RAM pixel image end (1M/1M)
WORD_RAM_2M		equ $80000				; Word RAM start (2M)
WORD_RAM_2M_END		equ WORD_RAM_2M+WORD_RAM_2M_SIZE-1	; Word RAM end (2M)
WORD_RAM_1M		equ $C0000				; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ WORD_RAM_1M+WORD_RAM_1M_SIZE-1	; Word RAM end (1M/1M)

; ------------------------------------------------------------------------------
; PCM
; ------------------------------------------------------------------------------

PCM_REGS		equ $FF0001				; PCM registers base
PCM_VOLUME		equ PCM_REGS				; Volume
PCM_PAN			equ PCM_REGS+2				; Pan
PCM_FREQ_L		equ PCM_REGS+4				; Frequency (low)
PCM_FREQ_H		equ PCM_REGS+6				; Frequency (high)
PCM_LOOP_L		equ PCM_REGS+8				; Wave memory stop address (low)
PCM_LOOP_H		equ PCM_REGS+$A				; Wave memory stop address (high)
PCM_START		equ PCM_REGS+$C				; Wave memory start address
PCM_CTRL		equ PCM_REGS+$E				; Control
PCM_ENABLE		equ PCM_REGS+$10			; Channel enable
PCM_ADDR		equ PCM_REGS+$20			; Wave address
PCM_ADDR_L_1		equ PCM_REGS+$20			; PCM1 wave address (low)
PCM_ADDR_H_1		equ PCM_REGS+$22			; PCM1 wave address (high)
PCM_ADDR_L_2		equ PCM_REGS+$24			; PCM2 wave address (low)
PCM_ADDR_H_2		equ PCM_REGS+$26			; PCM2 wave address (high)
PCM_ADDR_L_3		equ PCM_REGS+$28			; PCM3 wave address (low)
PCM_ADDR_H_3		equ PCM_REGS+$2A			; PCM3 wave address (high)
PCM_ADDR_L_4		equ PCM_REGS+$2C			; PCM4 wave address (low)
PCM_ADDR_H_4		equ PCM_REGS+$2E			; PCM4 wave address (high)
PCM_ADDR_L_5		equ PCM_REGS+$30			; PCM5 wave address (low)
PCM_ADDR_H_5		equ PCM_REGS+$32			; PCM5 wave address (high)
PCM_ADDR_L_6		equ PCM_REGS+$34			; PCM6 wave address (low)
PCM_ADDR_H_6		equ PCM_REGS+$36			; PCM6 wave address (high)
PCM_ADDR_L_7		equ PCM_REGS+$38			; PCM7 wave address (low)
PCM_ADDR_H_7		equ PCM_REGS+$3A			; PCM7 wave address (high)
PCM_ADDR_L_8		equ PCM_REGS+$3C			; PCM8 wave address (low)
PCM_ADDR_H_8		equ PCM_REGS+$3E			; PCM8 wave address (high)

; ------------------------------------------------------------------------------
; Wave RAM
; ------------------------------------------------------------------------------

WAVE_RAM_BANK		equ $FF2001				; Wave RAM bank start
WAVE_RAM_BANK_END	equ WAVE_RAM_BANK+WAVE_RAM_BANK_SIZE-1	; Wave RAM bank end

; ------------------------------------------------------------------------------
; Mega CD
; ------------------------------------------------------------------------------

MCD_REGS		equ $FFFF8000				; Mega CD registers
MCD_LED_CTRL		equ MCD_REGS				; LED control
MCD_RESET		equ MCD_REGS+1				; Periphery reset
MCD_PROTECT		equ MCD_REGS+2				; Program RAM write protection
MCD_MEM_MODE		equ MCD_REGS+3				; Memory mode
MCD_CDC_MODE		equ MCD_REGS+4				; CDC mode
MCD_CDC_REG_ADDR	equ MCD_REGS+5				; CDC register address
MCD_CDC_REG_DATA	equ MCD_REGS+7				; CDC register data
MCD_CDC_HOST		equ MCD_REGS+8				; CDC host data
MCD_CDC_DMA		equ MCD_REGS+$A				; CDC DMA address
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
MCD_IRQ3_TIME		equ MCD_REGS+$31			; Timer interrupt timer
MCD_IRQ_MASK		equ MCD_REGS+$33			; Interrupt mask
MCD_FADER		equ MCD_REGS+$34			; Fader volume and control
MCD_CDD_TYPE		equ MCD_REGS+$36			; CDD data type
MCD_CDD_CTRL		equ MCD_REGS+$37			; CDD control
MCD_CDD_STATS		equ MCD_REGS+$38			; CDD statuses
MCD_CDD_STAT_0		equ MCD_CDD_STATS			; CDD status 0
MCD_CDD_STAT_1		equ MCD_CDD_STATS+1			; CDD status 1
MCD_CDD_STAT_2		equ MCD_CDD_STATS+2			; CDD status 2
MCD_CDD_STAT_3		equ MCD_CDD_STATS+3			; CDD status 3
MCD_CDD_STAT_4		equ MCD_CDD_STATS+4			; CDD status 4
MCD_CDD_STAT_5		equ MCD_CDD_STATS+5			; CDD status 5
MCD_CDD_STAT_6		equ MCD_CDD_STATS+6			; CDD status 6
MCD_CDD_STAT_7		equ MCD_CDD_STATS+7			; CDD status 7
MCD_CDD_STAT_8		equ MCD_CDD_STATS+8			; CDD status 8
MCD_CDD_STAT_9		equ MCD_CDD_STATS+9			; CDD status 9
MCD_CDD_CMDS		equ MCD_REGS+$42			; CDD commands
MCD_CDD_CMD_0		equ MCD_CDD_CMDS			; CDD command 0
MCD_CDD_CMD_1		equ MCD_CDD_CMDS+1			; CDD command 1
MCD_CDD_CMD_2		equ MCD_CDD_CMDS+2			; CDD command 2
MCD_CDD_CMD_3		equ MCD_CDD_CMDS+3			; CDD command 3
MCD_CDD_CMD_4		equ MCD_CDD_CMDS+4			; CDD command 4
MCD_CDD_CMD_5		equ MCD_CDD_CMDS+5			; CDD command 5
MCD_CDD_CMD_6		equ MCD_CDD_CMDS+6			; CDD command 6
MCD_CDD_CMD_7		equ MCD_CDD_CMDS+7			; CDD command 7
MCD_CDD_CMD_8		equ MCD_CDD_CMDS+8			; CDD command 8
MCD_CDD_CMD_9		equ MCD_CDD_CMDS+9			; CDD command 9
MCD_1BPP_COLOR		equ MCD_REGS+$4C			; 1BPP conversion color
MCD_1BPP_IN		equ MCD_REGS+$4E			; 1BPP conversion input data
MCD_1BPP_OUT		equ MCD_REGS+$50			; 1BPP conversion output data
MCD_IMG_RENDER		equ MCD_REGS+$58			; Image rendering flag
MCD_IMG_SIZES		equ MCD_REGS+$59			; Image render sizes
MCD_IMG_STAMP_MAP	equ MCD_REGS+$5A			; Image stamp map address
MCD_IMG_STRIDE		equ MCD_REGS+$5C			; Image buffer stride
MCD_IMG_START		equ MCD_REGS+$5E			; Image buffer address
MCD_IMG_OFFSET		equ MCD_REGS+$61			; Image buffer pixel offset
MCD_IMG_WIDTH		equ MCD_REGS+$62			; Image buffer width
MCD_IMG_HEIGHT		equ MCD_REGS+$64			; Image buffer height
MCD_IMG_TRACE		equ MCD_REGS+$66			; Trace vector address
MCD_SUBCODE_ADDR	equ MCD_REGS+$69			; Subcode address
MCD_SUBCODE_DATA	equ MCD_REGS+$100			; Subcode data

_CDSTAT			equ PRG_RAM+$5E80			; BIOS status
_BOOTSTAT		equ PRG_RAM+$5EA0			; Boot status
_USERMODE		equ PRG_RAM+$5EA6			; User mode
_SETJMPTBL		equ PRG_RAM+$5F0A			; Set module
_WAITVSYNC		equ PRG_RAM+$5F10			; VSync
_BURAM			equ PRG_RAM+$5F16			; Backup RAM function
_CDBOOT			equ PRG_RAM+$5F1C			; Boot function
_CDBIOS			equ PRG_RAM+$5F22			; BIOS function
_USERCALL0		equ PRG_RAM+$5F28			; Module initialization
_USERCALL1		equ PRG_RAM+$5F2E			; Module main function
_USERCALL2		equ PRG_RAM+$5F34			; Module Mega Drive interrupt
_USERCALL3		equ PRG_RAM+$5F3A			; Module user call
_ADRERR			equ PRG_RAM+$5F40			; Address error
_CODERR			equ PRG_RAM+$5F46			; Illegal instruction
_DIVERR			equ PRG_RAM+$5F4C			; Division by zero
_CHKERR			equ PRG_RAM+$5F52			; CHK exception
_TRPERR			equ PRG_RAM+$5F58			; TRAPV exception
_SPVERR			equ PRG_RAM+$5F5E			; Privilege violation
_TRACE			equ PRG_RAM+$5F64			; TRACE exception
_NOCOD0			equ PRG_RAM+$5F6A			; Line A emulator
_NOCOD1			equ PRG_RAM+$5F70			; Line F emulator
_LEVEL1			equ PRG_RAM+$5F76			; Graphics interrupt
_LEVEL2			equ PRG_RAM+$5F7C			; Mega Drive interrupt
_LEVEL3			equ PRG_RAM+$5F82			; Timer interrupt
_LEVEL4			equ PRG_RAM+$5F88			; CDD interrupt
_LEVEL5			equ PRG_RAM+$5F8E			; CDC interrupt
_LEVEL6			equ PRG_RAM+$5F94			; Subcode interrupt
_LEVEL7			equ PRG_RAM+$5F9A			; Unused interrupt
_TRAP00			equ PRG_RAM+$5FA0			; TRAP #00
_TRAP01			equ PRG_RAM+$5FA6			; TRAP #01
_TRAP02			equ PRG_RAM+$5FAC			; TRAP #02
_TRAP03			equ PRG_RAM+$5FB2			; TRAP #03
_TRAP04			equ PRG_RAM+$5FB8			; TRAP #04
_TRAP05			equ PRG_RAM+$5FBE			; TRAP #05
_TRAP06			equ PRG_RAM+$5FC4			; TRAP #06
_TRAP07			equ PRG_RAM+$5FCA			; TRAP #07
_TRAP08			equ PRG_RAM+$5FD0			; TRAP #08
_TRAP09			equ PRG_RAM+$5FD6			; TRAP #09
_TRAP10			equ PRG_RAM+$5FDC			; TRAP #10
_TRAP11			equ PRG_RAM+$5FE2			; TRAP #11
_TRAP12			equ PRG_RAM+$5FE8			; TRAP #12
_TRAP13			equ PRG_RAM+$5FEE			; TRAP #13
_TRAP14			equ PRG_RAM+$5FF4			; TRAP #14
_TRAP15			equ PRG_RAM+$5FFA			; TRAP #15

; ------------------------------------------------------------------------------
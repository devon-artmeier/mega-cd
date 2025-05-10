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
; Program RAM
; ------------------------------------------------------------------------------

PRG_RAM			equ 0					; Program RAM
PRG_RAM_END		equ $7FFFF				; Program RAM end
PRG_RAM_SIZE		equ $80000				; Program RAM size

_CDSTAT			equ $5E80				; BIOS status
_BOOTSTAT		equ $5EA0				; Boot status
_USERMODE		equ $5EA6				; User mode
_SETJMPTBL		equ $5F0A				; Set module
_WAITVSYNC		equ $5F10				; VSync
_BURAM			equ $5F16				; Backup RAM function
_CDBOOT			equ $5F1C				; Boot function
_CDBIOS			equ $5F22				; BIOS function
_USERCALL0		equ $5F28				; Module initialization
_USERCALL1		equ $5F2E				; Module main function
_USERCALL2		equ $5F34				; Module Mega Drive interrupt
_USERCALL3		equ $5F3A				; Module user call
_ADRERR			equ $5F40				; Address error
_CODERR			equ $5F46				; Illegal instruction
_DIVERR			equ $5F4C				; Division by zero
_CHKERR			equ $5F52				; CHK exception
_TRPERR			equ $5F58				; TRAPV exception
_SPVERR			equ $5F5E				; Privilege violation
_TRACE			equ $5F64				; TRACE exception
_NOCOD0			equ $5F6A				; Line A emulator
_NOCOD1			equ $5F70				; Line F emulator
_LEVEL1			equ $5F76				; Graphics interrupt
_LEVEL2			equ $5F7C				; Mega Drive interrupt
_LEVEL3			equ $5F82				; Timer interrupt
_LEVEL4			equ $5F88				; CDD interrupt
_LEVEL5			equ $5F8E				; CDC interrupt
_LEVEL6			equ $5F94				; Subcode interrupt
_LEVEL7			equ $5F9A				; Unused interrupt
_TRAP00			equ $5FA0				; TRAP #00
_TRAP01			equ $5FA6				; TRAP #01
_TRAP02			equ $5FAC				; TRAP #02
_TRAP03			equ $5FB2				; TRAP #03
_TRAP04			equ $5FB8				; TRAP #04
_TRAP05			equ $5FBE				; TRAP #05
_TRAP06			equ $5FC4				; TRAP #06
_TRAP07			equ $5FCA				; TRAP #07
_TRAP08			equ $5FD0				; TRAP #08
_TRAP09			equ $5FD6				; TRAP #09
_TRAP10			equ $5FDC				; TRAP #10
_TRAP11			equ $5FE2				; TRAP #11
_TRAP12			equ $5FE8				; TRAP #12
_TRAP13			equ $5FEE				; TRAP #13
_TRAP14			equ $5FF4				; TRAP #14
_TRAP15			equ $5FFA				; TRAP #15

SP_START		equ $6000				; System program start

; ------------------------------------------------------------------------------
; Word RAM
; ------------------------------------------------------------------------------

WORD_RAM_PIXEL		equ $80000				; Word RAM pixel image start (1M/1M)
WORD_RAM_PIXEL_END	equ $BFFFF				; Word RAM pixel image end (1M/1M)
WORD_RAM_PIXEL_SIZE	equ $40000				; Word RAM pixel image size (1M/1M)
WORD_RAM_2M		equ $80000				; Word RAM start (2M)
WORD_RAM_2M_END		equ $BFFFF				; Word RAM end (2M)
WORD_RAM_2M_SIZE	equ $40000				; Word RAM size (2M)
WORD_RAM_1M		equ $C0000				; Word RAM start (1M/1M)
WORD_RAM_1M_END		equ $DFFFF				; Word RAM end (1M/1M)
WORD_RAM_1M_SIZE	equ $20000				; Word RAM size (1M/1M)

; ------------------------------------------------------------------------------
; PCM
; ------------------------------------------------------------------------------

PCM_REGS		equ $FF0001				; PCM registers
PCM_VOLUME		equ $FF0001				; Volume
PCM_PAN			equ $FF0003				; Pan
PCM_FREQ_L		equ $FF0005				; Frequency (low)
PCM_FREQ_H		equ $FF0007				; Frequency (high)
PCM_LOOP_L		equ $FF0009				; Wave memory stop address (low)
PCM_LOOP_H		equ $FF000B				; Wave memory stop address (high)
PCM_START		equ $FF000D				; Wave memory start address
PCM_CTRL		equ $FF000F				; Control
PCM_ENABLE		equ $FF0011				; Channel enable
PCM_ADDR		equ $FF0021				; Wave address
PCM_ADDR_L_1		equ $FF0021				; PCM1 wave address (low)
PCM_ADDR_H_1		equ $FF0023				; PCM1 wave address (high)
PCM_ADDR_L_2		equ $FF0025				; PCM2 wave address (low)
PCM_ADDR_H_2		equ $FF0027				; PCM2 wave address (high)
PCM_ADDR_L_3		equ $FF0029				; PCM3 wave address (low)
PCM_ADDR_H_3		equ $FF002B				; PCM3 wave address (high)
PCM_ADDR_L_4		equ $FF002D				; PCM4 wave address (low)
PCM_ADDR_H_4		equ $FF002F				; PCM4 wave address (high)
PCM_ADDR_L_5		equ $FF0031				; PCM5 wave address (low)
PCM_ADDR_H_5		equ $FF0033				; PCM5 wave address (high)
PCM_ADDR_L_6		equ $FF0035				; PCM6 wave address (low)
PCM_ADDR_H_6		equ $FF0037				; PCM6 wave address (high)
PCM_ADDR_L_7		equ $FF0039				; PCM7 wave address (low)
PCM_ADDR_H_7		equ $FF003B				; PCM7 wave address (high)
PCM_ADDR_L_8		equ $FF003D				; PCM8 wave address (low)
PCM_ADDR_H_8		equ $FF003F				; PCM8 wave address (high)

; ------------------------------------------------------------------------------
; Wave RAM
; ------------------------------------------------------------------------------

WAVE_RAM_BANK		equ $FF2001				; Wave RAM bank start
WAVE_RAM_BANK_END	equ $FF3FFF				; Wave RAM bank end
WAVE_RAM_BANK_SIZE	equ $1000				; Wave RAM bank size

; ------------------------------------------------------------------------------
; Gate array
; ------------------------------------------------------------------------------

MCD_REGS		equ $FFFF8000				; Mega CD registers
MCD_LED_CTRL		equ $FFFF8000				; LED control
MCD_RESET		equ $FFFF8001				; Periphery reset
MCD_PROTECT		equ $FFFF8002				; Program RAM write protection
MCD_MEM_MODE		equ $FFFF8003				; Memory mode
MCD_CDC_MODE		equ $FFFF8004				; CDC mode
MCD_CDC_REG_ADDR	equ $FFFF8005				; CDC register address
MCD_CDC_REG_DATA	equ $FFFF8007				; CDC register data
MCD_CDC_HOST		equ $FFFF8008				; CDC host data
MCD_CDC_DMA		equ $FFFF800A				; CDC DMA address
MCD_STOPWATCH		equ $FFFF800C				; Stopwatch
MCD_COMM_FLAGS		equ $FFFF800E				; Communication flags
MCD_MAIN_FLAG		equ $FFFF800E				; Main CPU communication flag
MCD_SUB_FLAG		equ $FFFF800F				; Sub CPU communication flag
MCD_MAIN_COMMS		equ $FFFF8010				; Main CPU communication registers
MCD_MAIN_COMM_0		equ $FFFF8010				; Main CPU communication register 0
MCD_MAIN_COMM_1		equ $FFFF8011				; Main CPU communication register 1
MCD_MAIN_COMM_2		equ $FFFF8012				; Main CPU communication register 2
MCD_MAIN_COMM_3		equ $FFFF8013				; Main CPU communication register 3
MCD_MAIN_COMM_4		equ $FFFF8014				; Main CPU communication register 4
MCD_MAIN_COMM_5		equ $FFFF8015				; Main CPU communication register 5
MCD_MAIN_COMM_6		equ $FFFF8016				; Main CPU communication register 6
MCD_MAIN_COMM_7		equ $FFFF8017				; Main CPU communication register 7
MCD_MAIN_COMM_8		equ $FFFF8018				; Main CPU communication register 8
MCD_MAIN_COMM_9		equ $FFFF8019				; Main CPU communication register 9
MCD_MAIN_COMM_10	equ $FFFF801A				; Main CPU communication register 10
MCD_MAIN_COMM_11	equ $FFFF801B				; Main CPU communication register 11
MCD_MAIN_COMM_12	equ $FFFF801C				; Main CPU communication register 12
MCD_MAIN_COMM_13	equ $FFFF801D				; Main CPU communication register 13
MCD_MAIN_COMM_14	equ $FFFF801E				; Main CPU communication register 14
MCD_MAIN_COMM_15	equ $FFFF801F				; Main CPU communication register 15
MCD_SUB_COMMS		equ $FFFF8020				; Sub CPU communication registers
MCD_SUB_COMM_0		equ $FFFF8020				; Sub CPU communication register 0
MCD_SUB_COMM_1		equ $FFFF8021				; Sub CPU communication register 1
MCD_SUB_COMM_2		equ $FFFF8022				; Sub CPU communication register 2
MCD_SUB_COMM_3		equ $FFFF8023				; Sub CPU communication register 3
MCD_SUB_COMM_4		equ $FFFF8024				; Sub CPU communication register 4
MCD_SUB_COMM_5		equ $FFFF8025				; Sub CPU communication register 5
MCD_SUB_COMM_6		equ $FFFF8026				; Sub CPU communication register 6
MCD_SUB_COMM_7		equ $FFFF8027				; Sub CPU communication register 7
MCD_SUB_COMM_8		equ $FFFF8028				; Sub CPU communication register 8
MCD_SUB_COMM_9		equ $FFFF8029				; Sub CPU communication register 9
MCD_SUB_COMM_10		equ $FFFF802A				; Sub CPU communication register 10
MCD_SUB_COMM_11		equ $FFFF802B				; Sub CPU communication register 11
MCD_SUB_COMM_12		equ $FFFF802C				; Sub CPU communication register 12
MCD_SUB_COMM_13		equ $FFFF802D				; Sub CPU communication register 13
MCD_SUB_COMM_14		equ $FFFF802E				; Sub CPU communication register 14
MCD_SUB_COMM_15		equ $FFFF802F				; Sub CPU communication register 15
MCD_IRQ3_TIME		equ $FFFF8031				; Timer interrupt timer
MCD_IRQ_MASK		equ $FFFF8033				; Interrupt mask
MCD_FADER		equ $FFFF8034				; Fader volume and control
MCD_CDD_TYPE		equ $FFFF8036				; CDD data type
MCD_CDD_CTRL		equ $FFFF8037				; CDD control
MCD_CDD_STATS		equ $FFFF8038				; CDD statuses
MCD_CDD_STAT_0		equ $FFFF8038				; CDD status 0
MCD_CDD_STAT_1		equ $FFFF8039				; CDD status 1
MCD_CDD_STAT_2		equ $FFFF803A				; CDD status 2
MCD_CDD_STAT_3		equ $FFFF803B				; CDD status 3
MCD_CDD_STAT_4		equ $FFFF803C				; CDD status 4
MCD_CDD_STAT_5		equ $FFFF803D				; CDD status 5
MCD_CDD_STAT_6		equ $FFFF803E				; CDD status 6
MCD_CDD_STAT_7		equ $FFFF803F				; CDD status 7
MCD_CDD_STAT_8		equ $FFFF8040				; CDD status 8
MCD_CDD_STAT_9		equ $FFFF8041				; CDD status 9
MCD_CDD_CMDS		equ $FFFF8042				; CDD commands
MCD_CDD_CMD_0		equ $FFFF8042				; CDD command 0
MCD_CDD_CMD_1		equ $FFFF8043				; CDD command 1
MCD_CDD_CMD_2		equ $FFFF8044				; CDD command 2
MCD_CDD_CMD_3		equ $FFFF8045				; CDD command 3
MCD_CDD_CMD_4		equ $FFFF8046				; CDD command 4
MCD_CDD_CMD_5		equ $FFFF8047				; CDD command 5
MCD_CDD_CMD_6		equ $FFFF8048				; CDD command 6
MCD_CDD_CMD_7		equ $FFFF8049				; CDD command 7
MCD_CDD_CMD_8		equ $FFFF804A				; CDD command 8
MCD_CDD_CMD_9		equ $FFFF804B				; CDD command 9
MCD_1BPP_COLOR		equ $FFFF804C				; 1BPP conversion color
MCD_1BPP_IN		equ $FFFF804E				; 1BPP conversion input data
MCD_1BPP_OUT		equ $FFFF8050				; 1BPP conversion output data
MCD_IMG_RENDER		equ $FFFF8058				; Image rendering flag
MCD_IMG_SIZES		equ $FFFF8059				; Image render sizes
MCD_IMG_STAMP_MAP	equ $FFFF805A				; Image stamp map address
MCD_IMG_STRIDE		equ $FFFF805C				; Image buffer stride
MCD_IMG_START		equ $FFFF805E				; Image buffer address
MCD_IMG_OFFSET		equ $FFFF8061				; Image buffer pixel offset
MCD_IMG_WIDTH		equ $FFFF8062				; Image buffer width
MCD_IMG_HEIGHT		equ $FFFF8064				; Image buffer height
MCD_IMG_TRACE		equ $FFFF8066				; Trace vector address
MCD_SUBCODE_ADDR	equ $FFFF8069				; Subcode address
MCD_SUBCODE_DATA	equ $FFFF8100				; Subcode data

; ------------------------------------------------------------------------------
; BIOS function codes
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

; ------------------------------------------------------------------------------
; Boot function codes
; ------------------------------------------------------------------------------

CBTINIT			equ 0					; Initialize boot system
CBTINT			equ 1					; Manage boot interrupt
CBTOPENDISC		equ 2					; Request disc tray open
CBTOPENSTAT		equ 3					; Check if disc tray open was completed
CBTCHKDISC		equ 4					; Check if disc is bootable
CBTCHKSTAT		equ 5					; Check boot and get disc type

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
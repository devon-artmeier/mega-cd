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

	include	"shared.inc"
	
	section header

; ------------------------------------------------------------------------------
; Vector table
; ------------------------------------------------------------------------------

	dc.l	stack						; Stack pointer
	dc.l	HardReset					; Entry point
	dc.l	BusError					; Bus error
	dc.l	AddressError					; Address error
	dc.l	IllegalInstr					; Illegal instruction
	dc.l	ZeroDivide					; Division by zero
	dc.l	ChkInstr					; CHK exception
	dc.l	TrapvInstr					; TRAPV exception
	dc.l	PrivilegeViol					; Privilege violation
	dc.l	Trace						; TRACE exception
	dc.l	Line1010Emu					; Line A emulator
	dc.l	Line1111Emu					; Line F emulator

	dcb.l	12, ErrorExcept					; Reserved

	dc.l	ErrorExcept					; Spurious exception
	dc.l	ErrorExcept					; IRQ level 1
	dc.l	ErrorExcept					; External interrupt
	dc.l	ErrorExcept					; IRQ level 3
	dc.l	HBlankIrq					; H-BLANK interrupt
	dc.l	ErrorExcept					; IRQ level 5
	dc.l	VBlankIrq					; V-BLANK interrupt
	dc.l	ErrorExcept					; IRQ level 7

	dc.l	ErrorExcept					; TRAP #00 exception
	dc.l	ErrorExcept					; TRAP #01 exception
	dc.l	ErrorExcept					; TRAP #02 exception
	dc.l	ErrorExcept					; TRAP #03 exception
	dc.l	ErrorExcept					; TRAP #04 exception
	dc.l	ErrorExcept					; TRAP #05 exception
	dc.l	ErrorExcept					; TRAP #06 exception
	dc.l	ErrorExcept					; TRAP #07 exception
	dc.l	ErrorExcept					; TRAP #08 exception
	dc.l	ErrorExcept					; TRAP #09 exception
	dc.l	ErrorExcept					; TRAP #10 exception
	dc.l	ErrorExcept					; TRAP #11 exception
	dc.l	ErrorExcept					; TRAP #12 exception
	dc.l	ErrorExcept					; TRAP #13 exception
	dc.l	ErrorExcept					; TRAP #14 exception
	dc.l	ErrorExcept					; TRAP #15 exception

	dcb.l	16, ErrorExcept					; Reserved

; ------------------------------------------------------------------------------
; ROM header
; ------------------------------------------------------------------------------

	dc.b	"SEGA MEGA DRIVE "				; Hardware ID
	dc.b	"DEVON   2025.MAY"				; Copyright
	dc.b	"Mega CD Cartridge Test                          "
	dc.b	"Mega CD Cartridge Test                          "
	dc.b	"GM XXXXXXXX-00"				; Version
	dc.w	0						; Checksum
	dc.b	"J               "				; I/O support
	dc.l	CARTRIDGE, CARTRIDGE_END			; ROM start and end
	dc.l	WORK_RAM, WORK_RAM_END				; RAM start and end
	dc.l	$20202020, $20202020, $20202020			; SRAM support
	dc.b	"            "					; Modem support
	dc.b	"                                        "	; Notes
	dc.b	"JUE             "				; Region

; ------------------------------------------------------------------------------
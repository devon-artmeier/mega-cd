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
USE_DOMESTIC		equ %0011				; Allow domestic models
USE_OVERSEAS		equ %1100				; Allow overseas models
USE_NTSC		equ %0101				; Allow NTSC models
USE_PAL			equ %1010				; Allow PAL models
USE_ALL_MODELS		equ %1111				; Allow all models
USE_JAPAN		equ %0001				; Allow Japan models
USE_USA			equ %0100				; Allow USA models
USE_EUROPE		equ %1000				; Allow Europe models

; ------------------------------------------------------------------------------
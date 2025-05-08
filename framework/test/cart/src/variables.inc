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
; Memory map and variables
; ------------------------------------------------------------------------------

	rsset WORK_RAM
scratch_buffer		rs.b $8000				; Scratch buffer

variables		rs.b 0					; Global variables
			rseven
variables_end		rs.b 0

scene_variables		rs.b 0					; Scene variables
			rs.b (WORK_RAM_END-$1FF)-__RS
scene_variables_end	rs.b 0

			rs.b $200				; Stack space
stack			rs.b 0					; Stack base

; ------------------------------------------------------------------------------
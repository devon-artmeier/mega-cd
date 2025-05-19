# ------------------------------------------------------------------------------
# Commands
# ------------------------------------------------------------------------------

ifeq ($(OS),Windows_NT)
MKDIR                := mkdir
RMDIR                := rmdir /s /q
else
MKDIR                := mkdir -p
RMDIR                := rm -rf
endif

# ------------------------------------------------------------------------------
# Tools
# ------------------------------------------------------------------------------

VASM                 := vasmm68k_mot
VLINK                := vlink
MKASMDEP             := mkasmdep
DUMPASMSYM           := dumpasmsym
MDROMFIX             := mdromfix

VASM_FLAGS           := -Fvobj -quiet -ldots -spaces -nowarn=62
VLINK_FLAGS          := -b rawbin
MKASMDEP_FLAGS       := -r
DUMPASMSYM_FLAGS     := -m asm
MDROMFIX_FLAGS       := -q

# ------------------------------------------------------------------------------
# Messages
# ------------------------------------------------------------------------------

DEPEND_MSG            = @echo Generating $@
ASSEMBLE_MSG          = @echo Assembling $<
LINK_MSG              = @echo Linking    $@
EXPORT_MSG            = @echo Exporting  $@

# ------------------------------------------------------------------------------
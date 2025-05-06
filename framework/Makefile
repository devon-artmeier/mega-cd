# ------------------------------------------------------------------------------
# Tools
# ------------------------------------------------------------------------------

VASM               := vasmm68k_mot
VLINK              := vlink
MKASMDEP           := mkasmdep
DUMPASMSYM         := dumpasmsym

VASM_FLAGS         := -quiet -Fvobj -ldots -spaces -Iinclude
VLINK_FLAGS        := -b rawbin
MKASMDEP_FLAGS     := -r
DUMPASMSYM_FLAGS   := -m asm

# ------------------------------------------------------------------------------
# Messages
# ------------------------------------------------------------------------------

ASSEMBLE_MSG        = @echo Assembling $<
LINK_MSG            = @echo Linking    $@
DEPEND_MSG          = @echo Generating $@
DUMP_MSG            = @echo Dumping   

# ------------------------------------------------------------------------------
# Paths
# ------------------------------------------------------------------------------

OUT_PATH           := out
SRC_PATH           := src
OBJ_PATH           := $(OUT_PATH)/obj

OUT_PATH_EXISTS    := $(wildcard $(OUT_PATH))

# ------------------------------------------------------------------------------
# Main CPU module files
# ------------------------------------------------------------------------------

SRC_PATH_MAIN      := $(SRC_PATH)/main
OBJ_PATH_MAIN      := $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_PATH_MAIN))
OBJ_PATH_MAIN_CART := $(OBJ_PATH_MAIN)/cart
OBJ_PATH_MAIN_CD   := $(OBJ_PATH_MAIN)/cd

SRC_MAIN           := $(wildcard $(SRC_PATH_MAIN)/*.asm)
OBJ_MAIN_CART      := $(patsubst $(SRC_PATH_MAIN)/%.asm,$(OBJ_PATH_MAIN_CART)/%.o,$(SRC_MAIN))
OBJ_MAIN_CD        := $(patsubst $(SRC_PATH_MAIN)/%.asm,$(OBJ_PATH_MAIN_CD)/%.o,$(SRC_MAIN))
DEPEND_MAIN_CART   := $(patsubst %.o,%.d,$(OBJ_MAIN_CART))
DEPEND_MAIN_CD     := $(patsubst %.o,%.d,$(OBJ_MAIN_CD))

OUT_MAIN_CART      := $(OUT_PATH)/mcd_framework_main_cart.bin
OUT_MAIN_CD        := $(OUT_PATH)/mcd_framework_main_cd.bin
SYM_MAIN_CART      := $(patsubst %.bin,%.inc,$(OUT_MAIN_CART))
SYM_MAIN_CD        := $(patsubst %.bin,%.inc,$(OUT_MAIN_CD))

# ------------------------------------------------------------------------------
# Sub CPU module files
# ------------------------------------------------------------------------------

SRC_PATH_SUB       := $(SRC_PATH)/sub
OBJ_PATH_SUB       := $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_PATH_SUB))

SRC_SUB            := $(wildcard $(SRC_PATH_SUB)/*.asm)
OBJ_SUB            := $(patsubst $(SRC_PATH)/%.asm,$(OBJ_PATH)/%.o,$(SRC_SUB))
DEPEND_SUB         := $(patsubst %.o,%.d,$(OBJ_SUB))

OUT_SUB            := $(OUT_PATH)/mcd_framework_sub.bin
SYM_SUB            := $(patsubst %.bin,%.inc,$(OUT_SUB))

# ------------------------------------------------------------------------------
# Reserved rules
# ------------------------------------------------------------------------------

.PHONY: all clean

# ------------------------------------------------------------------------------
# Make all
# ------------------------------------------------------------------------------

all: $(OUT_MAIN_CART) $(OUT_MAIN_CD) $(OUT_SUB)

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------

clean:
ifneq ($(OUT_PATH_EXISTS),)
	@rmdir /s /q "$(OUT_PATH)"
endif

# ------------------------------------------------------------------------------
# Main CPU (cartridge) module rules
# ------------------------------------------------------------------------------

$(OUT_MAIN_CART): $(OBJ_MAIN_CART) | $(OUT_PATH)
	$(LINK_MSG)
	$(DUMP_MSG) $(SYM_MAIN_CART)
	@$(VLINK) $(VLINK_FLAGS) -o $@ $^
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $(SYM_MAIN_CART) $^

$(OBJ_MAIN_CART): $(OBJ_PATH_MAIN_CART)/%.o: $(SRC_PATH_MAIN)/%.asm | $(DEPEND_MAIN_CART)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -DUSE_MCD_MODE_1=1 -o $@ $<

$(DEPEND_MAIN_CART): $(OBJ_PATH_MAIN_CART)/%.d: $(SRC_PATH_MAIN)/%.asm | $(OBJ_PATH_MAIN_CART)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Main CPU (CD) module rules
# ------------------------------------------------------------------------------

$(OUT_MAIN_CD): $(OBJ_MAIN_CD) | $(OUT_PATH)
	$(LINK_MSG)
	$(DUMP_MSG) $(SYM_MAIN_CD)
	@$(VLINK) $(VLINK_FLAGS) -o $@ $^
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $(SYM_MAIN_CD) $^

$(OBJ_MAIN_CD): $(OBJ_PATH_MAIN_CD)/%.o: $(SRC_PATH_MAIN)/%.asm | $(DEPEND_MAIN_CD)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -DUSE_MCD_MODE_1=0 -o $@ $<

$(DEPEND_MAIN_CD): $(OBJ_PATH_MAIN_CD)/%.d: $(SRC_PATH_MAIN)/%.asm | $(OBJ_PATH_MAIN_CD)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Sub CPU module rules
# ------------------------------------------------------------------------------

$(OUT_SUB): $(OBJ_SUB) | $(OUT_PATH)
	$(LINK_MSG)
	$(DUMP_MSG) $(SYM_SUB)
	@$(VLINK) $(VLINK_FLAGS) -o $@ $^
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $(SYM_SUB) $^

$(OBJ_SUB): $(OBJ_PATH)/%.o: $(SRC_PATH)/%.asm | $(DEPEND_SUB)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -o $@ $<

$(DEPEND_SUB): $(OBJ_PATH)/%.d: $(SRC_PATH)/%.asm | $(OBJ_PATH_SUB)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Path rules
# ------------------------------------------------------------------------------

$(OUT_PATH):
	@mkdir "$@"

$(OBJ_PATH_MAIN_CART):
	@mkdir "$@"
	
$(OBJ_PATH_MAIN_CD):
	@mkdir "$@"

$(OBJ_PATH_SUB):
	@mkdir "$@"

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

ifneq (clean,$(filter clean,$(MAKECMDGOALS)))
-include $(DEPEND_MAIN_CART)
-include $(DEPEND_MAIN_CD)
-include $(DEPEND_SUB)
endif

# ------------------------------------------------------------------------------
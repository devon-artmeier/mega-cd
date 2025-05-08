# ------------------------------------------------------------------------------
# Paths
# ------------------------------------------------------------------------------

OUT_PATH             := out
SRC_PATH             := src
INCLUDE_PATH         := include
BUILD_PATH           := $(OUT_PATH)/build

OUT_PATH_EXISTS      := $(wildcard $(OUT_PATH))

# ------------------------------------------------------------------------------
# Tools
# ------------------------------------------------------------------------------

VASM                 := vasmm68k_mot
VLINK                := vlink
MKASMDEP             := mkasmdep
DUMPASMSYM           := dumpasmsym

VASM_FLAGS           := -Fvobj -I$(INCLUDE_PATH) -quiet -ldots -spaces
VLINK_FLAGS          := -b rawbin -symctrl=4
MKASMDEP_FLAGS       := -r -i $(INCLUDE_PATH)
DUMPASMSYM_FLAGS     := -m asm -xp INT_

# ------------------------------------------------------------------------------
# Messages
# ------------------------------------------------------------------------------

DEPEND_MSG            = @echo Generating $@
ASSEMBLE_MSG          = @echo Assembling $<
LINK_MSG              = @echo Linking    $@
EXPORT_MSG            = @echo Exporting  $@

# ------------------------------------------------------------------------------
# Main CPU functions files
# ------------------------------------------------------------------------------

SRC_PATH_MAIN        := $(SRC_PATH)/main_cpu
BUILD_PATH_MAIN      := $(subst $(SRC_PATH),$(BUILD_PATH),$(SRC_PATH_MAIN))
BUILD_PATH_MAIN_CART := $(BUILD_PATH_MAIN)/cart
BUILD_PATH_MAIN_CD   := $(BUILD_PATH_MAIN)/cd

SRC_MAIN             := $(wildcard $(SRC_PATH_MAIN)/*.asm)
OBJ_MAIN_CART        := $(patsubst $(SRC_PATH_MAIN)/%.asm,$(BUILD_PATH_MAIN_CART)/%.o,$(SRC_MAIN))
OBJ_MAIN_CD          := $(patsubst $(SRC_PATH_MAIN)/%.asm,$(BUILD_PATH_MAIN_CD)/%.o,$(SRC_MAIN))
DEPEND_MAIN_CART     := $(patsubst %.o,%.d,$(OBJ_MAIN_CART))
DEPEND_MAIN_CD       := $(patsubst %.o,%.d,$(OBJ_MAIN_CD))

OUT_MAIN_CART        := $(OUT_PATH)/mcd_framework_main_cart.bin
SYM_MAIN_CART        := $(patsubst $(OUT_PATH)/%.bin,$(BUILD_PATH)/%.sym,$(OUT_MAIN_CART))
EXPORT_MAIN_CART     := $(patsubst %.bin,%.inc,$(OUT_MAIN_CART))

OUT_MAIN_CD          := $(OUT_PATH)/mcd_framework_main_cd.bin
SYM_MAIN_CD          := $(patsubst $(OUT_PATH)/%.bin,$(BUILD_PATH)/%.sym,$(OUT_MAIN_CD))
EXPORT_MAIN_CD       := $(patsubst %.bin,%.inc,$(OUT_MAIN_CD))

LINKER_MAIN          := linker_main.link

# ------------------------------------------------------------------------------
# Sub CPU program files
# ------------------------------------------------------------------------------

SRC_PATH_SUB         := $(SRC_PATH)/sub_cpu
BUILD_PATH_SUB       := $(subst $(SRC_PATH),$(BUILD_PATH),$(SRC_PATH_SUB))

SRC_SUB              := $(wildcard $(SRC_PATH_SUB)/*.asm)
OBJ_SUB              := $(patsubst $(SRC_PATH)/%.asm,$(BUILD_PATH)/%.o,$(SRC_SUB))
DEPEND_SUB           := $(patsubst %.o,%.d,$(OBJ_SUB))

OUT_SUB              := $(OUT_PATH)/mcd_framework_sub.bin
SYM_SUB              := $(patsubst $(OUT_PATH)/%.bin,$(BUILD_PATH)/%.sym,$(OUT_SUB))
EXPORT_SUB           := $(patsubst %.bin,%.inc,$(OUT_SUB))

LINKER_SUB           := linker_sub.link

# ------------------------------------------------------------------------------
# Reserved rules
# ------------------------------------------------------------------------------

.PHONY: all clean

# ------------------------------------------------------------------------------
# Make all
# ------------------------------------------------------------------------------

all: $(OUT_MAIN_CART) $(EXPORT_MAIN_CART) $(OUT_MAIN_CD) $(EXPORT_MAIN_CD) $(OUT_SUB) $(EXPORT_SUB)

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------

clean:
ifneq ($(OUT_PATH_EXISTS),)
	@rmdir /s /q "$(OUT_PATH)"
endif

# ------------------------------------------------------------------------------
# Main CPU (cartridge) functions rules
# ------------------------------------------------------------------------------

$(EXPORT_MAIN_CART): $(SYM_MAIN_CART) | $(OUT_PATH) $(OUT_MAIN_CART)
	$(EXPORT_MSG)
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $@ $^
	
$(OUT_MAIN_CART): $(OBJ_MAIN_CART) | $(OUT_PATH)
	$(LINK_MSG)
	@$(VLINK) $(VLINK_FLAGS) -T $(LINKER_MAIN) -symfile $(SYM_MAIN_CART) -o $@ $^

$(OBJ_MAIN_CART): $(BUILD_PATH_MAIN_CART)/%.o: $(SRC_PATH_MAIN)/%.asm | $(DEPEND_MAIN_CART)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -DUSE_MCD_MODE_1=1 -L $(patsubst %.o,%.lst,$@) -o $@ $<

$(DEPEND_MAIN_CART): $(BUILD_PATH_MAIN_CART)/%.d: $(SRC_PATH_MAIN)/%.asm | $(BUILD_PATH_MAIN_CART)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Main CPU (CD) functions rules
# ------------------------------------------------------------------------------

$(EXPORT_MAIN_CD): $(SYM_MAIN_CD) | $(OUT_PATH) $(OUT_MAIN_CD)
	$(EXPORT_MSG)
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $@ $^
	
$(OUT_MAIN_CD): $(OBJ_MAIN_CD) | $(OUT_PATH)
	$(LINK_MSG)
	@$(VLINK) $(VLINK_FLAGS) -T $(LINKER_MAIN) -symfile $(SYM_MAIN_CD) -o $@ $^

$(OBJ_MAIN_CD): $(BUILD_PATH_MAIN_CD)/%.o: $(SRC_PATH_MAIN)/%.asm | $(DEPEND_MAIN_CD)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -DUSE_MCD_MODE_1=0 -L $(patsubst %.o,%.lst,$@) -o $@ $<

$(DEPEND_MAIN_CD): $(BUILD_PATH_MAIN_CD)/%.d: $(SRC_PATH_MAIN)/%.asm | $(BUILD_PATH_MAIN_CD)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Sub CPU program rules
# ------------------------------------------------------------------------------

$(EXPORT_SUB): $(SYM_SUB) | $(OUT_PATH) $(OUT_SUB)
	$(EXPORT_MSG)
	@$(DUMPASMSYM) $(DUMPASMSYM_FLAGS) -o $@ $^

$(OUT_SUB): $(OBJ_SUB) | $(OUT_PATH)
	$(LINK_MSG)
	@$(VLINK) $(VLINK_FLAGS) -T $(LINKER_SUB) -symfile $(SYM_SUB) -o $@ $^

$(OBJ_SUB): $(BUILD_PATH)/%.o: $(SRC_PATH)/%.asm | $(DEPEND_SUB)
	$(ASSEMBLE_MSG)
	@$(VASM) $(VASM_FLAGS) -L $(patsubst %.o,%.lst,$@) -o $@ $<

$(DEPEND_SUB): $(BUILD_PATH)/%.d: $(SRC_PATH)/%.asm | $(BUILD_PATH_SUB)
	$(DEPEND_MSG)
	@$(MKASMDEP) $(MKASMDEP_FLAGS) -o $@ $(patsubst %.d,%.o,$@) $<

# ------------------------------------------------------------------------------
# Path rules
# ------------------------------------------------------------------------------

$(OUT_PATH):
	@mkdir "$@"

$(BUILD_PATH_MAIN_CART):
	@mkdir "$@"
	
$(BUILD_PATH_MAIN_CD):
	@mkdir "$@"

$(BUILD_PATH_SUB):
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
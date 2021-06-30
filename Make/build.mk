#
# build.mk
#

# toolchain

include ../Make/toolchain.mk

# sources, headers, compiling options

-include $(wildcard oal/bsp/Makefile)
-include $(wildcard oal/kernel/Makefile)
-include $(wildcard oal/drivers/*/Makefile)
-include $(wildcard oal/iw/Makefile)
# -include $(wildcard oal/interface/Makefile)
# -include $(wildcard Microservice/*/Makefile)
ifneq ($(PROJECT_PATH),)
-include $(wildcard $(PROJECT_PATH)/Makefile)
endif

# general options

ifeq ($(IW_OS),)
# $(error IW_OS is not defined)
else
MACROS += -DIW_$(shell echo $(IW_OS) | tr '[:lower:]' '[:upper:]')=1
endif # IW_OS

ifeq ($(IW_BSP),)
# $(error IW_BSP is not defined)
else
MACROS += -DIW_$(shell echo $(IW_BSP) | tr '[:lower:]' '[:upper:]')=1
endif # IW_BSP

MACROS += -D__IOTWARE__

IW_INCS += include
IW_SRCS +=# end of line
IW_LDLIBS +=# end of line
IW_CFLAGS += $(MACROS)
IW_CXXFLAGS += $(MACROS)
IW_CPPFLAGS += $(MACROS)
IW_ARFLAGS += $(MACROS)
IW_ASFLAGS += $(MACROS)
IW_LDFLAGS += $(MACROS)

# output

PROJECT_PATH ?= $(CURDIR)
OUT ?= $(PROJECT_PATH)/out
TAR ?= iotware
EXT ?= .bin

# objects

OBJS := $(IW_SRCS)
OBJS := $(OBJS:%.S=%.o)
OBJS := $(OBJS:%.s=%.o)
OBJS := $(OBJS:%.cpp=%.o)
OBJS := $(OBJS:%.C=%.o)
OBJS := $(OBJS:%.cc=%.o)
OBJS := $(OBJS:%.c=%.o)

# commands

.DEFAULT: build

build: $(TAR)

$(TAR): $(OUT)/$(TAR)

$(OUT)/$(TAR): $(OUT)/$(TAR)$(EXT)
	$(CP) $< $@

$(OUT)/$(TAR).bin: $(OUT)/$(TAR).elf
	$(OBJCOPY) -O binary $< $@

$(OUT)/$(TAR).hex: $(OUT)/$(TAR).elf
	$(OBJCOPY) -O ihex $< $@
	
$(OUT)/$(TAR).elf: $(OBJS:%=$(OUT)/%)
	$(MD) $(dir $@)
	$(LD) -Wl,-Map=$(@:%.elf=%.map) $(IW_CFLAGS) $(IW_LDFLAGS) $? $(IW_LDLIBS) -o $@

$(OUT)/%.o: %.S
	$(MD) $(dir $@)
	$(AS) $(IW_CFLAGS) $(IW_ASFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.s
	$(MD) $(dir $@)
	$(AS) $(IW_CFLAGS) $(IW_ASFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.cpp
	$(MD) $(dir $@)
	$(CXX) $(IW_CXXFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.C
	$(MD) $(dir $@)
	$(CXX) $(IW_CXXFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.cc
	$(MD) $(dir $@)
	$(CXX) $(IW_CXXFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.c
	$(MD) $(dir $@)
	$(CC) $(IW_CFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

clean:
	$(RM) $(TAR)
	$(RM) $(OUT)

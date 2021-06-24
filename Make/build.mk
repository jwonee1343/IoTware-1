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
-include $(wildcard oal/interface/Makefile)

# general options

IW_INCS += include
IW_SRCS +=# End of line
IW_CFLAGS += -D__IOTWARE__
IW_CXXFLAGS += -D__IOTWARE__
IW_CPPFLAGS += -D__IOTWARE__
IW_ARFLAGS += -D__IOTWARE__
IW_ASFLAGS += -D__IOTWARE__
IW_LDFLAGS += -D__IOTWARE__

# output attributes

OUT ?= out
TAR ?= iotware
EXT ?= .bin

OBJS := $(IW_SRCS)
OBJS := $(OBJS:%.S=%.o)
OBJS := $(OBJS:%.s=%.o)
OBJS := $(OBJS:%.cpp=%.o)
OBJS := $(OBJS:%.C=%.o)
OBJS := $(OBJS:%.cc=%.o)
OBJS := $(OBJS:%.c=%.o)

# commands

.DEFAULT: build

$(OUT)/%.o: %.S
	$(MD) $(dir $@)
	$(AS) $(IW_ASFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

$(OUT)/%.o: %.s
	$(MD) $(dir $@)
	$(AS) $(IW_ASFLAGS) $(IW_INCS:%=-I%) -MMD -MF $(@:%.o=%.d) -c -o $@ $<

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

$(OUT)/$(TAR).elf: $(OBJS:%=$(OUT)/%)

$(OUT)/$(TAR).hex: $(OUT)/$(TAR).elf

$(OUT)/$(TAR).bin: $(OUT)/$(TAR).elf

$(OUT)/$(TAR): $(OUT)/$(TAR)$(EXT)

$(TAR): $(OUT)/$(TAR)
# $(CP) $< $@

build: $(TAR)

clean:
	$(RM) $(TAR)
	$(RM) $(OUT)

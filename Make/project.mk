#
# project.mk
#

# toolchain

include ../Make/toolchain.mk

# check requirements

ifeq ($(IW_OS),)
$(error IW_OS is not defined)
endif # KERNEL

ifeq ($(IW_BSP),)
$(error IW_BSP is not defined)
endif # BSP

# allow 0 driver

# ifeq ($(IW_DRIVERS),)
# $(error IW_DRIVERS is not defined)
# endif # IW_DRIVERS

# path

EXT ?= ../External

# commands

copy:
	$(CP) $(EXT)/bsp/$(IW_BSP)/* oal/bsp/.
	$(CP) $(EXT)/kernel/$(IW_OS)/* oal/kernel/.
ifneq ($(IW_DRIVERS),)
	$(CP) $(IW_DRIVERS:%=$(EXT)/drivers/%) oal/drivers/.
endif # IW_DRIVERS

clean:
	$(RM) oal/bsp/*
	$(RM) oal/kernel/*
	$(RM) oal/drivers/*
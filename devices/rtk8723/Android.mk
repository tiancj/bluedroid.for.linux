
# Configuration

LOCAL_PATH := $(call my-dir)

# applied to REALTECK8723
ifeq ($(strip $(R_BT_TYPE)), rtl8723)
BUILD_RTL8723  := true
endif

#subdirectory
#include $(call first-makefiles-under,$(LOCAL_PATH))
include $(call all-subdir-makefiles)



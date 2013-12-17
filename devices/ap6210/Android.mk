
# Configuration

LOCAL_PATH := $(call my-dir)

# applied to AP6210
ifeq ($(strip $(R_BT_TYPE)), ap6210)
BUILD_AP6210  := true
endif

#subdirectory
include $(call first-makefiles-under,$(LOCAL_PATH))



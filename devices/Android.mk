
# Configuration

LOCAL_PATH := $(call my-dir)

# applied to MT6622
ifeq ($(strip $(R_BT_TYPE)), mt6622)
BUILD_MT6622  := true
endif

# applied to RTL8723
ifeq ($(strip $(R_BT_TYPE)), rtl8723)
BUILD_RTL8723  := true
endif

# applied to AP6210
ifeq ($(strip $(R_BT_TYPE)), ap6210)
BUILD_AP6210  := true
endif

ifeq ($(BUILD_MT6622), true)
#subdirectory
include $(LOCAL_PATH)/mtk6622/Android.mk
endif

ifeq ($(BUILD_RTL8723), true)
#subdirectory
include $(LOCAL_PATH)/rtk8723/Android.mk
endif

ifeq ($(BUILD_AP6210), true)
#subdirectory
include $(LOCAL_PATH)/ap6210/Android.mk
endif

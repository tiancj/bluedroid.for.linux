set(LOCAL_C_INCLUDES 
	common 
	ulinux 
	../include 
	../stack/include 
	../utils/include 
	${bdroid_C_INCLUDES} )
include_directories(${LOCAL_C_INCLUDES})

#
#LOCAL_CFLAGS += -Werror $(bdroid_CFLAGS)
#
#ifeq ($(BOARD_HAVE_BLUETOOTH_BCM),true)
#LOCAL_CFLAGS += \
#	-DBOARD_HAVE_BLUETOOTH_BCM
#endif
set(LOCAL_SRC_FILES 
    ulinux/gki_ulinux.c 
    common/gki_debug.c 
    common/gki_time.c 
    common/gki_buffer.c)
set(LOCAL_MODULE libbt-brcm_gki)
add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")

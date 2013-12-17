# HAL layer
set(LOCAL_SRC_FILES
	../btif/src/bluetooth.c)

# platform specific
set(LOCAL_SRC_FILES
	${LOCAL_SRC_FILES}
	bte_main.c 
	bte_init.c 
	bte_version.c 
	bte_logmsg.c 
	bte_conf.c)

# BTIF
set(LOCAL_SRC_FILES
	${LOCAL_SRC_FILES}
    ../btif/src/btif_core.c 
    ../btif/src/btif_dm.c 
    ../btif/src/btif_storage.c 
    ../btif/src/btif_util.c 
    ../btif/src/btif_sm.c 
    ../btif/src/btif_hf.c 
    ../btif/src/btif_av.c 
    ../btif/src/btif_rc.c 
    ../btif/src/btif_media_task.c 
    ../btif/src/btif_hh.c 
    ../btif/src/btif_hl.c 
    ../btif/src/btif_sock.c 
    ../btif/src/btif_sock_rfc.c 
    ../btif/src/btif_sock_thread.c 
    ../btif/src/btif_sock_sdp.c 
    ../btif/src/btif_sock_util.c 
    ../btif/src/btif_pan.c 
    ../btif/src/btif_config.c 
    ../btif/src/btif_config_util.cpp 
    ../btif/src/btif_profile_queue.c)

# callouts
set(LOCAL_SRC_FILES
	${LOCAL_SRC_FILES}
    ../btif/co/bta_sys_co.c 
    ../btif/co/bta_fs_co.c 
    ../btif/co/bta_ag_co.c 
    ../btif/co/bta_dm_co.c 
    ../btif/co/bta_av_co.c 
    ../btif/co/bta_hh_co.c 
    ../btif/co/bta_hl_co.c 
    ../btif/co/bta_pan_co.c)

# sbc encoder
set(LOCAL_SRC_FILES
	${LOCAL_SRC_FILES}
	../embdrv/sbc/encoder/srce/sbc_analysis.c 
	../embdrv/sbc/encoder/srce/sbc_dct.c 
	../embdrv/sbc/encoder/srce/sbc_dct_coeffs.c 
	../embdrv/sbc/encoder/srce/sbc_enc_bit_alloc_mono.c 
	../embdrv/sbc/encoder/srce/sbc_enc_bit_alloc_ste.c 
	../embdrv/sbc/encoder/srce/sbc_enc_coeffs.c 
	../embdrv/sbc/encoder/srce/sbc_encoder.c 
	../embdrv/sbc/encoder/srce/sbc_packing.c )

set(LOCAL_SRC_FILES
	${LOCAL_SRC_FILES}
	../udrv/ulinux/uipc.c)

set(LOCAL_C_INCLUDES
	. 
	..
	../bta/include 
	../bta/sys 
	../bta/dm 
	../gki/common 
	../gki/ulinux 
	../include 
	../stack/include 
	../stack/l2cap 
	../stack/a2dp 
	../stack/btm 
	../stack/avdt 
	../hcis 
	../hcis/include 
	../hcis/patchram 
	../udrv/include 
	../btif/include 
	../btif/co 
	../hci/include
	../brcm/include 
	../embdrv/sbc/encoder/include 
	../audio_a2dp_hw 
	../utils/include 
	$(bdroid_C_INCLUDES) )

#LOCAL_CFLAGS += -DBUILDCFG $(bdroid_CFLAGS) -Werror -Wno-error=maybe-uninitialized -Wno-error=uninitialized
set(LOCAL_MODULE  bluetooth.default)
add_definitions("-DLINUX_NATIVE -DSBC_FOR_EMBEDDED_LINUX")

include_directories(${LOCAL_C_INCLUDES})
add_library(${LOCAL_MODULE} SHARED ${LOCAL_SRC_FILES})
#add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
#set_target_properties(${LOCAL_MODULE} PROPERTIES OUTPUT_NAME ${LOCAL_MODULE})
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")
#target_link_libraries(${LOCAL_MODULE} ${CMAKE_THREAD_LIBS_INIT} 
#libbt-hci
#libbt-brcm_gki
#libbt-brcm_stack
#libbt-brcm_bta
#libbt-utils
#)


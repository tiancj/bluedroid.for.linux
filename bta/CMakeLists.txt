#if (${BOARD_HAVE_BLUETOOTH_BCM} EQUAL "true")
	add_definitions("-DDBOARD_HAVE_BLUETOOTH_BCM")
#endif()
add_definitions("-DBUILDCFG")
set(LOCAL_SRC_FILES dm/bta_dm_ci.c dm/bta_dm_act.c dm/bta_dm_pm.c dm/bta_dm_main.c dm/bta_dm_cfg.c dm/bta_dm_api.c 
    ./dm/bta_dm_sco.c 
    ./gatt/bta_gattc_api.c 
    ./gatt/bta_gatts_act.c 
    ./gatt/bta_gatts_main.c 
    ./gatt/bta_gattc_utils.c 
    ./gatt/bta_gattc_ci.c 
    ./gatt/bta_gatts_api.c 
    ./gatt/bta_gattc_main.c 
    ./gatt/bta_gattc_act.c 
    ./gatt/bta_gattc_cache.c 
    ./gatt/bta_gatts_utils.c 
    ./ag/bta_ag_sdp.c 
    ./ag/bta_ag_sco.c 
    ./ag/bta_ag_cfg.c 
    ./ag/bta_ag_main.c 
    ./ag/bta_ag_api.c 
    ./ag/bta_ag_rfc.c 
    ./ag/bta_ag_act.c 
    ./ag/bta_ag_cmd.c 
    ./ag/bta_ag_ci.c 
    ./ag/bta_ag_at.c 
    ./hh/bta_hh_cfg.c 
    ./hh/bta_hh_act.c 
    ./hh/bta_hh_api.c 
    ./hh/bta_hh_utils.c 
    ./hh/bta_hh_main.c 
    ./pb/bta_pbs_cfg.c 
    ./fs/bta_fs_ci.c 
    ./fs/bta_fs_cfg.c 
    ./pan/bta_pan_main.c 
    ./pan/bta_pan_ci.c 
    ./pan/bta_pan_act.c 
    ./pan/bta_pan_api.c 
    ./av/bta_av_act.c 
    ./av/bta_av_ci.c 
    ./av/bta_av_api.c 
    ./av/bta_av_aact.c 
    ./av/bta_av_main.c 
    ./av/bta_av_cfg.c 
    ./av/bta_av_ssm.c 
    ./av/bta_av_sbc.c 
    ./ar/bta_ar.c 
    ./hl/bta_hl_act.c 
    ./hl/bta_hl_api.c 
    ./hl/bta_hl_main.c 
    ./hl/bta_hl_utils.c 
    ./hl/bta_hl_sdp.c 
    ./hl/bta_hl_ci.c 
    ./sys/bta_sys_main.c 
    ./sys/bta_sys_ci.c 
    ./sys/bta_sys_conn.c 
    ./sys/bta_sys_cfg.c 
    ./sys/ptim.c 
    ./sys/bd.c 
    ./sys/utl.c 
    ./jv/bta_jv_act.c 
    ./jv/bta_jv_cfg.c 
    ./jv/bta_jv_main.c 
    ./jv/bta_jv_api.c)
#message("test" ${LOCAL_SRC_FILES})
set(LOCAL_MODULE libbt-brcm_bta)
add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
include_directories(include sys dm ../gki/common ../gki/ulinux ../include ../stack/include ../stack/btm 
                   ../hcis 
                   ../hcis/patchram 
                   ../udrv/include 
                   ../brcm/include 
				   ..)
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")
target_link_libraries(${LOCAL_MODULE} libbt-brcm_stack)


set(LOCAL_SRC_FILES 
        src/bt_vendor_rtk.c 
        src/hardware.c 
        src/userial_vendor.c 
        src/upio.c)
set(LOCAL_C_INCLUDES 
        include
		../../../hci/include)

set(LOCAL_MODULE libbt-vendor)

include_directories(${LOCAL_C_INCLUDES})
add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
#add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
#set_target_properties(${LOCAL_MODULE} PROPERTIES OUTPUT_NAME ${LOCAL_MODULE})
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")


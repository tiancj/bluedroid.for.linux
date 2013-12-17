set(LOCAL_SRC_FILES 
        src/bt_hci_bdroid.c 
        src/lpm.c 
        src/bt_hw.c 
        src/btsnoop.c 
        src/utils.c)

set(LOCAL_SRC_FILES 
		${LOCAL_SRC_FILES}
        src/hci_h4.c
        src/userial.c)

set(LOCAL_C_INCLUDES 
        include 
        ../utils/include)
set(LOCAL_MODULE libbt-hci)


include_directories(${LOCAL_C_INCLUDES})
add_library(${LOCAL_MODULE} SHARED ${LOCAL_SRC_FILES})
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")
#target_link_libraries(${LOCAL_MODULE} ${CMAKE_DL_LIBS} module -lrt)
target_link_libraries(${LOCAL_MODULE} -lrt -ldl)

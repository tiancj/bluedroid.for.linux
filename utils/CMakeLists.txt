set(LOCAL_C_INCLUDES
	include 
    ../gki/ulinux 
    ${bdroid_C_INCLUDES})

#LOCAL_CFLAGS += -Werror $(bdroid_CFLAGS)

set(LOCAL_SRC_FILES
    src/bt_utils.c
	src/tinyxml2.cpp)

set(LOCAL_MODULE libbt-utils)
include_directories(${LOCAL_C_INCLUDES})
add_library(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
set_target_properties(${LOCAL_MODULE} PROPERTIES PREFIX "")

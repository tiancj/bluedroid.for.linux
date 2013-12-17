set(LOCAL_SRC_FILES bluedroidtest.c)
set(LOCAL_MODULE bdt)
set(LOCAL_C_INCLUDES
	. 
	..
	../..)

find_package(Threads)
add_definitions("-DLINUX_NATIVE -DSBC_FOR_EMBEDDED_LINUX")
include_directories(${LOCAL_C_INCLUDES})
add_executable(${LOCAL_MODULE} ${LOCAL_SRC_FILES})
target_link_libraries(${LOCAL_MODULE} ${CMAKE_THREAD_LIBS_INIT} bluetooth.default
libbt-hci
libbt-brcm_gki
libbt-brcm_stack
libbt-brcm_bta
libbt-utils
)


cmake_minimum_required(VERSION 2.8)

# Cross-Compiler
set(CMAKE_C_COMPILER "arm-none-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-linux-gnueabi-g++")

project(BLUEDROID_FOR_LINUX)
add_definitions("-DHAS_BDROID_BUILDCFG -DLINUX_NATIVE -DANDROID_USE_LOGCAT=FALSE")
# bdroid_CFLAGS := -DHAS_BDROID_BUILDCFG
# add_subdirectory(audio_a2dp_hw)
add_subdirectory(bta)
#add_subdirectory(btif)
#add_subdirectory(conf)
#add_subdirectory(embdrv)
add_subdirectory(gki)
#add_subdirectory(hardware)
add_subdirectory(hci)
#add_subdirectory(include)
add_subdirectory(main)
add_subdirectory(stack)
add_subdirectory(test/bluedroidtest)
#add_subdirectory(tools)
#add_subdirectory(udrv)
add_subdirectory(utils)


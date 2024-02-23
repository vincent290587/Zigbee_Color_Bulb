set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.23.2)

project(ZLight VERSION 0.0.2 LANGUAGES ASM C CXX)

# -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE is mandatory")
else()
    message(STATUS "CMAKE_TOOLCHAIN_FILE= ${CMAKE_TOOLCHAIN_FILE}")
    if(NOT CMAKE_TOOLCHAIN_FILE_IN_USE)
        set(CMAKE_TOOLCHAIN_FILE_IN_USE "${CMAKE_TOOLCHAIN_FILE}" CACHE INTERNAL "The CMake toolchain file" FORCE)
    endif()
endif()

set(CMAKE_INSTALL_BINDIR          ${CMAKE_SOURCE_DIR}/versions) # Set install dir

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE        OFF)
set(CMAKE_COLOR_MAKEFILE          OFF)

# nRF5_SDK_16.0.0_98a08e2
# nRF5_SDK_17.1.0_ddde560
# nrf5_sdk_for_thread_and_zigbee_v4.2.0_af27f76
set(SDK_ROOT    "c:/Nordic/nrf5_sdk_for_thread_and_zigbee_v4.2.0_af27f76" CACHE FILEPATH "Nordic SDK path")

set(CHIP_ID     "nRF52840")
add_definitions(-DNRF52840_XXAA)
add_definitions(-DBOARD_PCA10056)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/pca10056/blank/config)

#add_definitions(-DPIN_WAT=15)
#add_definitions(-DLIS_INT1=28)
#add_definitions(-DLIS_INT2=29)
#add_definitions(-DSDA1_PIN_NUMBER=8)
#add_definitions(-DSCL1_PIN_NUMBER=7)
#add_definitions(-DSDA2_PIN_NUMBER=30)
#add_definitions(-DSCL2_PIN_NUMBER=31)
#add_definitions(-DLPS_INT7=5)
#add_definitions(-DLPS_INT5=11)
#add_definitions(-DLPS_INT6=12)

###

find_program(NRFUTIL "nrfutil")
find_program(NRFJPROG "nrfjprog")
find_program(MERGEHEX "mergehex" HINTS "c:/Program Files (x86)/Nordic Semiconductor/nrf5x/bin")

if(NOT NRFJPROG)
    message(FATAL_ERROR "nrfjprog not found, not able to merge connectivity firmware with SoftDevice.")
endif()

if(NOT MERGEHEX)
    message(FATAL_ERROR "mergehex not found, not able to merge connectivity firmware with SoftDevice.")
endif()

if(NOT NRFUTIL)
    message(FATAL_ERROR "nrfutil not found, not able to create DFU packages of connectivity firmware.")
endif()

add_custom_target(erase
        COMMAND ${NRFJPROG} --eraseall -f nrf52
)

###

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pca10056/blank/config)

add_subdirectory(sdk)

add_subdirectory(src)

###

#get_directory_property(SRC_PROJECT_NAME DIRECTORY src DEFINITION PROJECT_NAME)
#message(STATUS "Main project name: ${SRC_PROJECT_NAME}")

###

file( GENERATE OUTPUT "${CMAKE_BINARY_DIR}/.gitignore" CONTENT "*" )

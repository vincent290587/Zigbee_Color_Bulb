set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
else ()
    message(STATUS "Minimal optimization, debug info included")
endif ()

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map"
#        CONFIGURATIONS Release
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT applications
)

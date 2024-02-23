set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.17)

execute_process(COMMAND git describe --tags --dirty --always
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_DESCRIBE_INSTALL)
string(STRIP "${GIT_DESCRIBE_INSTALL}" GIT_DESCRIBE_INSTALL)
message(STATUS "Software version: ${GIT_DESCRIBE_INSTALL}")

configure_file(${CMAKE_SOURCE_DIR}/version.h.in   version.h  @ONLY)

set_source_files_properties(version.h PROPERTIES GENERATED TRUE)

target_sources(${PROJECT_NAME} PRIVATE version.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

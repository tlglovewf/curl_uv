cmake_minimum_required(VERSION 2.8)
project(curl_test)


message("---->Current OS " ${CMAKE_SYSTEM})
message("---->Current Build Type " ${CMAKE_BUILD_TYPE})
message("---->Current Build Tool " ${CMAKE_BUILD_TOOL})
find_package(CURL)

if(!CURL_FOUND)
    message("CURL NOT FOUND")
endif()

if(COMMAND cmake_policy)

    # Works around warnings libraries linked against that don't
    # have absolute paths (e.g. -lpthreads)
    cmake_policy(SET CMP0003 NEW)

    # Works around warnings about escaped quotes in ADD_DEFINITIONS
    # statements.
    cmake_policy(SET CMP0005 NEW)

    # tell CMake to prefer CMake's own CMake modules when available
    # only available from cmake-2.8.4
    if("${CMAKE_VERSION}" VERSION_GREATER 2.8.3)
        cmake_policy(SET CMP0017 NEW)
    endif()

endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()


FILE(GLOB MYLIB_SRC "${PROJECT_SOURCE_DIR}/source/*.cpp")

set(MYLIBS mylib)

add_library(${MYLIBS} STATIC ${MYLIB_SRC})

target_link_libraries(${MYLIBS} uv ${CURL_LIBRARY})


include_directories(${CURL_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(test)


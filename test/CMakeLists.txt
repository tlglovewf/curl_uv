MESSAGE("-----------------BUILD TEST PROGRAM----------------------")
FILE(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test*.cpp")

FOREACH(TEST_FILE ${TEST_FILES})
    STRING(REGEX REPLACE ".*/(.*)/(.*)/*.cpp" "\\2" TEST_NAME ${TEST_FILE})
    MESSAGE("BUILD TEST PROGRAM " ${TEST_NAME})
    add_executable(${TEST_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} ${MYLIBS})
ENDFOREACH()
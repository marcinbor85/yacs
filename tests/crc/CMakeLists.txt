create_test(test_crc
        ${CMAKE_CURRENT_SOURCE_DIR}/test_crc.cc
        ${PROJECT_SOURCE_DIR}/../crc/crc.c
)
target_include_directories(test_crc PRIVATE
        ${PROJECT_SOURCE_DIR}/../crc
)

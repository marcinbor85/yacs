create_test(test_cobs_decode
        ${CMAKE_CURRENT_SOURCE_DIR}/test_cobs_decode.cc
        ${PROJECT_SOURCE_DIR}/../cobs/cobs.c
)
target_include_directories(test_cobs_decode PRIVATE
        ${PROJECT_SOURCE_DIR}/../cobs
)

create_test(test_cobs_encode
        ${CMAKE_CURRENT_SOURCE_DIR}/test_cobs_encode.cc
        ${PROJECT_SOURCE_DIR}/../cobs/cobs.c
)
target_include_directories(test_cobs_encode PRIVATE
        ${PROJECT_SOURCE_DIR}/../cobs
)

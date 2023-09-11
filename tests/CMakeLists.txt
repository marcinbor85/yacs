cmake_minimum_required(VERSION 3.10)

project(MainTests LANGUAGES C CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/../googletest googletest)

function(create_test TARGET)
    add_executable(${TARGET})
    target_sources(${TARGET} PRIVATE
        ${PROJECT_SOURCE_DIR}/main.cc
        ${ARGN}
    )
    target_include_directories(${TARGET} PRIVATE
        ${GTEST_INCLUDE_DIRS}
        ${CORE_INCLUDE_DIRS}
    )
    target_link_libraries(${TARGET}
        gmock_main
        gtest_main
    )
    add_test(${TARGET} ${TARGET})
endfunction()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cobs)

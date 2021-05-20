add_library(testbed 
    src/init_test.c
    src/task_dio.c
    src/task_uart.c)
target_link_libraries(testbed PUBLIC freertos dprint periph)
target_include_directories(testbed PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE src)

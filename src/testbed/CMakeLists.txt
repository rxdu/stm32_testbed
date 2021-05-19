add_library(testbed 
    src/testbed_task.c
    src/init_test.c
    src/test_led.c
    src/test_dio.c)
target_link_libraries(testbed PUBLIC freertos dprint periph)
target_include_directories(testbed PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE src)

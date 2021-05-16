add_library(testbed 
    src/testbed_task.c
    src/led_test.c)
target_link_libraries(testbed PUBLIC freertos dprint)
target_include_directories(testbed PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE src)

## Add library
add_library(isotp src/isotp.c
    src/port_stm32f4.c)
target_link_libraries(isotp PUBLIC mcal freertos dprint)
target_include_directories(isotp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE src)

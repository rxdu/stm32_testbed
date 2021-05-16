# add library
add_library(periph STATIC 
    src/dio.c)
target_link_libraries(periph PUBLIC cmsis ${STM32HAL_LIB} dprint freertos)
target_include_directories(periph PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${TARGET_INC}>  
  PRIVATE src)

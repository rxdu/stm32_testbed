# add library
add_library(mcal STATIC src/dio.c
    src/can.c
    src/pwm.c
    src/spi.c
    src/utils.c
    src/dma.c
    src/uart.c)
if(USE_FREERTOS)
  target_link_libraries(mcal PUBLIC cmsis ${STM32HAL_LIB} dprint ringbuf freertos)
else()
  target_link_libraries(mcal PUBLIC cmsis ${STM32HAL_LIB} dprint ringbuf)
endif()
target_include_directories(mcal PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${TARGET_INC}>  
  PRIVATE src)

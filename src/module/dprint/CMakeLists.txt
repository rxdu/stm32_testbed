## Add library
set(DBG_PRINT_SRC
    src/dprint.c
    src/itm.c
    printf/printf.c
)
add_library(dprint ${DBG_PRINT_SRC})
target_link_libraries(dprint PUBLIC cmsis ${STM32HAL_LIB} freertos) 
if(DBG_OUTPUT_CHN MATCHES ITM)
    target_compile_definitions(dprint PUBLIC "-DDBG_PRINT -DDBG_OUTPUT_ITM")
elseif(DBG_OUTPUT_CHN MATCHES RTT)
    target_compile_definitions(dprint PUBLIC "-DDBG_PRINT -DDBG_OUTPUT_RTT")
    target_link_libraries(dprint PUBLIC segger_rtt)
elseif(DBG_OUTPUT_CHN MATCHES NONE)
    message(STATUS "No debugging info will be printed")
endif()
target_include_directories(dprint PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE src)

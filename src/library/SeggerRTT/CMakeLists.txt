## Add library
set(SEGGER_RTT_SRC
    SEGGER_RTT_printf.c
    SEGGER_RTT_Syscalls_GCC.c 
    SEGGER_RTT.c
)
add_library(segger_rtt ${SEGGER_RTT_SRC})
# target_link_libraries(segger_rtt PUBLIC cmsis)
target_include_directories(segger_rtt PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

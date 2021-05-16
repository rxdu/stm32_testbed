set(FREERTOS_SRC
    Source/list.c 
    Source/tasks.c 
    Source/queue.c 
    Source/timers.c 
    Source/stream_buffer.c
    Source/portable/MemMang/heap_4.c
    Source/CMSIS_RTOS_V2/cmsis_os2.c
)
if(${MCU_ARCH} STREQUAL ARMCM4)
    set(TARGET_PORT_SRC Source/portable/GCC/ARM_CM4F/port.c)
    set(TARGET_PORT_INC Source/portable/GCC/ARM_CM4F)
elseif(${MCU_ARCH} STREQUAL ARMCM7)
    set(TARGET_PORT_SRC Source/portable/GCC/ARM_CM7/r0p1/port.c)
    set(TARGET_PORT_INC Source/portable/GCC/ARM_CM7/r0p1)
elseif(${MCU_ARCH} STREQUAL ARMCM3)
    set(TARGET_PORT_SRC Source/portable/GCC/ARM_CM3/port.c)
    set(TARGET_PORT_INC Source/portable/GCC/ARM_CM3)
endif()

message(STATUS "FreeRTOS port: ${TARGET_PORT_SRC}")

if(USE_SYSTEM_VIEW)
set(SEGGER_SYSVIEW_SRC
    SystemView/SEGGER/SEGGER_SYSVIEW.c 
    SystemView/SEGGER/SEGGER_RTT_printf.c 
    SystemView/SEGGER/SEGGER_RTT_Syscalls_GCC.c 
    SystemView/SEGGER/SEGGER_RTT.c
    SystemView/SEGGER/SEGGER_RTT_ASM_ARMv7M.S
    SystemView/FreeRTOSV10/SEGGER_SYSVIEW_Config_FreeRTOS.c 
    SystemView/FreeRTOSV10/SEGGER_SYSVIEW_FreeRTOS.c
)
endif()

add_library(freertos ${FREERTOS_SRC} ${TARGET_PORT_SRC} ${SEGGER_SYSVIEW_SRC})
target_link_libraries(freertos PUBLIC cmsis)
target_include_directories(freertos PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/CMSIS_RTOS_V2>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PORT_INC}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SystemView/Config>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SystemView/FreeRTOSV10>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SystemView/SEGGER>
  PRIVATE Src)

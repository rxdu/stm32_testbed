## setup board/app directory
if(EXISTS "${TARGET_DIR}/${BOARD_NAME}")
    set(BOARD_DIR ${TARGET_DIR}/${BOARD_NAME})
else()
    message(FATAL_ERROR "Unknown board: ${BOARD_NAME}")
endif()

# print project info
message(STATUS "Building project: ${PROJECT_NAME}")
message(STATUS "Target board: ${BOARD_NAME}")
message(STATUS "Target application: stm32_testbed")

## Setup cross-compile toolchain 
set(CROSS_COMPILE_PREFIX arm-none-eabi)
include(${STM32_CMAKE_DIR}/gcc-arm-none-eabi.cmake)
include(${BOARD_DIR}/target-def.cmake)

## auto-set variables from user input
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(LINK_FLAGS "${MCU_FLAGS} -Wl,--gc-sections")
# normal configuration
set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=nosys.specs")
set(EXTRA_SYS_LIBS "-lc -lm -lnosys")
# semi-hosting configuration
# set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=rdimon.specs")
# set(EXTRA_SYS_LIBS "-lc -lm -lrdimon")
include(${STM32_CMAKE_DIR}/stm32-gcc-flags.cmake)

# print summary of configurations
message(STATUS "MCU_FAMILY: ${MCU_FAMILY}")
message(STATUS "MCU_NAME: ${MCU_NAME}")
message(STATUS "Specified C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")
message(STATUS "Use LL library: ${USE_LL_LIB}")
message(STATUS "Use HAL library: ${USE_HAL_LIB}")
message(STATUS "Use FreeRTOS: ${USE_FREERTOS}")
message(STATUS "Use Segger SystemView library: ${USE_SYSTEM_VIEW}")
message(STATUS "---------------------------------------")

## version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

## global include paths
# necessary to build ST libraries, e.g. stm32f4xx_hal_conf.h
include_directories(${BOARD_DIR}/cubemx/Core/Inc)

## additional definitions
add_definitions("-D${MCU_ARCH}")
add_definitions("-D${MCU_FAMILY}")
if(USE_LL_LIB)
add_definitions("-DUSE_LL_LIB")
endif()
if(USE_HAL_LIB)
add_definitions("-DUSE_HAL_LIB")
endif()
if(USE_FREERTOS)
add_definitions("-DUSE_FREERTOS")
endif()
if(USE_SYSTEM_VIEW)
add_definitions("-DENABLE_SYSTEMVIEW")
endif()

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
set(WS_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/library)
set(WS_MODULES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/module)

# arm/stm32 libraries
add_subdirectory(${WS_LIBRARY_PATH}/CMSIS)
string(SUBSTRING ${MCU_FAMILY} 0 7 STM32_SERIES)
if(${STM32_SERIES} STREQUAL "STM32F1")
    message(STATUS "Building STM32F1xx_HAL_Driver")
    add_subdirectory(${WS_LIBRARY_PATH}/STM32F1xx_HAL_Driver)
    set(STM32HAL_LIB stm32f1xx_hal)
elseif(${STM32_SERIES} STREQUAL "STM32F4")
    message(STATUS "Building STM32F4xx_HAL_Driver")
    add_subdirectory(${WS_LIBRARY_PATH}/STM32F4xx_HAL_Driver)
    set(STM32HAL_LIB stm32f4xx_hal)
endif()
add_definitions("-D${STM32_SERIES}")
# add_subdirectory(${WS_LIBRARY_PATH}/STM32_USB_Device_Library)

# common libraries
add_subdirectory(${WS_LIBRARY_PATH}/FreeRTOS)
add_subdirectory(${WS_LIBRARY_PATH}/SeggerRTT)

# common modules
add_subdirectory(${WS_MODULES_PATH}/dprint)
# add_subdirectory(${WS_MODULES_PATH}/mcal)

# project-specific modules
# add_subdirectory(driver)
# add_subdirectory(app)
add_subdirectory(testbed)

# STM32CubeMX generated source files (TARGET_SRC)
add_executable(${ELF_TARGET} ${TARGET_SRC})
target_compile_definitions(${ELF_TARGET} PRIVATE -D${MCU_FAMILY} -DAPP_START_ADDRESS=${FW_START_ADDRESS})
target_link_libraries(${ELF_TARGET} PRIVATE testbed ${EXTRA_SYS_LIBS})
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})
target_include_directories(${ELF_TARGET} PRIVATE
  $<BUILD_INTERFACE:${BOARD_DIR}/cubemx/Core/Inc>)

## add post-build targets
include(${STM32_CMAKE_DIR}/stm32-gcc-postbuild.cmake)
include(${TARGET_DIR}/stm32-gcc-jlink.cmake)
include(${TARGET_DIR}/stm32-gcc-stlink.cmake)
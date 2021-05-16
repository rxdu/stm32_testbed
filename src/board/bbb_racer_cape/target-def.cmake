# Target-specific flags
set(MCU_ARCH ARMCM4)
set(MCU_FAMILY STM32F427xx)
set(MCU_NAME STM32F427VI)

set(CPU "-mcpu=cortex-m4")
set(FPU "-mfpu=fpv4-sp-d16")
set(FLOAT_ABI "-mfloat-abi=hard")

set(FW_START_ADDRESS 0x08000000)

if(FW_START_ADDRESS EQUAL 0x08000000)
    set(LINKER_SCRIPT ${BOARD_DIR}/cubemx/STM32F427VITx_FLASH.ld)
# else()
#     set(LINKER_SCRIPT ${BOARD_DIR}/cubemx//STM32F405RGTx_FLASH_BL.ld)
endif()

option(USE_LL_LIB "Enable LL library" ON)
option(USE_HAL_LIB "Enable HAL library" ON)

option(USE_FREERTOS "Enable FreeRTOS" ON)
option(USE_SYSTEM_VIEW "Enable Segger SystemView library" OFF)

message(STATUS "Board path: ${BOARD_DIR}")

set(TARGET_SRC
    ${BOARD_DIR}/cubemx/Core/Src/freertos.c
    ${BOARD_DIR}/cubemx/Core/Src/main.c
    ${BOARD_DIR}/cubemx/Core/Src/stm32f4xx_hal_msp.c
    ${BOARD_DIR}/cubemx/Core/Src/stm32f4xx_hal_timebase_tim.c
    ${BOARD_DIR}/cubemx/Core/Src/stm32f4xx_it.c
    ${BOARD_DIR}/cubemx/Core/Src/system_stm32f4xx.c
    ${BOARD_DIR}/cubemx/startup_stm32f427xx.s
    # ${BOARD_DIR}/periph_impl/periph.c
)
set(TARGET_INC
    ${BOARD_DIR}/periph_impl
)

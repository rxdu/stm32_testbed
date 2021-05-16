# name of targets
set(BIN_TARGET ${PROJECT_NAME}.bin)
set(HEX_TARGET ${PROJECT_NAME}.hex)
set(MAP_TARGET ${PROJECT_NAME}.map)
set(LSS_TARGET ${PROJECT_NAME}.lss)

# flash
add_custom_target(stlink_flash 
    DEPENDS ${ELF_TARGET} 
    COMMAND STM32_Programmer_CLI -c port=SWD freq=24000 ap=0 -w ${HEX_TARGET} -rst -run
)

# reset
add_custom_target(stlink_reset 
    COMMAND JLinkExe -device ${MCU_NAME} -speed 4000 -if SWD -CommanderScript ${TARGET_DIR}/jlink-reset-stm32.jlink
)

# GDB
add_custom_target(stlink_gdb_server 
    DEPENDS ${ELF_TARGET} 
    COMMAND stlink-server
)

add_custom_target(stlink_gdb_debug 
    DEPENDS ${ELF_TARGET} 
    COMMAND ${ARM_GDB_EXECUTABLE} -x ${TARGET_DIR}/jlink-debug.gdbinit $(PROG).elf
)

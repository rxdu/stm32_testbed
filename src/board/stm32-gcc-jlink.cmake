# name of targets
set(BIN_TARGET ${PROJECT_NAME}.bin)
set(HEX_TARGET ${PROJECT_NAME}.hex)
set(MAP_TARGET ${PROJECT_NAME}.map)
set(LSS_TARGET ${PROJECT_NAME}.lss)

# flash
add_custom_target(jlink_flash 
    DEPENDS ${ELF_TARGET} 
    COMMAND JLinkExe -device ${MCU_NAME} -speed 4000 -if SWD -CommanderScript ${TARGET_DIR}/jlink-flash-stm32.jlink
)

# reset
add_custom_target(jlink_reset 
    COMMAND JLinkExe -device ${MCU_NAME} -speed 4000 -if SWD -CommanderScript ${TARGET_DIR}/jlink-reset-stm32.jlink
)

# GDB
add_custom_target(jlink_gdb_server 
    DEPENDS ${ELF_TARGET} 
    COMMAND JLinkGDBServer -device $(MCU_NAME) -if SWD
)

add_custom_target(jlink_gdb_debug 
    DEPENDS ${ELF_TARGET} 
    COMMAND ${ARM_GDB_EXECUTABLE} -x ${TARGET_DIR}/jlink-debug-stm32.gdbinit $(PROG).elf
)

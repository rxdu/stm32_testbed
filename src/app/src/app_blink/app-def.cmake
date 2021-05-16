set(APP_IMPL_SRC 
    ${CMAKE_CURRENT_LIST_DIR}/app_blink_init.c
    ${CMAKE_CURRENT_LIST_DIR}/blink_led.c)
set(APP_DEP_LIB mcal led freertos dprint)

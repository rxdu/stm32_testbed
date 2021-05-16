set(USB_DEV_LIB_SRC
    Class/CDC/Src/usbd_cdc.c
    Core/Src/usbd_core.c
    Core/Src/usbd_ctlreq.c
    Core/Src/usbd_ioreq.c
)
add_library(usb_device ${USB_DEV_LIB_SRC})
target_link_libraries(usb_device PUBLIC cmsis stm32f4xx_hal)
target_include_directories(usb_device PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Class/CDC/Inc>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc>)

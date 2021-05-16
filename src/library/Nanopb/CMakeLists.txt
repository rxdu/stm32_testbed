## Add library
add_library(nanopb src/pb_common.c
    src/pb_encode.c
    src/pb_decode.c)
# target_link_libraries(nanopb PUBLIC mcal freertos dprint)
target_include_directories(nanopb PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nanopb>
  PRIVATE src)

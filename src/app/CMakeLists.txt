# add application
set(APP_IMPL_SRC src/dummy_init.c)
include(src/${APP_NAME}/app-def.cmake)

add_library(app ${APP_IMPL_SRC})
target_link_libraries(app PUBLIC ${APP_DEP_LIB})
target_include_directories(app PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE src/${APP_NAME})

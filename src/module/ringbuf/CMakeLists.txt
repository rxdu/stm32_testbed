## Add libraries
set(RINGBUF_SRC 
    src/ringbuf.c
)
add_library(ringbuf STATIC ${RINGBUF_SRC})
target_include_directories(ringbuf PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>	
    PRIVATE src)
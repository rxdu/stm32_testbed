MOD_RINGBUF = $(MOD_DIR)/ringbuf

VPATH += $(MOD_RINGBUF)/src
INCLUDES += -I$(MOD_RINGBUF)/include

MOD_OBJ += ringbuf.o

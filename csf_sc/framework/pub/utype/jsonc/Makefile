include $(INST_DIR)/framework/tools/env.mk

.SUFFIXES: .o .c

a: libjsonc.a


OBJS=arraylist.o debug.o json_object.o json_tokener.o json_util.o linkhash.o printbuf.o json_object_iterator.o

libjsonc.a: $(OBJS)
	$(AR) $@ $(OBJS)

clean:
	rm -f *.o libjsonc.a


.c.o:
	$(C_COMP) $(CFLAGS) -c -o $@ $<
	

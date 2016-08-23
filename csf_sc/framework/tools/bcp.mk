include $(HOME)/run/framework/tools/env.mk

all:$(LIB_NAME)
$(LIB_NAME):$(ALL_OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(ALL_OBJS) -L$(TUX_LIB) -L$(WORK_LIB_DIR) $(LIB_FILE)
	-mv $(HOME)/run/solib/$(LIB_NAME) $(HOME)/run/solib/$(LIB_NAME)_`date       '+%s'`
	mv $@ $(WORK_LIB_DIR)

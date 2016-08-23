include $(WORKDIR)/framework/tools/env.mk

TAG=lib$(LIBNAME).so

all: $(TAG)

$(TAG):$(TAG_OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(TAG_OBJS)
#	mv $@ $(WORK_SO_DIR)
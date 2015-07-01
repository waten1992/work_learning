############LIB RSS QUOTE BRIDGE makefile ###########
VER_MAJ:=0
VER_MIN:=1
DEBUG:=y  # n/y
#####################################################
CC:=g++
TOP:=../..
SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,${SRCS})
INCPATH:=-I$(TOP)/lib/include -I$(TOP)/lib/include/mfast/
CFLAGS:=${INCPATH} -fPIC -std=c++11  
LIBPATH:=-L./ -L$(TOP)/lib/bin
LDFLAGS:=${LIBPATH} -shared -fPIC -lmfast -lmfast_coder -lzmq
#-lmfast_xml_parser  -lmfast_json
LIBNAME:=librqb.so
SONAME:= $(LIBNAME).$(VER_MAJ)
OUT:= $(LIBNAME).$(VER_MAJ).$(VER_MIN)

GCH:=header.h.gch rq_fast.h.gch
DEP:=.dep
XMLFILE:=rq_fast.xml

ifeq ($(strip $(DEBUG)),y)
#debug
 LDFLAGS +=-Wl,-soname,$(SONAME)
	#-Wl,-rpath,$(TOP)/lib/bin 
 CFLAGS +=-O0 -g2 
else
#release
 CFLAGS  +=-Wall -O2 -DNDEBUG
endif

all:${OUT}

$(OUT):$(GCH) $(OBJS) 
	g++ $(OBJS) ${LDFLAGS} -o $(OUT)
	ln -sf $(OUT) $(SONAME)
	ln -sf $(SONAME) $(LIBNAME)

%.o:%.cpp
	g++ -c $(CFLAGS) $< -o $@

# NOTE: manually update is needed when source/header
# dependency are changed.
dep:
	$(CC)  $(CFLAGS) -MM $(SRCS) > $(DEP)

-include $(DEP)

header.h.gch:header.h
	g++ $(CFLAGS) -x c++-header -c $< -o $@

rq_fast.h.gch:rq_fast.h
	g++ $(CFLAGS) -x c++-header -c $< -o $@
gen:
	$(TOP)/lib/bin/fast_type_gen  $(XMLFILE)
vi:
	vi -p *.h *.cpp Makefile ../*.h

debug:
	@echo $(VER_MAJ)
	@echo $(VER_MIN)

install:

clean:
	-@rm -f *.o ||True
	-@rm -f $(OUT) || True

distclean:
	-@rm -f $(GCH) ||True
	-@rm -f *.o ||True
	-@rm -f $(OUT) || True


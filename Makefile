MKDEP=$(CXX) -MM

SRCS=Celtree.cpp LoaderRLE.cpp Rules_totalistic.cpp
HDRS=Xcel.h Celtree.h Quadtree.h LoaderRLE.h Loader.h Rules_totalistic.h Rules_gol.h Rules.h cel.h pos2D.h
OUTS=Celtree.o LoaderRLE.o Rules_totalistic.o
CFLAGS=-c

Xcel: $(OUTS)
	ar rcs libXcel.a $(OUTS)

depend: .depend
.depend: $(SRCS) $(HDRS)
	$(MKDEP) $(CFLAGS) $(SRCS) > .depend
-include .depend

#
# $Id: Makefile,v 1.4.4.1 2007-09-28 04:54:03 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the 3D vector test app.
#


TARGETS += $(WORKDIR)/test


TEST_SRC = Length3D.cpp \
	Speed3D.cpp \
	Acceleration3D.cpp \
	AngularSpeed3D.cpp \
	AngularAcceleration3D.cpp \
	Force3D.cpp \
	Torque3D.cpp

SOURCE = $(TEST_SRC) test.cpp


#
# Must define TARGETS, SOURCE, LIB_OBJS before including this.
#
UNITS_ROOT = ../..
include $(UNITS_ROOT)/make_rules/common.rules


CPPFLAGS += -I..
CPPFLAGS += -I../..


TEST_OBJS = $(addprefix $(WORKDIR)/, $(TEST_SRC:.cpp=.o))
$(WORKDIR)/test: test.cpp $(TEST_OBJS)
	$(LINK.cc) $< $(TEST_OBJS) -lm -o $@

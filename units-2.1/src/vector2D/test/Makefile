#
# $Id: Makefile,v 1.2.4.5 2006-02-07 06:31:11 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the 2D vector test app.
#


TARGETS = $(WORKDIR)/test

TEST_SRC = Length2D.cpp \
	   Speed2D.cpp \
	   Acceleration2D.cpp \
	   Force2D.cpp \
	   Angle2D.cpp


SOURCE = $(TEST_SRC) test.cpp


#
# Must define TARGETS, SOURCE, LIB_OBJS before including this.
#
UNITS_ROOT = ../..
include $(UNITS_ROOT)/make_rules/common.rules

CPPFLAGS += -I../..
CPPFLAGS += -I..


TEST_OBJS = $(addprefix $(WORKDIR)/, $(TEST_SRC:.cpp=.o))
$(WORKDIR)/test: test.cpp $(TEST_OBJS)
	$(LINK.cc) $< $(TEST_OBJS) -lm -o $@

#
# $Id: Makefile,v 1.4.4.1 2007-09-28 04:54:03 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the 3D vector units library.
#


SUBDIRS = test

INSTALL_HTML_DIR = vector3D
INSTALL_HTML     = vector3D.html bugs.html \
		   Length3D.html \
		   Speed3D.html \
		   Acceleration3D.html \
		   AngularSpeed3D.html \
		   Force3D.html

INSTALL_HEADER_DIR = vector3D
INSTALL_HEADERS    = Vector3D.h Vector3D.i Vector3D.cpp \
		     Direction3D.h Direction3D.i Direction3D.cpp \
		     QuaternionRotation3D.h QuaternionRotation3D.i \
		     QuaternionRotation3D.cpp \
		     MatrixRotation3D.h MatrixRotation3D.i \
		     MatrixRotation3D.cpp \
		     Unit3D.h Unit3D.i \
		     Length3D.h Length3D.i \
		     Speed3D.h Speed3D.i \
		     Acceleration3D.h Acceleration3D.i \
		     AngularSpeed3D.h AngularSpeed3D.i \
		     AngularAcceleration3D.h AngularAcceleration3D.i \
		     Force3D.h Force3D.i \
		     Torque3D.h Torque3D.i


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
UNITS_ROOT = ..
include ../make_rules/common.rules


CPPFLAGS += -I..


TEST_OBJS = $(addprefix $(WORKDIR)/, $(TEST_SRC:.cpp=.o))
$(WORKDIR)/test: test.cpp $(TEST_OBJS)
	$(LINK.cc) $< $(TEST_OBJS) -lm -o $@

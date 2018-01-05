#
# $Id: Makefile,v 1.7.2.3 2007-10-01 05:44:30 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the scalar test app.
#


TARGETS = $(WORKDIR)/test


TEST_SRC = Time.cpp Frequency.cpp Mass.cpp MassFlowRate.cpp \
	   Length.cpp Area.cpp Volume.cpp \
	   Speed.cpp Acceleration.cpp Force.cpp \
	   Inertia.cpp Angle.cpp SignedAngle.cpp UnsignedAngle.cpp \
	   AngularSpeed.cpp AngularAcceleration.cpp Torque.cpp \
	   Voltage.cpp Current.cpp Power.cpp \
	   MagneticField.cpp MagneticFluxDensity.cpp MagneticFlux.cpp \
	   Pressure.cpp Density.cpp Temperature.cpp

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
	$(LINK.cc) $< $(TEST_OBJS) -o $@

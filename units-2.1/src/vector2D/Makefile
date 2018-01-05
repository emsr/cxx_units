#
# $Id: Makefile,v 1.2.4.5 2006-02-07 06:31:11 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the 2D vector units library.
#

SUBDIRS = test

INSTALL_HTML_DIR = vector2D
INSTALL_HTML     = vector2D.html bugs.html \
		   Length2D.html \
		   Speed2D.html \
		   Acceleration2D.html \
		   Force2D.html

INSTALL_HEADER_DIR = vector2D
INSTALL_HEADERS    = Vector2D.h Vector2D.i Vector2D.cpp \
		     Direction2D.h Direction2D.i Direction2D.cpp \
		     Rotation2D.h Rotation2D.i Rotation2D.cpp \
		     Unit2D.h Unit2D.i \
		     Length2D.h Length2D.i \
		     Speed2D.h Speed2D.i \
		     Acceleration2D.h Acceleration2D.i \
		     Force2D.h Force2D.i  \
		     Angle2D.h Angle2D.i


#
# Must define TARGETS, SOURCE, LIB_OBJS before including this.
#
UNITS_ROOT = ..
include ../make_rules/common.rules

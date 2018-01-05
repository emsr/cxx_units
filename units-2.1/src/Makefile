#
# $Id: Makefile,v 1.4 2001-08-10 06:37:56 knicewar Exp $
#
# Copyright Keith Nicewarner.  All rights reserved.
#
# Build the entire units library source tree.
#


INSTALL_HTML = units.html

SUBDIRS = system scalar vector2D vector3D

UNITS_ROOT = .
include make_rules/common.rules


clean.local::
	rm -rf $(UNITS_PUBLISH_DIR)/include
	rm -rf $(UNITS_PUBLISH_DIR)/lib
	rm -rf $(UNITS_PUBLISH_DIR)/bin
	rm -rf $(UNITS_PUBLISH_DIR)/html

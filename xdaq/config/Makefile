# $Id: Makefile,v 1.91 2009/04/06 13:17:19 gutleber Exp $

#########################################################################
# XDAQ Components for Distributed Data Acquisition                      #
# Copyright (C) 2000-2009, CERN.			                #
# All rights reserved.                                                  #
# Authors: J. Gutleber and L. Orsini					#
#                                                                       #
# For the licensing terms see LICENSE.		                        #
# For the list of contributors see CREDITS.   			        #
#########################################################################

#
# Makefile if TriDAS/config directory
#
BUILD_HOME:=$(shell pwd)/..

include $(XDAQ_ROOT)/config/mfAutoconf.rules
include $(XDAQ_ROOT)/config/mfDefs.$(XDAQ_OS)

Project=daq
Package=../config
PackageName=build

PACKAGE_VER_MAJOR=5
PACKAGE_VER_MINOR=12
PACKAGE_VER_PATCH=0

Summary=Build infrastructure (generic makefiles)

Description=Build infrastructure (generic makefiles)

#Authors=Johannes Gutleber & Luciano Orsini

Link=http://xdaqwiki.cern.ch

include $(XDAQ_ROOT)/config/mfBuildRPM.rules

# Adhere to targets of generic Makefile
# Nothing to build and nothing to cleanup

_cleanall:

_all:

_installall:


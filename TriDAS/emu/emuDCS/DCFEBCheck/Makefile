# $Id: Makefile,v 1.5 2006/05/19 13:34:16 xdaq Exp $

#########################################################################
# XDAQ Components for Distributed Data Acquisition                      #
# Copyright (C) 2000-2004, CERN.			                #
# All rights reserved.                                                  #
# Authors: J. Gutleber and L. Orsini					#
#                                                                       #
# For the licensing terms see LICENSE.		                        #
# For the list of contributors see CREDITS.   			        #
#########################################################################

##
#
# This is the example Makefile
#
# make Library=ExampleName
#
##

include $(XDAQ_ROOT)/config/mfAutoconf.rules
include $(XDAQ_ROOT)/config/mfDefs.$(XDAQ_OS)

Project=emu
Package=emuDCS/DCFEBCheck
PackageName=DCFEBCheck

Sources= \
   StndAloneDAQ.cc \
   SmallUnpack.cc \
   DMBHead.cc \
   CFEBData.cc \
   TMBData.cc \
   DCFEBCheck.cc

#Sources= \
#   Test.cc \
#   DCFEBTestDAQ.cc \
#   DCFEBTestMain.cc

IncludeDirs = \
	$(XDAQ_ROOT)/include/xerces/$(XDAQ_OS)$(XDAQ_PLATFORM)/include \
	$(XDAQ_ROOT)/include/log4cplus/$(XDAQ_OS)$(XDAQ_PLATFORM)/include \
	$(XDAQ_ROOT)/include/cgicc/$(XDAQ_OS)$(XDAQ_PLATFORM)/include \
	$(XDAQ_ROOT)/include/toolbox/include \
	$(XDAQ_ROOT)/include/toolbox/include/$(XDAQ_OS) \
	$(XDAQ_ROOT)/include/toolbox/include/solaris \
	$(XDAQ_ROOT)/include/mimetic/$(XDAQ_OS)$(XDAQ_PLATFORM)/include \
	$(XDAQ_ROOT)/include/xoap/include \
	$(XDAQ_ROOT)/include/xdata/include \
	$(XDAQ_ROOT)/include/pt/include \
	$(XDAQ_ROOT)/include/xcept \
	$(XDAQ_ROOT)/include/xgi/include \
	$(XDAQ_ROOT)/ \
	$(XDAQ_ROOT)/include/i2o/include/ \
	$(XDAQ_ROOT)/include/i2o/include/i2o \
	$(XDAQ_ROOT)/include/i2o/include/i2o/shared \
	$(XDAQ_ROOT)/include \
	$(XDAQ_ROOT)/include/solaris \
	$(XDAQ_ROOT)/include/linux \
        $(BUILD_HOME)/emu/emuDCS/PeripheralCore/include \
        $(BUILD_HOME)/emu/emuDCS/PeripheralApps/include \
	$(BUILD_HOME)/emu/daq/reader/include \
	$(BUILD_HOME)/emu/emuDCS/DCFEBCheck/include \
        $(BUILD_HOME)/emu/base/include \
        $(BUILD_HOME)/emu 

LibraryDirs = $(XDAQ_ROOT)/xoap/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xerces/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/asyncresolv/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/log4cplus/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/toolbox/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xdata/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xcept/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/pt/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/mimetic/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
        $(BUILD_HOME)/emu/emuDCS/DCFEBCheck/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/emuDCS/PeripheralCore/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/emuDCS/PeripheralApps/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/base/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) 

TestLibraryDirs = \$(XDAQ_ROOT)/xoap/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xerces/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/asyncresolv/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/log4cplus/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/toolbox/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xdata/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/xcept/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/pt/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
	$(XDAQ_ROOT)/mimetic/$(XDAQ_OS)$(XDAQ_PLATFORM)/lib \
	$(XDAQ_ROOT)/lib \
        $(BUILD_HOME)/emu/cscSV/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/emuDCS/PeripheralCore/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/emuDCS/PeripheralApps/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) \
        $(BUILD_HOME)/emu/base/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM) 


UserCFlags =
UserCCFlags = -g
UserDynamicLinkFlags =
UserStaticLinkFlags =
UserExecutableLinkFlags =

# These libraries can be platform specific and
# potentially need conditional processing
#

Libraries = xerces-c xdaq xdata log4cplus toolbox xoap cgicc xcept xgi peer

TestLibraries = xerces-c xdaq xdata log4cplus toolbox xoap cgicc xcept xgi peer \
                mimetic logxmlappender logudpappender asyncresolv config \
                EmuPeripheralCore EmuPeripheralApps uuid 

#
# Compile the source files and create a shared library
#

DynamicLibrary= DCFEBCheck

StaticLibrary= DCFEBCheck

ifdef Executable
Libraries=toolbox xdata xcept xoap xerces-c log4cplus mimetic asyncresolv
Executables= $(Executable).cc
endif

Executables=
TestExecutables= \
	Test1.cpp 

include $(XDAQ_ROOT)/config/Makefile.rules
include $(XDAQ_ROOT)/config/mfRPM.rules

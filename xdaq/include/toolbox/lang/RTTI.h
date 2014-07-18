// $Id: RTTI.h,v 1.3 2008/07/18 15:27:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_lang_RTTI_h_
#define _toolbox_lang_RTTI_h_

#include <string>
#include <typeinfo>

namespace toolbox {
namespace lang {

//! Demangle a type info into a human readable type string
//
std::string demangle(const std::type_info &ti);

//! Mangle a C++ namespace declaration in the form NS1::NS2::... into an ABI specific symbol string
//
std::string scopemangle(const std::string & scope);

}}

#endif

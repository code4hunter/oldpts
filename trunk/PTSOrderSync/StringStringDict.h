// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1

// Freeze types in this file:
// name="PTS2::StringStringDict", key="string", value="string"

#ifndef __StringStringDict_h__
#define __StringStringDict_h__

#include <Freeze/Map.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 303
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace PTS2
{

class StringStringDictKeyCodec
{
public:

    static void write(const ::std::string&, Freeze::Key&, const ::Ice::CommunicatorPtr&);
    static void read(::std::string&, const Freeze::Key&, const ::Ice::CommunicatorPtr&);
    static const std::string& typeId();
};

class StringStringDictValueCodec
{
public:

    static void write(const ::std::string&, Freeze::Value&, const ::Ice::CommunicatorPtr&);
    static void read(::std::string&, const Freeze::Value&, const ::Ice::CommunicatorPtr&);
    static const std::string& typeId();
};

typedef Freeze::Map< ::std::string, ::std::string, StringStringDictKeyCodec, StringStringDictValueCodec, Freeze::IceEncodingCompare > StringStringDict;

}

#endif

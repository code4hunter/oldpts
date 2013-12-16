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

#include <Ice/BasicStream.h>
#include <IceUtil/StringUtil.h>
#include <StringStringDict.h>

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

void
PTS2::StringStringDictKeyCodec::write(const ::std::string& v, Freeze::Key& bytes, const ::Ice::CommunicatorPtr& communicator)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get());
    stream.write(v);
    ::std::vector<Ice::Byte>(stream.b.begin(), stream.b.end()).swap(bytes);
}

void
PTS2::StringStringDictKeyCodec::read(::std::string& v, const Freeze::Key& bytes, const ::Ice::CommunicatorPtr& communicator)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get());
    stream.b.resize(bytes.size());
    ::memcpy(&stream.b[0], &bytes[0], bytes.size());
    stream.i = stream.b.begin();
    stream.read(v);
}

static const ::std::string __PTS2__StringStringDictKeyCodec_typeId = "string";

const ::std::string&
PTS2::StringStringDictKeyCodec::typeId()
{
    return __PTS2__StringStringDictKeyCodec_typeId;
}

void
PTS2::StringStringDictValueCodec::write(const ::std::string& v, Freeze::Value& bytes, const ::Ice::CommunicatorPtr& communicator)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get());
    stream.startWriteEncaps();
    stream.write(v);
    stream.endWriteEncaps();
    ::std::vector<Ice::Byte>(stream.b.begin(), stream.b.end()).swap(bytes);
}

void
PTS2::StringStringDictValueCodec::read(::std::string& v, const Freeze::Value& bytes, const ::Ice::CommunicatorPtr& communicator)
{
    IceInternal::InstancePtr instance = IceInternal::getInstance(communicator);
    IceInternal::BasicStream stream(instance.get());
    stream.b.resize(bytes.size());
    ::memcpy(&stream.b[0], &bytes[0], bytes.size());
    stream.i = stream.b.begin();
    stream.startReadEncaps();
    stream.read(v);
    stream.endReadEncaps();
}

static const ::std::string __PTS2__StringStringDictValueCodec_typeId = "string";

const ::std::string&
PTS2::StringStringDictValueCodec::typeId()
{
    return __PTS2__StringStringDictValueCodec_typeId;
}

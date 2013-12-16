// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Connection.ice'

#ifndef __Ice_Connection_h__
#define __Ice_Connection_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/ObjectAdapterF.h>
#include <Ice/Identity.h>
#include <Ice/UndefSysMacros.h>

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

#ifndef ICE_API
#   ifdef ICE_API_EXPORTS
#       define ICE_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Ice
{

class Connection;
ICE_API bool operator==(const Connection&, const Connection&);
ICE_API bool operator<(const Connection&, const Connection&);

}

namespace IceInternal
{

ICE_API ::Ice::LocalObject* upCast(::Ice::Connection*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Connection> ConnectionPtr;

}

namespace Ice
{

class ICE_API Connection : virtual public ::Ice::LocalObject
{
public:

    typedef ConnectionPtr PointerType;
    

    virtual void close(bool) = 0;

    virtual ::Ice::ObjectPrx createProxy(const ::Ice::Identity&) const = 0;

    virtual void setAdapter(const ::Ice::ObjectAdapterPtr&) = 0;

    virtual ::Ice::ObjectAdapterPtr getAdapter() const = 0;

    virtual void flushBatchRequests() = 0;

    virtual ::std::string type() const = 0;

    virtual ::Ice::Int timeout() const = 0;

    virtual ::std::string toString() const = 0;
};

}

#endif

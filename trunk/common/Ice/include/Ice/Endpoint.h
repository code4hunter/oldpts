// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Endpoint.ice'

#ifndef __Ice_Endpoint_h__
#define __Ice_Endpoint_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
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

class Endpoint;
ICE_API bool operator==(const Endpoint&, const Endpoint&);
ICE_API bool operator<(const Endpoint&, const Endpoint&);

}

namespace IceInternal
{

ICE_API ::Ice::LocalObject* upCast(::Ice::Endpoint*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Endpoint> EndpointPtr;

}

namespace Ice
{

enum EndpointSelectionType
{
    Random,
    Ordered
};

ICE_API void __write(::IceInternal::BasicStream*, EndpointSelectionType);
ICE_API void __read(::IceInternal::BasicStream*, EndpointSelectionType&);

typedef ::std::vector< ::Ice::EndpointPtr> EndpointSeq;

}

namespace Ice
{

class ICE_API Endpoint : virtual public ::Ice::LocalObject
{
public:

    typedef EndpointPtr PointerType;
    

    virtual ::std::string toString() const = 0;
};

}

#endif

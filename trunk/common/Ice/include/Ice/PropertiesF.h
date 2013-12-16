// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `PropertiesF.ice'

#ifndef __Ice_PropertiesF_h__
#define __Ice_PropertiesF_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
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

namespace IceProxy
{

namespace Ice
{

class PropertiesAdmin;

}

}

namespace Ice
{

class Properties;
ICE_API bool operator==(const Properties&, const Properties&);
ICE_API bool operator<(const Properties&, const Properties&);

class PropertiesAdmin;
ICE_API bool operator==(const PropertiesAdmin&, const PropertiesAdmin&);
ICE_API bool operator<(const PropertiesAdmin&, const PropertiesAdmin&);

}

namespace IceInternal
{

ICE_API ::Ice::LocalObject* upCast(::Ice::Properties*);

ICE_API ::Ice::Object* upCast(::Ice::PropertiesAdmin*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::PropertiesAdmin*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Properties> PropertiesPtr;

typedef ::IceInternal::Handle< ::Ice::PropertiesAdmin> PropertiesAdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::PropertiesAdmin> PropertiesAdminPrx;

ICE_API void __read(::IceInternal::BasicStream*, PropertiesAdminPrx&);
ICE_API void __patch__PropertiesAdminPtr(void*, ::Ice::ObjectPtr&);

}

#endif

// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Plugin.ice'

#ifndef __Ice_Plugin_h__
#define __Ice_Plugin_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/LoggerF.h>
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

class Plugin;
ICE_API bool operator==(const Plugin&, const Plugin&);
ICE_API bool operator<(const Plugin&, const Plugin&);

class PluginManager;
ICE_API bool operator==(const PluginManager&, const PluginManager&);
ICE_API bool operator<(const PluginManager&, const PluginManager&);

}

namespace IceInternal
{

ICE_API ::Ice::LocalObject* upCast(::Ice::Plugin*);

ICE_API ::Ice::LocalObject* upCast(::Ice::PluginManager*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Plugin> PluginPtr;

typedef ::IceInternal::Handle< ::Ice::PluginManager> PluginManagerPtr;

}

namespace Ice
{

class ICE_API Plugin : virtual public ::Ice::LocalObject
{
public:

    typedef PluginPtr PointerType;
    

    virtual void initialize() = 0;

    virtual void destroy() = 0;
};

class ICE_API PluginManager : virtual public ::Ice::LocalObject
{
public:

    typedef PluginManagerPtr PointerType;
    

    virtual void initializePlugins() = 0;

    virtual ::Ice::PluginPtr getPlugin(const ::std::string&) = 0;

    virtual void addPlugin(const ::std::string&, const ::Ice::PluginPtr&) = 0;

    virtual void destroy() = 0;
};

}

#endif

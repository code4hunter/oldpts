// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Registry.ice'

#ifndef __IceGrid_Registry_h__
#define __IceGrid_Registry_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/Incoming.h>
#include <Ice/IncomingAsync.h>
#include <Ice/Direct.h>
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <IceGrid/Exception.h>
#include <IceGrid/Session.h>
#include <IceGrid/Admin.h>
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

#ifndef ICE_GRID_API
#   ifdef ICE_GRID_API_EXPORTS
#       define ICE_GRID_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_GRID_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace IceGrid
{

class Registry;

}

}

namespace IceGrid
{

class Registry;
ICE_GRID_API bool operator==(const Registry&, const Registry&);
ICE_GRID_API bool operator<(const Registry&, const Registry&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::Registry*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::Registry*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::Registry> RegistryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::Registry> RegistryPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, RegistryPrx&);
ICE_GRID_API void __patch__RegistryPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceAsync
{

}

namespace IceProxy
{

namespace IceGrid
{

class Registry : virtual public ::IceProxy::Ice::Object
{
public:

    ::IceGrid::SessionPrx createSession(const ::std::string& userId, const ::std::string& password)
    {
        return createSession(userId, password, 0);
    }
    ::IceGrid::SessionPrx createSession(const ::std::string& userId, const ::std::string& password, const ::Ice::Context& __ctx)
    {
        return createSession(userId, password, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string& userId, const ::std::string& password)
    {
        return createAdminSession(userId, password, 0);
    }
    ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string& userId, const ::std::string& password, const ::Ice::Context& __ctx)
    {
        return createAdminSession(userId, password, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::SessionPrx createSessionFromSecureConnection()
    {
        return createSessionFromSecureConnection(0);
    }
    ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Context& __ctx)
    {
        return createSessionFromSecureConnection(&__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);
    
public:

    ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection()
    {
        return createAdminSessionFromSecureConnection(0);
    }
    ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Context& __ctx)
    {
        return createAdminSessionFromSecureConnection(&__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Context*);
    
public:

    ::Ice::Int getSessionTimeout()
    {
        return getSessionTimeout(0);
    }
    ::Ice::Int getSessionTimeout(const ::Ice::Context& __ctx)
    {
        return getSessionTimeout(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::Int getSessionTimeout(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Registry> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Registry> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Registry*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Registry*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace IceGrid
{

class ICE_GRID_API Registry : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::IceGrid::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*) = 0;

    virtual ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Context*) = 0;

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API Registry : virtual public ::IceDelegate::IceGrid::Registry,
                              virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::IceGrid::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);

    virtual ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Context*);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API Registry : virtual public ::IceDelegate::IceGrid::Registry,
                              virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::IceGrid::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);

    virtual ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Context*);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*);
};

}

}

namespace IceGrid
{

class ICE_GRID_API Registry : virtual public ::Ice::Object
{
public:

    typedef RegistryPrx ProxyType;
    typedef RegistryPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::IceGrid::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createSession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::AdminSessionPrx createAdminSession(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createAdminSession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::SessionPrx createSessionFromSecureConnection(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createSessionFromSecureConnection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::AdminSessionPrx createAdminSessionFromSecureConnection(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createAdminSessionFromSecureConnection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getSessionTimeout(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

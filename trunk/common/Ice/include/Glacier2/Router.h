// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Router.ice'

#ifndef __Glacier2_Router_h__
#define __Glacier2_Router_h__

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
#include <Ice/Router.h>
#include <Glacier2/Session.h>
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

#ifndef GLACIER2_API
#   ifdef GLACIER2_API_EXPORTS
#       define GLACIER2_API ICE_DECLSPEC_EXPORT
#   else
#       define GLACIER2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace Glacier2
{

class Router;

class Admin;

}

}

namespace Glacier2
{

class Router;
GLACIER2_API bool operator==(const Router&, const Router&);
GLACIER2_API bool operator<(const Router&, const Router&);

class Admin;
GLACIER2_API bool operator==(const Admin&, const Admin&);
GLACIER2_API bool operator<(const Admin&, const Admin&);

}

namespace IceInternal
{

GLACIER2_API ::Ice::Object* upCast(::Glacier2::Router*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::Router*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::Admin*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::Admin*);

}

namespace Glacier2
{

typedef ::IceInternal::Handle< ::Glacier2::Router> RouterPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::Router> RouterPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, RouterPrx&);
GLACIER2_API void __patch__RouterPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::Admin> AdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::Admin> AdminPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, AdminPrx&);
GLACIER2_API void __patch__AdminPtr(void*, ::Ice::ObjectPtr&);

}

namespace Glacier2
{

class GLACIER2_API PermissionDeniedException : public ::Ice::UserException
{
public:

    PermissionDeniedException() {}
    explicit PermissionDeniedException(const ::std::string&);
    virtual ~PermissionDeniedException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string reason;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static PermissionDeniedException __PermissionDeniedException_init;

class GLACIER2_API SessionNotExistException : public ::Ice::UserException
{
public:

    SessionNotExistException() {}
    virtual ~SessionNotExistException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

namespace Glacier2
{

class GLACIER2_API AMD_Router_createSession : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Glacier2::SessionPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Glacier2::AMD_Router_createSession> AMD_Router_createSessionPtr;

class GLACIER2_API AMD_Router_createSessionFromSecureConnection : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Glacier2::SessionPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Glacier2::AMD_Router_createSessionFromSecureConnection> AMD_Router_createSessionFromSecureConnectionPtr;

class GLACIER2_API AMI_Router_destroySession : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::RouterPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_Router_destroySession> AMI_Router_destroySessionPtr;

}

namespace IceAsync
{

namespace Glacier2
{

class GLACIER2_API AMD_Router_createSession : public ::Glacier2::AMD_Router_createSession, public ::IceInternal::IncomingAsync
{
public:

    AMD_Router_createSession(::IceInternal::Incoming&);

    virtual void ice_response(const ::Glacier2::SessionPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class GLACIER2_API AMD_Router_createSessionFromSecureConnection : public ::Glacier2::AMD_Router_createSessionFromSecureConnection, public ::IceInternal::IncomingAsync
{
public:

    AMD_Router_createSessionFromSecureConnection(::IceInternal::Incoming&);

    virtual void ice_response(const ::Glacier2::SessionPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

namespace IceProxy
{

namespace Glacier2
{

class Router : virtual public ::IceProxy::Ice::Router
{
public:

    ::std::string getCategoryForClient()
    {
        return getCategoryForClient(0);
    }
    ::std::string getCategoryForClient(const ::Ice::Context& __ctx)
    {
        return getCategoryForClient(&__ctx);
    }
    
private:

    GLACIER2_API ::std::string getCategoryForClient(const ::Ice::Context*);
    
public:

    ::Glacier2::SessionPrx createSession(const ::std::string& userId, const ::std::string& password)
    {
        return createSession(userId, password, 0);
    }
    ::Glacier2::SessionPrx createSession(const ::std::string& userId, const ::std::string& password, const ::Ice::Context& __ctx)
    {
        return createSession(userId, password, &__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:

    ::Glacier2::SessionPrx createSessionFromSecureConnection()
    {
        return createSessionFromSecureConnection(0);
    }
    ::Glacier2::SessionPrx createSessionFromSecureConnection(const ::Ice::Context& __ctx)
    {
        return createSessionFromSecureConnection(&__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);
    
public:

    void destroySession()
    {
        destroySession(0);
    }
    void destroySession(const ::Ice::Context& __ctx)
    {
        destroySession(&__ctx);
    }
    
private:

    GLACIER2_API void destroySession(const ::Ice::Context*);
    
public:
    GLACIER2_API bool destroySession_async(const ::Glacier2::AMI_Router_destroySessionPtr&);
    GLACIER2_API bool destroySession_async(const ::Glacier2::AMI_Router_destroySessionPtr&, const ::Ice::Context&);

    ::Ice::Long getSessionTimeout()
    {
        return getSessionTimeout(0);
    }
    ::Ice::Long getSessionTimeout(const ::Ice::Context& __ctx)
    {
        return getSessionTimeout(&__ctx);
    }
    
private:

    GLACIER2_API ::Ice::Long getSessionTimeout(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Router> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Router> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Router*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Router*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class Admin : virtual public ::IceProxy::Ice::Object
{
public:

    void shutdown()
    {
        shutdown(0);
    }
    void shutdown(const ::Ice::Context& __ctx)
    {
        shutdown(&__ctx);
    }
    
private:

    GLACIER2_API void shutdown(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Admin> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Admin> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Admin*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Admin*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace Glacier2
{

class GLACIER2_API Router : virtual public ::IceDelegate::Ice::Router
{
public:

    virtual ::std::string getCategoryForClient(const ::Ice::Context*) = 0;

    virtual ::Glacier2::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Glacier2::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*) = 0;

    virtual void destroySession(const ::Ice::Context*) = 0;

    virtual ::Ice::Long getSessionTimeout(const ::Ice::Context*) = 0;
};

class GLACIER2_API Admin : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Glacier2
{

class GLACIER2_API Router : virtual public ::IceDelegate::Glacier2::Router,
                            virtual public ::IceDelegateM::Ice::Router
{
public:

    virtual ::std::string getCategoryForClient(const ::Ice::Context*);

    virtual ::Glacier2::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::Glacier2::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);

    virtual void destroySession(const ::Ice::Context*);

    virtual ::Ice::Long getSessionTimeout(const ::Ice::Context*);
};

class GLACIER2_API Admin : virtual public ::IceDelegate::Glacier2::Admin,
                           virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Glacier2
{

class GLACIER2_API Router : virtual public ::IceDelegate::Glacier2::Router,
                            virtual public ::IceDelegateD::Ice::Router
{
public:

    virtual ::std::string getCategoryForClient(const ::Ice::Context*);

    virtual ::Glacier2::SessionPrx createSession(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual ::Glacier2::SessionPrx createSessionFromSecureConnection(const ::Ice::Context*);

    virtual void destroySession(const ::Ice::Context*);

    virtual ::Ice::Long getSessionTimeout(const ::Ice::Context*);
};

class GLACIER2_API Admin : virtual public ::IceDelegate::Glacier2::Admin,
                           virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace Glacier2
{

class GLACIER2_API Router : virtual public ::Ice::Router
{
public:

    typedef RouterPrx ProxyType;
    typedef RouterPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::std::string getCategoryForClient(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getCategoryForClient(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void createSession_async(const ::Glacier2::AMD_Router_createSessionPtr&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createSession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void createSessionFromSecureConnection_async(const ::Glacier2::AMD_Router_createSessionFromSecureConnectionPtr&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___createSessionFromSecureConnection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void destroySession(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___destroySession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Long getSessionTimeout(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getSessionTimeout(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API Admin : virtual public ::Ice::Object
{
public:

    typedef AdminPrx ProxyType;
    typedef AdminPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void shutdown(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___shutdown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

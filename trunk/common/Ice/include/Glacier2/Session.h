// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Session.ice'

#ifndef __Glacier2_Session_h__
#define __Glacier2_Session_h__

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
#include <Ice/Direct.h>
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <Ice/BuiltinSequences.h>
#include <Ice/Identity.h>
#include <Glacier2/SSLInfo.h>
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

class Session;

class StringSet;

class IdentitySet;

class SessionControl;

class SessionManager;

class SSLSessionManager;

}

}

namespace Glacier2
{

class Session;
GLACIER2_API bool operator==(const Session&, const Session&);
GLACIER2_API bool operator<(const Session&, const Session&);

class StringSet;
GLACIER2_API bool operator==(const StringSet&, const StringSet&);
GLACIER2_API bool operator<(const StringSet&, const StringSet&);

class IdentitySet;
GLACIER2_API bool operator==(const IdentitySet&, const IdentitySet&);
GLACIER2_API bool operator<(const IdentitySet&, const IdentitySet&);

class SessionControl;
GLACIER2_API bool operator==(const SessionControl&, const SessionControl&);
GLACIER2_API bool operator<(const SessionControl&, const SessionControl&);

class SessionManager;
GLACIER2_API bool operator==(const SessionManager&, const SessionManager&);
GLACIER2_API bool operator<(const SessionManager&, const SessionManager&);

class SSLSessionManager;
GLACIER2_API bool operator==(const SSLSessionManager&, const SSLSessionManager&);
GLACIER2_API bool operator<(const SSLSessionManager&, const SSLSessionManager&);

}

namespace IceInternal
{

GLACIER2_API ::Ice::Object* upCast(::Glacier2::Session*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::Session*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::StringSet*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::StringSet*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::IdentitySet*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::IdentitySet*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::SessionControl*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::SessionControl*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::SessionManager*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::SessionManager*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::SSLSessionManager*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::SSLSessionManager*);

}

namespace Glacier2
{

typedef ::IceInternal::Handle< ::Glacier2::Session> SessionPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::Session> SessionPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, SessionPrx&);
GLACIER2_API void __patch__SessionPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::StringSet> StringSetPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::StringSet> StringSetPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, StringSetPrx&);
GLACIER2_API void __patch__StringSetPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::IdentitySet> IdentitySetPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::IdentitySet> IdentitySetPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, IdentitySetPrx&);
GLACIER2_API void __patch__IdentitySetPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::SessionControl> SessionControlPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::SessionControl> SessionControlPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, SessionControlPrx&);
GLACIER2_API void __patch__SessionControlPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::SessionManager> SessionManagerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::SessionManager> SessionManagerPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, SessionManagerPrx&);
GLACIER2_API void __patch__SessionManagerPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::SSLSessionManager> SSLSessionManagerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::SSLSessionManager> SSLSessionManagerPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, SSLSessionManagerPrx&);
GLACIER2_API void __patch__SSLSessionManagerPtr(void*, ::Ice::ObjectPtr&);

}

namespace Glacier2
{

class GLACIER2_API CannotCreateSessionException : public ::Ice::UserException
{
public:

    CannotCreateSessionException() {}
    explicit CannotCreateSessionException(const ::std::string&);
    virtual ~CannotCreateSessionException() throw();

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

static CannotCreateSessionException __CannotCreateSessionException_init;

}

namespace Glacier2
{

class GLACIER2_API AMI_Session_destroy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::SessionPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_Session_destroy> AMI_Session_destroyPtr;

class GLACIER2_API AMI_SessionControl_destroy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_SessionControl_destroy> AMI_SessionControl_destroyPtr;

class GLACIER2_API AMI_SessionManager_create : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Glacier2::SessionPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::SessionManagerPrx&, const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_SessionManager_create> AMI_SessionManager_createPtr;

class GLACIER2_API AMI_SSLSessionManager_create : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Glacier2::SessionPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::SSLSessionManagerPrx&, const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_SSLSessionManager_create> AMI_SSLSessionManager_createPtr;

}

namespace IceProxy
{

namespace Glacier2
{

class Session : virtual public ::IceProxy::Ice::Object
{
public:

    void destroy()
    {
        destroy(0);
    }
    void destroy(const ::Ice::Context& __ctx)
    {
        destroy(&__ctx);
    }
    
private:

    GLACIER2_API void destroy(const ::Ice::Context*);
    
public:
    GLACIER2_API bool destroy_async(const ::Glacier2::AMI_Session_destroyPtr&);
    GLACIER2_API bool destroy_async(const ::Glacier2::AMI_Session_destroyPtr&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<Session> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Session> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Session*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Session*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class StringSet : virtual public ::IceProxy::Ice::Object
{
public:

    void add(const ::Ice::StringSeq& additions)
    {
        add(additions, 0);
    }
    void add(const ::Ice::StringSeq& additions, const ::Ice::Context& __ctx)
    {
        add(additions, &__ctx);
    }
    
private:

    GLACIER2_API void add(const ::Ice::StringSeq&, const ::Ice::Context*);
    
public:

    void remove(const ::Ice::StringSeq& deletions)
    {
        remove(deletions, 0);
    }
    void remove(const ::Ice::StringSeq& deletions, const ::Ice::Context& __ctx)
    {
        remove(deletions, &__ctx);
    }
    
private:

    GLACIER2_API void remove(const ::Ice::StringSeq&, const ::Ice::Context*);
    
public:

    ::Ice::StringSeq get()
    {
        return get(0);
    }
    ::Ice::StringSeq get(const ::Ice::Context& __ctx)
    {
        return get(&__ctx);
    }
    
private:

    GLACIER2_API ::Ice::StringSeq get(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<StringSet> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<StringSet> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<StringSet*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<StringSet*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class IdentitySet : virtual public ::IceProxy::Ice::Object
{
public:

    void add(const ::Ice::IdentitySeq& additions)
    {
        add(additions, 0);
    }
    void add(const ::Ice::IdentitySeq& additions, const ::Ice::Context& __ctx)
    {
        add(additions, &__ctx);
    }
    
private:

    GLACIER2_API void add(const ::Ice::IdentitySeq&, const ::Ice::Context*);
    
public:

    void remove(const ::Ice::IdentitySeq& deletions)
    {
        remove(deletions, 0);
    }
    void remove(const ::Ice::IdentitySeq& deletions, const ::Ice::Context& __ctx)
    {
        remove(deletions, &__ctx);
    }
    
private:

    GLACIER2_API void remove(const ::Ice::IdentitySeq&, const ::Ice::Context*);
    
public:

    ::Ice::IdentitySeq get()
    {
        return get(0);
    }
    ::Ice::IdentitySeq get(const ::Ice::Context& __ctx)
    {
        return get(&__ctx);
    }
    
private:

    GLACIER2_API ::Ice::IdentitySeq get(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IdentitySet> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IdentitySet*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<IdentitySet*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class SessionControl : virtual public ::IceProxy::Ice::Object
{
public:

    ::Glacier2::StringSetPrx categories()
    {
        return categories(0);
    }
    ::Glacier2::StringSetPrx categories(const ::Ice::Context& __ctx)
    {
        return categories(&__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::StringSetPrx categories(const ::Ice::Context*);
    
public:

    ::Glacier2::StringSetPrx adapterIds()
    {
        return adapterIds(0);
    }
    ::Glacier2::StringSetPrx adapterIds(const ::Ice::Context& __ctx)
    {
        return adapterIds(&__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::StringSetPrx adapterIds(const ::Ice::Context*);
    
public:

    ::Glacier2::IdentitySetPrx identities()
    {
        return identities(0);
    }
    ::Glacier2::IdentitySetPrx identities(const ::Ice::Context& __ctx)
    {
        return identities(&__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::IdentitySetPrx identities(const ::Ice::Context*);
    
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

    GLACIER2_API ::Ice::Int getSessionTimeout(const ::Ice::Context*);
    
public:

    void destroy()
    {
        destroy(0);
    }
    void destroy(const ::Ice::Context& __ctx)
    {
        destroy(&__ctx);
    }
    
private:

    GLACIER2_API void destroy(const ::Ice::Context*);
    
public:
    GLACIER2_API bool destroy_async(const ::Glacier2::AMI_SessionControl_destroyPtr&);
    GLACIER2_API bool destroy_async(const ::Glacier2::AMI_SessionControl_destroyPtr&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<SessionControl> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionControl> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionControl*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<SessionControl*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class SessionManager : virtual public ::IceProxy::Ice::Object
{
public:

    ::Glacier2::SessionPrx create(const ::std::string& userId, const ::Glacier2::SessionControlPrx& control)
    {
        return create(userId, control, 0);
    }
    ::Glacier2::SessionPrx create(const ::std::string& userId, const ::Glacier2::SessionControlPrx& control, const ::Ice::Context& __ctx)
    {
        return create(userId, control, &__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::SessionPrx create(const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
    
public:
    GLACIER2_API bool create_async(const ::Glacier2::AMI_SessionManager_createPtr&, const ::std::string&, const ::Glacier2::SessionControlPrx&);
    GLACIER2_API bool create_async(const ::Glacier2::AMI_SessionManager_createPtr&, const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<SessionManager> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SessionManager> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SessionManager*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<SessionManager*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class SSLSessionManager : virtual public ::IceProxy::Ice::Object
{
public:

    ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo& info, const ::Glacier2::SessionControlPrx& control)
    {
        return create(info, control, 0);
    }
    ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo& info, const ::Glacier2::SessionControlPrx& control, const ::Ice::Context& __ctx)
    {
        return create(info, control, &__ctx);
    }
    
private:

    GLACIER2_API ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
    
public:
    GLACIER2_API bool create_async(const ::Glacier2::AMI_SSLSessionManager_createPtr&, const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&);
    GLACIER2_API bool create_async(const ::Glacier2::AMI_SSLSessionManager_createPtr&, const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLSessionManager> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLSessionManager*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<SSLSessionManager*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class GLACIER2_API Session : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*) = 0;
};

class GLACIER2_API StringSet : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void add(const ::Ice::StringSeq&, const ::Ice::Context*) = 0;

    virtual void remove(const ::Ice::StringSeq&, const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq get(const ::Ice::Context*) = 0;
};

class GLACIER2_API IdentitySet : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void add(const ::Ice::IdentitySeq&, const ::Ice::Context*) = 0;

    virtual void remove(const ::Ice::IdentitySeq&, const ::Ice::Context*) = 0;

    virtual ::Ice::IdentitySeq get(const ::Ice::Context*) = 0;
};

class GLACIER2_API SessionControl : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Glacier2::StringSetPrx categories(const ::Ice::Context*) = 0;

    virtual ::Glacier2::StringSetPrx adapterIds(const ::Ice::Context*) = 0;

    virtual ::Glacier2::IdentitySetPrx identities(const ::Ice::Context*) = 0;

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*) = 0;

    virtual void destroy(const ::Ice::Context*) = 0;
};

class GLACIER2_API SessionManager : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*) = 0;
};

class GLACIER2_API SSLSessionManager : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Glacier2
{

class GLACIER2_API Session : virtual public ::IceDelegate::Glacier2::Session,
                             virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*);
};

class GLACIER2_API StringSet : virtual public ::IceDelegate::Glacier2::StringSet,
                               virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void add(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void remove(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual ::Ice::StringSeq get(const ::Ice::Context*);
};

class GLACIER2_API IdentitySet : virtual public ::IceDelegate::Glacier2::IdentitySet,
                                 virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void add(const ::Ice::IdentitySeq&, const ::Ice::Context*);

    virtual void remove(const ::Ice::IdentitySeq&, const ::Ice::Context*);

    virtual ::Ice::IdentitySeq get(const ::Ice::Context*);
};

class GLACIER2_API SessionControl : virtual public ::IceDelegate::Glacier2::SessionControl,
                                    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Glacier2::StringSetPrx categories(const ::Ice::Context*);

    virtual ::Glacier2::StringSetPrx adapterIds(const ::Ice::Context*);

    virtual ::Glacier2::IdentitySetPrx identities(const ::Ice::Context*);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class GLACIER2_API SessionManager : virtual public ::IceDelegate::Glacier2::SessionManager,
                                    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
};

class GLACIER2_API SSLSessionManager : virtual public ::IceDelegate::Glacier2::SSLSessionManager,
                                       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Glacier2
{

class GLACIER2_API Session : virtual public ::IceDelegate::Glacier2::Session,
                             virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void destroy(const ::Ice::Context*);
};

class GLACIER2_API StringSet : virtual public ::IceDelegate::Glacier2::StringSet,
                               virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void add(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void remove(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual ::Ice::StringSeq get(const ::Ice::Context*);
};

class GLACIER2_API IdentitySet : virtual public ::IceDelegate::Glacier2::IdentitySet,
                                 virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void add(const ::Ice::IdentitySeq&, const ::Ice::Context*);

    virtual void remove(const ::Ice::IdentitySeq&, const ::Ice::Context*);

    virtual ::Ice::IdentitySeq get(const ::Ice::Context*);
};

class GLACIER2_API SessionControl : virtual public ::IceDelegate::Glacier2::SessionControl,
                                    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Glacier2::StringSetPrx categories(const ::Ice::Context*);

    virtual ::Glacier2::StringSetPrx adapterIds(const ::Ice::Context*);

    virtual ::Glacier2::IdentitySetPrx identities(const ::Ice::Context*);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class GLACIER2_API SessionManager : virtual public ::IceDelegate::Glacier2::SessionManager,
                                    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
};

class GLACIER2_API SSLSessionManager : virtual public ::IceDelegate::Glacier2::SSLSessionManager,
                                       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Context*);
};

}

}

namespace Glacier2
{

class GLACIER2_API Session : virtual public ::Ice::Object
{
public:

    typedef SessionPrx ProxyType;
    typedef SessionPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API StringSet : virtual public ::Ice::Object
{
public:

    typedef StringSetPrx ProxyType;
    typedef StringSetPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void add(const ::Ice::StringSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___add(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void remove(const ::Ice::StringSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remove(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::StringSeq get(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API IdentitySet : virtual public ::Ice::Object
{
public:

    typedef IdentitySetPrx ProxyType;
    typedef IdentitySetPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void add(const ::Ice::IdentitySeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___add(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void remove(const ::Ice::IdentitySeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remove(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::IdentitySeq get(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API SessionControl : virtual public ::Ice::Object
{
public:

    typedef SessionControlPrx ProxyType;
    typedef SessionControlPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Glacier2::StringSetPrx categories(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___categories(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Glacier2::StringSetPrx adapterIds(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___adapterIds(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Glacier2::IdentitySetPrx identities(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___identities(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getSessionTimeout(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getSessionTimeout(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API SessionManager : virtual public ::Ice::Object
{
public:

    typedef SessionManagerPrx ProxyType;
    typedef SessionManagerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Glacier2::SessionPrx create(const ::std::string&, const ::Glacier2::SessionControlPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___create(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API SSLSessionManager : virtual public ::Ice::Object
{
public:

    typedef SSLSessionManagerPrx ProxyType;
    typedef SSLSessionManagerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Glacier2::SessionPrx create(const ::Glacier2::SSLInfo&, const ::Glacier2::SessionControlPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___create(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

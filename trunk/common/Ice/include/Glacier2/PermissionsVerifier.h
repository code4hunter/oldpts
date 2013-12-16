// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `PermissionsVerifier.ice'

#ifndef __Glacier2_PermissionsVerifier_h__
#define __Glacier2_PermissionsVerifier_h__

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
#include <Ice/StreamF.h>
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

class PermissionsVerifier;

class SSLPermissionsVerifier;

}

}

namespace Glacier2
{

class PermissionsVerifier;
GLACIER2_API bool operator==(const PermissionsVerifier&, const PermissionsVerifier&);
GLACIER2_API bool operator<(const PermissionsVerifier&, const PermissionsVerifier&);

class SSLPermissionsVerifier;
GLACIER2_API bool operator==(const SSLPermissionsVerifier&, const SSLPermissionsVerifier&);
GLACIER2_API bool operator<(const SSLPermissionsVerifier&, const SSLPermissionsVerifier&);

}

namespace IceInternal
{

GLACIER2_API ::Ice::Object* upCast(::Glacier2::PermissionsVerifier*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::PermissionsVerifier*);

GLACIER2_API ::Ice::Object* upCast(::Glacier2::SSLPermissionsVerifier*);
GLACIER2_API ::IceProxy::Ice::Object* upCast(::IceProxy::Glacier2::SSLPermissionsVerifier*);

}

namespace Glacier2
{

typedef ::IceInternal::Handle< ::Glacier2::PermissionsVerifier> PermissionsVerifierPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::PermissionsVerifier> PermissionsVerifierPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, PermissionsVerifierPrx&);
GLACIER2_API void __patch__PermissionsVerifierPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Glacier2::SSLPermissionsVerifier> SSLPermissionsVerifierPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Glacier2::SSLPermissionsVerifier> SSLPermissionsVerifierPrx;

GLACIER2_API void __read(::IceInternal::BasicStream*, SSLPermissionsVerifierPrx&);
GLACIER2_API void __patch__SSLPermissionsVerifierPtr(void*, ::Ice::ObjectPtr&);

}

namespace Glacier2
{

class GLACIER2_API AMI_PermissionsVerifier_checkPermissions : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(bool, const ::std::string&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::PermissionsVerifierPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_PermissionsVerifier_checkPermissions> AMI_PermissionsVerifier_checkPermissionsPtr;

class GLACIER2_API AMI_SSLPermissionsVerifier_authorize : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(bool, const ::std::string&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Glacier2::SSLPermissionsVerifierPrx&, const ::Glacier2::SSLInfo&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Glacier2::AMI_SSLPermissionsVerifier_authorize> AMI_SSLPermissionsVerifier_authorizePtr;

}

namespace IceProxy
{

namespace Glacier2
{

class PermissionsVerifier : virtual public ::IceProxy::Ice::Object
{
public:

    bool checkPermissions(const ::std::string& userId, const ::std::string& password, ::std::string& reason)
    {
        return checkPermissions(userId, password, reason, 0);
    }
    bool checkPermissions(const ::std::string& userId, const ::std::string& password, ::std::string& reason, const ::Ice::Context& __ctx)
    {
        return checkPermissions(userId, password, reason, &__ctx);
    }
    
private:

    GLACIER2_API bool checkPermissions(const ::std::string&, const ::std::string&, ::std::string&, const ::Ice::Context*);
    
public:
    GLACIER2_API bool checkPermissions_async(const ::Glacier2::AMI_PermissionsVerifier_checkPermissionsPtr&, const ::std::string&, const ::std::string&);
    GLACIER2_API bool checkPermissions_async(const ::Glacier2::AMI_PermissionsVerifier_checkPermissionsPtr&, const ::std::string&, const ::std::string&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PermissionsVerifier> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PermissionsVerifier*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<PermissionsVerifier*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    GLACIER2_API static const ::std::string& ice_staticId();

private: 

    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    GLACIER2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    GLACIER2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class SSLPermissionsVerifier : virtual public ::IceProxy::Ice::Object
{
public:

    bool authorize(const ::Glacier2::SSLInfo& info, ::std::string& reason)
    {
        return authorize(info, reason, 0);
    }
    bool authorize(const ::Glacier2::SSLInfo& info, ::std::string& reason, const ::Ice::Context& __ctx)
    {
        return authorize(info, reason, &__ctx);
    }
    
private:

    GLACIER2_API bool authorize(const ::Glacier2::SSLInfo&, ::std::string&, const ::Ice::Context*);
    
public:
    GLACIER2_API bool authorize_async(const ::Glacier2::AMI_SSLPermissionsVerifier_authorizePtr&, const ::Glacier2::SSLInfo&);
    GLACIER2_API bool authorize_async(const ::Glacier2::AMI_SSLPermissionsVerifier_authorizePtr&, const ::Glacier2::SSLInfo&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<SSLPermissionsVerifier> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<SSLPermissionsVerifier*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<SSLPermissionsVerifier*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class GLACIER2_API PermissionsVerifier : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool checkPermissions(const ::std::string&, const ::std::string&, ::std::string&, const ::Ice::Context*) = 0;
};

class GLACIER2_API SSLPermissionsVerifier : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool authorize(const ::Glacier2::SSLInfo&, ::std::string&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Glacier2
{

class GLACIER2_API PermissionsVerifier : virtual public ::IceDelegate::Glacier2::PermissionsVerifier,
                                         virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool checkPermissions(const ::std::string&, const ::std::string&, ::std::string&, const ::Ice::Context*);
};

class GLACIER2_API SSLPermissionsVerifier : virtual public ::IceDelegate::Glacier2::SSLPermissionsVerifier,
                                            virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool authorize(const ::Glacier2::SSLInfo&, ::std::string&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Glacier2
{

class GLACIER2_API PermissionsVerifier : virtual public ::IceDelegate::Glacier2::PermissionsVerifier,
                                         virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool checkPermissions(const ::std::string&, const ::std::string&, ::std::string&, const ::Ice::Context*);
};

class GLACIER2_API SSLPermissionsVerifier : virtual public ::IceDelegate::Glacier2::SSLPermissionsVerifier,
                                            virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool authorize(const ::Glacier2::SSLInfo&, ::std::string&, const ::Ice::Context*);
};

}

}

namespace Glacier2
{

class GLACIER2_API PermissionsVerifier : virtual public ::Ice::Object
{
public:

    typedef PermissionsVerifierPrx ProxyType;
    typedef PermissionsVerifierPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool checkPermissions(const ::std::string&, const ::std::string&, ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___checkPermissions(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class GLACIER2_API SSLPermissionsVerifier : virtual public ::Ice::Object
{
public:

    typedef SSLPermissionsVerifierPrx ProxyType;
    typedef SSLPermissionsVerifierPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool authorize(const ::Glacier2::SSLInfo&, ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___authorize(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

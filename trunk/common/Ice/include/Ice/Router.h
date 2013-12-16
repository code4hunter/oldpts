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

#ifndef __Ice_Router_h__
#define __Ice_Router_h__

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
#include <Ice/BuiltinSequences.h>
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

class Router;

}

}

namespace Ice
{

class Router;
ICE_API bool operator==(const Router&, const Router&);
ICE_API bool operator<(const Router&, const Router&);

}

namespace IceInternal
{

ICE_API ::Ice::Object* upCast(::Ice::Router*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Router*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Router> RouterPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Router> RouterPrx;

ICE_API void __read(::IceInternal::BasicStream*, RouterPrx&);
ICE_API void __patch__RouterPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

class ICE_API AMI_Router_getClientProxy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::RouterPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Router_getClientProxy> AMI_Router_getClientProxyPtr;

class ICE_API AMI_Router_addProxies : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectProxySeq&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::RouterPrx&, const ::Ice::ObjectProxySeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Router_addProxies> AMI_Router_addProxiesPtr;

}

namespace IceProxy
{

namespace Ice
{

class Router : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::ObjectPrx getClientProxy()
    {
        return getClientProxy(0);
    }
    ::Ice::ObjectPrx getClientProxy(const ::Ice::Context& __ctx)
    {
        return getClientProxy(&__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx getClientProxy(const ::Ice::Context*);
    
public:
    ICE_API bool getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr&);
    ICE_API bool getClientProxy_async(const ::Ice::AMI_Router_getClientProxyPtr&, const ::Ice::Context&);

    ::Ice::ObjectPrx getServerProxy()
    {
        return getServerProxy(0);
    }
    ::Ice::ObjectPrx getServerProxy(const ::Ice::Context& __ctx)
    {
        return getServerProxy(&__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx getServerProxy(const ::Ice::Context*);
    
public:

    ICE_DEPRECATED_API void addProxy(const ::Ice::ObjectPrx& proxy)
    {
        addProxy(proxy, 0);
    }
    ICE_DEPRECATED_API void addProxy(const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        addProxy(proxy, &__ctx);
    }
    
private:

    ICE_API void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq& proxies)
    {
        return addProxies(proxies, 0);
    }
    ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq& proxies, const ::Ice::Context& __ctx)
    {
        return addProxies(proxies, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Context*);
    
public:
    ICE_API bool addProxies_async(const ::Ice::AMI_Router_addProxiesPtr&, const ::Ice::ObjectProxySeq&);
    ICE_API bool addProxies_async(const ::Ice::AMI_Router_addProxiesPtr&, const ::Ice::ObjectProxySeq&, const ::Ice::Context&);
    
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
    
    ICE_API static const ::std::string& ice_staticId();

private: 

    ICE_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace Ice
{

class ICE_API Router : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx getClientProxy(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx getServerProxy(const ::Ice::Context*) = 0;

    virtual void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Ice
{

class ICE_API Router : virtual public ::IceDelegate::Ice::Router,
                       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx getClientProxy(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getServerProxy(const ::Ice::Context*);

    virtual void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Ice
{

class ICE_API Router : virtual public ::IceDelegate::Ice::Router,
                       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx getClientProxy(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getServerProxy(const ::Ice::Context*);

    virtual void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Context*);
};

}

}

namespace Ice
{

class ICE_API Router : virtual public ::Ice::Object
{
public:

    typedef RouterPrx ProxyType;
    typedef RouterPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::ObjectPrx getClientProxy(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getClientProxy(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx getServerProxy(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerProxy(::IceInternal::Incoming&, const ::Ice::Current&) const;

    ICE_DEPRECATED_API virtual void addProxy(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addProxy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::ObjectProxySeq addProxies(const ::Ice::ObjectProxySeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addProxies(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

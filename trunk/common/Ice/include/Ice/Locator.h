// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Locator.ice'

#ifndef __Ice_Locator_h__
#define __Ice_Locator_h__

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
#include <Ice/Identity.h>
#include <Ice/ProcessF.h>
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

class LocatorRegistry;

class Locator;

}

}

namespace Ice
{

class LocatorRegistry;
ICE_API bool operator==(const LocatorRegistry&, const LocatorRegistry&);
ICE_API bool operator<(const LocatorRegistry&, const LocatorRegistry&);

class Locator;
ICE_API bool operator==(const Locator&, const Locator&);
ICE_API bool operator<(const Locator&, const Locator&);

}

namespace IceInternal
{

ICE_API ::Ice::Object* upCast(::Ice::LocatorRegistry*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::LocatorRegistry*);

ICE_API ::Ice::Object* upCast(::Ice::Locator*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Locator*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::LocatorRegistry> LocatorRegistryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::LocatorRegistry> LocatorRegistryPrx;

ICE_API void __read(::IceInternal::BasicStream*, LocatorRegistryPrx&);
ICE_API void __patch__LocatorRegistryPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::Ice::Locator> LocatorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Locator> LocatorPrx;

ICE_API void __read(::IceInternal::BasicStream*, LocatorPrx&);
ICE_API void __patch__LocatorPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

class ICE_API AdapterNotFoundException : public ::Ice::UserException
{
public:

    AdapterNotFoundException() {}
    virtual ~AdapterNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static AdapterNotFoundException __AdapterNotFoundException_init;

class ICE_API InvalidReplicaGroupIdException : public ::Ice::UserException
{
public:

    InvalidReplicaGroupIdException() {}
    virtual ~InvalidReplicaGroupIdException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_API AdapterAlreadyActiveException : public ::Ice::UserException
{
public:

    AdapterAlreadyActiveException() {}
    virtual ~AdapterAlreadyActiveException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_API ObjectNotFoundException : public ::Ice::UserException
{
public:

    ObjectNotFoundException() {}
    virtual ~ObjectNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_API ServerNotFoundException : public ::Ice::UserException
{
public:

    ServerNotFoundException() {}
    virtual ~ServerNotFoundException() throw();

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

namespace Ice
{

class ICE_API AMI_Locator_findObjectById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorPrx&, const ::Ice::Identity&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Locator_findObjectById> AMI_Locator_findObjectByIdPtr;

class ICE_API AMD_Locator_findObjectById : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Ice::AMD_Locator_findObjectById> AMD_Locator_findObjectByIdPtr;

class ICE_API AMI_Locator_findAdapterById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Locator_findAdapterById> AMI_Locator_findAdapterByIdPtr;

class ICE_API AMD_Locator_findAdapterById : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Ice::AMD_Locator_findAdapterById> AMD_Locator_findAdapterByIdPtr;

class ICE_API AMI_LocatorRegistry_setAdapterDirectProxy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorRegistryPrx&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_LocatorRegistry_setAdapterDirectProxy> AMI_LocatorRegistry_setAdapterDirectProxyPtr;

class ICE_API AMD_LocatorRegistry_setAdapterDirectProxy : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Ice::AMD_LocatorRegistry_setAdapterDirectProxy> AMD_LocatorRegistry_setAdapterDirectProxyPtr;

class ICE_API AMI_LocatorRegistry_setReplicatedAdapterDirectProxy : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::LocatorRegistryPrx&, const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_LocatorRegistry_setReplicatedAdapterDirectProxy> AMI_LocatorRegistry_setReplicatedAdapterDirectProxyPtr;

class ICE_API AMD_LocatorRegistry_setReplicatedAdapterDirectProxy : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Ice::AMD_LocatorRegistry_setReplicatedAdapterDirectProxy> AMD_LocatorRegistry_setReplicatedAdapterDirectProxyPtr;

class ICE_API AMD_LocatorRegistry_setServerProcessProxy : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::Ice::AMD_LocatorRegistry_setServerProcessProxy> AMD_LocatorRegistry_setServerProcessProxyPtr;

}

namespace IceAsync
{

namespace Ice
{

class ICE_API AMD_Locator_findObjectById : public ::Ice::AMD_Locator_findObjectById, public ::IceInternal::IncomingAsync
{
public:

    AMD_Locator_findObjectById(::IceInternal::Incoming&);

    virtual void ice_response(const ::Ice::ObjectPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_API AMD_Locator_findAdapterById : public ::Ice::AMD_Locator_findAdapterById, public ::IceInternal::IncomingAsync
{
public:

    AMD_Locator_findAdapterById(::IceInternal::Incoming&);

    virtual void ice_response(const ::Ice::ObjectPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_API AMD_LocatorRegistry_setAdapterDirectProxy : public ::Ice::AMD_LocatorRegistry_setAdapterDirectProxy, public ::IceInternal::IncomingAsync
{
public:

    AMD_LocatorRegistry_setAdapterDirectProxy(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_API AMD_LocatorRegistry_setReplicatedAdapterDirectProxy : public ::Ice::AMD_LocatorRegistry_setReplicatedAdapterDirectProxy, public ::IceInternal::IncomingAsync
{
public:

    AMD_LocatorRegistry_setReplicatedAdapterDirectProxy(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_API AMD_LocatorRegistry_setServerProcessProxy : public ::Ice::AMD_LocatorRegistry_setServerProcessProxy, public ::IceInternal::IncomingAsync
{
public:

    AMD_LocatorRegistry_setServerProcessProxy(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

namespace IceProxy
{

namespace Ice
{

class Locator : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::ObjectPrx findObjectById(const ::Ice::Identity& id)
    {
        return findObjectById(id, 0);
    }
    ::Ice::ObjectPrx findObjectById(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        return findObjectById(id, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    ICE_API bool findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr&, const ::Ice::Identity&);
    ICE_API bool findObjectById_async(const ::Ice::AMI_Locator_findObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Context&);

    ::Ice::ObjectPrx findAdapterById(const ::std::string& id)
    {
        return findAdapterById(id, 0);
    }
    ::Ice::ObjectPrx findAdapterById(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return findAdapterById(id, &__ctx);
    }
    
private:

    ICE_API ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_API bool findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr&, const ::std::string&);
    ICE_API bool findAdapterById_async(const ::Ice::AMI_Locator_findAdapterByIdPtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::LocatorRegistryPrx getRegistry()
    {
        return getRegistry(0);
    }
    ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context& __ctx)
    {
        return getRegistry(&__ctx);
    }
    
private:

    ICE_API ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Locator> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Locator> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Locator*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Locator*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_API static const ::std::string& ice_staticId();

private: 

    ICE_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class LocatorRegistry : virtual public ::IceProxy::Ice::Object
{
public:

    void setAdapterDirectProxy(const ::std::string& id, const ::Ice::ObjectPrx& proxy)
    {
        setAdapterDirectProxy(id, proxy, 0);
    }
    void setAdapterDirectProxy(const ::std::string& id, const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        setAdapterDirectProxy(id, proxy, &__ctx);
    }
    
private:

    ICE_API void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:
    ICE_API bool setAdapterDirectProxy_async(const ::Ice::AMI_LocatorRegistry_setAdapterDirectProxyPtr&, const ::std::string&, const ::Ice::ObjectPrx&);
    ICE_API bool setAdapterDirectProxy_async(const ::Ice::AMI_LocatorRegistry_setAdapterDirectProxyPtr&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context&);

    void setReplicatedAdapterDirectProxy(const ::std::string& adapterId, const ::std::string& replicaGroupId, const ::Ice::ObjectPrx& p)
    {
        setReplicatedAdapterDirectProxy(adapterId, replicaGroupId, p, 0);
    }
    void setReplicatedAdapterDirectProxy(const ::std::string& adapterId, const ::std::string& replicaGroupId, const ::Ice::ObjectPrx& p, const ::Ice::Context& __ctx)
    {
        setReplicatedAdapterDirectProxy(adapterId, replicaGroupId, p, &__ctx);
    }
    
private:

    ICE_API void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:
    ICE_API bool setReplicatedAdapterDirectProxy_async(const ::Ice::AMI_LocatorRegistry_setReplicatedAdapterDirectProxyPtr&, const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&);
    ICE_API bool setReplicatedAdapterDirectProxy_async(const ::Ice::AMI_LocatorRegistry_setReplicatedAdapterDirectProxyPtr&, const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context&);

    void setServerProcessProxy(const ::std::string& id, const ::Ice::ProcessPrx& proxy)
    {
        setServerProcessProxy(id, proxy, 0);
    }
    void setServerProcessProxy(const ::std::string& id, const ::Ice::ProcessPrx& proxy, const ::Ice::Context& __ctx)
    {
        setServerProcessProxy(id, proxy, &__ctx);
    }
    
private:

    ICE_API void setServerProcessProxy(const ::std::string&, const ::Ice::ProcessPrx&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LocatorRegistry> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LocatorRegistry*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<LocatorRegistry*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_API Locator : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context*) = 0;
};

class ICE_API LocatorRegistry : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void setServerProcessProxy(const ::std::string&, const ::Ice::ProcessPrx&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Ice
{

class ICE_API Locator : virtual public ::IceDelegate::Ice::Locator,
                        virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context*);
};

class ICE_API LocatorRegistry : virtual public ::IceDelegate::Ice::LocatorRegistry,
                                virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void setServerProcessProxy(const ::std::string&, const ::Ice::ProcessPrx&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Ice
{

class ICE_API Locator : virtual public ::IceDelegate::Ice::Locator,
                        virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findAdapterById(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Context*);
};

class ICE_API LocatorRegistry : virtual public ::IceDelegate::Ice::LocatorRegistry,
                                virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void setAdapterDirectProxy(const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void setReplicatedAdapterDirectProxy(const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void setServerProcessProxy(const ::std::string&, const ::Ice::ProcessPrx&, const ::Ice::Context*);
};

}

}

namespace Ice
{

class ICE_API Locator : virtual public ::Ice::Object
{
public:

    typedef LocatorPrx ProxyType;
    typedef LocatorPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void findObjectById_async(const ::Ice::AMD_Locator_findObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findObjectById(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void findAdapterById_async(const ::Ice::AMD_Locator_findAdapterByIdPtr&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findAdapterById(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::LocatorRegistryPrx getRegistry(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getRegistry(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_API LocatorRegistry : virtual public ::Ice::Object
{
public:

    typedef LocatorRegistryPrx ProxyType;
    typedef LocatorRegistryPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void setAdapterDirectProxy_async(const ::Ice::AMD_LocatorRegistry_setAdapterDirectProxyPtr&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setAdapterDirectProxy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setReplicatedAdapterDirectProxy_async(const ::Ice::AMD_LocatorRegistry_setReplicatedAdapterDirectProxyPtr&, const ::std::string&, const ::std::string&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setReplicatedAdapterDirectProxy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setServerProcessProxy_async(const ::Ice::AMD_LocatorRegistry_setServerProcessProxyPtr&, const ::std::string&, const ::Ice::ProcessPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setServerProcessProxy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

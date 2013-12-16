// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `IceBox.ice'

#ifndef __IceBox_IceBox_h__
#define __IceBox_IceBox_h__

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
#include <Ice/CommunicatorF.h>
#include <Ice/PropertiesF.h>
#include <Ice/SliceChecksumDict.h>
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

#ifndef ICE_BOX_API
#   ifdef ICE_BOX_API_EXPORTS
#       define ICE_BOX_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_BOX_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace IceBox
{

class ServiceObserver;

class ServiceManager;

}

}

namespace IceBox
{

class Service;
ICE_BOX_API bool operator==(const Service&, const Service&);
ICE_BOX_API bool operator<(const Service&, const Service&);

class ServiceObserver;
ICE_BOX_API bool operator==(const ServiceObserver&, const ServiceObserver&);
ICE_BOX_API bool operator<(const ServiceObserver&, const ServiceObserver&);

class ServiceManager;
ICE_BOX_API bool operator==(const ServiceManager&, const ServiceManager&);
ICE_BOX_API bool operator<(const ServiceManager&, const ServiceManager&);

}

namespace IceInternal
{

ICE_BOX_API ::Ice::LocalObject* upCast(::IceBox::Service*);

ICE_BOX_API ::Ice::Object* upCast(::IceBox::ServiceObserver*);
ICE_BOX_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceBox::ServiceObserver*);

ICE_BOX_API ::Ice::Object* upCast(::IceBox::ServiceManager*);
ICE_BOX_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceBox::ServiceManager*);

}

namespace IceBox
{

typedef ::IceInternal::Handle< ::IceBox::Service> ServicePtr;

typedef ::IceInternal::Handle< ::IceBox::ServiceObserver> ServiceObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceBox::ServiceObserver> ServiceObserverPrx;

ICE_BOX_API void __read(::IceInternal::BasicStream*, ServiceObserverPrx&);
ICE_BOX_API void __patch__ServiceObserverPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceBox::ServiceManager> ServiceManagerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceBox::ServiceManager> ServiceManagerPrx;

ICE_BOX_API void __read(::IceInternal::BasicStream*, ServiceManagerPrx&);
ICE_BOX_API void __patch__ServiceManagerPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceBox
{

class ICE_BOX_API FailureException : public ::Ice::LocalException
{
public:

    FailureException(const char*, int);
    FailureException(const char*, int, const ::std::string&);
    virtual ~FailureException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    ::std::string reason;
};

class ICE_BOX_API AlreadyStartedException : public ::Ice::UserException
{
public:

    AlreadyStartedException() {}
    virtual ~AlreadyStartedException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static AlreadyStartedException __AlreadyStartedException_init;

class ICE_BOX_API AlreadyStoppedException : public ::Ice::UserException
{
public:

    AlreadyStoppedException() {}
    virtual ~AlreadyStoppedException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_BOX_API NoSuchServiceException : public ::Ice::UserException
{
public:

    NoSuchServiceException() {}
    virtual ~NoSuchServiceException() throw();

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

namespace IceBox
{

class ICE_BOX_API AMI_ServiceObserver_servicesStarted : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceBox::ServiceObserverPrx&, const ::Ice::StringSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceBox::AMI_ServiceObserver_servicesStarted> AMI_ServiceObserver_servicesStartedPtr;

class ICE_BOX_API AMI_ServiceObserver_servicesStopped : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceBox::ServiceObserverPrx&, const ::Ice::StringSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceBox::AMI_ServiceObserver_servicesStopped> AMI_ServiceObserver_servicesStoppedPtr;

class ICE_BOX_API AMI_ServiceManager_startService : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceBox::ServiceManagerPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceBox::AMI_ServiceManager_startService> AMI_ServiceManager_startServicePtr;

class ICE_BOX_API AMI_ServiceManager_stopService : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceBox::ServiceManagerPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceBox::AMI_ServiceManager_stopService> AMI_ServiceManager_stopServicePtr;

class ICE_BOX_API AMI_ServiceManager_addObserver : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceBox::ServiceManagerPrx&, const ::IceBox::ServiceObserverPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceBox::AMI_ServiceManager_addObserver> AMI_ServiceManager_addObserverPtr;

}

namespace IceProxy
{

namespace IceBox
{

class ServiceObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void servicesStarted(const ::Ice::StringSeq& services)
    {
        servicesStarted(services, 0);
    }
    void servicesStarted(const ::Ice::StringSeq& services, const ::Ice::Context& __ctx)
    {
        servicesStarted(services, &__ctx);
    }
    
private:

    ICE_BOX_API void servicesStarted(const ::Ice::StringSeq&, const ::Ice::Context*);
    
public:
    ICE_BOX_API bool servicesStarted_async(const ::IceBox::AMI_ServiceObserver_servicesStartedPtr&, const ::Ice::StringSeq&);
    ICE_BOX_API bool servicesStarted_async(const ::IceBox::AMI_ServiceObserver_servicesStartedPtr&, const ::Ice::StringSeq&, const ::Ice::Context&);

    void servicesStopped(const ::Ice::StringSeq& services)
    {
        servicesStopped(services, 0);
    }
    void servicesStopped(const ::Ice::StringSeq& services, const ::Ice::Context& __ctx)
    {
        servicesStopped(services, &__ctx);
    }
    
private:

    ICE_BOX_API void servicesStopped(const ::Ice::StringSeq&, const ::Ice::Context*);
    
public:
    ICE_BOX_API bool servicesStopped_async(const ::IceBox::AMI_ServiceObserver_servicesStoppedPtr&, const ::Ice::StringSeq&);
    ICE_BOX_API bool servicesStopped_async(const ::IceBox::AMI_ServiceObserver_servicesStoppedPtr&, const ::Ice::StringSeq&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ServiceObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_BOX_API static const ::std::string& ice_staticId();

private: 

    ICE_BOX_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_BOX_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_BOX_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class ServiceManager : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::SliceChecksumDict getSliceChecksums()
    {
        return getSliceChecksums(0);
    }
    ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context& __ctx)
    {
        return getSliceChecksums(&__ctx);
    }
    
private:

    ICE_BOX_API ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
    
public:

    void startService(const ::std::string& service)
    {
        startService(service, 0);
    }
    void startService(const ::std::string& service, const ::Ice::Context& __ctx)
    {
        startService(service, &__ctx);
    }
    
private:

    ICE_BOX_API void startService(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_BOX_API bool startService_async(const ::IceBox::AMI_ServiceManager_startServicePtr&, const ::std::string&);
    ICE_BOX_API bool startService_async(const ::IceBox::AMI_ServiceManager_startServicePtr&, const ::std::string&, const ::Ice::Context&);

    void stopService(const ::std::string& service)
    {
        stopService(service, 0);
    }
    void stopService(const ::std::string& service, const ::Ice::Context& __ctx)
    {
        stopService(service, &__ctx);
    }
    
private:

    ICE_BOX_API void stopService(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_BOX_API bool stopService_async(const ::IceBox::AMI_ServiceManager_stopServicePtr&, const ::std::string&);
    ICE_BOX_API bool stopService_async(const ::IceBox::AMI_ServiceManager_stopServicePtr&, const ::std::string&, const ::Ice::Context&);

    void addObserver(const ::IceBox::ServiceObserverPrx& observer)
    {
        addObserver(observer, 0);
    }
    void addObserver(const ::IceBox::ServiceObserverPrx& observer, const ::Ice::Context& __ctx)
    {
        addObserver(observer, &__ctx);
    }
    
private:

    ICE_BOX_API void addObserver(const ::IceBox::ServiceObserverPrx&, const ::Ice::Context*);
    
public:
    ICE_BOX_API bool addObserver_async(const ::IceBox::AMI_ServiceManager_addObserverPtr&, const ::IceBox::ServiceObserverPrx&);
    ICE_BOX_API bool addObserver_async(const ::IceBox::AMI_ServiceManager_addObserverPtr&, const ::IceBox::ServiceObserverPrx&, const ::Ice::Context&);

    void shutdown()
    {
        shutdown(0);
    }
    void shutdown(const ::Ice::Context& __ctx)
    {
        shutdown(&__ctx);
    }
    
private:

    ICE_BOX_API void shutdown(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceManager> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceManager*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ServiceManager*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_BOX_API static const ::std::string& ice_staticId();

private: 

    ICE_BOX_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_BOX_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_BOX_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace IceBox
{

class ICE_BOX_API ServiceObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void servicesStarted(const ::Ice::StringSeq&, const ::Ice::Context*) = 0;

    virtual void servicesStopped(const ::Ice::StringSeq&, const ::Ice::Context*) = 0;
};

class ICE_BOX_API ServiceManager : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*) = 0;

    virtual void startService(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void stopService(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void addObserver(const ::IceBox::ServiceObserverPrx&, const ::Ice::Context*) = 0;

    virtual void shutdown(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceBox
{

class ICE_BOX_API ServiceObserver : virtual public ::IceDelegate::IceBox::ServiceObserver,
                                    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void servicesStarted(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void servicesStopped(const ::Ice::StringSeq&, const ::Ice::Context*);
};

class ICE_BOX_API ServiceManager : virtual public ::IceDelegate::IceBox::ServiceManager,
                                   virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);

    virtual void startService(const ::std::string&, const ::Ice::Context*);

    virtual void stopService(const ::std::string&, const ::Ice::Context*);

    virtual void addObserver(const ::IceBox::ServiceObserverPrx&, const ::Ice::Context*);

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceBox
{

class ICE_BOX_API ServiceObserver : virtual public ::IceDelegate::IceBox::ServiceObserver,
                                    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void servicesStarted(const ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void servicesStopped(const ::Ice::StringSeq&, const ::Ice::Context*);
};

class ICE_BOX_API ServiceManager : virtual public ::IceDelegate::IceBox::ServiceManager,
                                   virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);

    virtual void startService(const ::std::string&, const ::Ice::Context*);

    virtual void stopService(const ::std::string&, const ::Ice::Context*);

    virtual void addObserver(const ::IceBox::ServiceObserverPrx&, const ::Ice::Context*);

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IceBox
{

class ICE_BOX_API Service : virtual public ::Ice::LocalObject
{
public:

    typedef ServicePtr PointerType;
    

    virtual void start(const ::std::string&, const ::Ice::CommunicatorPtr&, const ::Ice::StringSeq&) = 0;

    virtual void stop() = 0;
};

class ICE_BOX_API ServiceObserver : virtual public ::Ice::Object
{
public:

    typedef ServiceObserverPrx ProxyType;
    typedef ServiceObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void servicesStarted(const ::Ice::StringSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___servicesStarted(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void servicesStopped(const ::Ice::StringSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___servicesStopped(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_BOX_API ServiceManager : virtual public ::Ice::Object
{
public:

    typedef ServiceManagerPrx ProxyType;
    typedef ServiceManagerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getSliceChecksums(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void startService(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___startService(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void stopService(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___stopService(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void addObserver(const ::IceBox::ServiceObserverPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addObserver(::IceInternal::Incoming&, const ::Ice::Current&);

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

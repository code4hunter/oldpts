// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Observer.ice'

#ifndef __IceGrid_Observer_h__
#define __IceGrid_Observer_h__

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
#include <Glacier2/Session.h>
#include <IceGrid/Exception.h>
#include <IceGrid/Descriptor.h>
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

class NodeObserver;

class ApplicationObserver;

class AdapterObserver;

class ObjectObserver;

class RegistryObserver;

}

}

namespace IceGrid
{

class NodeObserver;
ICE_GRID_API bool operator==(const NodeObserver&, const NodeObserver&);
ICE_GRID_API bool operator<(const NodeObserver&, const NodeObserver&);

class ApplicationObserver;
ICE_GRID_API bool operator==(const ApplicationObserver&, const ApplicationObserver&);
ICE_GRID_API bool operator<(const ApplicationObserver&, const ApplicationObserver&);

class AdapterObserver;
ICE_GRID_API bool operator==(const AdapterObserver&, const AdapterObserver&);
ICE_GRID_API bool operator<(const AdapterObserver&, const AdapterObserver&);

class ObjectObserver;
ICE_GRID_API bool operator==(const ObjectObserver&, const ObjectObserver&);
ICE_GRID_API bool operator<(const ObjectObserver&, const ObjectObserver&);

class RegistryObserver;
ICE_GRID_API bool operator==(const RegistryObserver&, const RegistryObserver&);
ICE_GRID_API bool operator<(const RegistryObserver&, const RegistryObserver&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::NodeObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::NodeObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ApplicationObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ApplicationObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::AdapterObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::AdapterObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ObjectObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ObjectObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::RegistryObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::RegistryObserver*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::NodeObserver> NodeObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::NodeObserver> NodeObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, NodeObserverPrx&);
ICE_GRID_API void __patch__NodeObserverPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::ApplicationObserver> ApplicationObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::ApplicationObserver> ApplicationObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, ApplicationObserverPrx&);
ICE_GRID_API void __patch__ApplicationObserverPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::AdapterObserver> AdapterObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::AdapterObserver> AdapterObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, AdapterObserverPrx&);
ICE_GRID_API void __patch__AdapterObserverPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::ObjectObserver> ObjectObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::ObjectObserver> ObjectObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, ObjectObserverPrx&);
ICE_GRID_API void __patch__ObjectObserverPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::RegistryObserver> RegistryObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::RegistryObserver> RegistryObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, RegistryObserverPrx&);
ICE_GRID_API void __patch__RegistryObserverPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceGrid
{

struct ServerDynamicInfo
{
    ::std::string id;
    ::IceGrid::ServerState state;
    ::Ice::Int pid;
    bool enabled;

    ICE_GRID_API bool operator==(const ServerDynamicInfo&) const;
    ICE_GRID_API bool operator<(const ServerDynamicInfo&) const;
    bool operator!=(const ServerDynamicInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ServerDynamicInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ServerDynamicInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ServerDynamicInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ServerDynamicInfo> ServerDynamicInfoSeq;
ICE_GRID_API void __writeServerDynamicInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::ServerDynamicInfo*, const ::IceGrid::ServerDynamicInfo*);
ICE_GRID_API void __readServerDynamicInfoSeq(::IceInternal::BasicStream*, ServerDynamicInfoSeq&);

struct AdapterDynamicInfo
{
    ::std::string id;
    ::Ice::ObjectPrx proxy;

    ICE_GRID_API bool operator==(const AdapterDynamicInfo&) const;
    ICE_GRID_API bool operator<(const AdapterDynamicInfo&) const;
    bool operator!=(const AdapterDynamicInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const AdapterDynamicInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const AdapterDynamicInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const AdapterDynamicInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::AdapterDynamicInfo> AdapterDynamicInfoSeq;
ICE_GRID_API void __writeAdapterDynamicInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::AdapterDynamicInfo*, const ::IceGrid::AdapterDynamicInfo*);
ICE_GRID_API void __readAdapterDynamicInfoSeq(::IceInternal::BasicStream*, AdapterDynamicInfoSeq&);

struct NodeDynamicInfo
{
    ::IceGrid::NodeInfo info;
    ::IceGrid::ServerDynamicInfoSeq servers;
    ::IceGrid::AdapterDynamicInfoSeq adapters;

    ICE_GRID_API bool operator==(const NodeDynamicInfo&) const;
    ICE_GRID_API bool operator<(const NodeDynamicInfo&) const;
    bool operator!=(const NodeDynamicInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const NodeDynamicInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const NodeDynamicInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const NodeDynamicInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::NodeDynamicInfo> NodeDynamicInfoSeq;
ICE_GRID_API void __writeNodeDynamicInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::NodeDynamicInfo*, const ::IceGrid::NodeDynamicInfo*);
ICE_GRID_API void __readNodeDynamicInfoSeq(::IceInternal::BasicStream*, NodeDynamicInfoSeq&);

}

namespace IceGrid
{

class ICE_GRID_API AMI_NodeObserver_nodeInit : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::NodeObserverPrx&, const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_NodeObserver_nodeInit> AMI_NodeObserver_nodeInitPtr;

class ICE_GRID_API AMI_NodeObserver_nodeUp : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::NodeObserverPrx&, const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_NodeObserver_nodeUp> AMI_NodeObserver_nodeUpPtr;

class ICE_GRID_API AMI_NodeObserver_nodeDown : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::NodeObserverPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_NodeObserver_nodeDown> AMI_NodeObserver_nodeDownPtr;

class ICE_GRID_API AMI_NodeObserver_updateServer : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::NodeObserverPrx&, const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_NodeObserver_updateServer> AMI_NodeObserver_updateServerPtr;

class ICE_GRID_API AMI_NodeObserver_updateAdapter : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::NodeObserverPrx&, const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_NodeObserver_updateAdapter> AMI_NodeObserver_updateAdapterPtr;

class ICE_GRID_API AMI_ApplicationObserver_applicationInit : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::ApplicationObserverPrx&, ::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_ApplicationObserver_applicationInit> AMI_ApplicationObserver_applicationInitPtr;

class ICE_GRID_API AMI_AdapterObserver_adapterInit : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_AdapterObserver_adapterInit> AMI_AdapterObserver_adapterInitPtr;

class ICE_GRID_API AMI_ObjectObserver_objectInit : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::ObjectObserverPrx&, const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_ObjectObserver_objectInit> AMI_ObjectObserver_objectInitPtr;

class ICE_GRID_API AMI_RegistryObserver_registryInit : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_RegistryObserver_registryInit> AMI_RegistryObserver_registryInitPtr;

}

namespace IceAsync
{

}

namespace IceProxy
{

namespace IceGrid
{

class NodeObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void nodeInit(const ::IceGrid::NodeDynamicInfoSeq& nodes)
    {
        nodeInit(nodes, 0);
    }
    void nodeInit(const ::IceGrid::NodeDynamicInfoSeq& nodes, const ::Ice::Context& __ctx)
    {
        nodeInit(nodes, &__ctx);
    }
    
private:

    ICE_GRID_API void nodeInit(const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool nodeInit_async(const ::IceGrid::AMI_NodeObserver_nodeInitPtr&, const ::IceGrid::NodeDynamicInfoSeq&);
    ICE_GRID_API bool nodeInit_async(const ::IceGrid::AMI_NodeObserver_nodeInitPtr&, const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context&);

    void nodeUp(const ::IceGrid::NodeDynamicInfo& node)
    {
        nodeUp(node, 0);
    }
    void nodeUp(const ::IceGrid::NodeDynamicInfo& node, const ::Ice::Context& __ctx)
    {
        nodeUp(node, &__ctx);
    }
    
private:

    ICE_GRID_API void nodeUp(const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool nodeUp_async(const ::IceGrid::AMI_NodeObserver_nodeUpPtr&, const ::IceGrid::NodeDynamicInfo&);
    ICE_GRID_API bool nodeUp_async(const ::IceGrid::AMI_NodeObserver_nodeUpPtr&, const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context&);

    void nodeDown(const ::std::string& name)
    {
        nodeDown(name, 0);
    }
    void nodeDown(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        nodeDown(name, &__ctx);
    }
    
private:

    ICE_GRID_API void nodeDown(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool nodeDown_async(const ::IceGrid::AMI_NodeObserver_nodeDownPtr&, const ::std::string&);
    ICE_GRID_API bool nodeDown_async(const ::IceGrid::AMI_NodeObserver_nodeDownPtr&, const ::std::string&, const ::Ice::Context&);

    void updateServer(const ::std::string& node, const ::IceGrid::ServerDynamicInfo& updatedInfo)
    {
        updateServer(node, updatedInfo, 0);
    }
    void updateServer(const ::std::string& node, const ::IceGrid::ServerDynamicInfo& updatedInfo, const ::Ice::Context& __ctx)
    {
        updateServer(node, updatedInfo, &__ctx);
    }
    
private:

    ICE_GRID_API void updateServer(const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool updateServer_async(const ::IceGrid::AMI_NodeObserver_updateServerPtr&, const ::std::string&, const ::IceGrid::ServerDynamicInfo&);
    ICE_GRID_API bool updateServer_async(const ::IceGrid::AMI_NodeObserver_updateServerPtr&, const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context&);

    void updateAdapter(const ::std::string& node, const ::IceGrid::AdapterDynamicInfo& updatedInfo)
    {
        updateAdapter(node, updatedInfo, 0);
    }
    void updateAdapter(const ::std::string& node, const ::IceGrid::AdapterDynamicInfo& updatedInfo, const ::Ice::Context& __ctx)
    {
        updateAdapter(node, updatedInfo, &__ctx);
    }
    
private:

    ICE_GRID_API void updateAdapter(const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool updateAdapter_async(const ::IceGrid::AMI_NodeObserver_updateAdapterPtr&, const ::std::string&, const ::IceGrid::AdapterDynamicInfo&);
    ICE_GRID_API bool updateAdapter_async(const ::IceGrid::AMI_NodeObserver_updateAdapterPtr&, const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<NodeObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<NodeObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<NodeObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class ApplicationObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void applicationInit(::Ice::Int serial, const ::IceGrid::ApplicationInfoSeq& applications)
    {
        applicationInit(serial, applications, 0);
    }
    void applicationInit(::Ice::Int serial, const ::IceGrid::ApplicationInfoSeq& applications, const ::Ice::Context& __ctx)
    {
        applicationInit(serial, applications, &__ctx);
    }
    
private:

    ICE_GRID_API void applicationInit(::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool applicationInit_async(const ::IceGrid::AMI_ApplicationObserver_applicationInitPtr&, ::Ice::Int, const ::IceGrid::ApplicationInfoSeq&);
    ICE_GRID_API bool applicationInit_async(const ::IceGrid::AMI_ApplicationObserver_applicationInitPtr&, ::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context&);

    void applicationAdded(::Ice::Int serial, const ::IceGrid::ApplicationInfo& desc)
    {
        applicationAdded(serial, desc, 0);
    }
    void applicationAdded(::Ice::Int serial, const ::IceGrid::ApplicationInfo& desc, const ::Ice::Context& __ctx)
    {
        applicationAdded(serial, desc, &__ctx);
    }
    
private:

    ICE_GRID_API void applicationAdded(::Ice::Int, const ::IceGrid::ApplicationInfo&, const ::Ice::Context*);
    
public:

    void applicationRemoved(::Ice::Int serial, const ::std::string& name)
    {
        applicationRemoved(serial, name, 0);
    }
    void applicationRemoved(::Ice::Int serial, const ::std::string& name, const ::Ice::Context& __ctx)
    {
        applicationRemoved(serial, name, &__ctx);
    }
    
private:

    ICE_GRID_API void applicationRemoved(::Ice::Int, const ::std::string&, const ::Ice::Context*);
    
public:

    void applicationUpdated(::Ice::Int serial, const ::IceGrid::ApplicationUpdateInfo& desc)
    {
        applicationUpdated(serial, desc, 0);
    }
    void applicationUpdated(::Ice::Int serial, const ::IceGrid::ApplicationUpdateInfo& desc, const ::Ice::Context& __ctx)
    {
        applicationUpdated(serial, desc, &__ctx);
    }
    
private:

    ICE_GRID_API void applicationUpdated(::Ice::Int, const ::IceGrid::ApplicationUpdateInfo&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ApplicationObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ApplicationObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ApplicationObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class AdapterObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void adapterInit(const ::IceGrid::AdapterInfoSeq& adpts)
    {
        adapterInit(adpts, 0);
    }
    void adapterInit(const ::IceGrid::AdapterInfoSeq& adpts, const ::Ice::Context& __ctx)
    {
        adapterInit(adpts, &__ctx);
    }
    
private:

    ICE_GRID_API void adapterInit(const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool adapterInit_async(const ::IceGrid::AMI_AdapterObserver_adapterInitPtr&, const ::IceGrid::AdapterInfoSeq&);
    ICE_GRID_API bool adapterInit_async(const ::IceGrid::AMI_AdapterObserver_adapterInitPtr&, const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context&);

    void adapterAdded(const ::IceGrid::AdapterInfo& info)
    {
        adapterAdded(info, 0);
    }
    void adapterAdded(const ::IceGrid::AdapterInfo& info, const ::Ice::Context& __ctx)
    {
        adapterAdded(info, &__ctx);
    }
    
private:

    ICE_GRID_API void adapterAdded(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);
    
public:

    void adapterUpdated(const ::IceGrid::AdapterInfo& info)
    {
        adapterUpdated(info, 0);
    }
    void adapterUpdated(const ::IceGrid::AdapterInfo& info, const ::Ice::Context& __ctx)
    {
        adapterUpdated(info, &__ctx);
    }
    
private:

    ICE_GRID_API void adapterUpdated(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);
    
public:

    void adapterRemoved(const ::std::string& id)
    {
        adapterRemoved(id, 0);
    }
    void adapterRemoved(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        adapterRemoved(id, &__ctx);
    }
    
private:

    ICE_GRID_API void adapterRemoved(const ::std::string&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdapterObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdapterObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<AdapterObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class ObjectObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void objectInit(const ::IceGrid::ObjectInfoSeq& objects)
    {
        objectInit(objects, 0);
    }
    void objectInit(const ::IceGrid::ObjectInfoSeq& objects, const ::Ice::Context& __ctx)
    {
        objectInit(objects, &__ctx);
    }
    
private:

    ICE_GRID_API void objectInit(const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool objectInit_async(const ::IceGrid::AMI_ObjectObserver_objectInitPtr&, const ::IceGrid::ObjectInfoSeq&);
    ICE_GRID_API bool objectInit_async(const ::IceGrid::AMI_ObjectObserver_objectInitPtr&, const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context&);

    void objectAdded(const ::IceGrid::ObjectInfo& info)
    {
        objectAdded(info, 0);
    }
    void objectAdded(const ::IceGrid::ObjectInfo& info, const ::Ice::Context& __ctx)
    {
        objectAdded(info, &__ctx);
    }
    
private:

    ICE_GRID_API void objectAdded(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);
    
public:

    void objectUpdated(const ::IceGrid::ObjectInfo& info)
    {
        objectUpdated(info, 0);
    }
    void objectUpdated(const ::IceGrid::ObjectInfo& info, const ::Ice::Context& __ctx)
    {
        objectUpdated(info, &__ctx);
    }
    
private:

    ICE_GRID_API void objectUpdated(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);
    
public:

    void objectRemoved(const ::Ice::Identity& id)
    {
        objectRemoved(id, 0);
    }
    void objectRemoved(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        objectRemoved(id, &__ctx);
    }
    
private:

    ICE_GRID_API void objectRemoved(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ObjectObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ObjectObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ObjectObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class RegistryObserver : virtual public ::IceProxy::Ice::Object
{
public:

    void registryInit(const ::IceGrid::RegistryInfoSeq& registries)
    {
        registryInit(registries, 0);
    }
    void registryInit(const ::IceGrid::RegistryInfoSeq& registries, const ::Ice::Context& __ctx)
    {
        registryInit(registries, &__ctx);
    }
    
private:

    ICE_GRID_API void registryInit(const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool registryInit_async(const ::IceGrid::AMI_RegistryObserver_registryInitPtr&, const ::IceGrid::RegistryInfoSeq&);
    ICE_GRID_API bool registryInit_async(const ::IceGrid::AMI_RegistryObserver_registryInitPtr&, const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context&);

    void registryUp(const ::IceGrid::RegistryInfo& node)
    {
        registryUp(node, 0);
    }
    void registryUp(const ::IceGrid::RegistryInfo& node, const ::Ice::Context& __ctx)
    {
        registryUp(node, &__ctx);
    }
    
private:

    ICE_GRID_API void registryUp(const ::IceGrid::RegistryInfo&, const ::Ice::Context*);
    
public:

    void registryDown(const ::std::string& name)
    {
        registryDown(name, 0);
    }
    void registryDown(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        registryDown(name, &__ctx);
    }
    
private:

    ICE_GRID_API void registryDown(const ::std::string&, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RegistryObserver> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RegistryObserver*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<RegistryObserver*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_GRID_API NodeObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void nodeInit(const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context*) = 0;

    virtual void nodeUp(const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context*) = 0;

    virtual void nodeDown(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void updateServer(const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context*) = 0;

    virtual void updateAdapter(const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context*) = 0;
};

class ICE_GRID_API ApplicationObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void applicationInit(::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context*) = 0;

    virtual void applicationAdded(::Ice::Int, const ::IceGrid::ApplicationInfo&, const ::Ice::Context*) = 0;

    virtual void applicationRemoved(::Ice::Int, const ::std::string&, const ::Ice::Context*) = 0;

    virtual void applicationUpdated(::Ice::Int, const ::IceGrid::ApplicationUpdateInfo&, const ::Ice::Context*) = 0;
};

class ICE_GRID_API AdapterObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void adapterInit(const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context*) = 0;

    virtual void adapterAdded(const ::IceGrid::AdapterInfo&, const ::Ice::Context*) = 0;

    virtual void adapterUpdated(const ::IceGrid::AdapterInfo&, const ::Ice::Context*) = 0;

    virtual void adapterRemoved(const ::std::string&, const ::Ice::Context*) = 0;
};

class ICE_GRID_API ObjectObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void objectInit(const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context*) = 0;

    virtual void objectAdded(const ::IceGrid::ObjectInfo&, const ::Ice::Context*) = 0;

    virtual void objectUpdated(const ::IceGrid::ObjectInfo&, const ::Ice::Context*) = 0;

    virtual void objectRemoved(const ::Ice::Identity&, const ::Ice::Context*) = 0;
};

class ICE_GRID_API RegistryObserver : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void registryInit(const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context*) = 0;

    virtual void registryUp(const ::IceGrid::RegistryInfo&, const ::Ice::Context*) = 0;

    virtual void registryDown(const ::std::string&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API NodeObserver : virtual public ::IceDelegate::IceGrid::NodeObserver,
                                  virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void nodeInit(const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context*);

    virtual void nodeUp(const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context*);

    virtual void nodeDown(const ::std::string&, const ::Ice::Context*);

    virtual void updateServer(const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context*);

    virtual void updateAdapter(const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context*);
};

class ICE_GRID_API ApplicationObserver : virtual public ::IceDelegate::IceGrid::ApplicationObserver,
                                         virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void applicationInit(::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context*);

    virtual void applicationAdded(::Ice::Int, const ::IceGrid::ApplicationInfo&, const ::Ice::Context*);

    virtual void applicationRemoved(::Ice::Int, const ::std::string&, const ::Ice::Context*);

    virtual void applicationUpdated(::Ice::Int, const ::IceGrid::ApplicationUpdateInfo&, const ::Ice::Context*);
};

class ICE_GRID_API AdapterObserver : virtual public ::IceDelegate::IceGrid::AdapterObserver,
                                     virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void adapterInit(const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context*);

    virtual void adapterAdded(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);

    virtual void adapterUpdated(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);

    virtual void adapterRemoved(const ::std::string&, const ::Ice::Context*);
};

class ICE_GRID_API ObjectObserver : virtual public ::IceDelegate::IceGrid::ObjectObserver,
                                    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void objectInit(const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context*);

    virtual void objectAdded(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);

    virtual void objectUpdated(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);

    virtual void objectRemoved(const ::Ice::Identity&, const ::Ice::Context*);
};

class ICE_GRID_API RegistryObserver : virtual public ::IceDelegate::IceGrid::RegistryObserver,
                                      virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void registryInit(const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context*);

    virtual void registryUp(const ::IceGrid::RegistryInfo&, const ::Ice::Context*);

    virtual void registryDown(const ::std::string&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API NodeObserver : virtual public ::IceDelegate::IceGrid::NodeObserver,
                                  virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void nodeInit(const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Context*);

    virtual void nodeUp(const ::IceGrid::NodeDynamicInfo&, const ::Ice::Context*);

    virtual void nodeDown(const ::std::string&, const ::Ice::Context*);

    virtual void updateServer(const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Context*);

    virtual void updateAdapter(const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Context*);
};

class ICE_GRID_API ApplicationObserver : virtual public ::IceDelegate::IceGrid::ApplicationObserver,
                                         virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void applicationInit(::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Context*);

    virtual void applicationAdded(::Ice::Int, const ::IceGrid::ApplicationInfo&, const ::Ice::Context*);

    virtual void applicationRemoved(::Ice::Int, const ::std::string&, const ::Ice::Context*);

    virtual void applicationUpdated(::Ice::Int, const ::IceGrid::ApplicationUpdateInfo&, const ::Ice::Context*);
};

class ICE_GRID_API AdapterObserver : virtual public ::IceDelegate::IceGrid::AdapterObserver,
                                     virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void adapterInit(const ::IceGrid::AdapterInfoSeq&, const ::Ice::Context*);

    virtual void adapterAdded(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);

    virtual void adapterUpdated(const ::IceGrid::AdapterInfo&, const ::Ice::Context*);

    virtual void adapterRemoved(const ::std::string&, const ::Ice::Context*);
};

class ICE_GRID_API ObjectObserver : virtual public ::IceDelegate::IceGrid::ObjectObserver,
                                    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void objectInit(const ::IceGrid::ObjectInfoSeq&, const ::Ice::Context*);

    virtual void objectAdded(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);

    virtual void objectUpdated(const ::IceGrid::ObjectInfo&, const ::Ice::Context*);

    virtual void objectRemoved(const ::Ice::Identity&, const ::Ice::Context*);
};

class ICE_GRID_API RegistryObserver : virtual public ::IceDelegate::IceGrid::RegistryObserver,
                                      virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void registryInit(const ::IceGrid::RegistryInfoSeq&, const ::Ice::Context*);

    virtual void registryUp(const ::IceGrid::RegistryInfo&, const ::Ice::Context*);

    virtual void registryDown(const ::std::string&, const ::Ice::Context*);
};

}

}

namespace IceGrid
{

class ICE_GRID_API NodeObserver : virtual public ::Ice::Object
{
public:

    typedef NodeObserverPrx ProxyType;
    typedef NodeObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void nodeInit(const ::IceGrid::NodeDynamicInfoSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___nodeInit(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void nodeUp(const ::IceGrid::NodeDynamicInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___nodeUp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void nodeDown(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___nodeDown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateServer(const ::std::string&, const ::IceGrid::ServerDynamicInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___updateServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateAdapter(const ::std::string&, const ::IceGrid::AdapterDynamicInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___updateAdapter(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API ApplicationObserver : virtual public ::Ice::Object
{
public:

    typedef ApplicationObserverPrx ProxyType;
    typedef ApplicationObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void applicationInit(::Ice::Int, const ::IceGrid::ApplicationInfoSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___applicationInit(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void applicationAdded(::Ice::Int, const ::IceGrid::ApplicationInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___applicationAdded(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void applicationRemoved(::Ice::Int, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___applicationRemoved(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void applicationUpdated(::Ice::Int, const ::IceGrid::ApplicationUpdateInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___applicationUpdated(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API AdapterObserver : virtual public ::Ice::Object
{
public:

    typedef AdapterObserverPrx ProxyType;
    typedef AdapterObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void adapterInit(const ::IceGrid::AdapterInfoSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___adapterInit(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void adapterAdded(const ::IceGrid::AdapterInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___adapterAdded(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void adapterUpdated(const ::IceGrid::AdapterInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___adapterUpdated(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void adapterRemoved(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___adapterRemoved(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API ObjectObserver : virtual public ::Ice::Object
{
public:

    typedef ObjectObserverPrx ProxyType;
    typedef ObjectObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void objectInit(const ::IceGrid::ObjectInfoSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___objectInit(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void objectAdded(const ::IceGrid::ObjectInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___objectAdded(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void objectUpdated(const ::IceGrid::ObjectInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___objectUpdated(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void objectRemoved(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___objectRemoved(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API RegistryObserver : virtual public ::Ice::Object
{
public:

    typedef RegistryObserverPrx ProxyType;
    typedef RegistryObserverPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void registryInit(const ::IceGrid::RegistryInfoSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___registryInit(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void registryUp(const ::IceGrid::RegistryInfo&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___registryUp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void registryDown(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___registryDown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

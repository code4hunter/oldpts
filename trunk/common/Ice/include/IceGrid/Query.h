// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Query.ice'

#ifndef __IceGrid_Query_h__
#define __IceGrid_Query_h__

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
#include <Ice/Identity.h>
#include <Ice/BuiltinSequences.h>
#include <IceGrid/Exception.h>
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

class Query;

}

}

namespace IceGrid
{

class Query;
ICE_GRID_API bool operator==(const Query&, const Query&);
ICE_GRID_API bool operator<(const Query&, const Query&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::Query*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::Query*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::Query> QueryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::Query> QueryPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, QueryPrx&);
ICE_GRID_API void __patch__QueryPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceGrid
{

enum LoadSample
{
    LoadSample1,
    LoadSample5,
    LoadSample15
};

ICE_GRID_API void __write(::IceInternal::BasicStream*, LoadSample);
ICE_GRID_API void __read(::IceInternal::BasicStream*, LoadSample&);

}

namespace IceGrid
{

class ICE_GRID_API AMI_Query_findObjectById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::QueryPrx&, const ::Ice::Identity&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Query_findObjectById> AMI_Query_findObjectByIdPtr;

class ICE_GRID_API AMI_Query_findObjectByType : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::QueryPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Query_findObjectByType> AMI_Query_findObjectByTypePtr;

class ICE_GRID_API AMI_Query_findObjectByTypeOnLeastLoadedNode : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::QueryPrx&, const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Query_findObjectByTypeOnLeastLoadedNode> AMI_Query_findObjectByTypeOnLeastLoadedNodePtr;

class ICE_GRID_API AMI_Query_findAllObjectsByType : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectProxySeq&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::QueryPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Query_findAllObjectsByType> AMI_Query_findAllObjectsByTypePtr;

class ICE_GRID_API AMI_Query_findAllReplicas : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectProxySeq&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::QueryPrx&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Query_findAllReplicas> AMI_Query_findAllReplicasPtr;

}

namespace IceProxy
{

namespace IceGrid
{

class Query : virtual public ::IceProxy::Ice::Object
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

    ICE_GRID_API ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool findObjectById_async(const ::IceGrid::AMI_Query_findObjectByIdPtr&, const ::Ice::Identity&);
    ICE_GRID_API bool findObjectById_async(const ::IceGrid::AMI_Query_findObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Context&);

    ::Ice::ObjectPrx findObjectByType(const ::std::string& type)
    {
        return findObjectByType(type, 0);
    }
    ::Ice::ObjectPrx findObjectByType(const ::std::string& type, const ::Ice::Context& __ctx)
    {
        return findObjectByType(type, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx findObjectByType(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool findObjectByType_async(const ::IceGrid::AMI_Query_findObjectByTypePtr&, const ::std::string&);
    ICE_GRID_API bool findObjectByType_async(const ::IceGrid::AMI_Query_findObjectByTypePtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string& type, ::IceGrid::LoadSample sample)
    {
        return findObjectByTypeOnLeastLoadedNode(type, sample, 0);
    }
    ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string& type, ::IceGrid::LoadSample sample, const ::Ice::Context& __ctx)
    {
        return findObjectByTypeOnLeastLoadedNode(type, sample, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool findObjectByTypeOnLeastLoadedNode_async(const ::IceGrid::AMI_Query_findObjectByTypeOnLeastLoadedNodePtr&, const ::std::string&, ::IceGrid::LoadSample);
    ICE_GRID_API bool findObjectByTypeOnLeastLoadedNode_async(const ::IceGrid::AMI_Query_findObjectByTypeOnLeastLoadedNodePtr&, const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context&);

    ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string& type)
    {
        return findAllObjectsByType(type, 0);
    }
    ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string& type, const ::Ice::Context& __ctx)
    {
        return findAllObjectsByType(type, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool findAllObjectsByType_async(const ::IceGrid::AMI_Query_findAllObjectsByTypePtr&, const ::std::string&);
    ICE_GRID_API bool findAllObjectsByType_async(const ::IceGrid::AMI_Query_findAllObjectsByTypePtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx& proxy)
    {
        return findAllReplicas(proxy, 0);
    }
    ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx& proxy, const ::Ice::Context& __ctx)
    {
        return findAllReplicas(proxy, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool findAllReplicas_async(const ::IceGrid::AMI_Query_findAllReplicasPtr&, const ::Ice::ObjectPrx&);
    ICE_GRID_API bool findAllReplicas_async(const ::IceGrid::AMI_Query_findAllReplicasPtr&, const ::Ice::ObjectPrx&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<Query> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Query> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Query*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Query*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_GRID_API Query : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx findObjectByType(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API Query : virtual public ::IceDelegate::IceGrid::Query,
                           virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findObjectByType(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API Query : virtual public ::IceDelegate::IceGrid::Query,
                           virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findObjectByType(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx&, const ::Ice::Context*);
};

}

}

namespace IceGrid
{

class ICE_GRID_API Query : virtual public ::Ice::Object
{
public:

    typedef QueryPrx ProxyType;
    typedef QueryPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::ObjectPrx findObjectById(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findObjectById(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx findObjectByType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findObjectByType(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx findObjectByTypeOnLeastLoadedNode(const ::std::string&, ::IceGrid::LoadSample, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findObjectByTypeOnLeastLoadedNode(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectProxySeq findAllObjectsByType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findAllObjectsByType(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectProxySeq findAllReplicas(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___findAllReplicas(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

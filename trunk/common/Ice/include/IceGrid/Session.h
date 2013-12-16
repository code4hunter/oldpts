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

#ifndef __IceGrid_Session_h__
#define __IceGrid_Session_h__

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

class Session;

}

}

namespace IceGrid
{

class Session;
ICE_GRID_API bool operator==(const Session&, const Session&);
ICE_GRID_API bool operator<(const Session&, const Session&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::Session*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::Session*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::Session> SessionPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::Session> SessionPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, SessionPrx&);
ICE_GRID_API void __patch__SessionPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceGrid
{

class ICE_GRID_API AMI_Session_allocateObjectById : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::SessionPrx&, const ::Ice::Identity&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Session_allocateObjectById> AMI_Session_allocateObjectByIdPtr;

class ICE_GRID_API AMD_Session_allocateObjectById : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Session_allocateObjectById> AMD_Session_allocateObjectByIdPtr;

class ICE_GRID_API AMI_Session_allocateObjectByType : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::SessionPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Session_allocateObjectByType> AMI_Session_allocateObjectByTypePtr;

class ICE_GRID_API AMD_Session_allocateObjectByType : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::Ice::ObjectPrx&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Session_allocateObjectByType> AMD_Session_allocateObjectByTypePtr;

}

namespace IceAsync
{

namespace IceGrid
{

class ICE_GRID_API AMD_Session_allocateObjectById : public ::IceGrid::AMD_Session_allocateObjectById, public ::IceInternal::IncomingAsync
{
public:

    AMD_Session_allocateObjectById(::IceInternal::Incoming&);

    virtual void ice_response(const ::Ice::ObjectPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_GRID_API AMD_Session_allocateObjectByType : public ::IceGrid::AMD_Session_allocateObjectByType, public ::IceInternal::IncomingAsync
{
public:

    AMD_Session_allocateObjectByType(::IceInternal::Incoming&);

    virtual void ice_response(const ::Ice::ObjectPrx&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

namespace IceProxy
{

namespace IceGrid
{

class Session : virtual public ::IceProxy::Glacier2::Session
{
public:

    void keepAlive()
    {
        keepAlive(0);
    }
    void keepAlive(const ::Ice::Context& __ctx)
    {
        keepAlive(&__ctx);
    }
    
private:

    ICE_GRID_API void keepAlive(const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity& id)
    {
        return allocateObjectById(id, 0);
    }
    ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        return allocateObjectById(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool allocateObjectById_async(const ::IceGrid::AMI_Session_allocateObjectByIdPtr&, const ::Ice::Identity&);
    ICE_GRID_API bool allocateObjectById_async(const ::IceGrid::AMI_Session_allocateObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Context&);

    ::Ice::ObjectPrx allocateObjectByType(const ::std::string& type)
    {
        return allocateObjectByType(type, 0);
    }
    ::Ice::ObjectPrx allocateObjectByType(const ::std::string& type, const ::Ice::Context& __ctx)
    {
        return allocateObjectByType(type, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx allocateObjectByType(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool allocateObjectByType_async(const ::IceGrid::AMI_Session_allocateObjectByTypePtr&, const ::std::string&);
    ICE_GRID_API bool allocateObjectByType_async(const ::IceGrid::AMI_Session_allocateObjectByTypePtr&, const ::std::string&, const ::Ice::Context&);

    void releaseObject(const ::Ice::Identity& id)
    {
        releaseObject(id, 0);
    }
    void releaseObject(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        releaseObject(id, &__ctx);
    }
    
private:

    ICE_GRID_API void releaseObject(const ::Ice::Identity&, const ::Ice::Context*);
    
public:

    void setAllocationTimeout(::Ice::Int timeout)
    {
        setAllocationTimeout(timeout, 0);
    }
    void setAllocationTimeout(::Ice::Int timeout, const ::Ice::Context& __ctx)
    {
        setAllocationTimeout(timeout, &__ctx);
    }
    
private:

    ICE_GRID_API void setAllocationTimeout(::Ice::Int, const ::Ice::Context*);
    
public:
    
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

class ICE_GRID_API Session : virtual public ::IceDelegate::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx allocateObjectByType(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void releaseObject(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual void setAllocationTimeout(::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API Session : virtual public ::IceDelegate::IceGrid::Session,
                             virtual public ::IceDelegateM::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx allocateObjectByType(const ::std::string&, const ::Ice::Context*);

    virtual void releaseObject(const ::Ice::Identity&, const ::Ice::Context*);

    virtual void setAllocationTimeout(::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API Session : virtual public ::IceDelegate::IceGrid::Session,
                             virtual public ::IceDelegateD::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx allocateObjectById(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx allocateObjectByType(const ::std::string&, const ::Ice::Context*);

    virtual void releaseObject(const ::Ice::Identity&, const ::Ice::Context*);

    virtual void setAllocationTimeout(::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceGrid
{

class ICE_GRID_API Session : virtual public ::Glacier2::Session
{
public:

    typedef SessionPrx ProxyType;
    typedef SessionPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void keepAlive(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___keepAlive(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void allocateObjectById_async(const ::IceGrid::AMD_Session_allocateObjectByIdPtr&, const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___allocateObjectById(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void allocateObjectByType_async(const ::IceGrid::AMD_Session_allocateObjectByTypePtr&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___allocateObjectByType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void releaseObject(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___releaseObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setAllocationTimeout(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setAllocationTimeout(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

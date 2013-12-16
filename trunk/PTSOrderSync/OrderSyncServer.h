// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `OrderSyncServer.ice'

#ifndef __OrderSyncServer_h__
#define __OrderSyncServer_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
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

namespace IceProxy
{

namespace PTS2
{

class Admin;

}

}

namespace PTS2
{

class Admin;
bool operator==(const Admin&, const Admin&);
bool operator<(const Admin&, const Admin&);

}

namespace IceInternal
{

::Ice::Object* upCast(::PTS2::Admin*);
::IceProxy::Ice::Object* upCast(::IceProxy::PTS2::Admin*);

}

namespace PTS2
{

typedef ::IceInternal::Handle< ::PTS2::Admin> AdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::PTS2::Admin> AdminPrx;

void __read(::IceInternal::BasicStream*, AdminPrx&);
void __patch__AdminPtr(void*, ::Ice::ObjectPtr&);

}

namespace PTS2
{

class FailureException : public ::Ice::LocalException
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

}

namespace IceProxy
{

namespace PTS2
{

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

    void shutdown(const ::Ice::Context*);
    
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
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace PTS2
{

class Admin : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace PTS2
{

class Admin : virtual public ::IceDelegate::PTS2::Admin,
              virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace PTS2
{

class Admin : virtual public ::IceDelegate::PTS2::Admin,
              virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace PTS2
{

class Admin : virtual public ::Ice::Object
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

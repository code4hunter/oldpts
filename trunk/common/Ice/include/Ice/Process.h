// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Process.ice'

#ifndef __Ice_Process_h__
#define __Ice_Process_h__

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

class Process;

}

}

namespace Ice
{

class Process;
ICE_API bool operator==(const Process&, const Process&);
ICE_API bool operator<(const Process&, const Process&);

}

namespace IceInternal
{

ICE_API ::Ice::Object* upCast(::Ice::Process*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::Process*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Process> ProcessPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::Process> ProcessPrx;

ICE_API void __read(::IceInternal::BasicStream*, ProcessPrx&);
ICE_API void __patch__ProcessPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

class ICE_API AMI_Process_shutdown : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::ProcessPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Process_shutdown> AMI_Process_shutdownPtr;

class ICE_API AMI_Process_writeMessage : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::ProcessPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_Process_writeMessage> AMI_Process_writeMessagePtr;

}

namespace IceProxy
{

namespace Ice
{

class Process : virtual public ::IceProxy::Ice::Object
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

    ICE_API void shutdown(const ::Ice::Context*);
    
public:
    ICE_API bool shutdown_async(const ::Ice::AMI_Process_shutdownPtr&);
    ICE_API bool shutdown_async(const ::Ice::AMI_Process_shutdownPtr&, const ::Ice::Context&);

    void writeMessage(const ::std::string& message, ::Ice::Int fd)
    {
        writeMessage(message, fd, 0);
    }
    void writeMessage(const ::std::string& message, ::Ice::Int fd, const ::Ice::Context& __ctx)
    {
        writeMessage(message, fd, &__ctx);
    }
    
private:

    ICE_API void writeMessage(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:
    ICE_API bool writeMessage_async(const ::Ice::AMI_Process_writeMessagePtr&, const ::std::string&, ::Ice::Int);
    ICE_API bool writeMessage_async(const ::Ice::AMI_Process_writeMessagePtr&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<Process> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Process> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Process*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Process*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_API Process : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*) = 0;

    virtual void writeMessage(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Ice
{

class ICE_API Process : virtual public ::IceDelegate::Ice::Process,
                        virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);

    virtual void writeMessage(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Ice
{

class ICE_API Process : virtual public ::IceDelegate::Ice::Process,
                        virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);

    virtual void writeMessage(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace Ice
{

class ICE_API Process : virtual public ::Ice::Object
{
public:

    typedef ProcessPrx ProxyType;
    typedef ProcessPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void shutdown(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___shutdown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void writeMessage(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___writeMessage(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

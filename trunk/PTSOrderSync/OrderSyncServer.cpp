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

#include <OrderSyncServer.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/ScopedArray.h>

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

static const ::std::string __PTS2__Admin__shutdown_name = "shutdown";

::Ice::Object* IceInternal::upCast(::PTS2::Admin* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::PTS2::Admin* p) { return p; }

void
PTS2::__read(::IceInternal::BasicStream* __is, ::PTS2::AdminPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::PTS2::Admin;
        v->__copyFrom(proxy);
    }
}

PTS2::FailureException::FailureException(const char* __file, int __line) :
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    LocalException(__file, __line)
#else
    ::Ice::LocalException(__file, __line)
#endif
{
}

PTS2::FailureException::FailureException(const char* __file, int __line, const ::std::string& __ice_reason) :
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    LocalException(__file, __line),
#else
    ::Ice::LocalException(__file, __line),
#endif
    reason(__ice_reason)
{
}

PTS2::FailureException::~FailureException() throw()
{
}

static const char* __PTS2__FailureException_name = "PTS2::FailureException";

::std::string
PTS2::FailureException::ice_name() const
{
    return __PTS2__FailureException_name;
}

::Ice::Exception*
PTS2::FailureException::ice_clone() const
{
    return new FailureException(*this);
}

void
PTS2::FailureException::ice_throw() const
{
    throw *this;
}

void
IceProxy::PTS2::Admin::shutdown(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __delBase = __getDelegate(false);
            ::IceDelegate::PTS2::Admin* __del = dynamic_cast< ::IceDelegate::PTS2::Admin*>(__delBase.get());
            __del->shutdown(__ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

const ::std::string&
IceProxy::PTS2::Admin::ice_staticId()
{
    return ::PTS2::Admin::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::PTS2::Admin::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::PTS2::Admin);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::PTS2::Admin::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::PTS2::Admin);
}

::IceProxy::Ice::Object*
IceProxy::PTS2::Admin::__newInstance() const
{
    return new Admin;
}

void
IceDelegateM::PTS2::Admin::shutdown(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __PTS2__Admin__shutdown_name, ::Ice::Normal, __context);
    bool __ok = __og.invoke();
    if(!__og.is()->b.empty())
    {
        try
        {
            if(!__ok)
            {
                try
                {
                    __og.throwUserException();
                }
                catch(const ::Ice::UserException& __ex)
                {
                    ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                    throw __uue;
                }
            }
            __og.is()->skipEmptyEncaps();
        }
        catch(const ::Ice::LocalException& __ex)
        {
            throw ::IceInternal::LocalExceptionWrapper(__ex, false);
        }
    }
}

void
IceDelegateD::PTS2::Admin::shutdown(const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::PTS2::Admin* servant = dynamic_cast< ::PTS2::Admin*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            servant->shutdown(_current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __PTS2__Admin__shutdown_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(__current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
}

::Ice::ObjectPtr
PTS2::Admin::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __PTS2__Admin_ids[2] =
{
    "::Ice::Object",
    "::PTS2::Admin"
};

bool
PTS2::Admin::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__PTS2__Admin_ids, __PTS2__Admin_ids + 2, _s);
}

::std::vector< ::std::string>
PTS2::Admin::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__PTS2__Admin_ids[0], &__PTS2__Admin_ids[2]);
}

const ::std::string&
PTS2::Admin::ice_id(const ::Ice::Current&) const
{
    return __PTS2__Admin_ids[1];
}

const ::std::string&
PTS2::Admin::ice_staticId()
{
    return __PTS2__Admin_ids[1];
}

::Ice::DispatchStatus
PTS2::Admin::___shutdown(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.is()->skipEmptyEncaps();
    shutdown(__current);
    return ::Ice::DispatchOK;
}

static ::std::string __PTS2__Admin_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "shutdown"
};

::Ice::DispatchStatus
PTS2::Admin::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__PTS2__Admin_all, __PTS2__Admin_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __PTS2__Admin_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___shutdown(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
PTS2::Admin::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
PTS2::Admin::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
PTS2::Admin::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type PTS2::Admin was not generated with stream support";
    throw ex;
}

void
PTS2::Admin::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type PTS2::Admin was not generated with stream support";
    throw ex;
}

void 
PTS2::__patch__AdminPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::PTS2::AdminPtr* p = static_cast< ::PTS2::AdminPtr*>(__addr);
    assert(p);
    *p = ::PTS2::AdminPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::PTS2::Admin::ice_staticId(), v->ice_id());
    }
}

bool
PTS2::operator==(const ::PTS2::Admin& l, const ::PTS2::Admin& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
PTS2::operator<(const ::PTS2::Admin& l, const ::PTS2::Admin& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Properties.ice'

#ifndef __Ice_Properties_h__
#define __Ice_Properties_h__

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

class PropertiesAdmin;

}

}

namespace Ice
{

class Properties;
ICE_API bool operator==(const Properties&, const Properties&);
ICE_API bool operator<(const Properties&, const Properties&);

class PropertiesAdmin;
ICE_API bool operator==(const PropertiesAdmin&, const PropertiesAdmin&);
ICE_API bool operator<(const PropertiesAdmin&, const PropertiesAdmin&);

}

namespace IceInternal
{

ICE_API ::Ice::LocalObject* upCast(::Ice::Properties*);

ICE_API ::Ice::Object* upCast(::Ice::PropertiesAdmin*);
ICE_API ::IceProxy::Ice::Object* upCast(::IceProxy::Ice::PropertiesAdmin*);

}

namespace Ice
{

typedef ::IceInternal::Handle< ::Ice::Properties> PropertiesPtr;

typedef ::IceInternal::Handle< ::Ice::PropertiesAdmin> PropertiesAdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Ice::PropertiesAdmin> PropertiesAdminPrx;

ICE_API void __read(::IceInternal::BasicStream*, PropertiesAdminPrx&);
ICE_API void __patch__PropertiesAdminPtr(void*, ::Ice::ObjectPtr&);

}

namespace Ice
{

typedef ::std::map< ::std::string, ::std::string> PropertyDict;
ICE_API void __writePropertyDict(::IceInternal::BasicStream*, const PropertyDict&);
ICE_API void __readPropertyDict(::IceInternal::BasicStream*, PropertyDict&);

}

namespace Ice
{

class ICE_API AMI_PropertiesAdmin_getProperty : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::std::string&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::PropertiesAdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_PropertiesAdmin_getProperty> AMI_PropertiesAdmin_getPropertyPtr;

class ICE_API AMI_PropertiesAdmin_getPropertiesForPrefix : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::Ice::PropertyDict&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::Ice::PropertiesAdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::Ice::AMI_PropertiesAdmin_getPropertiesForPrefix> AMI_PropertiesAdmin_getPropertiesForPrefixPtr;

}

namespace IceProxy
{

namespace Ice
{

class PropertiesAdmin : virtual public ::IceProxy::Ice::Object
{
public:

    ::std::string getProperty(const ::std::string& key)
    {
        return getProperty(key, 0);
    }
    ::std::string getProperty(const ::std::string& key, const ::Ice::Context& __ctx)
    {
        return getProperty(key, &__ctx);
    }
    
private:

    ICE_API ::std::string getProperty(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_API bool getProperty_async(const ::Ice::AMI_PropertiesAdmin_getPropertyPtr&, const ::std::string&);
    ICE_API bool getProperty_async(const ::Ice::AMI_PropertiesAdmin_getPropertyPtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string& prefix)
    {
        return getPropertiesForPrefix(prefix, 0);
    }
    ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string& prefix, const ::Ice::Context& __ctx)
    {
        return getPropertiesForPrefix(prefix, &__ctx);
    }
    
private:

    ICE_API ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_API bool getPropertiesForPrefix_async(const ::Ice::AMI_PropertiesAdmin_getPropertiesForPrefixPtr&, const ::std::string&);
    ICE_API bool getPropertiesForPrefix_async(const ::Ice::AMI_PropertiesAdmin_getPropertiesForPrefixPtr&, const ::std::string&, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<PropertiesAdmin> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<PropertiesAdmin*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<PropertiesAdmin*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_API PropertiesAdmin : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::std::string getProperty(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace Ice
{

class ICE_API PropertiesAdmin : virtual public ::IceDelegate::Ice::PropertiesAdmin,
                                virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::std::string getProperty(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace Ice
{

class ICE_API PropertiesAdmin : virtual public ::IceDelegate::Ice::PropertiesAdmin,
                                virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::std::string getProperty(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Context*);
};

}

}

namespace Ice
{

class ICE_API Properties : virtual public ::Ice::LocalObject
{
public:

    typedef PropertiesPtr PointerType;
    

    virtual ::std::string getProperty(const ::std::string&) = 0;

    virtual ::std::string getPropertyWithDefault(const ::std::string&, const ::std::string&) = 0;

    virtual ::Ice::Int getPropertyAsInt(const ::std::string&) = 0;

    virtual ::Ice::Int getPropertyAsIntWithDefault(const ::std::string&, ::Ice::Int) = 0;

    virtual ::Ice::StringSeq getPropertyAsList(const ::std::string&) = 0;

    virtual ::Ice::StringSeq getPropertyAsListWithDefault(const ::std::string&, const ::Ice::StringSeq&) = 0;

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&) = 0;

    virtual void setProperty(const ::std::string&, const ::std::string&) = 0;

    virtual ::Ice::StringSeq getCommandLineOptions() = 0;

    virtual ::Ice::StringSeq parseCommandLineOptions(const ::std::string&, const ::Ice::StringSeq&) = 0;

    virtual ::Ice::StringSeq parseIceCommandLineOptions(const ::Ice::StringSeq&) = 0;

    virtual void load(const ::std::string&) = 0;

    virtual ::Ice::PropertiesPtr clone() = 0;
};

class ICE_API PropertiesAdmin : virtual public ::Ice::Object
{
public:

    typedef PropertiesAdminPrx ProxyType;
    typedef PropertiesAdminPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::std::string getProperty(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::PropertyDict getPropertiesForPrefix(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getPropertiesForPrefix(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

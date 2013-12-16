// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `IceStorm.ice'

#ifndef __IceStorm_IceStorm_h__
#define __IceStorm_IceStorm_h__

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
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <Ice/SliceChecksumDict.h>
#include <Ice/Identity.h>
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

#ifndef ICE_STORM_LIB_API
#   ifdef ICE_STORM_LIB_API_EXPORTS
#       define ICE_STORM_LIB_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_STORM_LIB_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace IceStorm
{

class Topic;

class TopicManager;

}

}

namespace IceStorm
{

class Topic;
ICE_STORM_LIB_API bool operator==(const Topic&, const Topic&);
ICE_STORM_LIB_API bool operator<(const Topic&, const Topic&);

class TopicManager;
ICE_STORM_LIB_API bool operator==(const TopicManager&, const TopicManager&);
ICE_STORM_LIB_API bool operator<(const TopicManager&, const TopicManager&);

}

namespace IceInternal
{

ICE_STORM_LIB_API ::Ice::Object* upCast(::IceStorm::Topic*);
ICE_STORM_LIB_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceStorm::Topic*);

ICE_STORM_LIB_API ::Ice::Object* upCast(::IceStorm::TopicManager*);
ICE_STORM_LIB_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceStorm::TopicManager*);

}

namespace IceStorm
{

typedef ::IceInternal::Handle< ::IceStorm::Topic> TopicPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceStorm::Topic> TopicPrx;

ICE_STORM_LIB_API void __read(::IceInternal::BasicStream*, TopicPrx&);
ICE_STORM_LIB_API void __patch__TopicPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceStorm::TopicManager> TopicManagerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceStorm::TopicManager> TopicManagerPrx;

ICE_STORM_LIB_API void __read(::IceInternal::BasicStream*, TopicManagerPrx&);
ICE_STORM_LIB_API void __patch__TopicManagerPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceStorm
{

struct LinkInfo
{
    ::IceStorm::TopicPrx theTopic;
    ::std::string name;
    ::Ice::Int cost;

    ICE_STORM_LIB_API bool operator==(const LinkInfo&) const;
    ICE_STORM_LIB_API bool operator<(const LinkInfo&) const;
    bool operator!=(const LinkInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const LinkInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const LinkInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const LinkInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_STORM_LIB_API void __write(::IceInternal::BasicStream*) const;
    ICE_STORM_LIB_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceStorm::LinkInfo> LinkInfoSeq;
ICE_STORM_LIB_API void __writeLinkInfoSeq(::IceInternal::BasicStream*, const ::IceStorm::LinkInfo*, const ::IceStorm::LinkInfo*);
ICE_STORM_LIB_API void __readLinkInfoSeq(::IceInternal::BasicStream*, LinkInfoSeq&);

typedef ::std::map< ::std::string, ::std::string> QoS;
ICE_STORM_LIB_API void __writeQoS(::IceInternal::BasicStream*, const QoS&);
ICE_STORM_LIB_API void __readQoS(::IceInternal::BasicStream*, QoS&);

class ICE_STORM_LIB_API LinkExists : public ::Ice::UserException
{
public:

    LinkExists() {}
    explicit LinkExists(const ::std::string&);
    virtual ~LinkExists() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string name;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static LinkExists __LinkExists_init;

class ICE_STORM_LIB_API NoSuchLink : public ::Ice::UserException
{
public:

    NoSuchLink() {}
    explicit NoSuchLink(const ::std::string&);
    virtual ~NoSuchLink() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string name;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_STORM_LIB_API AlreadySubscribed : public ::Ice::UserException
{
public:

    AlreadySubscribed() {}
    virtual ~AlreadySubscribed() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_STORM_LIB_API BadQoS : public ::Ice::UserException
{
public:

    BadQoS() {}
    explicit BadQoS(const ::std::string&);
    virtual ~BadQoS() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string reason;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

typedef ::std::map< ::std::string, ::IceStorm::TopicPrx> TopicDict;
ICE_STORM_LIB_API void __writeTopicDict(::IceInternal::BasicStream*, const TopicDict&);
ICE_STORM_LIB_API void __readTopicDict(::IceInternal::BasicStream*, TopicDict&);

class ICE_STORM_LIB_API TopicExists : public ::Ice::UserException
{
public:

    TopicExists() {}
    explicit TopicExists(const ::std::string&);
    virtual ~TopicExists() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string name;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_STORM_LIB_API NoSuchTopic : public ::Ice::UserException
{
public:

    NoSuchTopic() {}
    explicit NoSuchTopic(const ::std::string&);
    virtual ~NoSuchTopic() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    ::std::string name;

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

namespace IceProxy
{

namespace IceStorm
{

class Topic : virtual public ::IceProxy::Ice::Object
{
public:

    ::std::string getName()
    {
        return getName(0);
    }
    ::std::string getName(const ::Ice::Context& __ctx)
    {
        return getName(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::std::string getName(const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx getPublisher()
    {
        return getPublisher(0);
    }
    ::Ice::ObjectPrx getPublisher(const ::Ice::Context& __ctx)
    {
        return getPublisher(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::Ice::ObjectPrx getPublisher(const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx getNonReplicatedPublisher()
    {
        return getNonReplicatedPublisher(0);
    }
    ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Context& __ctx)
    {
        return getNonReplicatedPublisher(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Context*);
    
public:

    ICE_DEPRECATED_API void subscribe(const ::IceStorm::QoS& theQoS, const ::Ice::ObjectPrx& subscriber)
    {
        subscribe(theQoS, subscriber, 0);
    }
    ICE_DEPRECATED_API void subscribe(const ::IceStorm::QoS& theQoS, const ::Ice::ObjectPrx& subscriber, const ::Ice::Context& __ctx)
    {
        subscribe(theQoS, subscriber, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API void subscribe(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS& theQoS, const ::Ice::ObjectPrx& subscriber)
    {
        return subscribeAndGetPublisher(theQoS, subscriber, 0);
    }
    ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS& theQoS, const ::Ice::ObjectPrx& subscriber, const ::Ice::Context& __ctx)
    {
        return subscribeAndGetPublisher(theQoS, subscriber, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    void unsubscribe(const ::Ice::ObjectPrx& subscriber)
    {
        unsubscribe(subscriber, 0);
    }
    void unsubscribe(const ::Ice::ObjectPrx& subscriber, const ::Ice::Context& __ctx)
    {
        unsubscribe(subscriber, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API void unsubscribe(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    void link(const ::IceStorm::TopicPrx& linkTo, ::Ice::Int cost)
    {
        link(linkTo, cost, 0);
    }
    void link(const ::IceStorm::TopicPrx& linkTo, ::Ice::Int cost, const ::Ice::Context& __ctx)
    {
        link(linkTo, cost, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API void link(const ::IceStorm::TopicPrx&, ::Ice::Int, const ::Ice::Context*);
    
public:

    void unlink(const ::IceStorm::TopicPrx& linkTo)
    {
        unlink(linkTo, 0);
    }
    void unlink(const ::IceStorm::TopicPrx& linkTo, const ::Ice::Context& __ctx)
    {
        unlink(linkTo, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API void unlink(const ::IceStorm::TopicPrx&, const ::Ice::Context*);
    
public:

    ::IceStorm::LinkInfoSeq getLinkInfoSeq()
    {
        return getLinkInfoSeq(0);
    }
    ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Context& __ctx)
    {
        return getLinkInfoSeq(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Context*);
    
public:

    void destroy()
    {
        destroy(0);
    }
    void destroy(const ::Ice::Context& __ctx)
    {
        destroy(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API void destroy(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Topic> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Topic> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Topic*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Topic*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_STORM_LIB_API static const ::std::string& ice_staticId();

private: 

    ICE_STORM_LIB_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_STORM_LIB_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_STORM_LIB_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class TopicManager : virtual public ::IceProxy::Ice::Object
{
public:

    ::IceStorm::TopicPrx create(const ::std::string& name)
    {
        return create(name, 0);
    }
    ::IceStorm::TopicPrx create(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return create(name, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::IceStorm::TopicPrx create(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceStorm::TopicPrx retrieve(const ::std::string& name)
    {
        return retrieve(name, 0);
    }
    ::IceStorm::TopicPrx retrieve(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return retrieve(name, &__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::IceStorm::TopicPrx retrieve(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceStorm::TopicDict retrieveAll()
    {
        return retrieveAll(0);
    }
    ::IceStorm::TopicDict retrieveAll(const ::Ice::Context& __ctx)
    {
        return retrieveAll(&__ctx);
    }
    
private:

    ICE_STORM_LIB_API ::IceStorm::TopicDict retrieveAll(const ::Ice::Context*);
    
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

    ICE_STORM_LIB_API ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<TopicManager> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<TopicManager> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<TopicManager*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<TopicManager*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_STORM_LIB_API static const ::std::string& ice_staticId();

private: 

    ICE_STORM_LIB_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_STORM_LIB_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_STORM_LIB_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace IceStorm
{

class ICE_STORM_LIB_API Topic : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::std::string getName(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx getPublisher(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Context*) = 0;

    virtual void subscribe(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void unsubscribe(const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void link(const ::IceStorm::TopicPrx&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual void unlink(const ::IceStorm::TopicPrx&, const ::Ice::Context*) = 0;

    virtual ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Context*) = 0;

    virtual void destroy(const ::Ice::Context*) = 0;
};

class ICE_STORM_LIB_API TopicManager : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::IceStorm::TopicPrx create(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceStorm::TopicPrx retrieve(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceStorm::TopicDict retrieveAll(const ::Ice::Context*) = 0;

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceStorm
{

class ICE_STORM_LIB_API Topic : virtual public ::IceDelegate::IceStorm::Topic,
                                virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::std::string getName(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getPublisher(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Context*);

    virtual void subscribe(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void unsubscribe(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void link(const ::IceStorm::TopicPrx&, ::Ice::Int, const ::Ice::Context*);

    virtual void unlink(const ::IceStorm::TopicPrx&, const ::Ice::Context*);

    virtual ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class ICE_STORM_LIB_API TopicManager : virtual public ::IceDelegate::IceStorm::TopicManager,
                                       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::IceStorm::TopicPrx create(const ::std::string&, const ::Ice::Context*);

    virtual ::IceStorm::TopicPrx retrieve(const ::std::string&, const ::Ice::Context*);

    virtual ::IceStorm::TopicDict retrieveAll(const ::Ice::Context*);

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceStorm
{

class ICE_STORM_LIB_API Topic : virtual public ::IceDelegate::IceStorm::Topic,
                                virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::std::string getName(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getPublisher(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Context*);

    virtual void subscribe(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void unsubscribe(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void link(const ::IceStorm::TopicPrx&, ::Ice::Int, const ::Ice::Context*);

    virtual void unlink(const ::IceStorm::TopicPrx&, const ::Ice::Context*);

    virtual ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class ICE_STORM_LIB_API TopicManager : virtual public ::IceDelegate::IceStorm::TopicManager,
                                       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::IceStorm::TopicPrx create(const ::std::string&, const ::Ice::Context*);

    virtual ::IceStorm::TopicPrx retrieve(const ::std::string&, const ::Ice::Context*);

    virtual ::IceStorm::TopicDict retrieveAll(const ::Ice::Context*);

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
};

}

}

namespace IceStorm
{

class ICE_STORM_LIB_API Topic : virtual public ::Ice::Object
{
public:

    typedef TopicPrx ProxyType;
    typedef TopicPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::std::string getName(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getName(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx getPublisher(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getPublisher(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx getNonReplicatedPublisher(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getNonReplicatedPublisher(::IceInternal::Incoming&, const ::Ice::Current&) const;

    ICE_DEPRECATED_API virtual void subscribe(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___subscribe(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::ObjectPrx subscribeAndGetPublisher(const ::IceStorm::QoS&, const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___subscribeAndGetPublisher(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void unsubscribe(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___unsubscribe(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void link(const ::IceStorm::TopicPrx&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___link(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void unlink(const ::IceStorm::TopicPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___unlink(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceStorm::LinkInfoSeq getLinkInfoSeq(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getLinkInfoSeq(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_STORM_LIB_API TopicManager : virtual public ::Ice::Object
{
public:

    typedef TopicManagerPrx ProxyType;
    typedef TopicManagerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::IceStorm::TopicPrx create(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___create(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceStorm::TopicPrx retrieve(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___retrieve(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceStorm::TopicDict retrieveAll(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___retrieveAll(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getSliceChecksums(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

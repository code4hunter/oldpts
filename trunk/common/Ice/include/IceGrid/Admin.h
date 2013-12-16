// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Admin.ice'

#ifndef __IceGrid_Admin_h__
#define __IceGrid_Admin_h__

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
#include <Ice/BuiltinSequences.h>
#include <Ice/Properties.h>
#include <Ice/SliceChecksumDict.h>
#include <Glacier2/Session.h>
#include <IceGrid/Exception.h>
#include <IceGrid/Descriptor.h>
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

class Admin;

class FileIterator;

class RegistryObserver;

class NodeObserver;

class ApplicationObserver;

class AdapterObserver;

class ObjectObserver;

class AdminSession;

}

}

namespace IceGrid
{

class Admin;
ICE_GRID_API bool operator==(const Admin&, const Admin&);
ICE_GRID_API bool operator<(const Admin&, const Admin&);

class FileIterator;
ICE_GRID_API bool operator==(const FileIterator&, const FileIterator&);
ICE_GRID_API bool operator<(const FileIterator&, const FileIterator&);

class RegistryObserver;
ICE_GRID_API bool operator==(const RegistryObserver&, const RegistryObserver&);
ICE_GRID_API bool operator<(const RegistryObserver&, const RegistryObserver&);

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

class AdminSession;
ICE_GRID_API bool operator==(const AdminSession&, const AdminSession&);
ICE_GRID_API bool operator<(const AdminSession&, const AdminSession&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::Admin*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::Admin*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::FileIterator*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::FileIterator*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::RegistryObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::RegistryObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::NodeObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::NodeObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ApplicationObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ApplicationObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::AdapterObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::AdapterObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ObjectObserver*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ObjectObserver*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::AdminSession*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::AdminSession*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::Admin> AdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::Admin> AdminPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, AdminPrx&);
ICE_GRID_API void __patch__AdminPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::FileIterator> FileIteratorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::FileIterator> FileIteratorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, FileIteratorPrx&);
ICE_GRID_API void __patch__FileIteratorPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::RegistryObserver> RegistryObserverPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::RegistryObserver> RegistryObserverPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, RegistryObserverPrx&);
ICE_GRID_API void __patch__RegistryObserverPtr(void*, ::Ice::ObjectPtr&);

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

typedef ::IceInternal::Handle< ::IceGrid::AdminSession> AdminSessionPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::AdminSession> AdminSessionPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, AdminSessionPrx&);
ICE_GRID_API void __patch__AdminSessionPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceGrid
{

enum ServerState
{
    Inactive,
    Activating,
    ActivationTimedOut,
    Active,
    Deactivating,
    Destroying,
    Destroyed
};

ICE_GRID_API void __write(::IceInternal::BasicStream*, ServerState);
ICE_GRID_API void __read(::IceInternal::BasicStream*, ServerState&);

typedef ::std::map< ::std::string, ::Ice::ObjectPrx> StringObjectProxyDict;
ICE_GRID_API void __writeStringObjectProxyDict(::IceInternal::BasicStream*, const StringObjectProxyDict&);
ICE_GRID_API void __readStringObjectProxyDict(::IceInternal::BasicStream*, StringObjectProxyDict&);

struct ObjectInfo
{
    ::Ice::ObjectPrx proxy;
    ::std::string type;

    ICE_GRID_API bool operator==(const ObjectInfo&) const;
    ICE_GRID_API bool operator<(const ObjectInfo&) const;
    bool operator!=(const ObjectInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ObjectInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ObjectInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ObjectInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ObjectInfo> ObjectInfoSeq;
ICE_GRID_API void __writeObjectInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::ObjectInfo*, const ::IceGrid::ObjectInfo*);
ICE_GRID_API void __readObjectInfoSeq(::IceInternal::BasicStream*, ObjectInfoSeq&);

struct AdapterInfo
{
    ::std::string id;
    ::Ice::ObjectPrx proxy;
    ::std::string replicaGroupId;

    ICE_GRID_API bool operator==(const AdapterInfo&) const;
    ICE_GRID_API bool operator<(const AdapterInfo&) const;
    bool operator!=(const AdapterInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const AdapterInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const AdapterInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const AdapterInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::AdapterInfo> AdapterInfoSeq;
ICE_GRID_API void __writeAdapterInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::AdapterInfo*, const ::IceGrid::AdapterInfo*);
ICE_GRID_API void __readAdapterInfoSeq(::IceInternal::BasicStream*, AdapterInfoSeq&);

struct ServerInfo
{
    ::std::string application;
    ::std::string uuid;
    ::Ice::Int revision;
    ::std::string node;
    ::IceGrid::ServerDescriptorPtr descriptor;
    ::std::string sessionId;

    ICE_GRID_API bool operator==(const ServerInfo&) const;
    ICE_GRID_API bool operator<(const ServerInfo&) const;
    bool operator!=(const ServerInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ServerInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ServerInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ServerInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

struct NodeInfo
{
    ::std::string name;
    ::std::string os;
    ::std::string hostname;
    ::std::string release;
    ::std::string version;
    ::std::string machine;
    ::Ice::Int nProcessors;
    ::std::string dataDir;

    ICE_GRID_API bool operator==(const NodeInfo&) const;
    ICE_GRID_API bool operator<(const NodeInfo&) const;
    bool operator!=(const NodeInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const NodeInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const NodeInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const NodeInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

struct RegistryInfo
{
    ::std::string name;
    ::std::string hostname;

    ICE_GRID_API bool operator==(const RegistryInfo&) const;
    ICE_GRID_API bool operator<(const RegistryInfo&) const;
    bool operator!=(const RegistryInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const RegistryInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const RegistryInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const RegistryInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::RegistryInfo> RegistryInfoSeq;
ICE_GRID_API void __writeRegistryInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::RegistryInfo*, const ::IceGrid::RegistryInfo*);
ICE_GRID_API void __readRegistryInfoSeq(::IceInternal::BasicStream*, RegistryInfoSeq&);

struct LoadInfo
{
    ::Ice::Float avg1;
    ::Ice::Float avg5;
    ::Ice::Float avg15;

    ICE_GRID_API bool operator==(const LoadInfo&) const;
    ICE_GRID_API bool operator<(const LoadInfo&) const;
    bool operator!=(const LoadInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const LoadInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const LoadInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const LoadInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

struct ApplicationInfo
{
    ::std::string uuid;
    ::Ice::Long createTime;
    ::std::string createUser;
    ::Ice::Long updateTime;
    ::std::string updateUser;
    ::Ice::Int revision;
    ::IceGrid::ApplicationDescriptor descriptor;

    ICE_GRID_API bool operator==(const ApplicationInfo&) const;
    ICE_GRID_API bool operator<(const ApplicationInfo&) const;
    bool operator!=(const ApplicationInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ApplicationInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ApplicationInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ApplicationInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ApplicationInfo> ApplicationInfoSeq;
ICE_GRID_API void __writeApplicationInfoSeq(::IceInternal::BasicStream*, const ::IceGrid::ApplicationInfo*, const ::IceGrid::ApplicationInfo*);
ICE_GRID_API void __readApplicationInfoSeq(::IceInternal::BasicStream*, ApplicationInfoSeq&);

struct ApplicationUpdateInfo
{
    ::Ice::Long updateTime;
    ::std::string updateUser;
    ::Ice::Int revision;
    ::IceGrid::ApplicationUpdateDescriptor descriptor;

    ICE_GRID_API bool operator==(const ApplicationUpdateInfo&) const;
    ICE_GRID_API bool operator<(const ApplicationUpdateInfo&) const;
    bool operator!=(const ApplicationUpdateInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ApplicationUpdateInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ApplicationUpdateInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ApplicationUpdateInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

}

namespace IceGrid
{

class ICE_GRID_API AMI_Admin_addApplication : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_addApplication> AMI_Admin_addApplicationPtr;

class ICE_GRID_API AMI_Admin_syncApplication : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_syncApplication> AMI_Admin_syncApplicationPtr;

class ICE_GRID_API AMI_Admin_updateApplication : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_updateApplication> AMI_Admin_updateApplicationPtr;

class ICE_GRID_API AMI_Admin_removeApplication : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_removeApplication> AMI_Admin_removeApplicationPtr;

class ICE_GRID_API AMI_Admin_patchApplication : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, bool, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_patchApplication> AMI_Admin_patchApplicationPtr;

class ICE_GRID_API AMD_Admin_patchApplication : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Admin_patchApplication> AMD_Admin_patchApplicationPtr;

class ICE_GRID_API AMI_Admin_enableServer : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, bool, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_enableServer> AMI_Admin_enableServerPtr;

class ICE_GRID_API AMI_Admin_startServer : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_startServer> AMI_Admin_startServerPtr;

class ICE_GRID_API AMD_Admin_startServer : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Admin_startServer> AMD_Admin_startServerPtr;

class ICE_GRID_API AMI_Admin_stopServer : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_stopServer> AMI_Admin_stopServerPtr;

class ICE_GRID_API AMD_Admin_stopServer : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Admin_stopServer> AMD_Admin_stopServerPtr;

class ICE_GRID_API AMI_Admin_patchServer : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, bool, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_patchServer> AMI_Admin_patchServerPtr;

class ICE_GRID_API AMD_Admin_patchServer : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IceGrid::AMD_Admin_patchServer> AMD_Admin_patchServerPtr;

class ICE_GRID_API AMI_Admin_sendSignal : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_sendSignal> AMI_Admin_sendSignalPtr;

class ICE_GRID_API AMI_Admin_writeMessage : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_writeMessage> AMI_Admin_writeMessagePtr;

class ICE_GRID_API AMI_Admin_removeAdapter : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_removeAdapter> AMI_Admin_removeAdapterPtr;

class ICE_GRID_API AMI_Admin_addObject : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::Ice::ObjectPrx&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_addObject> AMI_Admin_addObjectPtr;

class ICE_GRID_API AMI_Admin_addObjectWithType : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_addObjectWithType> AMI_Admin_addObjectWithTypePtr;

class ICE_GRID_API AMI_Admin_removeObject : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::Ice::Identity&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_removeObject> AMI_Admin_removeObjectPtr;

class ICE_GRID_API AMI_Admin_getNodeLoad : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::IceGrid::LoadInfo&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_getNodeLoad> AMI_Admin_getNodeLoadPtr;

class ICE_GRID_API AMI_Admin_shutdownNode : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_shutdownNode> AMI_Admin_shutdownNodePtr;

class ICE_GRID_API AMI_Admin_shutdownRegistry : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response() = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IceGrid::AdminPrx&, const ::std::string&, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IceGrid::AMI_Admin_shutdownRegistry> AMI_Admin_shutdownRegistryPtr;

}

namespace IceAsync
{

namespace IceGrid
{

class ICE_GRID_API AMD_Admin_patchApplication : public ::IceGrid::AMD_Admin_patchApplication, public ::IceInternal::IncomingAsync
{
public:

    AMD_Admin_patchApplication(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_GRID_API AMD_Admin_startServer : public ::IceGrid::AMD_Admin_startServer, public ::IceInternal::IncomingAsync
{
public:

    AMD_Admin_startServer(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_GRID_API AMD_Admin_stopServer : public ::IceGrid::AMD_Admin_stopServer, public ::IceInternal::IncomingAsync
{
public:

    AMD_Admin_stopServer(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

class ICE_GRID_API AMD_Admin_patchServer : public ::IceGrid::AMD_Admin_patchServer, public ::IceInternal::IncomingAsync
{
public:

    AMD_Admin_patchServer(::IceInternal::Incoming&);

    virtual void ice_response();
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

namespace IceProxy
{

namespace IceGrid
{

class Admin : virtual public ::IceProxy::Ice::Object
{
public:

    void addApplication(const ::IceGrid::ApplicationDescriptor& descriptor)
    {
        addApplication(descriptor, 0);
    }
    void addApplication(const ::IceGrid::ApplicationDescriptor& descriptor, const ::Ice::Context& __ctx)
    {
        addApplication(descriptor, &__ctx);
    }
    
private:

    ICE_GRID_API void addApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool addApplication_async(const ::IceGrid::AMI_Admin_addApplicationPtr&, const ::IceGrid::ApplicationDescriptor&);
    ICE_GRID_API bool addApplication_async(const ::IceGrid::AMI_Admin_addApplicationPtr&, const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context&);

    void syncApplication(const ::IceGrid::ApplicationDescriptor& descriptor)
    {
        syncApplication(descriptor, 0);
    }
    void syncApplication(const ::IceGrid::ApplicationDescriptor& descriptor, const ::Ice::Context& __ctx)
    {
        syncApplication(descriptor, &__ctx);
    }
    
private:

    ICE_GRID_API void syncApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool syncApplication_async(const ::IceGrid::AMI_Admin_syncApplicationPtr&, const ::IceGrid::ApplicationDescriptor&);
    ICE_GRID_API bool syncApplication_async(const ::IceGrid::AMI_Admin_syncApplicationPtr&, const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context&);

    void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor& descriptor)
    {
        updateApplication(descriptor, 0);
    }
    void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor& descriptor, const ::Ice::Context& __ctx)
    {
        updateApplication(descriptor, &__ctx);
    }
    
private:

    ICE_GRID_API void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool updateApplication_async(const ::IceGrid::AMI_Admin_updateApplicationPtr&, const ::IceGrid::ApplicationUpdateDescriptor&);
    ICE_GRID_API bool updateApplication_async(const ::IceGrid::AMI_Admin_updateApplicationPtr&, const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context&);

    void removeApplication(const ::std::string& name)
    {
        removeApplication(name, 0);
    }
    void removeApplication(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        removeApplication(name, &__ctx);
    }
    
private:

    ICE_GRID_API void removeApplication(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool removeApplication_async(const ::IceGrid::AMI_Admin_removeApplicationPtr&, const ::std::string&);
    ICE_GRID_API bool removeApplication_async(const ::IceGrid::AMI_Admin_removeApplicationPtr&, const ::std::string&, const ::Ice::Context&);

    void instantiateServer(const ::std::string& application, const ::std::string& node, const ::IceGrid::ServerInstanceDescriptor& desc)
    {
        instantiateServer(application, node, desc, 0);
    }
    void instantiateServer(const ::std::string& application, const ::std::string& node, const ::IceGrid::ServerInstanceDescriptor& desc, const ::Ice::Context& __ctx)
    {
        instantiateServer(application, node, desc, &__ctx);
    }
    
private:

    ICE_GRID_API void instantiateServer(const ::std::string&, const ::std::string&, const ::IceGrid::ServerInstanceDescriptor&, const ::Ice::Context*);
    
public:

    void patchApplication(const ::std::string& name, bool shutdown)
    {
        patchApplication(name, shutdown, 0);
    }
    void patchApplication(const ::std::string& name, bool shutdown, const ::Ice::Context& __ctx)
    {
        patchApplication(name, shutdown, &__ctx);
    }
    
private:

    ICE_GRID_API void patchApplication(const ::std::string&, bool, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool patchApplication_async(const ::IceGrid::AMI_Admin_patchApplicationPtr&, const ::std::string&, bool);
    ICE_GRID_API bool patchApplication_async(const ::IceGrid::AMI_Admin_patchApplicationPtr&, const ::std::string&, bool, const ::Ice::Context&);

    ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string& name)
    {
        return getApplicationInfo(name, 0);
    }
    ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return getApplicationInfo(name, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor()
    {
        return getDefaultApplicationDescriptor(0);
    }
    ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Context& __ctx)
    {
        return getDefaultApplicationDescriptor(&__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Context*);
    
public:

    ::Ice::StringSeq getAllApplicationNames()
    {
        return getAllApplicationNames(0);
    }
    ::Ice::StringSeq getAllApplicationNames(const ::Ice::Context& __ctx)
    {
        return getAllApplicationNames(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::StringSeq getAllApplicationNames(const ::Ice::Context*);
    
public:

    ::IceGrid::ServerInfo getServerInfo(const ::std::string& id)
    {
        return getServerInfo(id, 0);
    }
    ::IceGrid::ServerInfo getServerInfo(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return getServerInfo(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ServerInfo getServerInfo(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::ServerState getServerState(const ::std::string& id)
    {
        return getServerState(id, 0);
    }
    ::IceGrid::ServerState getServerState(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return getServerState(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ServerState getServerState(const ::std::string&, const ::Ice::Context*);
    
public:

    ::Ice::Int getServerPid(const ::std::string& id)
    {
        return getServerPid(id, 0);
    }
    ::Ice::Int getServerPid(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return getServerPid(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::Int getServerPid(const ::std::string&, const ::Ice::Context*);
    
public:

    ::std::string getServerAdminCategory()
    {
        return getServerAdminCategory(0);
    }
    ::std::string getServerAdminCategory(const ::Ice::Context& __ctx)
    {
        return getServerAdminCategory(&__ctx);
    }
    
private:

    ICE_GRID_API ::std::string getServerAdminCategory(const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx getServerAdmin(const ::std::string& id)
    {
        return getServerAdmin(id, 0);
    }
    ::Ice::ObjectPrx getServerAdmin(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return getServerAdmin(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx getServerAdmin(const ::std::string&, const ::Ice::Context*);
    
public:

    void enableServer(const ::std::string& id, bool enabled)
    {
        enableServer(id, enabled, 0);
    }
    void enableServer(const ::std::string& id, bool enabled, const ::Ice::Context& __ctx)
    {
        enableServer(id, enabled, &__ctx);
    }
    
private:

    ICE_GRID_API void enableServer(const ::std::string&, bool, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool enableServer_async(const ::IceGrid::AMI_Admin_enableServerPtr&, const ::std::string&, bool);
    ICE_GRID_API bool enableServer_async(const ::IceGrid::AMI_Admin_enableServerPtr&, const ::std::string&, bool, const ::Ice::Context&);

    bool isServerEnabled(const ::std::string& id)
    {
        return isServerEnabled(id, 0);
    }
    bool isServerEnabled(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return isServerEnabled(id, &__ctx);
    }
    
private:

    ICE_GRID_API bool isServerEnabled(const ::std::string&, const ::Ice::Context*);
    
public:

    void startServer(const ::std::string& id)
    {
        startServer(id, 0);
    }
    void startServer(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        startServer(id, &__ctx);
    }
    
private:

    ICE_GRID_API void startServer(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool startServer_async(const ::IceGrid::AMI_Admin_startServerPtr&, const ::std::string&);
    ICE_GRID_API bool startServer_async(const ::IceGrid::AMI_Admin_startServerPtr&, const ::std::string&, const ::Ice::Context&);

    void stopServer(const ::std::string& id)
    {
        stopServer(id, 0);
    }
    void stopServer(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        stopServer(id, &__ctx);
    }
    
private:

    ICE_GRID_API void stopServer(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool stopServer_async(const ::IceGrid::AMI_Admin_stopServerPtr&, const ::std::string&);
    ICE_GRID_API bool stopServer_async(const ::IceGrid::AMI_Admin_stopServerPtr&, const ::std::string&, const ::Ice::Context&);

    void patchServer(const ::std::string& id, bool shutdown)
    {
        patchServer(id, shutdown, 0);
    }
    void patchServer(const ::std::string& id, bool shutdown, const ::Ice::Context& __ctx)
    {
        patchServer(id, shutdown, &__ctx);
    }
    
private:

    ICE_GRID_API void patchServer(const ::std::string&, bool, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool patchServer_async(const ::IceGrid::AMI_Admin_patchServerPtr&, const ::std::string&, bool);
    ICE_GRID_API bool patchServer_async(const ::IceGrid::AMI_Admin_patchServerPtr&, const ::std::string&, bool, const ::Ice::Context&);

    void sendSignal(const ::std::string& id, const ::std::string& signal)
    {
        sendSignal(id, signal, 0);
    }
    void sendSignal(const ::std::string& id, const ::std::string& signal, const ::Ice::Context& __ctx)
    {
        sendSignal(id, signal, &__ctx);
    }
    
private:

    ICE_GRID_API void sendSignal(const ::std::string&, const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool sendSignal_async(const ::IceGrid::AMI_Admin_sendSignalPtr&, const ::std::string&, const ::std::string&);
    ICE_GRID_API bool sendSignal_async(const ::IceGrid::AMI_Admin_sendSignalPtr&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ICE_DEPRECATED_API void writeMessage(const ::std::string& id, const ::std::string& message, ::Ice::Int fd)
    {
        writeMessage(id, message, fd, 0);
    }
    ICE_DEPRECATED_API void writeMessage(const ::std::string& id, const ::std::string& message, ::Ice::Int fd, const ::Ice::Context& __ctx)
    {
        writeMessage(id, message, fd, &__ctx);
    }
    
private:

    ICE_GRID_API void writeMessage(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool writeMessage_async(const ::IceGrid::AMI_Admin_writeMessagePtr&, const ::std::string&, const ::std::string&, ::Ice::Int);
    ICE_GRID_API bool writeMessage_async(const ::IceGrid::AMI_Admin_writeMessagePtr&, const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    ::Ice::StringSeq getAllServerIds()
    {
        return getAllServerIds(0);
    }
    ::Ice::StringSeq getAllServerIds(const ::Ice::Context& __ctx)
    {
        return getAllServerIds(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::StringSeq getAllServerIds(const ::Ice::Context*);
    
public:

    ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string& id)
    {
        return getAdapterInfo(id, 0);
    }
    ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string& id, const ::Ice::Context& __ctx)
    {
        return getAdapterInfo(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string&, const ::Ice::Context*);
    
public:

    void removeAdapter(const ::std::string& adapterId)
    {
        removeAdapter(adapterId, 0);
    }
    void removeAdapter(const ::std::string& adapterId, const ::Ice::Context& __ctx)
    {
        removeAdapter(adapterId, &__ctx);
    }
    
private:

    ICE_GRID_API void removeAdapter(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool removeAdapter_async(const ::IceGrid::AMI_Admin_removeAdapterPtr&, const ::std::string&);
    ICE_GRID_API bool removeAdapter_async(const ::IceGrid::AMI_Admin_removeAdapterPtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::StringSeq getAllAdapterIds()
    {
        return getAllAdapterIds(0);
    }
    ::Ice::StringSeq getAllAdapterIds(const ::Ice::Context& __ctx)
    {
        return getAllAdapterIds(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::StringSeq getAllAdapterIds(const ::Ice::Context*);
    
public:

    void addObject(const ::Ice::ObjectPrx& obj)
    {
        addObject(obj, 0);
    }
    void addObject(const ::Ice::ObjectPrx& obj, const ::Ice::Context& __ctx)
    {
        addObject(obj, &__ctx);
    }
    
private:

    ICE_GRID_API void addObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool addObject_async(const ::IceGrid::AMI_Admin_addObjectPtr&, const ::Ice::ObjectPrx&);
    ICE_GRID_API bool addObject_async(const ::IceGrid::AMI_Admin_addObjectPtr&, const ::Ice::ObjectPrx&, const ::Ice::Context&);

    void updateObject(const ::Ice::ObjectPrx& obj)
    {
        updateObject(obj, 0);
    }
    void updateObject(const ::Ice::ObjectPrx& obj, const ::Ice::Context& __ctx)
    {
        updateObject(obj, &__ctx);
    }
    
private:

    ICE_GRID_API void updateObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);
    
public:

    void addObjectWithType(const ::Ice::ObjectPrx& obj, const ::std::string& type)
    {
        addObjectWithType(obj, type, 0);
    }
    void addObjectWithType(const ::Ice::ObjectPrx& obj, const ::std::string& type, const ::Ice::Context& __ctx)
    {
        addObjectWithType(obj, type, &__ctx);
    }
    
private:

    ICE_GRID_API void addObjectWithType(const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool addObjectWithType_async(const ::IceGrid::AMI_Admin_addObjectWithTypePtr&, const ::Ice::ObjectPrx&, const ::std::string&);
    ICE_GRID_API bool addObjectWithType_async(const ::IceGrid::AMI_Admin_addObjectWithTypePtr&, const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context&);

    void removeObject(const ::Ice::Identity& id)
    {
        removeObject(id, 0);
    }
    void removeObject(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        removeObject(id, &__ctx);
    }
    
private:

    ICE_GRID_API void removeObject(const ::Ice::Identity&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool removeObject_async(const ::IceGrid::AMI_Admin_removeObjectPtr&, const ::Ice::Identity&);
    ICE_GRID_API bool removeObject_async(const ::IceGrid::AMI_Admin_removeObjectPtr&, const ::Ice::Identity&, const ::Ice::Context&);

    ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity& id)
    {
        return getObjectInfo(id, 0);
    }
    ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity& id, const ::Ice::Context& __ctx)
    {
        return getObjectInfo(id, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity&, const ::Ice::Context*);
    
public:

    ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string& type)
    {
        return getObjectInfosByType(type, 0);
    }
    ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string& type, const ::Ice::Context& __ctx)
    {
        return getObjectInfosByType(type, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string& expr)
    {
        return getAllObjectInfos(expr, 0);
    }
    ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string& expr, const ::Ice::Context& __ctx)
    {
        return getAllObjectInfos(expr, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string&, const ::Ice::Context*);
    
public:

    bool pingNode(const ::std::string& name)
    {
        return pingNode(name, 0);
    }
    bool pingNode(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return pingNode(name, &__ctx);
    }
    
private:

    ICE_GRID_API bool pingNode(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::LoadInfo getNodeLoad(const ::std::string& name)
    {
        return getNodeLoad(name, 0);
    }
    ::IceGrid::LoadInfo getNodeLoad(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return getNodeLoad(name, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::LoadInfo getNodeLoad(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool getNodeLoad_async(const ::IceGrid::AMI_Admin_getNodeLoadPtr&, const ::std::string&);
    ICE_GRID_API bool getNodeLoad_async(const ::IceGrid::AMI_Admin_getNodeLoadPtr&, const ::std::string&, const ::Ice::Context&);

    ::IceGrid::NodeInfo getNodeInfo(const ::std::string& name)
    {
        return getNodeInfo(name, 0);
    }
    ::IceGrid::NodeInfo getNodeInfo(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return getNodeInfo(name, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::NodeInfo getNodeInfo(const ::std::string&, const ::Ice::Context*);
    
public:

    void shutdownNode(const ::std::string& name)
    {
        shutdownNode(name, 0);
    }
    void shutdownNode(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        shutdownNode(name, &__ctx);
    }
    
private:

    ICE_GRID_API void shutdownNode(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool shutdownNode_async(const ::IceGrid::AMI_Admin_shutdownNodePtr&, const ::std::string&);
    ICE_GRID_API bool shutdownNode_async(const ::IceGrid::AMI_Admin_shutdownNodePtr&, const ::std::string&, const ::Ice::Context&);

    ::std::string getNodeHostname(const ::std::string& name)
    {
        return getNodeHostname(name, 0);
    }
    ::std::string getNodeHostname(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return getNodeHostname(name, &__ctx);
    }
    
private:

    ICE_GRID_API ::std::string getNodeHostname(const ::std::string&, const ::Ice::Context*);
    
public:

    ::Ice::StringSeq getAllNodeNames()
    {
        return getAllNodeNames(0);
    }
    ::Ice::StringSeq getAllNodeNames(const ::Ice::Context& __ctx)
    {
        return getAllNodeNames(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::StringSeq getAllNodeNames(const ::Ice::Context*);
    
public:

    bool pingRegistry(const ::std::string& name)
    {
        return pingRegistry(name, 0);
    }
    bool pingRegistry(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return pingRegistry(name, &__ctx);
    }
    
private:

    ICE_GRID_API bool pingRegistry(const ::std::string&, const ::Ice::Context*);
    
public:

    ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string& name)
    {
        return getRegistryInfo(name, 0);
    }
    ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return getRegistryInfo(name, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string&, const ::Ice::Context*);
    
public:

    void shutdownRegistry(const ::std::string& name)
    {
        shutdownRegistry(name, 0);
    }
    void shutdownRegistry(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        shutdownRegistry(name, &__ctx);
    }
    
private:

    ICE_GRID_API void shutdownRegistry(const ::std::string&, const ::Ice::Context*);
    
public:
    ICE_GRID_API bool shutdownRegistry_async(const ::IceGrid::AMI_Admin_shutdownRegistryPtr&, const ::std::string&);
    ICE_GRID_API bool shutdownRegistry_async(const ::IceGrid::AMI_Admin_shutdownRegistryPtr&, const ::std::string&, const ::Ice::Context&);

    ::Ice::StringSeq getAllRegistryNames()
    {
        return getAllRegistryNames(0);
    }
    ::Ice::StringSeq getAllRegistryNames(const ::Ice::Context& __ctx)
    {
        return getAllRegistryNames(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::StringSeq getAllRegistryNames(const ::Ice::Context*);
    
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

    ICE_GRID_API void shutdown(const ::Ice::Context*);
    
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

    ICE_GRID_API ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
    
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
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class FileIterator : virtual public ::IceProxy::Ice::Object
{
public:

    bool read(::Ice::Int size, ::Ice::StringSeq& lines)
    {
        return read(size, lines, 0);
    }
    bool read(::Ice::Int size, ::Ice::StringSeq& lines, const ::Ice::Context& __ctx)
    {
        return read(size, lines, &__ctx);
    }
    
private:

    ICE_GRID_API bool read(::Ice::Int, ::Ice::StringSeq&, const ::Ice::Context*);
    
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

    ICE_GRID_API void destroy(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<FileIterator> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileIterator> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileIterator*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<FileIterator*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class AdminSession : virtual public ::IceProxy::Glacier2::Session
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

    ::IceGrid::AdminPrx getAdmin()
    {
        return getAdmin(0);
    }
    ::IceGrid::AdminPrx getAdmin(const ::Ice::Context& __ctx)
    {
        return getAdmin(&__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::AdminPrx getAdmin(const ::Ice::Context*);
    
public:

    ::Ice::ObjectPrx getAdminCallbackTemplate()
    {
        return getAdminCallbackTemplate(0);
    }
    ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Context& __ctx)
    {
        return getAdminCallbackTemplate(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Context*);
    
public:

    void setObservers(const ::IceGrid::RegistryObserverPrx& registryObs, const ::IceGrid::NodeObserverPrx& nodeObs, const ::IceGrid::ApplicationObserverPrx& appObs, const ::IceGrid::AdapterObserverPrx& adptObs, const ::IceGrid::ObjectObserverPrx& objObs)
    {
        setObservers(registryObs, nodeObs, appObs, adptObs, objObs, 0);
    }
    void setObservers(const ::IceGrid::RegistryObserverPrx& registryObs, const ::IceGrid::NodeObserverPrx& nodeObs, const ::IceGrid::ApplicationObserverPrx& appObs, const ::IceGrid::AdapterObserverPrx& adptObs, const ::IceGrid::ObjectObserverPrx& objObs, const ::Ice::Context& __ctx)
    {
        setObservers(registryObs, nodeObs, appObs, adptObs, objObs, &__ctx);
    }
    
private:

    ICE_GRID_API void setObservers(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::NodeObserverPrx&, const ::IceGrid::ApplicationObserverPrx&, const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::ObjectObserverPrx&, const ::Ice::Context*);
    
public:

    void setObserversByIdentity(const ::Ice::Identity& registryObs, const ::Ice::Identity& nodeObs, const ::Ice::Identity& appObs, const ::Ice::Identity& adptObs, const ::Ice::Identity& objObs)
    {
        setObserversByIdentity(registryObs, nodeObs, appObs, adptObs, objObs, 0);
    }
    void setObserversByIdentity(const ::Ice::Identity& registryObs, const ::Ice::Identity& nodeObs, const ::Ice::Identity& appObs, const ::Ice::Identity& adptObs, const ::Ice::Identity& objObs, const ::Ice::Context& __ctx)
    {
        setObserversByIdentity(registryObs, nodeObs, appObs, adptObs, objObs, &__ctx);
    }
    
private:

    ICE_GRID_API void setObserversByIdentity(const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Context*);
    
public:

    ::Ice::Int startUpdate()
    {
        return startUpdate(0);
    }
    ::Ice::Int startUpdate(const ::Ice::Context& __ctx)
    {
        return startUpdate(&__ctx);
    }
    
private:

    ICE_GRID_API ::Ice::Int startUpdate(const ::Ice::Context*);
    
public:

    void finishUpdate()
    {
        finishUpdate(0);
    }
    void finishUpdate(const ::Ice::Context& __ctx)
    {
        finishUpdate(&__ctx);
    }
    
private:

    ICE_GRID_API void finishUpdate(const ::Ice::Context*);
    
public:

    ::std::string getReplicaName()
    {
        return getReplicaName(0);
    }
    ::std::string getReplicaName(const ::Ice::Context& __ctx)
    {
        return getReplicaName(&__ctx);
    }
    
private:

    ICE_GRID_API ::std::string getReplicaName(const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openServerLog(const ::std::string& id, const ::std::string& path, ::Ice::Int count)
    {
        return openServerLog(id, path, count, 0);
    }
    ::IceGrid::FileIteratorPrx openServerLog(const ::std::string& id, const ::std::string& path, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openServerLog(id, path, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openServerLog(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string& id, ::Ice::Int count)
    {
        return openServerStdErr(id, count, 0);
    }
    ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string& id, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openServerStdErr(id, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string& id, ::Ice::Int count)
    {
        return openServerStdOut(id, count, 0);
    }
    ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string& id, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openServerStdOut(id, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string& name, ::Ice::Int count)
    {
        return openNodeStdErr(name, count, 0);
    }
    ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string& name, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openNodeStdErr(name, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string& name, ::Ice::Int count)
    {
        return openNodeStdOut(name, count, 0);
    }
    ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string& name, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openNodeStdOut(name, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string& name, ::Ice::Int count)
    {
        return openRegistryStdErr(name, count, 0);
    }
    ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string& name, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openRegistryStdErr(name, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:

    ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string& name, ::Ice::Int count)
    {
        return openRegistryStdOut(name, count, 0);
    }
    ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string& name, ::Ice::Int count, const ::Ice::Context& __ctx)
    {
        return openRegistryStdOut(name, count, &__ctx);
    }
    
private:

    ICE_GRID_API ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<AdminSession> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdminSession> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdminSession*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<AdminSession*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_GRID_API Admin : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void addApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*) = 0;

    virtual void syncApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*) = 0;

    virtual void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context*) = 0;

    virtual void removeApplication(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void instantiateServer(const ::std::string&, const ::std::string&, const ::IceGrid::ServerInstanceDescriptor&, const ::Ice::Context*) = 0;

    virtual void patchApplication(const ::std::string&, bool, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq getAllApplicationNames(const ::Ice::Context*) = 0;

    virtual ::IceGrid::ServerInfo getServerInfo(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ServerState getServerState(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int getServerPid(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::std::string getServerAdminCategory(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx getServerAdmin(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void enableServer(const ::std::string&, bool, const ::Ice::Context*) = 0;

    virtual bool isServerEnabled(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void startServer(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void stopServer(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void patchServer(const ::std::string&, bool, const ::Ice::Context*) = 0;

    virtual void sendSignal(const ::std::string&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual void writeMessage(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq getAllServerIds(const ::Ice::Context*) = 0;

    virtual ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void removeAdapter(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq getAllAdapterIds(const ::Ice::Context*) = 0;

    virtual void addObject(const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void updateObject(const ::Ice::ObjectPrx&, const ::Ice::Context*) = 0;

    virtual void addObjectWithType(const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual void removeObject(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string&, const ::Ice::Context*) = 0;

    virtual bool pingNode(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::LoadInfo getNodeLoad(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::NodeInfo getNodeInfo(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void shutdownNode(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::std::string getNodeHostname(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq getAllNodeNames(const ::Ice::Context*) = 0;

    virtual bool pingRegistry(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string&, const ::Ice::Context*) = 0;

    virtual void shutdownRegistry(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::Ice::StringSeq getAllRegistryNames(const ::Ice::Context*) = 0;

    virtual void shutdown(const ::Ice::Context*) = 0;

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*) = 0;
};

class ICE_GRID_API FileIterator : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool read(::Ice::Int, ::Ice::StringSeq&, const ::Ice::Context*) = 0;

    virtual void destroy(const ::Ice::Context*) = 0;
};

class ICE_GRID_API AdminSession : virtual public ::IceDelegate::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*) = 0;

    virtual ::IceGrid::AdminPrx getAdmin(const ::Ice::Context*) = 0;

    virtual ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Context*) = 0;

    virtual void setObservers(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::NodeObserverPrx&, const ::IceGrid::ApplicationObserverPrx&, const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::ObjectObserverPrx&, const ::Ice::Context*) = 0;

    virtual void setObserversByIdentity(const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int startUpdate(const ::Ice::Context*) = 0;

    virtual void finishUpdate(const ::Ice::Context*) = 0;

    virtual ::std::string getReplicaName(const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openServerLog(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API Admin : virtual public ::IceDelegate::IceGrid::Admin,
                           virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void addApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

    virtual void syncApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

    virtual void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context*);

    virtual void removeApplication(const ::std::string&, const ::Ice::Context*);

    virtual void instantiateServer(const ::std::string&, const ::std::string&, const ::IceGrid::ServerInstanceDescriptor&, const ::Ice::Context*);

    virtual void patchApplication(const ::std::string&, bool, const ::Ice::Context*);

    virtual ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllApplicationNames(const ::Ice::Context*);

    virtual ::IceGrid::ServerInfo getServerInfo(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ServerState getServerState(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::Int getServerPid(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string getServerAdminCategory(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getServerAdmin(const ::std::string&, const ::Ice::Context*);

    virtual void enableServer(const ::std::string&, bool, const ::Ice::Context*);

    virtual bool isServerEnabled(const ::std::string&, const ::Ice::Context*);

    virtual void startServer(const ::std::string&, const ::Ice::Context*);

    virtual void stopServer(const ::std::string&, const ::Ice::Context*);

    virtual void patchServer(const ::std::string&, bool, const ::Ice::Context*);

    virtual void sendSignal(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual void writeMessage(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllServerIds(const ::Ice::Context*);

    virtual ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string&, const ::Ice::Context*);

    virtual void removeAdapter(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllAdapterIds(const ::Ice::Context*);

    virtual void addObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void updateObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void addObjectWithType(const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context*);

    virtual void removeObject(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string&, const ::Ice::Context*);

    virtual bool pingNode(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::LoadInfo getNodeLoad(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::NodeInfo getNodeInfo(const ::std::string&, const ::Ice::Context*);

    virtual void shutdownNode(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string getNodeHostname(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllNodeNames(const ::Ice::Context*);

    virtual bool pingRegistry(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string&, const ::Ice::Context*);

    virtual void shutdownRegistry(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllRegistryNames(const ::Ice::Context*);

    virtual void shutdown(const ::Ice::Context*);

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
};

class ICE_GRID_API FileIterator : virtual public ::IceDelegate::IceGrid::FileIterator,
                                  virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool read(::Ice::Int, ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class ICE_GRID_API AdminSession : virtual public ::IceDelegate::IceGrid::AdminSession,
                                  virtual public ::IceDelegateM::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*);

    virtual ::IceGrid::AdminPrx getAdmin(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Context*);

    virtual void setObservers(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::NodeObserverPrx&, const ::IceGrid::ApplicationObserverPrx&, const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::ObjectObserverPrx&, const ::Ice::Context*);

    virtual void setObserversByIdentity(const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::Int startUpdate(const ::Ice::Context*);

    virtual void finishUpdate(const ::Ice::Context*);

    virtual ::std::string getReplicaName(const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerLog(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API Admin : virtual public ::IceDelegate::IceGrid::Admin,
                           virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void addApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

    virtual void syncApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Context*);

    virtual void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Context*);

    virtual void removeApplication(const ::std::string&, const ::Ice::Context*);

    virtual void instantiateServer(const ::std::string&, const ::std::string&, const ::IceGrid::ServerInstanceDescriptor&, const ::Ice::Context*);

    virtual void patchApplication(const ::std::string&, bool, const ::Ice::Context*);

    virtual ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllApplicationNames(const ::Ice::Context*);

    virtual ::IceGrid::ServerInfo getServerInfo(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ServerState getServerState(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::Int getServerPid(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string getServerAdminCategory(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getServerAdmin(const ::std::string&, const ::Ice::Context*);

    virtual void enableServer(const ::std::string&, bool, const ::Ice::Context*);

    virtual bool isServerEnabled(const ::std::string&, const ::Ice::Context*);

    virtual void startServer(const ::std::string&, const ::Ice::Context*);

    virtual void stopServer(const ::std::string&, const ::Ice::Context*);

    virtual void patchServer(const ::std::string&, bool, const ::Ice::Context*);

    virtual void sendSignal(const ::std::string&, const ::std::string&, const ::Ice::Context*);

    virtual void writeMessage(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllServerIds(const ::Ice::Context*);

    virtual ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string&, const ::Ice::Context*);

    virtual void removeAdapter(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllAdapterIds(const ::Ice::Context*);

    virtual void addObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void updateObject(const ::Ice::ObjectPrx&, const ::Ice::Context*);

    virtual void addObjectWithType(const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Context*);

    virtual void removeObject(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string&, const ::Ice::Context*);

    virtual bool pingNode(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::LoadInfo getNodeLoad(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::NodeInfo getNodeInfo(const ::std::string&, const ::Ice::Context*);

    virtual void shutdownNode(const ::std::string&, const ::Ice::Context*);

    virtual ::std::string getNodeHostname(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllNodeNames(const ::Ice::Context*);

    virtual bool pingRegistry(const ::std::string&, const ::Ice::Context*);

    virtual ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string&, const ::Ice::Context*);

    virtual void shutdownRegistry(const ::std::string&, const ::Ice::Context*);

    virtual ::Ice::StringSeq getAllRegistryNames(const ::Ice::Context*);

    virtual void shutdown(const ::Ice::Context*);

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Context*);
};

class ICE_GRID_API FileIterator : virtual public ::IceDelegate::IceGrid::FileIterator,
                                  virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool read(::Ice::Int, ::Ice::StringSeq&, const ::Ice::Context*);

    virtual void destroy(const ::Ice::Context*);
};

class ICE_GRID_API AdminSession : virtual public ::IceDelegate::IceGrid::AdminSession,
                                  virtual public ::IceDelegateD::Glacier2::Session
{
public:

    virtual void keepAlive(const ::Ice::Context*);

    virtual ::IceGrid::AdminPrx getAdmin(const ::Ice::Context*);

    virtual ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Context*);

    virtual void setObservers(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::NodeObserverPrx&, const ::IceGrid::ApplicationObserverPrx&, const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::ObjectObserverPrx&, const ::Ice::Context*);

    virtual void setObserversByIdentity(const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Context*);

    virtual ::Ice::Int startUpdate(const ::Ice::Context*);

    virtual void finishUpdate(const ::Ice::Context*);

    virtual ::std::string getReplicaName(const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerLog(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Context*);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceGrid
{

class ICE_GRID_API Admin : virtual public ::Ice::Object
{
public:

    typedef AdminPrx ProxyType;
    typedef AdminPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void addApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addApplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void syncApplication(const ::IceGrid::ApplicationDescriptor&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___syncApplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateApplication(const ::IceGrid::ApplicationUpdateDescriptor&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___updateApplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void removeApplication(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___removeApplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void instantiateServer(const ::std::string&, const ::std::string&, const ::IceGrid::ServerInstanceDescriptor&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___instantiateServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void patchApplication_async(const ::IceGrid::AMD_Admin_patchApplicationPtr&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___patchApplication(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::ApplicationInfo getApplicationInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getApplicationInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::ApplicationDescriptor getDefaultApplicationDescriptor(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getDefaultApplicationDescriptor(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::StringSeq getAllApplicationNames(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllApplicationNames(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::ServerInfo getServerInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::ServerState getServerState(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerState(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::Int getServerPid(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerPid(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::std::string getServerAdminCategory(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerAdminCategory(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx getServerAdmin(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getServerAdmin(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void enableServer(const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___enableServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool isServerEnabled(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___isServerEnabled(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void startServer_async(const ::IceGrid::AMD_Admin_startServerPtr&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___startServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void stopServer_async(const ::IceGrid::AMD_Admin_stopServerPtr&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___stopServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void patchServer_async(const ::IceGrid::AMD_Admin_patchServerPtr&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___patchServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void sendSignal(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___sendSignal(::IceInternal::Incoming&, const ::Ice::Current&);

    ICE_DEPRECATED_API virtual void writeMessage(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___writeMessage(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::StringSeq getAllServerIds(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllServerIds(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::AdapterInfoSeq getAdapterInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAdapterInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void removeAdapter(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___removeAdapter(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::StringSeq getAllAdapterIds(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllAdapterIds(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void addObject(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void updateObject(const ::Ice::ObjectPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___updateObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void addObjectWithType(const ::Ice::ObjectPrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___addObjectWithType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void removeObject(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___removeObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::ObjectInfo getObjectInfo(const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getObjectInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::ObjectInfoSeq getObjectInfosByType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getObjectInfosByType(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::ObjectInfoSeq getAllObjectInfos(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllObjectInfos(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual bool pingNode(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___pingNode(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::LoadInfo getNodeLoad(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getNodeLoad(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::NodeInfo getNodeInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getNodeInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void shutdownNode(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___shutdownNode(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string getNodeHostname(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getNodeHostname(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::StringSeq getAllNodeNames(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllNodeNames(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual bool pingRegistry(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___pingRegistry(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::RegistryInfo getRegistryInfo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getRegistryInfo(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void shutdownRegistry(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___shutdownRegistry(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::StringSeq getAllRegistryNames(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAllRegistryNames(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void shutdown(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___shutdown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::SliceChecksumDict getSliceChecksums(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getSliceChecksums(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API FileIterator : virtual public ::Ice::Object
{
public:

    typedef FileIteratorPrx ProxyType;
    typedef FileIteratorPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool read(::Ice::Int, ::Ice::StringSeq&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___read(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_GRID_API AdminSession : virtual public ::Glacier2::Session
{
public:

    typedef AdminSessionPrx ProxyType;
    typedef AdminSessionPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void keepAlive(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___keepAlive(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::AdminPrx getAdmin(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAdmin(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ObjectPrx getAdminCallbackTemplate(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getAdminCallbackTemplate(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void setObservers(const ::IceGrid::RegistryObserverPrx&, const ::IceGrid::NodeObserverPrx&, const ::IceGrid::ApplicationObserverPrx&, const ::IceGrid::AdapterObserverPrx&, const ::IceGrid::ObjectObserverPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setObservers(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setObserversByIdentity(const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Identity&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___setObserversByIdentity(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int startUpdate(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___startUpdate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void finishUpdate(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___finishUpdate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string getReplicaName(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getReplicaName(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IceGrid::FileIteratorPrx openServerLog(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openServerLog(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openServerStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openServerStdErr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openServerStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openServerStdOut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openNodeStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openNodeStdErr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openNodeStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openNodeStdOut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdErr(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openRegistryStdErr(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceGrid::FileIteratorPrx openRegistryStdOut(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___openRegistryStdOut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif

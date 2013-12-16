// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Descriptor.ice'

#ifndef __IceGrid_Descriptor_h__
#define __IceGrid_Descriptor_h__

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
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <Ice/Identity.h>
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

class CommunicatorDescriptor;

class ServerDescriptor;

class ServiceDescriptor;

class IceBoxDescriptor;

class LoadBalancingPolicy;

class RandomLoadBalancingPolicy;

class OrderedLoadBalancingPolicy;

class RoundRobinLoadBalancingPolicy;

class AdaptiveLoadBalancingPolicy;

class BoxedString;

class BoxedDistributionDescriptor;

}

}

namespace IceGrid
{

class CommunicatorDescriptor;
ICE_GRID_API bool operator==(const CommunicatorDescriptor&, const CommunicatorDescriptor&);
ICE_GRID_API bool operator<(const CommunicatorDescriptor&, const CommunicatorDescriptor&);

class ServerDescriptor;
ICE_GRID_API bool operator==(const ServerDescriptor&, const ServerDescriptor&);
ICE_GRID_API bool operator<(const ServerDescriptor&, const ServerDescriptor&);

class ServiceDescriptor;
ICE_GRID_API bool operator==(const ServiceDescriptor&, const ServiceDescriptor&);
ICE_GRID_API bool operator<(const ServiceDescriptor&, const ServiceDescriptor&);

class IceBoxDescriptor;
ICE_GRID_API bool operator==(const IceBoxDescriptor&, const IceBoxDescriptor&);
ICE_GRID_API bool operator<(const IceBoxDescriptor&, const IceBoxDescriptor&);

class LoadBalancingPolicy;
ICE_GRID_API bool operator==(const LoadBalancingPolicy&, const LoadBalancingPolicy&);
ICE_GRID_API bool operator<(const LoadBalancingPolicy&, const LoadBalancingPolicy&);

class RandomLoadBalancingPolicy;
ICE_GRID_API bool operator==(const RandomLoadBalancingPolicy&, const RandomLoadBalancingPolicy&);
ICE_GRID_API bool operator<(const RandomLoadBalancingPolicy&, const RandomLoadBalancingPolicy&);

class OrderedLoadBalancingPolicy;
ICE_GRID_API bool operator==(const OrderedLoadBalancingPolicy&, const OrderedLoadBalancingPolicy&);
ICE_GRID_API bool operator<(const OrderedLoadBalancingPolicy&, const OrderedLoadBalancingPolicy&);

class RoundRobinLoadBalancingPolicy;
ICE_GRID_API bool operator==(const RoundRobinLoadBalancingPolicy&, const RoundRobinLoadBalancingPolicy&);
ICE_GRID_API bool operator<(const RoundRobinLoadBalancingPolicy&, const RoundRobinLoadBalancingPolicy&);

class AdaptiveLoadBalancingPolicy;
ICE_GRID_API bool operator==(const AdaptiveLoadBalancingPolicy&, const AdaptiveLoadBalancingPolicy&);
ICE_GRID_API bool operator<(const AdaptiveLoadBalancingPolicy&, const AdaptiveLoadBalancingPolicy&);

class BoxedString;
ICE_GRID_API bool operator==(const BoxedString&, const BoxedString&);
ICE_GRID_API bool operator<(const BoxedString&, const BoxedString&);

class BoxedDistributionDescriptor;
ICE_GRID_API bool operator==(const BoxedDistributionDescriptor&, const BoxedDistributionDescriptor&);
ICE_GRID_API bool operator<(const BoxedDistributionDescriptor&, const BoxedDistributionDescriptor&);

}

namespace IceInternal
{

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::CommunicatorDescriptor*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::CommunicatorDescriptor*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ServerDescriptor*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ServerDescriptor*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::ServiceDescriptor*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::ServiceDescriptor*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::IceBoxDescriptor*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::IceBoxDescriptor*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::LoadBalancingPolicy*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::LoadBalancingPolicy*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::RandomLoadBalancingPolicy*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::RandomLoadBalancingPolicy*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::OrderedLoadBalancingPolicy*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::OrderedLoadBalancingPolicy*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::RoundRobinLoadBalancingPolicy*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::RoundRobinLoadBalancingPolicy*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::AdaptiveLoadBalancingPolicy*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::AdaptiveLoadBalancingPolicy*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::BoxedString*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::BoxedString*);

ICE_GRID_API ::Ice::Object* upCast(::IceGrid::BoxedDistributionDescriptor*);
ICE_GRID_API ::IceProxy::Ice::Object* upCast(::IceProxy::IceGrid::BoxedDistributionDescriptor*);

}

namespace IceGrid
{

typedef ::IceInternal::Handle< ::IceGrid::CommunicatorDescriptor> CommunicatorDescriptorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::CommunicatorDescriptor> CommunicatorDescriptorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, CommunicatorDescriptorPrx&);
ICE_GRID_API void __patch__CommunicatorDescriptorPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::ServerDescriptor> ServerDescriptorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::ServerDescriptor> ServerDescriptorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, ServerDescriptorPrx&);
ICE_GRID_API void __patch__ServerDescriptorPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::ServiceDescriptor> ServiceDescriptorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::ServiceDescriptor> ServiceDescriptorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, ServiceDescriptorPrx&);
ICE_GRID_API void __patch__ServiceDescriptorPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::IceBoxDescriptor> IceBoxDescriptorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::IceBoxDescriptor> IceBoxDescriptorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, IceBoxDescriptorPrx&);
ICE_GRID_API void __patch__IceBoxDescriptorPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::LoadBalancingPolicy> LoadBalancingPolicyPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::LoadBalancingPolicy> LoadBalancingPolicyPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, LoadBalancingPolicyPrx&);
ICE_GRID_API void __patch__LoadBalancingPolicyPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::RandomLoadBalancingPolicy> RandomLoadBalancingPolicyPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::RandomLoadBalancingPolicy> RandomLoadBalancingPolicyPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, RandomLoadBalancingPolicyPrx&);
ICE_GRID_API void __patch__RandomLoadBalancingPolicyPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::OrderedLoadBalancingPolicy> OrderedLoadBalancingPolicyPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::OrderedLoadBalancingPolicy> OrderedLoadBalancingPolicyPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, OrderedLoadBalancingPolicyPrx&);
ICE_GRID_API void __patch__OrderedLoadBalancingPolicyPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::RoundRobinLoadBalancingPolicy> RoundRobinLoadBalancingPolicyPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::RoundRobinLoadBalancingPolicy> RoundRobinLoadBalancingPolicyPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, RoundRobinLoadBalancingPolicyPrx&);
ICE_GRID_API void __patch__RoundRobinLoadBalancingPolicyPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::AdaptiveLoadBalancingPolicy> AdaptiveLoadBalancingPolicyPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::AdaptiveLoadBalancingPolicy> AdaptiveLoadBalancingPolicyPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, AdaptiveLoadBalancingPolicyPrx&);
ICE_GRID_API void __patch__AdaptiveLoadBalancingPolicyPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::BoxedString> BoxedStringPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::BoxedString> BoxedStringPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, BoxedStringPrx&);
ICE_GRID_API void __patch__BoxedStringPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IceGrid::BoxedDistributionDescriptor> BoxedDistributionDescriptorPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceGrid::BoxedDistributionDescriptor> BoxedDistributionDescriptorPrx;

ICE_GRID_API void __read(::IceInternal::BasicStream*, BoxedDistributionDescriptorPrx&);
ICE_GRID_API void __patch__BoxedDistributionDescriptorPtr(void*, ::Ice::ObjectPtr&);

}

namespace IceGrid
{

typedef ::std::map< ::std::string, ::std::string> StringStringDict;
ICE_GRID_API void __writeStringStringDict(::IceInternal::BasicStream*, const StringStringDict&);
ICE_GRID_API void __readStringStringDict(::IceInternal::BasicStream*, StringStringDict&);

struct PropertyDescriptor
{
    ::std::string name;
    ::std::string value;

    ICE_GRID_API bool operator==(const PropertyDescriptor&) const;
    ICE_GRID_API bool operator<(const PropertyDescriptor&) const;
    bool operator!=(const PropertyDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const PropertyDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const PropertyDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const PropertyDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::PropertyDescriptor> PropertyDescriptorSeq;
ICE_GRID_API void __writePropertyDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::PropertyDescriptor*, const ::IceGrid::PropertyDescriptor*);
ICE_GRID_API void __readPropertyDescriptorSeq(::IceInternal::BasicStream*, PropertyDescriptorSeq&);

struct PropertySetDescriptor
{
    ::Ice::StringSeq references;
    ::IceGrid::PropertyDescriptorSeq properties;

    ICE_GRID_API bool operator==(const PropertySetDescriptor&) const;
    ICE_GRID_API bool operator<(const PropertySetDescriptor&) const;
    bool operator!=(const PropertySetDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const PropertySetDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const PropertySetDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const PropertySetDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::map< ::std::string, ::IceGrid::PropertySetDescriptor> PropertySetDescriptorDict;
ICE_GRID_API void __writePropertySetDescriptorDict(::IceInternal::BasicStream*, const PropertySetDescriptorDict&);
ICE_GRID_API void __readPropertySetDescriptorDict(::IceInternal::BasicStream*, PropertySetDescriptorDict&);

struct ObjectDescriptor
{
    ::Ice::Identity id;
    ::std::string type;

    ICE_GRID_API bool operator==(const ObjectDescriptor&) const;
    ICE_GRID_API bool operator<(const ObjectDescriptor&) const;
    bool operator!=(const ObjectDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ObjectDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ObjectDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ObjectDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ObjectDescriptor> ObjectDescriptorSeq;
ICE_GRID_API void __writeObjectDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ObjectDescriptor*, const ::IceGrid::ObjectDescriptor*);
ICE_GRID_API void __readObjectDescriptorSeq(::IceInternal::BasicStream*, ObjectDescriptorSeq&);

struct AdapterDescriptor
{
    ::std::string name;
    ::std::string description;
    ::std::string id;
    ::std::string replicaGroupId;
    ::std::string priority;
    bool registerProcess;
    bool serverLifetime;
    ::IceGrid::ObjectDescriptorSeq objects;
    ::IceGrid::ObjectDescriptorSeq allocatables;

    ICE_GRID_API bool operator==(const AdapterDescriptor&) const;
    ICE_GRID_API bool operator<(const AdapterDescriptor&) const;
    bool operator!=(const AdapterDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const AdapterDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const AdapterDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const AdapterDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::AdapterDescriptor> AdapterDescriptorSeq;
ICE_GRID_API void __writeAdapterDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::AdapterDescriptor*, const ::IceGrid::AdapterDescriptor*);
ICE_GRID_API void __readAdapterDescriptorSeq(::IceInternal::BasicStream*, AdapterDescriptorSeq&);

struct DbEnvDescriptor
{
    ::std::string name;
    ::std::string description;
    ::std::string dbHome;
    ::IceGrid::PropertyDescriptorSeq properties;

    ICE_GRID_API bool operator==(const DbEnvDescriptor&) const;
    ICE_GRID_API bool operator<(const DbEnvDescriptor&) const;
    bool operator!=(const DbEnvDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const DbEnvDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const DbEnvDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const DbEnvDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::DbEnvDescriptor> DbEnvDescriptorSeq;
ICE_GRID_API void __writeDbEnvDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::DbEnvDescriptor*, const ::IceGrid::DbEnvDescriptor*);
ICE_GRID_API void __readDbEnvDescriptorSeq(::IceInternal::BasicStream*, DbEnvDescriptorSeq&);

struct DistributionDescriptor
{
    ::std::string icepatch;
    ::Ice::StringSeq directories;

    ICE_GRID_API bool operator==(const DistributionDescriptor&) const;
    ICE_GRID_API bool operator<(const DistributionDescriptor&) const;
    bool operator!=(const DistributionDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const DistributionDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const DistributionDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const DistributionDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ServerDescriptorPtr> ServerDescriptorSeq;
ICE_GRID_API void __writeServerDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ServerDescriptorPtr*, const ::IceGrid::ServerDescriptorPtr*);
ICE_GRID_API void __readServerDescriptorSeq(::IceInternal::BasicStream*, ServerDescriptorSeq&);

typedef ::std::vector< ::IceGrid::ServiceDescriptorPtr> ServiceDescriptorSeq;
ICE_GRID_API void __writeServiceDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ServiceDescriptorPtr*, const ::IceGrid::ServiceDescriptorPtr*);
ICE_GRID_API void __readServiceDescriptorSeq(::IceInternal::BasicStream*, ServiceDescriptorSeq&);

struct ServerInstanceDescriptor
{
    ::std::string _cpp_template;
    ::IceGrid::StringStringDict parameterValues;
    ::IceGrid::PropertySetDescriptor propertySet;
    ::IceGrid::PropertySetDescriptorDict servicePropertySets;

    ICE_GRID_API bool operator==(const ServerInstanceDescriptor&) const;
    ICE_GRID_API bool operator<(const ServerInstanceDescriptor&) const;
    bool operator!=(const ServerInstanceDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ServerInstanceDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ServerInstanceDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ServerInstanceDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ServerInstanceDescriptor> ServerInstanceDescriptorSeq;
ICE_GRID_API void __writeServerInstanceDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ServerInstanceDescriptor*, const ::IceGrid::ServerInstanceDescriptor*);
ICE_GRID_API void __readServerInstanceDescriptorSeq(::IceInternal::BasicStream*, ServerInstanceDescriptorSeq&);

struct TemplateDescriptor
{
    ::IceGrid::CommunicatorDescriptorPtr descriptor;
    ::Ice::StringSeq parameters;
    ::IceGrid::StringStringDict parameterDefaults;

    ICE_GRID_API bool operator==(const TemplateDescriptor&) const;
    ICE_GRID_API bool operator<(const TemplateDescriptor&) const;
    bool operator!=(const TemplateDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const TemplateDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const TemplateDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const TemplateDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::map< ::std::string, ::IceGrid::TemplateDescriptor> TemplateDescriptorDict;
ICE_GRID_API void __writeTemplateDescriptorDict(::IceInternal::BasicStream*, const TemplateDescriptorDict&);
ICE_GRID_API void __readTemplateDescriptorDict(::IceInternal::BasicStream*, TemplateDescriptorDict&);

struct ServiceInstanceDescriptor
{
    ::std::string _cpp_template;
    ::IceGrid::StringStringDict parameterValues;
    ::IceGrid::ServiceDescriptorPtr descriptor;
    ::IceGrid::PropertySetDescriptor propertySet;

    ICE_GRID_API bool operator==(const ServiceInstanceDescriptor&) const;
    ICE_GRID_API bool operator<(const ServiceInstanceDescriptor&) const;
    bool operator!=(const ServiceInstanceDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ServiceInstanceDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ServiceInstanceDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ServiceInstanceDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ServiceInstanceDescriptor> ServiceInstanceDescriptorSeq;
ICE_GRID_API void __writeServiceInstanceDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ServiceInstanceDescriptor*, const ::IceGrid::ServiceInstanceDescriptor*);
ICE_GRID_API void __readServiceInstanceDescriptorSeq(::IceInternal::BasicStream*, ServiceInstanceDescriptorSeq&);

struct NodeDescriptor
{
    ::IceGrid::StringStringDict variables;
    ::IceGrid::ServerInstanceDescriptorSeq serverInstances;
    ::IceGrid::ServerDescriptorSeq servers;
    ::std::string loadFactor;
    ::std::string description;
    ::IceGrid::PropertySetDescriptorDict propertySets;

    ICE_GRID_API bool operator==(const NodeDescriptor&) const;
    ICE_GRID_API bool operator<(const NodeDescriptor&) const;
    bool operator!=(const NodeDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const NodeDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const NodeDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const NodeDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::map< ::std::string, ::IceGrid::NodeDescriptor> NodeDescriptorDict;
ICE_GRID_API void __writeNodeDescriptorDict(::IceInternal::BasicStream*, const NodeDescriptorDict&);
ICE_GRID_API void __readNodeDescriptorDict(::IceInternal::BasicStream*, NodeDescriptorDict&);

struct ReplicaGroupDescriptor
{
    ::std::string id;
    ::IceGrid::LoadBalancingPolicyPtr loadBalancing;
    ::IceGrid::ObjectDescriptorSeq objects;
    ::std::string description;

    ICE_GRID_API bool operator==(const ReplicaGroupDescriptor&) const;
    ICE_GRID_API bool operator<(const ReplicaGroupDescriptor&) const;
    bool operator!=(const ReplicaGroupDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ReplicaGroupDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ReplicaGroupDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ReplicaGroupDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ReplicaGroupDescriptor> ReplicaGroupDescriptorSeq;
ICE_GRID_API void __writeReplicaGroupDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ReplicaGroupDescriptor*, const ::IceGrid::ReplicaGroupDescriptor*);
ICE_GRID_API void __readReplicaGroupDescriptorSeq(::IceInternal::BasicStream*, ReplicaGroupDescriptorSeq&);

struct ApplicationDescriptor
{
    ::std::string name;
    ::IceGrid::StringStringDict variables;
    ::IceGrid::ReplicaGroupDescriptorSeq replicaGroups;
    ::IceGrid::TemplateDescriptorDict serverTemplates;
    ::IceGrid::TemplateDescriptorDict serviceTemplates;
    ::IceGrid::NodeDescriptorDict nodes;
    ::IceGrid::DistributionDescriptor distrib;
    ::std::string description;
    ::IceGrid::PropertySetDescriptorDict propertySets;

    ICE_GRID_API bool operator==(const ApplicationDescriptor&) const;
    ICE_GRID_API bool operator<(const ApplicationDescriptor&) const;
    bool operator!=(const ApplicationDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ApplicationDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ApplicationDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ApplicationDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::ApplicationDescriptor> ApplicationDescriptorSeq;
ICE_GRID_API void __writeApplicationDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::ApplicationDescriptor*, const ::IceGrid::ApplicationDescriptor*);
ICE_GRID_API void __readApplicationDescriptorSeq(::IceInternal::BasicStream*, ApplicationDescriptorSeq&);

struct NodeUpdateDescriptor
{
    ::std::string name;
    ::IceGrid::BoxedStringPtr description;
    ::IceGrid::StringStringDict variables;
    ::Ice::StringSeq removeVariables;
    ::IceGrid::PropertySetDescriptorDict propertySets;
    ::Ice::StringSeq removePropertySets;
    ::IceGrid::ServerInstanceDescriptorSeq serverInstances;
    ::IceGrid::ServerDescriptorSeq servers;
    ::Ice::StringSeq removeServers;
    ::IceGrid::BoxedStringPtr loadFactor;

    ICE_GRID_API bool operator==(const NodeUpdateDescriptor&) const;
    ICE_GRID_API bool operator<(const NodeUpdateDescriptor&) const;
    bool operator!=(const NodeUpdateDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const NodeUpdateDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const NodeUpdateDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const NodeUpdateDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IceGrid::NodeUpdateDescriptor> NodeUpdateDescriptorSeq;
ICE_GRID_API void __writeNodeUpdateDescriptorSeq(::IceInternal::BasicStream*, const ::IceGrid::NodeUpdateDescriptor*, const ::IceGrid::NodeUpdateDescriptor*);
ICE_GRID_API void __readNodeUpdateDescriptorSeq(::IceInternal::BasicStream*, NodeUpdateDescriptorSeq&);

struct ApplicationUpdateDescriptor
{
    ::std::string name;
    ::IceGrid::BoxedStringPtr description;
    ::IceGrid::BoxedDistributionDescriptorPtr distrib;
    ::IceGrid::StringStringDict variables;
    ::Ice::StringSeq removeVariables;
    ::IceGrid::PropertySetDescriptorDict propertySets;
    ::Ice::StringSeq removePropertySets;
    ::IceGrid::ReplicaGroupDescriptorSeq replicaGroups;
    ::Ice::StringSeq removeReplicaGroups;
    ::IceGrid::TemplateDescriptorDict serverTemplates;
    ::Ice::StringSeq removeServerTemplates;
    ::IceGrid::TemplateDescriptorDict serviceTemplates;
    ::Ice::StringSeq removeServiceTemplates;
    ::IceGrid::NodeUpdateDescriptorSeq nodes;
    ::Ice::StringSeq removeNodes;

    ICE_GRID_API bool operator==(const ApplicationUpdateDescriptor&) const;
    ICE_GRID_API bool operator<(const ApplicationUpdateDescriptor&) const;
    bool operator!=(const ApplicationUpdateDescriptor& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const ApplicationUpdateDescriptor& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const ApplicationUpdateDescriptor& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const ApplicationUpdateDescriptor& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_GRID_API void __write(::IceInternal::BasicStream*) const;
    ICE_GRID_API void __read(::IceInternal::BasicStream*);
};

}

namespace IceProxy
{

namespace IceGrid
{

class CommunicatorDescriptor : virtual public ::IceProxy::Ice::Object
{
public:
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<CommunicatorDescriptor> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<CommunicatorDescriptor*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<CommunicatorDescriptor*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class ServerDescriptor : virtual public ::IceProxy::IceGrid::CommunicatorDescriptor
{
public:
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServerDescriptor> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServerDescriptor*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ServerDescriptor*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class ServiceDescriptor : virtual public ::IceProxy::IceGrid::CommunicatorDescriptor
{
public:
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ServiceDescriptor> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ServiceDescriptor*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ServiceDescriptor*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class IceBoxDescriptor : virtual public ::IceProxy::IceGrid::ServerDescriptor
{
public:
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<IceBoxDescriptor> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<IceBoxDescriptor*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<IceBoxDescriptor*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class LoadBalancingPolicy : virtual public ::IceProxy::Ice::Object
{
public:
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<LoadBalancingPolicy> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<LoadBalancingPolicy*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<LoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class RandomLoadBalancingPolicy : virtual public ::IceProxy::IceGrid::LoadBalancingPolicy
{
public:
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RandomLoadBalancingPolicy> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RandomLoadBalancingPolicy*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<RandomLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class OrderedLoadBalancingPolicy : virtual public ::IceProxy::IceGrid::LoadBalancingPolicy
{
public:
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<OrderedLoadBalancingPolicy> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<OrderedLoadBalancingPolicy*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<OrderedLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class RoundRobinLoadBalancingPolicy : virtual public ::IceProxy::IceGrid::LoadBalancingPolicy
{
public:
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<RoundRobinLoadBalancingPolicy> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<RoundRobinLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class AdaptiveLoadBalancingPolicy : virtual public ::IceProxy::IceGrid::LoadBalancingPolicy
{
public:
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<AdaptiveLoadBalancingPolicy> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<AdaptiveLoadBalancingPolicy*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class BoxedString : virtual public ::IceProxy::Ice::Object
{
public:
    
    ::IceInternal::ProxyHandle<BoxedString> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedString> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedString*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<BoxedString*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_GRID_API static const ::std::string& ice_staticId();

private: 

    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_GRID_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_GRID_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

class BoxedDistributionDescriptor : virtual public ::IceProxy::Ice::Object
{
public:
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<BoxedDistributionDescriptor> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<BoxedDistributionDescriptor*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<BoxedDistributionDescriptor*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
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

class ICE_GRID_API CommunicatorDescriptor : virtual public ::IceDelegate::Ice::Object
{
public:
};

class ICE_GRID_API ServerDescriptor : virtual public ::IceDelegate::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API ServiceDescriptor : virtual public ::IceDelegate::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API IceBoxDescriptor : virtual public ::IceDelegate::IceGrid::ServerDescriptor
{
public:
};

class ICE_GRID_API LoadBalancingPolicy : virtual public ::IceDelegate::Ice::Object
{
public:
};

class ICE_GRID_API RandomLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API OrderedLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API RoundRobinLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API AdaptiveLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API BoxedString : virtual public ::IceDelegate::Ice::Object
{
public:
};

class ICE_GRID_API BoxedDistributionDescriptor : virtual public ::IceDelegate::Ice::Object
{
public:
};

}

}

namespace IceDelegateM
{

namespace IceGrid
{

class ICE_GRID_API CommunicatorDescriptor : virtual public ::IceDelegate::IceGrid::CommunicatorDescriptor,
                                            virtual public ::IceDelegateM::Ice::Object
{
public:
};

class ICE_GRID_API ServerDescriptor : virtual public ::IceDelegate::IceGrid::ServerDescriptor,
                                      virtual public ::IceDelegateM::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API ServiceDescriptor : virtual public ::IceDelegate::IceGrid::ServiceDescriptor,
                                       virtual public ::IceDelegateM::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API IceBoxDescriptor : virtual public ::IceDelegate::IceGrid::IceBoxDescriptor,
                                      virtual public ::IceDelegateM::IceGrid::ServerDescriptor
{
public:
};

class ICE_GRID_API LoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy,
                                         virtual public ::IceDelegateM::Ice::Object
{
public:
};

class ICE_GRID_API RandomLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::RandomLoadBalancingPolicy,
                                               virtual public ::IceDelegateM::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API OrderedLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::OrderedLoadBalancingPolicy,
                                                virtual public ::IceDelegateM::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API RoundRobinLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::RoundRobinLoadBalancingPolicy,
                                                   virtual public ::IceDelegateM::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API AdaptiveLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::AdaptiveLoadBalancingPolicy,
                                                 virtual public ::IceDelegateM::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API BoxedString : virtual public ::IceDelegate::IceGrid::BoxedString,
                                 virtual public ::IceDelegateM::Ice::Object
{
public:
};

class ICE_GRID_API BoxedDistributionDescriptor : virtual public ::IceDelegate::IceGrid::BoxedDistributionDescriptor,
                                                 virtual public ::IceDelegateM::Ice::Object
{
public:
};

}

}

namespace IceDelegateD
{

namespace IceGrid
{

class ICE_GRID_API CommunicatorDescriptor : virtual public ::IceDelegate::IceGrid::CommunicatorDescriptor,
                                            virtual public ::IceDelegateD::Ice::Object
{
public:
};

class ICE_GRID_API ServerDescriptor : virtual public ::IceDelegate::IceGrid::ServerDescriptor,
                                      virtual public ::IceDelegateD::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API ServiceDescriptor : virtual public ::IceDelegate::IceGrid::ServiceDescriptor,
                                       virtual public ::IceDelegateD::IceGrid::CommunicatorDescriptor
{
public:
};

class ICE_GRID_API IceBoxDescriptor : virtual public ::IceDelegate::IceGrid::IceBoxDescriptor,
                                      virtual public ::IceDelegateD::IceGrid::ServerDescriptor
{
public:
};

class ICE_GRID_API LoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::LoadBalancingPolicy,
                                         virtual public ::IceDelegateD::Ice::Object
{
public:
};

class ICE_GRID_API RandomLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::RandomLoadBalancingPolicy,
                                               virtual public ::IceDelegateD::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API OrderedLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::OrderedLoadBalancingPolicy,
                                                virtual public ::IceDelegateD::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API RoundRobinLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::RoundRobinLoadBalancingPolicy,
                                                   virtual public ::IceDelegateD::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API AdaptiveLoadBalancingPolicy : virtual public ::IceDelegate::IceGrid::AdaptiveLoadBalancingPolicy,
                                                 virtual public ::IceDelegateD::IceGrid::LoadBalancingPolicy
{
public:
};

class ICE_GRID_API BoxedString : virtual public ::IceDelegate::IceGrid::BoxedString,
                                 virtual public ::IceDelegateD::Ice::Object
{
public:
};

class ICE_GRID_API BoxedDistributionDescriptor : virtual public ::IceDelegate::IceGrid::BoxedDistributionDescriptor,
                                                 virtual public ::IceDelegateD::Ice::Object
{
public:
};

}

}

namespace IceGrid
{

class ICE_GRID_API CommunicatorDescriptor : virtual public ::Ice::Object
{
public:

    typedef CommunicatorDescriptorPrx ProxyType;
    typedef CommunicatorDescriptorPtr PointerType;
    
    CommunicatorDescriptor() {}
    CommunicatorDescriptor(const ::IceGrid::AdapterDescriptorSeq&, const ::IceGrid::PropertySetDescriptor&, const ::IceGrid::DbEnvDescriptorSeq&, const ::Ice::StringSeq&, const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~CommunicatorDescriptor() {}

    friend class CommunicatorDescriptor__staticInit;

public:

    ::IceGrid::AdapterDescriptorSeq adapters;

    ::IceGrid::PropertySetDescriptor propertySet;

    ::IceGrid::DbEnvDescriptorSeq dbEnvs;

    ::Ice::StringSeq logs;

    ::std::string description;
};

class CommunicatorDescriptor__staticInit
{
public:

    ::IceGrid::CommunicatorDescriptor _init;
};

static CommunicatorDescriptor__staticInit _CommunicatorDescriptor_init;

class ICE_GRID_API ServerDescriptor : virtual public ::IceGrid::CommunicatorDescriptor
{
public:

    typedef ServerDescriptorPrx ProxyType;
    typedef ServerDescriptorPtr PointerType;
    
    ServerDescriptor() {}
    ServerDescriptor(const ::IceGrid::AdapterDescriptorSeq&, const ::IceGrid::PropertySetDescriptor&, const ::IceGrid::DbEnvDescriptorSeq&, const ::Ice::StringSeq&, const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::StringSeq&, const ::Ice::StringSeq&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::IceGrid::DistributionDescriptor&, bool, const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~ServerDescriptor() {}

public:

    ::std::string id;

    ::std::string exe;

    ::std::string iceVersion;

    ::std::string pwd;

    ::Ice::StringSeq options;

    ::Ice::StringSeq envs;

    ::std::string activation;

    ::std::string activationTimeout;

    ::std::string deactivationTimeout;

    bool applicationDistrib;

    ::IceGrid::DistributionDescriptor distrib;

    bool allocatable;

    ::std::string user;
};

class ICE_GRID_API ServiceDescriptor : virtual public ::IceGrid::CommunicatorDescriptor
{
public:

    typedef ServiceDescriptorPrx ProxyType;
    typedef ServiceDescriptorPtr PointerType;
    
    ServiceDescriptor() {}
    ServiceDescriptor(const ::IceGrid::AdapterDescriptorSeq&, const ::IceGrid::PropertySetDescriptor&, const ::IceGrid::DbEnvDescriptorSeq&, const ::Ice::StringSeq&, const ::std::string&, const ::std::string&, const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~ServiceDescriptor() {}

public:

    ::std::string name;

    ::std::string entry;
};

class ICE_GRID_API IceBoxDescriptor : virtual public ::IceGrid::ServerDescriptor
{
public:

    typedef IceBoxDescriptorPrx ProxyType;
    typedef IceBoxDescriptorPtr PointerType;
    
    IceBoxDescriptor() {}
    IceBoxDescriptor(const ::IceGrid::AdapterDescriptorSeq&, const ::IceGrid::PropertySetDescriptor&, const ::IceGrid::DbEnvDescriptorSeq&, const ::Ice::StringSeq&, const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::StringSeq&, const ::Ice::StringSeq&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::IceGrid::DistributionDescriptor&, bool, const ::std::string&, const ::IceGrid::ServiceInstanceDescriptorSeq&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void __incRef();
    virtual void __decRef();
    virtual void __addObject(::IceInternal::GCCountMap&);
    virtual bool __usesClasses();
    virtual void __gcReachable(::IceInternal::GCCountMap&) const;
    virtual void __gcClear();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~IceBoxDescriptor() {}

public:

    ::IceGrid::ServiceInstanceDescriptorSeq services;
};

class ICE_GRID_API LoadBalancingPolicy : virtual public ::Ice::Object
{
public:

    typedef LoadBalancingPolicyPrx ProxyType;
    typedef LoadBalancingPolicyPtr PointerType;
    
    LoadBalancingPolicy() {}
    explicit LoadBalancingPolicy(const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~LoadBalancingPolicy() {}

public:

    ::std::string nReplicas;
};

class ICE_GRID_API RandomLoadBalancingPolicy : virtual public ::IceGrid::LoadBalancingPolicy
{
public:

    typedef RandomLoadBalancingPolicyPrx ProxyType;
    typedef RandomLoadBalancingPolicyPtr PointerType;
    
    RandomLoadBalancingPolicy() {}
    explicit RandomLoadBalancingPolicy(const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~RandomLoadBalancingPolicy() {}
};

class ICE_GRID_API OrderedLoadBalancingPolicy : virtual public ::IceGrid::LoadBalancingPolicy
{
public:

    typedef OrderedLoadBalancingPolicyPrx ProxyType;
    typedef OrderedLoadBalancingPolicyPtr PointerType;
    
    OrderedLoadBalancingPolicy() {}
    explicit OrderedLoadBalancingPolicy(const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~OrderedLoadBalancingPolicy() {}
};

class ICE_GRID_API RoundRobinLoadBalancingPolicy : virtual public ::IceGrid::LoadBalancingPolicy
{
public:

    typedef RoundRobinLoadBalancingPolicyPrx ProxyType;
    typedef RoundRobinLoadBalancingPolicyPtr PointerType;
    
    RoundRobinLoadBalancingPolicy() {}
    explicit RoundRobinLoadBalancingPolicy(const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~RoundRobinLoadBalancingPolicy() {}
};

class ICE_GRID_API AdaptiveLoadBalancingPolicy : virtual public ::IceGrid::LoadBalancingPolicy
{
public:

    typedef AdaptiveLoadBalancingPolicyPrx ProxyType;
    typedef AdaptiveLoadBalancingPolicyPtr PointerType;
    
    AdaptiveLoadBalancingPolicy() {}
    AdaptiveLoadBalancingPolicy(const ::std::string&, const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~AdaptiveLoadBalancingPolicy() {}

public:

    ::std::string loadSample;
};

class ICE_GRID_API BoxedString : virtual public ::Ice::Object
{
public:

    typedef BoxedStringPrx ProxyType;
    typedef BoxedStringPtr PointerType;
    
    BoxedString() {}
    explicit BoxedString(const ::std::string&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~BoxedString() {}

public:

    ::std::string value;
};

class ICE_GRID_API BoxedDistributionDescriptor : virtual public ::Ice::Object
{
public:

    typedef BoxedDistributionDescriptorPrx ProxyType;
    typedef BoxedDistributionDescriptorPtr PointerType;
    
    BoxedDistributionDescriptor() {}
    explicit BoxedDistributionDescriptor(const ::IceGrid::DistributionDescriptor&);
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();


    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);

    static const ::Ice::ObjectFactoryPtr& ice_factory();

protected:

    virtual ~BoxedDistributionDescriptor() {}

public:

    ::IceGrid::DistributionDescriptor value;
};

}

#endif

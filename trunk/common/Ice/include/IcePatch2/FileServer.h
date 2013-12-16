// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `FileServer.ice'

#ifndef __IcePatch2_FileServer_h__
#define __IcePatch2_FileServer_h__

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
#include <IcePatch2/FileInfo.h>
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

#ifndef ICE_PATCH2_API
#   ifdef ICE_PATCH2_API_EXPORTS
#       define ICE_PATCH2_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_PATCH2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

namespace IcePatch2
{

class FileServer;

class Admin;

}

}

namespace IcePatch2
{

class FileServer;
ICE_PATCH2_API bool operator==(const FileServer&, const FileServer&);
ICE_PATCH2_API bool operator<(const FileServer&, const FileServer&);

class Admin;
ICE_PATCH2_API bool operator==(const Admin&, const Admin&);
ICE_PATCH2_API bool operator<(const Admin&, const Admin&);

}

namespace IceInternal
{

ICE_PATCH2_API ::Ice::Object* upCast(::IcePatch2::FileServer*);
ICE_PATCH2_API ::IceProxy::Ice::Object* upCast(::IceProxy::IcePatch2::FileServer*);

ICE_PATCH2_API ::Ice::Object* upCast(::IcePatch2::Admin*);
ICE_PATCH2_API ::IceProxy::Ice::Object* upCast(::IceProxy::IcePatch2::Admin*);

}

namespace IcePatch2
{

typedef ::IceInternal::Handle< ::IcePatch2::FileServer> FileServerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IcePatch2::FileServer> FileServerPrx;

ICE_PATCH2_API void __read(::IceInternal::BasicStream*, FileServerPrx&);
ICE_PATCH2_API void __patch__FileServerPtr(void*, ::Ice::ObjectPtr&);

typedef ::IceInternal::Handle< ::IcePatch2::Admin> AdminPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IcePatch2::Admin> AdminPrx;

ICE_PATCH2_API void __read(::IceInternal::BasicStream*, AdminPrx&);
ICE_PATCH2_API void __patch__AdminPtr(void*, ::Ice::ObjectPtr&);

}

namespace IcePatch2
{

typedef ::std::vector< ::Ice::ByteSeq> ByteSeqSeq;
ICE_PATCH2_API void __writeByteSeqSeq(::IceInternal::BasicStream*, const ::Ice::ByteSeq*, const ::Ice::ByteSeq*);
ICE_PATCH2_API void __readByteSeqSeq(::IceInternal::BasicStream*, ByteSeqSeq&);

class ICE_PATCH2_API PartitionOutOfRangeException : public ::Ice::UserException
{
public:

    PartitionOutOfRangeException() {}
    virtual ~PartitionOutOfRangeException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static PartitionOutOfRangeException __PartitionOutOfRangeException_init;

class ICE_PATCH2_API FileAccessException : public ::Ice::UserException
{
public:

    FileAccessException() {}
    explicit FileAccessException(const ::std::string&);
    virtual ~FileAccessException() throw();

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

}

namespace IcePatch2
{

class ICE_PATCH2_API AMI_FileServer_getFileInfoSeq : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::IcePatch2::FileInfoSeq&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IcePatch2::FileServerPrx&, ::Ice::Int, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IcePatch2::AMI_FileServer_getFileInfoSeq> AMI_FileServer_getFileInfoSeqPtr;

class ICE_PATCH2_API AMI_FileServer_getFileCompressed : public ::IceInternal::OutgoingAsync
{
public:

    virtual void ice_response(const ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*>&) = 0;
    virtual void ice_exception(const ::Ice::Exception&) = 0;

    bool __invoke(const ::IcePatch2::FileServerPrx&, const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);

protected:

    virtual void __response(bool);
};

typedef ::IceUtil::Handle< ::IcePatch2::AMI_FileServer_getFileCompressed> AMI_FileServer_getFileCompressedPtr;

class ICE_PATCH2_API AMD_FileServer_getFileCompressed : virtual public ::IceUtil::Shared
{
public:

    virtual void ice_response(const ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*>&) = 0;
    virtual void ice_exception(const ::std::exception&) = 0;
    virtual void ice_exception() = 0;
};

typedef ::IceUtil::Handle< ::IcePatch2::AMD_FileServer_getFileCompressed> AMD_FileServer_getFileCompressedPtr;

}

namespace IceAsync
{

namespace IcePatch2
{

class ICE_PATCH2_API AMD_FileServer_getFileCompressed : public ::IcePatch2::AMD_FileServer_getFileCompressed, public ::IceInternal::IncomingAsync
{
public:

    AMD_FileServer_getFileCompressed(::IceInternal::Incoming&);

    virtual void ice_response(const ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*>&);
    virtual void ice_exception(const ::std::exception&);
    virtual void ice_exception();
};

}

}

namespace IceProxy
{

namespace IcePatch2
{

class FileServer : virtual public ::IceProxy::Ice::Object
{
public:

    ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int partition)
    {
        return getFileInfoSeq(partition, 0);
    }
    ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int partition, const ::Ice::Context& __ctx)
    {
        return getFileInfoSeq(partition, &__ctx);
    }
    
private:

    ICE_PATCH2_API ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int, const ::Ice::Context*);
    
public:
    ICE_PATCH2_API bool getFileInfoSeq_async(const ::IcePatch2::AMI_FileServer_getFileInfoSeqPtr&, ::Ice::Int);
    ICE_PATCH2_API bool getFileInfoSeq_async(const ::IcePatch2::AMI_FileServer_getFileInfoSeqPtr&, ::Ice::Int, const ::Ice::Context&);

    ::IcePatch2::ByteSeqSeq getChecksumSeq()
    {
        return getChecksumSeq(0);
    }
    ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Context& __ctx)
    {
        return getChecksumSeq(&__ctx);
    }
    
private:

    ICE_PATCH2_API ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Context*);
    
public:

    ::Ice::ByteSeq getChecksum()
    {
        return getChecksum(0);
    }
    ::Ice::ByteSeq getChecksum(const ::Ice::Context& __ctx)
    {
        return getChecksum(&__ctx);
    }
    
private:

    ICE_PATCH2_API ::Ice::ByteSeq getChecksum(const ::Ice::Context*);
    
public:

    ::Ice::ByteSeq getFileCompressed(const ::std::string& path, ::Ice::Int pos, ::Ice::Int num)
    {
        return getFileCompressed(path, pos, num, 0);
    }
    ::Ice::ByteSeq getFileCompressed(const ::std::string& path, ::Ice::Int pos, ::Ice::Int num, const ::Ice::Context& __ctx)
    {
        return getFileCompressed(path, pos, num, &__ctx);
    }
    
private:

    ICE_PATCH2_API ::Ice::ByteSeq getFileCompressed(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
    
public:
    ICE_PATCH2_API bool getFileCompressed_async(const ::IcePatch2::AMI_FileServer_getFileCompressedPtr&, const ::std::string&, ::Ice::Int, ::Ice::Int);
    ICE_PATCH2_API bool getFileCompressed_async(const ::IcePatch2::AMI_FileServer_getFileCompressedPtr&, const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);
    
    ::IceInternal::ProxyHandle<FileServer> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<FileServer> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<FileServer*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<FileServer*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    ICE_PATCH2_API static const ::std::string& ice_staticId();

private: 

    ICE_PATCH2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_PATCH2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_PATCH2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

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

    ICE_PATCH2_API void shutdown(const ::Ice::Context*);
    
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
    
    ICE_PATCH2_API static const ::std::string& ice_staticId();

private: 

    ICE_PATCH2_API virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    ICE_PATCH2_API virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    ICE_PATCH2_API virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace IcePatch2
{

class ICE_PATCH2_API FileServer : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Context*) = 0;

    virtual ::Ice::ByteSeq getChecksum(const ::Ice::Context*) = 0;

    virtual ::Ice::ByteSeq getFileCompressed(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*) = 0;
};

class ICE_PATCH2_API Admin : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace IcePatch2
{

class ICE_PATCH2_API FileServer : virtual public ::IceDelegate::IcePatch2::FileServer,
                                  virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int, const ::Ice::Context*);

    virtual ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Context*);

    virtual ::Ice::ByteSeq getChecksum(const ::Ice::Context*);

    virtual ::Ice::ByteSeq getFileCompressed(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
};

class ICE_PATCH2_API Admin : virtual public ::IceDelegate::IcePatch2::Admin,
                             virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace IcePatch2
{

class ICE_PATCH2_API FileServer : virtual public ::IceDelegate::IcePatch2::FileServer,
                                  virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int, const ::Ice::Context*);

    virtual ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Context*);

    virtual ::Ice::ByteSeq getChecksum(const ::Ice::Context*);

    virtual ::Ice::ByteSeq getFileCompressed(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context*);
};

class ICE_PATCH2_API Admin : virtual public ::IceDelegate::IcePatch2::Admin,
                             virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void shutdown(const ::Ice::Context*);
};

}

}

namespace IcePatch2
{

class ICE_PATCH2_API FileServer : virtual public ::Ice::Object
{
public:

    typedef FileServerPrx ProxyType;
    typedef FileServerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::IcePatch2::FileInfoSeq getFileInfoSeq(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getFileInfoSeq(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::IcePatch2::ByteSeqSeq getChecksumSeq(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getChecksumSeq(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::ByteSeq getChecksum(const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getChecksum(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual void getFileCompressed_async(const ::IcePatch2::AMD_FileServer_getFileCompressedPtr&, const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) const = 0;
    ::Ice::DispatchStatus ___getFileCompressed(::IceInternal::Incoming&, const ::Ice::Current&) const;

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class ICE_PATCH2_API Admin : virtual public ::Ice::Object
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

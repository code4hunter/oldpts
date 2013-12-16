// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `FileInfo.ice'

#ifndef __IcePatch2_FileInfo_h__
#define __IcePatch2_FileInfo_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
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

#ifndef ICE_PATCH2_API
#   ifdef ICE_PATCH2_API_EXPORTS
#       define ICE_PATCH2_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_PATCH2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IcePatch2
{

struct FileInfo
{
    ::std::string path;
    ::Ice::ByteSeq checksum;
    ::Ice::Int size;
    bool executable;

    ICE_PATCH2_API bool operator==(const FileInfo&) const;
    ICE_PATCH2_API bool operator<(const FileInfo&) const;
    bool operator!=(const FileInfo& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const FileInfo& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const FileInfo& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const FileInfo& __rhs) const
    {
        return !operator<(__rhs);
    }

    ICE_PATCH2_API void __write(::IceInternal::BasicStream*) const;
    ICE_PATCH2_API void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::IcePatch2::FileInfo> FileInfoSeq;
ICE_PATCH2_API void __writeFileInfoSeq(::IceInternal::BasicStream*, const ::IcePatch2::FileInfo*, const ::IcePatch2::FileInfo*);
ICE_PATCH2_API void __readFileInfoSeq(::IceInternal::BasicStream*, FileInfoSeq&);

}

#endif

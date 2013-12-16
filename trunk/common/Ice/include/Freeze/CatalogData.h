// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `CatalogData.ice'

#ifndef __Freeze_CatalogData_h__
#define __Freeze_CatalogData_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
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

#ifndef FREEZE_API
#   ifdef FREEZE_API_EXPORTS
#       define FREEZE_API ICE_DECLSPEC_EXPORT
#   else
#       define FREEZE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace Freeze
{

struct CatalogData
{
    bool evictor;
    ::std::string key;
    ::std::string value;

    FREEZE_API bool operator==(const CatalogData&) const;
    FREEZE_API bool operator<(const CatalogData&) const;
    bool operator!=(const CatalogData& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const CatalogData& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const CatalogData& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const CatalogData& __rhs) const
    {
        return !operator<(__rhs);
    }

    FREEZE_API void __write(::IceInternal::BasicStream*) const;
    FREEZE_API void __read(::IceInternal::BasicStream*);
};

}

#endif

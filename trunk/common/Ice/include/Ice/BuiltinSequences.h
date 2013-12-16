// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `BuiltinSequences.ice'

#ifndef __Ice_BuiltinSequences_h__
#define __Ice_BuiltinSequences_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
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

namespace Ice
{

typedef ::std::vector<bool> BoolSeq;

typedef ::std::vector< ::Ice::Byte> ByteSeq;

typedef ::std::vector< ::Ice::Short> ShortSeq;

typedef ::std::vector< ::Ice::Int> IntSeq;

typedef ::std::vector< ::Ice::Long> LongSeq;

typedef ::std::vector< ::Ice::Float> FloatSeq;

typedef ::std::vector< ::Ice::Double> DoubleSeq;

typedef ::std::vector< ::std::string> StringSeq;

typedef ::std::vector< ::Ice::ObjectPtr> ObjectSeq;
ICE_API void __writeObjectSeq(::IceInternal::BasicStream*, const ::Ice::ObjectPtr*, const ::Ice::ObjectPtr*);
ICE_API void __readObjectSeq(::IceInternal::BasicStream*, ObjectSeq&);
ICE_API void ice_writeObjectSeq(const ::Ice::OutputStreamPtr&, const ObjectSeq&);
ICE_API void ice_readObjectSeq(const ::Ice::InputStreamPtr&, ObjectSeq&);

typedef ::std::vector< ::Ice::ObjectPrx> ObjectProxySeq;
ICE_API void __writeObjectProxySeq(::IceInternal::BasicStream*, const ::Ice::ObjectPrx*, const ::Ice::ObjectPrx*);
ICE_API void __readObjectProxySeq(::IceInternal::BasicStream*, ObjectProxySeq&);
ICE_API void ice_writeObjectProxySeq(const ::Ice::OutputStreamPtr&, const ObjectProxySeq&);
ICE_API void ice_readObjectProxySeq(const ::Ice::InputStreamPtr&, ObjectProxySeq&);

}

#endif

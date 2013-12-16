// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `TransactionalEvictor.ice'

#ifndef __Freeze_TransactionalEvictor_h__
#define __Freeze_TransactionalEvictor_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Freeze/Evictor.h>
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

class Transaction;
FREEZE_API bool operator==(const Transaction&, const Transaction&);
FREEZE_API bool operator<(const Transaction&, const Transaction&);

class TransactionalEvictor;
FREEZE_API bool operator==(const TransactionalEvictor&, const TransactionalEvictor&);
FREEZE_API bool operator<(const TransactionalEvictor&, const TransactionalEvictor&);

}

namespace IceInternal
{

FREEZE_API ::Ice::LocalObject* upCast(::Freeze::Transaction*);

FREEZE_API ::Ice::LocalObject* upCast(::Freeze::TransactionalEvictor*);

}

namespace Freeze
{

typedef ::IceInternal::Handle< ::Freeze::Transaction> TransactionPtr;

typedef ::IceInternal::Handle< ::Freeze::TransactionalEvictor> TransactionalEvictorPtr;

}

namespace Freeze
{

class FREEZE_API TransactionalEvictor : virtual public ::Freeze::Evictor
{
public:

    typedef TransactionalEvictorPtr PointerType;
    

    virtual ::Freeze::TransactionPtr getCurrentTransaction() const = 0;

    virtual void setCurrentTransaction(const ::Freeze::TransactionPtr&) = 0;
};

}

#endif

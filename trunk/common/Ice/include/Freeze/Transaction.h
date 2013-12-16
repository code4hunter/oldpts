// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Transaction.ice'

#ifndef __Freeze_Transaction_h__
#define __Freeze_Transaction_h__

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

class Connection;
FREEZE_API bool operator==(const Connection&, const Connection&);
FREEZE_API bool operator<(const Connection&, const Connection&);

class Transaction;
FREEZE_API bool operator==(const Transaction&, const Transaction&);
FREEZE_API bool operator<(const Transaction&, const Transaction&);

}

namespace IceInternal
{

FREEZE_API ::Ice::LocalObject* upCast(::Freeze::Connection*);

FREEZE_API ::Ice::LocalObject* upCast(::Freeze::Transaction*);

}

namespace Freeze
{

typedef ::IceInternal::Handle< ::Freeze::Connection> ConnectionPtr;

typedef ::IceInternal::Handle< ::Freeze::Transaction> TransactionPtr;

}

namespace Freeze
{

class FREEZE_API Transaction : virtual public ::Ice::LocalObject
{
public:

    typedef TransactionPtr PointerType;
    

    virtual void commit() = 0;

    virtual void rollback() = 0;

    virtual ::Freeze::ConnectionPtr getConnection() const = 0;
};

}

#endif

// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Exception.ice'

#ifndef __Freeze_Exception_h__
#define __Freeze_Exception_h__

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

class Transaction;
FREEZE_API bool operator==(const Transaction&, const Transaction&);
FREEZE_API bool operator<(const Transaction&, const Transaction&);

}

namespace IceInternal
{

FREEZE_API ::Ice::LocalObject* upCast(::Freeze::Transaction*);

}

namespace Freeze
{

typedef ::IceInternal::Handle< ::Freeze::Transaction> TransactionPtr;

}

namespace Freeze
{

class FREEZE_API DatabaseException : public ::Ice::LocalException
{
public:

    DatabaseException(const char*, int);
    DatabaseException(const char*, int, const ::std::string&);
    virtual ~DatabaseException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    ::std::string message;
};

class FREEZE_API NotFoundException : public ::Freeze::DatabaseException
{
public:

    NotFoundException(const char*, int);
    NotFoundException(const char*, int, const ::std::string&);
    virtual ~NotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;
};

class FREEZE_API DeadlockException : public ::Freeze::DatabaseException
{
public:

    DeadlockException(const char*, int);
    DeadlockException(const char*, int, const ::std::string&, const ::Freeze::TransactionPtr&);
    virtual ~DeadlockException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    ::Freeze::TransactionPtr tx;
};

class FREEZE_API InvalidPositionException : public ::Ice::LocalException
{
public:

    InvalidPositionException(const char*, int);
    virtual ~InvalidPositionException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;
};

class FREEZE_API IndexNotFoundException : public ::Ice::LocalException
{
public:

    IndexNotFoundException(const char*, int);
    IndexNotFoundException(const char*, int, const ::std::string&, const ::std::string&);
    virtual ~IndexNotFoundException() throw();

    virtual ::std::string ice_name() const;
    virtual void ice_print(::std::ostream&) const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    ::std::string mapName;
    ::std::string indexName;
};

}

#endif

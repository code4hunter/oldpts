#ifndef SYNC_SERVER_ICE
#define SYNC_SERVER_ICE

module PTS2
{

local exception FailureException
{
    string reason;
};

interface Admin
{
    void shutdown();
};

};

#endif

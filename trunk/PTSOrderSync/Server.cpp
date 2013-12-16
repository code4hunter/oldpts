
#include <Ice/Ice.h>
#include <IceUtil/Options.h>
#include <Ice/Service.h>
#include <SyncThread.h>
#include <ReportSyncThread.h>
#include <OrderSyncServer.h>

#include <windows.h>   
#include <winbase.h>   
#include <iostream>   

#define SYNC_STRING_VERSION "2.0.0"

using namespace std;
using namespace Ice;
using namespace PTS2;

namespace PTS2
{

void FailureException::ice_print(ostream& out) const
{
#ifdef __BCPLUSPLUS__
    Ice::Exception::ice_print(out);
#else
    Exception::ice_print(out);
#endif
    out << ":\nservice failure exception: " << reason;
}

class MyLoggerI : public Ice::Logger
{
public:
    MyLoggerI()
    {
        _trace = 0;
        _warning = 0;
        _error = 0;
    }

    virtual void print(const std::string& message)
    {
    }

    virtual void trace(const std::string& category, const std::string& message)
    {
        _message = "{T} " + message;
        _trace++;
    }

    virtual void warning(const std::string& message)
    {
        _message = "{W} " + message;
        _warning++;
    }

    virtual void error(const std::string& message)
    {
        _message = "{E} " + message;
        _error++;
    }

    std::string getLastMessage()
    {
        ostringstream os;
        os << "T:" << _trace << " W:" << _warning << " E:" << _error << "\r\n" << _message;

        return os.str();
    }
private:
    std::string _message;
    int _trace;
    int _warning;
    int _error;
};

typedef IceUtil::Handle<MyLoggerI> MyLoggerIPtr;


class SyncService : public Service
{
public:

    SyncService();
    void refreshScreen();

protected:

    virtual bool start(int, char*[]);
    virtual bool stop();

private:

    void usage(const std::string&);

    IceUtil::TimerPtr _timer;
    AccountInfoSeq _accounts;
    DatabasePtr _db;
    SyncThreadPtr _syncThread;
    std::map<std::string, ReportSyncThreadPtr> _rsThreads;
    MyLoggerIPtr _myLogger;
};

class RefreshScreenTask : public IceUtil::TimerTask
{
public:
    RefreshScreenTask(SyncService *service):
      _service(service)
    {
    }

    virtual void runTimerTask()
    {
        _service->refreshScreen();
    }
private:
    SyncService *_service;
};

};

SyncService::SyncService()
{
}

void 
SyncService::refreshScreen()
{
    HANDLE hStdout;   
    // 光标位置   
    COORD cursorPos;   
    // 标准输出句柄   
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);   
    cursorPos.X = 0;   
    cursorPos.Y = 1;   
    SetConsoleCursorPosition(hStdout, cursorPos);  

    SYSTEMTIME st;
    GetLocalTime(&st);	
    long time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
    long date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;

    //cout << "PTSOrderSync 2.0 ==> SD:" << date << " " << time << " ID:" << _syncThread->getCurrDate() << " SI:" << _syncThread->getStartIndex() << endl;
    printf("PTSOrderSync 2.0 ==> SD:%8d %-6d ID:%8d SI:%-10d", date, time, _syncThread->getCurrDate(), _syncThread->getStartIndex());
    cout << "" << endl;
    cursorPos.Y = 3;   
    SetConsoleCursorPosition(hStdout, cursorPos);  
    cout << "ACCT            AC     RC     UCO  WC FC      PFC   MC   DLY   SSN" << endl;
    cursorPos.Y = 4;   
    SetConsoleCursorPosition(hStdout, cursorPos);  
    cout << "----------------------------------------------------------------------------------------" << endl;

    for (AccountInfoSeq::iterator p = _accounts.begin(); p != _accounts.end(); ++p)
    {
        cursorPos.Y++;   
        SetConsoleCursorPosition(hStdout, cursorPos);  
    
        SyncInfo si = _syncThread->getSyncInfo(p->account);
        ReportSyncInfo rsi = {};
        std::map<std::string, ReportSyncThreadPtr>::iterator q = _rsThreads.find(p->account);
        if(q != _rsThreads.end())
            rsi = q->second->getReportSyncInfo();

        printf("%-15s %-6d %-6d %-4d %-2d %-7d %-5d %-4d %-5d %-s", p->account.c_str(), si.acceptCount, si.rejectCount, si.workCount, si.workerCount,
            rsi.filledCount, rsi.pendingCount, rsi.maxCount, rsi.delay, rsi.seqNum.c_str());
    } 
    cout << "" << endl;
    cout << "=========================================================================================" << endl;
    cout << _myLogger->getLastMessage() << endl;
}

bool SyncService::start(int argc, char* argv[])
{
    _myLogger = (MyLoggerI*)communicator()->getLogger()._ptr;

    Ice::PropertiesPtr properties = communicator()->getProperties();

    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    
    vector<string> args;
    try
    {
        args = opts.parse(argc, (const char**)argv);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        error(e.reason);
        usage(argv[0]);
        return false;
    }

    if(opts.isSet("help"))
    {
        usage(argv[0]);
        return false;
    }
    if(opts.isSet("version"))
    {
        print(SYNC_STRING_VERSION);
        return false;
    }

	string connString = properties->getProperty("DB.ConnectionString");
    _db = new Database(connString, communicator(), communicator()->getLogger());

    std::map<std::string, OrderQueuePtr> queueMap;
    _accounts = _db->getAccounts();
    for (AccountInfoSeq::iterator p = _accounts.begin(); p != _accounts.end(); ++p)
    {
        TraderPtr recvTrader = new Trader(*p, communicator()->getLogger());
        ReportSyncThreadPtr thread = new ReportSyncThread(p->account, recvTrader, communicator(), _db);
        thread->start();
        _rsThreads[p->account] = thread;

        int workerCount = _db->getPropertyAsInt(p->account + "_wrokerCount");
        if (workerCount <= 0)
        {
            _db->setLongProperty(p->account + "_wrokerCount", 1);
            workerCount = 1;
        }

        OrderQueuePtr queue = new OrderQueue(*p, recvTrader, communicator()->getLogger());
        queue->start(workerCount);
        queueMap[p->account] = queue;
    } 

    _syncThread = new SyncThread(queueMap, communicator(), _db);
    _syncThread->start();

    _timer = new IceUtil::Timer();
    _timer->scheduleRepeated(new RefreshScreenTask(this), IceUtil::Time::seconds(2));

    return true;
}

bool SyncService::stop()
{
    if (_syncThread)
    {
        _syncThread->terminate();
        _syncThread->getThreadControl().join();
        _syncThread = 0;
    }

    for (std::map<std::string, ReportSyncThreadPtr>::iterator p = _rsThreads.begin(); p != _rsThreads.end(); ++p)
    {
        p->second->terminate();
        p->second->getThreadControl().join();
        p->second = 0;
    }
    
    _rsThreads.clear();

    if (_db)
    {
        _db = 0;
    }

    return true;
}

void SyncService::usage(const string& appName)
{
    string options =
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.";
#ifdef _WIN32
    if(checkSystem())
    {
        options.append(
        "\n"
        "\n"
        "--service NAME       Run as the Windows service NAME.\n"
        "\n"
        "--install NAME [--display DISP] [--executable EXEC] [args]\n"
        "                     Install as Windows service NAME. If DISP is\n"
        "                     provided, use it as the display name,\n"
        "                     otherwise NAME is used. If EXEC is provided,\n"
        "                     use it as the service executable, otherwise\n"
        "                     this executable is used. Any additional\n"
        "                     arguments are passed unchanged to the\n"
        "                     service at startup.\n"
        "--uninstall NAME     Uninstall Windows service NAME.\n"
        "--start NAME [args]  Start Windows service NAME. Any additional\n"
        "                     arguments are passed unchanged to the\n"
        "                     service.\n"
        "--stop NAME          Stop Windows service NAME."
        );
    }
#else
    options.append(
        "\n"
        "\n"
        "--daemon             Run as a daemon.\n"
        "--pidfile FILE       Write process ID into FILE.\n"
        "--noclose            Do not close open file descriptors."

        // --nochdir is intentionally not shown here. (See the comment in main().)
    );
#endif
    print("Usage: " + appName + " [options] [DIR]\n" + options);
}

int main(int argc, char* argv[])
{
    CoInitializeEx(NULL, 0);

    Ice::InitializationData id = InitializationData();
    id.properties = Ice::createProperties();
    id.properties->load("config.server");
    id.logger = new MyLoggerI();
    Ice::initialize(argc, argv, id);

    SyncService svc;
    int status = EXIT_FAILURE;

#ifdef _WIN32
    status = svc.main(argc, argv, id);
#else
    //
    // For UNIX, force --nochdir option, so the service isn't started
    // with / as the working directory. That way, if the data
    // directory is specified as a relative path, we don't
    // misinterpret that path.
    //
    StringSeq args;
    args.push_back(argv[0]);
    args.push_back("--nochdir");
    for(int i = 1; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
    status = svc.main(args);
#endif

    return status;
}

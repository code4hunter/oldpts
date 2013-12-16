#ifndef server_socketH
#define server_socketH

#include "ucpio.h"
#include "server_client.h"
#include "USetup.h"

class server_socket : public completion_socket
{
private:
  //InterfaceType m_interface;
protected:
	virtual void new_key(completion_key ** ck,int index);
  virtual void del_key(completion_key * ck);
public:
	server_socket(char *svr_ip,int svr_port,int nwork_thread,int max_client):
			completion_socket(svr_ip,svr_port,nwork_thread,max_client)
	{
    m_client_num=0;
	}

  long m_client_num;

  virtual void on_new_client(void);
  virtual void on_del_client(void);

  void check_disconnect(void);

  void keep_alive(void);
};
#endif
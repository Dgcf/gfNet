#include <stdio.h>
#include <stdlib.h>
#include "../../src/net/fnetgt/inc/TcpServer.h"
#include "../../src/net/fnetgt/inc/fnetgt.h"

using namespace gNet::Fnetgt;

void NewConnectionNotify()
{
    printf("New Connected! \n");
}

void OnMessageCallback(const TcpConnectionPtr& _ptr, const char* _msg, int _len)
{
    printf("Enter in OnMessageCallback\n");
    string s = _msg;
    // char sz[1024];
    // strncpy(sz, _msg, _len);
    printf("Received msg is : %s\n", s.c_str());
    s += "ECARX_TEST";
    _ptr->Send(s.c_str(), s.length());
}

int test0()
{
    gNet::Fnetgt::TcpServer server("127.0.0.1", 37777);
    server.SetNewCollectionCallback(NewConnectionNotify);
    server.SetMessageCallback(OnMessageCallback);
    server.Start();
}

/****************************************************************
 * /home/gongfeng/study/code/C++/gfNet/src/net/fnetgt/src
 * **************************************************************/
int main()
{
    test0();
}

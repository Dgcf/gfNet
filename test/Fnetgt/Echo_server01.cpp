#include "../../src/net/fnetgt/inc/TcpServer.h"
#include <stdio.h>
#include <stdlib.h>
using namespace gNet::Fnetgt;

void NewConnectionNotify()
{
    printf("New Connected! \n");
}

void OnMessageCallback(const void* msg)
{

}

int test0()
{
    gNet::Fnetgt::TcpServer server("127.0.0.1", 37777);
    server.SetNewCollectionCallback(NewConnectionNotify);
    server.SetMessageCallback(OnMessageCallback);
    server.Start();
}

int main()
{
    test0();
}

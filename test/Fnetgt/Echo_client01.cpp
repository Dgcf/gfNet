#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <future>
using namespace std;

class TcpClient
{
public:
    TcpClient():
    v_{"hello","world","good","morning"},
    count_(0),
    sock_(0)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(37777);

        sock_ = socket(PF_INET, SOCK_STREAM, 0);
        if (-1 == sock_)
        {
            printf("create socket fail \n");
        }
    }

    int connec()
    {
        if (-1 == connect(sock_, (sockaddr*)&addr, sizeof(addr)))
        {
            printf("connect fail\n");
            return -1;
        }
        printf("#############New connect, sock is : %d##############\n", sock_);
        return 0;
    }

    void start()
    {
        int ret = connec();
        if (ret == -1)
        {
            return;
        }
        
        char read_buf[1024];
        int read_num = 0;

        while (1)
        {
            if(count_ >= v_.size())
            {
                count_ = 0;
            }
            if(-1 == write(sock_, v_[count_].c_str(), sizeof(v_[count_])))
            {
                printf("write fail\n");
                continue;
            }
            memset(read_buf, 0, sizeof(read_buf));
            read_num = read(sock_, read_buf, 32);
            printf("read bytes: %d, buf: %s\n", read_num, read_buf);
            sleep(5);
        }
    }

private:
    sockaddr_in addr;
    int sock_;
    int count_;
    std::vector<string> v_;
};

void test()
{
    TcpClient client;
    client.start();
}

int main()
{
    const int count = 1000;
    std::future<void> results[count];
    for (size_t i = 0; i < count; i++)
    {
        results[i] = std::async(test);
        sleep(1);
    }

    for (size_t i = 0; i < count; i++)
    {
        results[i].wait();
    }
    
}

#include "server.hpp"

#define PORT 8080
#define LOCALHOST "127.0.0.1"

int main(int argc,char **argv)
{
    int socket_server;
    int bind_server;
    struct sockaddr_in server_address;

    socket_server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(socket_server < 0)
    {
        std::cerr << "SERVER CLIENT INIT ERROR\n" << std::flush;
        return -1;
    }
    else
    {
        std::cout << "SERVER CLIENT INIT SUCCESS\n" << std::flush;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = std::atoi(LOCALHOST);

    bind_server = bind(socket_server,(struct sockaddr*)&server_address,sizeof(server_address));

    if(bind_server == 0)
    {
        std::cout << "BIND: SERVER THROW AN ERROR\n" << std::flush;
    }
    else
    {
        std::cerr << "BIND: SERVER THROW AN ERROR\n" << std::flush;
        return -1;
    }

    return 0;
}
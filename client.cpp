#include "client.hpp"


int main(int argc,char **argv)
{
    int sock_client;
    int connection;


    sock_client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(sock_client < 0)
    {
        std::cerr << "SOCKET CLIENT INIT ERROR\n" << std::flush;
        return -1;
    }

    connection = connect();
    
    

    return 0;
}
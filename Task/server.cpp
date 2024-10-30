#include "server.hpp"


int main(int argc,char **argv)
{
    struct sockaddr_in server_address;
    int socket_server = 0;
    int bind_server = 0;
    int accept_server = 0;
    int recv_server = 0;
    int send_server = 0;
    int close_server = 0;
    int listener = 0;
    const size_t size_of_msg = 1024;
    char buffer_msg[size_of_msg] = {0};
    
    

    
    socket_server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if(socket_server < 0)
    {
        std::cerr << "SERVER: INIT ERROR\n" << std::flush;
        return -1;
    }
    else
    {
        
        std::cout << "SERVER: INIT SUCCESS\n" << std::flush;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind_server = bind(socket_server,(struct sockaddr*)&server_address,sizeof(server_address));

    if(bind_server == 0)
    {
        std::cout << "BIND: SERVER SUCCESS\n" << std::flush;
    }
    else
    {
        std::cerr << "BIND: SERVER THROW AN ERROR\n" << std::flush;
        return -1;
    }


  for (;;)
    {          
        listener = listen(socket_server,10);
        if(listener == ECONNREFUSED)
        {
            std::cout << "Listen SERVER: QUEUE IS OVERLOAD\n" << std::flush;
        }
        if(listener < 0)
        {
            std::cout << "Listen SERVER: ERROR\n" << std::flush;
            return -1;
        }
      
        
         accept_server = accept4(socket_server,(struct sockaddr*)&server_address,(socklen_t*)&size_of_msg,SOCK_NONBLOCK);


        if(accept_server < 0)
        {
            std::cout << "ACCEPT SERVER:ERROR\n" << std::flush;
            return -1;
        }

         

        recv_server = recv(accept_server,buffer_msg,size_of_msg,0);


        if(recv_server < 0)
        {  
            std::cout << "RECV SERVER: EROR\n" << std::flush;
            return -1;
        }

        std::cout << buffer_msg  << '\n' << std::flush;        


    }

     close_server = close(socket_server);


    return 0;
}
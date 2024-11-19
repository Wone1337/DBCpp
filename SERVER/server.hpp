#include <sys/socket.h> // подключения функции сокет основная библиотека , содержит структуры необходимые сокету
#include <sys/types.h>  // библиотека типов сокектов
#include <arpa/inet.h>  // библиотека для преобразования из аппаратного адреса в  сетевой и наоборот
#include <netinet/in.h>
#include <iostream>
#include <array>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include </home/biba/Documents/c++prac/CLIENT/client.hpp>


#define SERVER
#ifdef SERVER


// struct CLIENT_IS_ONLINE
// {

// std::string username;
// int accept_to_talk;

// };


 int connection(int &__accept_server__,int &__socket_server__,struct sockaddr_in &__server_address__,const size_t &__size_of_msg__)
 {
    
    if(__accept_server__ > 0)
    {
        return __accept_server__;
    }

    __accept_server__ = accept(__socket_server__,(struct sockaddr*)&__server_address__,(socklen_t*)&__size_of_msg__);


        if(__accept_server__ < 0)
        {
            std::cout << "ACCEPT SERVER:ERROR\n" << std::flush;
            return -1;
        }

         
    return __accept_server__;
 }

 


#endif

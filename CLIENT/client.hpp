#include <sys/socket.h> // подключения функции сокет основная библиотека , содержит структуры необходимые сокету
#include <sys/types.h>  // библиотека типов сокектов
#include <arpa/inet.h>  // библиотека для преобразования из аппаратного адреса в  сетевой и наоборот
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <limits>
#include <sstream>


#ifndef CLIENT
#define CLIENT

struct DATA_CLIENT
{
    std::string username;
    std::string password;
    int accept_to_talk;

};

void Authorization(struct DATA_CLIENT *__data__);



#endif
#include <iostream>
#include <fstream>
#include <string>
// #include <vector>
#include <memory>
#include <filesystem>
// #include <limits>
#include <cstdio>

#ifndef BLAH
#define BLAH







namespace
{
    static inline size_t counter {0};

}

namespace res
{

    
enum WRITESTATES
{
    WRITE_OUT = 0, 
    WRITE_APP = 1,
    WRITE_ATE = 2,
    WRITE_TRUCN = 3,
    WRITE_BIN = 4
};

class Resource 
{
    public:
    Resource(){INIT();};
    explicit Resource(std::string &__str):FILE_NAME(__str){INIT();};
    explicit Resource(std::string &&__str):FILE_NAME(__str){INIT();};
    
    Resource &operator=(const Resource &RES) = default;
    Resource &operator=(Resource &&RES) = default;



    void WRIF([[maybe_unused]] const size_t __choice__ = WRITESTATES::WRITE_OUT, [[maybe_unused]]const std::string &__str__ = "FILE CLEARED")
    {
        size_t overflow_check = sizeof(WRITESTATES); 

        if(__choice__  > overflow_check)
        {
            std::cerr << "EROR: CHOICE WAS AN OVERFLOW BY USER" << std::endl;
            std::cerr << "RETURN..." << std::endl;
            return;
        }

        switch(__choice__)
        {
        
        case WRITESTATES::WRITE_APP:
        (*FILE).open(FILE_NAME,std::ios::app);
         if((*FILE).is_open())
        {
            *FILE << __str__ << std::endl;
        }
        break;

        case WRITESTATES::WRITE_ATE:
        (*FILE).open(FILE_NAME,std::ios::ate);
        if((*FILE).is_open())
        {
            *FILE << __str__;
        }
        break;

        case WRITESTATES::WRITE_TRUCN:
        (*FILE).open(FILE_NAME,std::ios::trunc);

        if((*FILE).is_open())
        {
            *FILE << __str__;
        }
        break;

        case WRITESTATES::WRITE_BIN:
        (*FILE).open(FILE_NAME,std::ios::binary);
        if((*FILE).is_open())
        {
            *FILE << __str__;
        }
        break;

        case WRITESTATES::WRITE_OUT:
        [[fallthrough]]

        default:
        (*FILE).open(FILE_NAME,std::ios::out);
        if((*FILE).is_open())
        {
            *FILE << __str__;
        }
        break;
        

    }
     (*FILE).close();
    }

    //  void WRIF(const std::string &__str__ = "FILE CLEARED", const size_t __choice__ = 0) #Запись не через строку в 1 параметре , а через другой файл
    // {
    //     switch(__choice__):
        
    //     case 1:
    //     (*FILE).open(FILE_NAME,std::ios::app);

    //     break;

    //     case 2:
    //     (*FILE).open(FILE_NAME,std::ios::ate);
    //     break;

    //     case 3:
    //     (*FILE).open(FILE_NAME,std::ios::trunc);
    //     break;

    //     case 4:
    //     (*FILE).open(FILE_NAME,std::ios::binary);
    //     break;

    //     case 0:
    //     [[fallthrough]]

    //     default:
    //     (*FILE).open(FILE_NAME,std::ios::out);

    //     break;
        

    //     (*FILE).close();
    // }


    void REF() noexcept(true)
    {
        std::string STR;
        (*FILE).open(FILE_NAME,std::ios::in);
        if((*FILE).is_open())
        {   
            std::cout << "\nFILE CONTAIN:\n" << std::flush;
            std::cout << "---------------------\n" << std::flush;

            while(std::getline(*FILE,STR))
            {
                std::cout << STR << std::endl;
            }

            std::cout << "---------------------\n\n" << std::flush;
        }
        (*FILE).close();
    }

    void XCHNG([[maybe_unused]]res::Resource &__f1__,[[maybe_unused]]res::Resource &__f2__);
    
    ~Resource(){}

    protected:
    void INIT()
    {
        if(std::filesystem::exists(FILE_NAME))
        {   
            std::cout << "INIT SUCCESS!\n" << std::flush; 
        }
        else
        {
            std::string str = "text" + std::to_string(counter) + ".txt";
            std::string Current_path = std::filesystem::current_path();
            FILE_NAME = Current_path + '/' + str;
            std::cout << "FILE NOT EXIST,BUT CREATED NEW!\n" << std::flush;
            ++counter;
        }


        FILE = std::make_shared<std::fstream>(FILE_NAME);
        (*FILE).close();

    }


    private:
    std::shared_ptr<std::fstream> FILE;
    std::string FILE_NAME;


};

void XCHNG([[maybe_unused]]res::Resource &__f1__,[[maybe_unused]]res::Resource &__f2__)
{
     std::string TEMP_NAME_OF_FILE = "temp.txt";      
           
     std::shared_ptr<std::fstream> TEMP = std::make_shared<std::fstream>(TEMP_NAME_OF_FILE, std::ios::out);
     
      *TEMP << "";
     
     (*TEMP).close();   

     Resource __temp__(TEMP_NAME_OF_FILE); 

            __temp__ = __f1__;
            __f1__ = __f2__;
            __f2__ = __temp__;

        //remove(TEMP_NAME_OF_FILE.c_str()); посмотреть удаление файла
}


}





#endif



//    Умные указатели:
        // Создай класс Resource, который управляет некоторым 
        // ресурсом (например, открытым файлом или сетевым соединением). 
        // Используй std::shared_ptr для управления этим ресурсом и реализуй функции для создания, 
        // копирования и перемещения объектов. Обеспечь корректное управление ресурсами.
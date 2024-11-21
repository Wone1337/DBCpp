#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <filesystem>
#include <iomanip>

#ifndef BLAH
#define BLAH


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
    explicit Resource(const std::string &__str,bool __save_file = false,const std::string &__path = std::filesystem::current_path()):FILE_NAME(__str),is_save(__save_file),PATH(__path){INIT();};
    explicit Resource(const std::string &&__str,bool __save_file = false,const std::string &__path = std::filesystem::current_path()):FILE_NAME(__str),is_save(__save_file),PATH(__path){INIT();};
    
    Resource &operator=(const Resource &RES) = default;
    Resource &operator=(Resource &&RES) = default;


   const void WRIF(const size_t __choice__ = WRITESTATES::WRITE_OUT, const std::string &__str__ = "FILE CLEARED") noexcept(true);

   const void REF() noexcept(true);

   const void SWAP(res::Resource &__object__) noexcept(true);

    
    ~Resource()
    {
         if(!is_save)
         {
            std::cout << "FILE " + FILE_NAME + " DESTROYED" <<std::endl;
            remove(FILE_NAME.c_str());
         }
    }

    protected:
    const void INIT() noexcept(true);
    const void copy_obj(res::Resource &__obj_src,res::Resource &__obj_dest, std::string &__tmp_str) noexcept(true);


    private:
    std::shared_ptr<std::fstream> FILE;
    std::string FILE_NAME;
    bool is_save;
    std::string PATH;


};

const void Resource::copy_obj(res::Resource &__obj_src,res::Resource &__obj_dest, std::string &__tmp_str) noexcept(true)
{
        __obj_dest.FILE->open(__obj_dest.FILE_NAME, std::ios::out);       
        __obj_src.FILE->open(__obj_src.FILE_NAME, std::ios::in); 
       *__obj_dest.FILE << __obj_src.FILE->rdbuf();
        __obj_src.FILE->close();
        __obj_dest.FILE->close();
}

const void Resource::SWAP(res::Resource &__object__) noexcept(true)
   {
        Resource __temp__("TEMP.txt");

        std::string temp_string;

    copy_obj(*this,__temp__,temp_string);
    copy_obj(__object__,*this,temp_string);
    copy_obj(__temp__,__object__,temp_string);

  }

const void Resource::INIT() noexcept(true)
    {
        if(std::filesystem::exists(FILE_NAME))
        {   
            std::cout << "INIT SUCCESS!\n" << std::flush; 
        }
        else
        {
            if(FILE_NAME.empty())
            {
                FILE_NAME = "UNNAMED.txt";
            }
            FILE_NAME = PATH + '/' + FILE_NAME;
            std::cout << "FILE NOT EXIST,BUT CREATED NEW!\n" << std::flush;
        }


        FILE = std::make_shared<std::fstream>(FILE_NAME,std::ios::out);
        (*FILE).close();

    }

const void Resource::REF() noexcept(true)
    {
        std::string STR;
        (*FILE).open(FILE_NAME,std::ios::in);
        if((*FILE).is_open())
        {   
            std::string head = "+---------------------------------+" ;
            std::size_t head_size = head.size();
            std::cout << "FILE " + FILE_NAME + " CONTAIN:\n" << std::flush;       
            

            std::cout << head << std::endl;

            while(std::getline(*FILE,STR))
            {
                if(STR.size() > head_size)
                {
                    STR = STR.substr(NULL,head.size()-5)  + "...";
                }
                std::cout << "|" << STR << std::setw(head_size-STR.size()-1) << '|'  << std::endl;
            }

            std::cout << head << std::endl;
        
       }
       else
       {
            std::cout << "REF:ERROR" << std::endl;
       }
        (*FILE).close();
    }

const void Resource::WRIF(const size_t __openmode__,const std::string &__str__) noexcept(true)
    {
        size_t overflow_check = sizeof(WRITESTATES); 

        auto write = [this](const std::string &_str_)
        { 
            if((*FILE).is_open())
            {
                *FILE << _str_;
            }
            else
            {
                std::cout << "WRITE_LAMBDA_WRIF:ERROR" << std::endl;
            }

            (*FILE).close();
        };
        

        if(__openmode__  > overflow_check)
        {
            std::cerr << "EROR: CHOICE WAS AN OVERFLOW BY USER" << std::endl;
            std::cerr << "RETURN..." << std::endl;
            return;
        }

        switch(__openmode__)
        {
        
        case WRITESTATES::WRITE_APP:
        (*FILE).open(FILE_NAME,std::ios::app);
        write(__str__);
        break;

        case WRITESTATES::WRITE_ATE:
        (*FILE).open(FILE_NAME,std::ios::ate);
        write(__str__);
        break;

        case WRITESTATES::WRITE_TRUCN:
        (*FILE).open(FILE_NAME,std::ios::trunc | std::ios::out);
        write(" ");
        break;

        case WRITESTATES::WRITE_BIN:
        (*FILE).open(FILE_NAME, std::ios::out | std::ios::binary);
        write(__str__);        
        break;

        case WRITESTATES::WRITE_OUT:
        [[fallthrough]]

        default:
        (*FILE).open(FILE_NAME,std::ios::out);
        write(__str__);
        break;
        

    }
    }

}





#endif



//    Умные указатели:
        // Создай класс Resource, который управляет некоторым 
        // ресурсом (например, открытым файлом или сетевым соединением). 
        // Используй std::shared_ptr для управления этим ресурсом и реализуй функции для создания, 
        // копирования и перемещения объектов. Обеспечь корректное управление ресурсами.
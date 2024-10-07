#include <iostream>
#include <string>
#include <vector>
#include <sys/mman.h>
#include <memory>
#include <thread>
#include <unistd.h>
namespace biba
    {
        using size_t_int = unsigned int;
        template<typename T> class MemoryManager;






        template<typename T> class MemoryManager
            {
                public:
                explicit MemoryManager(const T& _variable,const size_t_int _size = sizeof(T)):InType(_variable),size(_size) {}
                explicit MemoryManager(const T&& _variable,const size_t_int _size = sizeof(T)):InType(std::move(_variable)),size(_size){}
                MemoryManager &operator=(MemoryManager&& value) noexcept = default;
                MemoryManager &operator=(const MemoryManager& value) noexcept = default;
                

                void* alloc(size_t_int __size = 0)
                {
                

                    if(sizeof(size_t_int) == __size)
                    {
                        std::cerr << "Eror of memory allocated\n" << std::flush; 
                        return nullptr;
                    }


                    to_rotate = sbrk(__size); 

                    return to_rotate;
                }

                ~MemoryManager()
                {
                    
                };

                
                private:
                size_t_int size;
                void *to_rotate;
                T InType;
             
 
            };


            // template<typename T>
            // class A 
            // {
            //     public:
            //     A(const T& _e):e(_e){}
            //     const A &operator=(const A &value)
            //     {
            //         return A{value.e};
            //     }
            //     private:
            //     T e;
            // };
      

    };
//MemoryManager<int[]> mem ;






int main([[maybe_unused]]int argc,[[maybe_unused]] char **argv) 
{
// int s = 10;
// const int &f  = s;
// biba::MemoryManager<int> e{10};


biba::MemoryManager<int> f(10);

f.alloc(-10);

// std::cout << sizeof(intptr_t); 

// std::shared_ptr<std::vector<int>>(std::vector<int>{10,10,10});
return 0;
}


//  Указатели и память:
//    Реализуй класс MemoryManager, который управляет динамически выделенной памятью. Класс должен предоставлять методы для:
//        Выделения и освобождения памяти (аналог new и delete). (использование mmap)
//        Проверки, выделена ли память. (check_mem)
//        Подсчета текущего объема выделенной памяти.(capacity)



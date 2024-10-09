#include <iostream>
#include <string>
#include <vector>
#include <sys/mman.h>
#include <memory>
#include <thread>
#include <unistd.h>

namespace biba
    {
        template<typename T>class Allocator;
        template<typename T> class MemoryManager;

        template<typename T> class Allocator
        {
            public:

            void* biba_init()
            {
                
                   to_rotate = sbrk(size);
                   return to_rotate;           
            }

            void* biba()
            {

            }

            void* freedom()
            {


            } 

            private:
            size_t size = sizeof(T);
            void *to_rotate;
        };


        template<typename T> class MemoryManager:public Allocator<T>
            {
                public:
                MemoryManager() = default;
                explicit MemoryManager(const T& _variable):InType(_variable) 
                {
                    Allocator<T>::biba_init();
                }
                explicit MemoryManager(const T&& _variable):InType(std::move(_variable)){}
                MemoryManager &operator=(MemoryManager&& value) noexcept = default;
                MemoryManager &operator=(const MemoryManager& value) noexcept = default;
                
                
                ~MemoryManager(){};
                

                private:
                T InType;

            };

       
           

    

    };
//MemoryManager<int[]> mem ;


void* my_malloc(size_t size) {
    return sbrk(size); // Запрашиваем у sbrk `size` байт
}



int main([[maybe_unused]]int argc,[[maybe_unused]] char **argv) 
{
    
    int s = 10;
// const int &f  = s;
// biba::MemoryManager<int> e{10};

 int* array = (int*)my_malloc(10 * sizeof(int));


// biba::MemoryManager<int> f(s);


// std::cout << sizeof(intptr_t); 

return 0;
}


//  Указатели и память:
//    Реализуй класс MemoryManager, который управляет динамически выделенной памятью. Класс должен предоставлять методы для:
//        Выделения и освобождения памяти (аналог new и delete). (использование mmap)
//        Проверки, выделена ли память. (check_mem)
//        Подсчета текущего объема выделенной памяти.(capacity)



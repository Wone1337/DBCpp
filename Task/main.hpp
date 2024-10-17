#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <memory>



#define MAIN_HPP
#ifdef MAIN_HPP

    namespace 
        {
            static inline size_t counter {};
        }


namespace biba
    {
        template<typename T>class Allocator;
        template<typename T> class MemoryManager;

    
        

        template<typename T> class Allocator
        {
            protected:
            void biba_init() noexcept
            {
                to_rotate = sbrk(size);
                capacity += size;
                ++counter;
                return;
            }

            void biba(T& var)
            {
                biba_init();

                TypeAlloc = reinterpret_cast<decltype(TypeAlloc)>(to_rotate);

                *TypeAlloc = var;
                
                return;     
            }

            void freedom() noexcept
            {
              
                    to_rotate = sbrk(-size);
                    to_rotate = nullptr;
                    capacity -= size;
                    --counter;
                return;
            } 
            

            private:
            const static size_t size = sizeof(T);
           

            protected:
            static inline size_t capacity {};
            void *to_rotate; 
            T* TypeAlloc = nullptr;

        };


        template<typename T> class MemoryManager:protected Allocator<T>
            {
                public:
                MemoryManager()
                {
                     Allocator<T>::biba(InType);
                }
                explicit MemoryManager(const T& _variable):InType(_variable) 
                {                
                     Allocator<T>::biba(InType);
                }
                explicit MemoryManager(const T&& _variable):InType(std::move(_variable))
                {
                     Allocator<T>::biba(InType);
                }
                MemoryManager &operator=(MemoryManager&& value) noexcept = default;
                MemoryManager &operator=(const MemoryManager& value) noexcept = default;

                MemoryManager &operator=(T&& value) noexcept 
                {
                    InType = std::move(value);
            
                    return *this;
                }
                MemoryManager &operator=(T& value) noexcept 
                {
                    InType = value;
            
                    return *this;
                }

               ~MemoryManager()
               {
                 Allocator<T>::freedom();
               };
                

                void Capasity()
                {
                    std::cout << "Capacity of memory alloc: " << Allocator<T>::capacity << " MB\n" << std::flush;
                }


                private:
                T InType;
                
            };

            void Mem_checker()
                {
                     if(counter > 0)
                     {  
                        std::cout << "Memory allocate now!" << '\n' <<  std::flush;
                        
                     }
                     else
                     {
                       std::cout << "No one object with allocated memory is not available\n" << std::flush;
                     }
                }       
           


        class ResourceFile
        {
                public:
                
                ResourceFile() = default;

                void overwrite()
                {


                }
                void writelast()
                {


                }
                void read()
                {


                }

                private:
                std::fstream in_out;
                std::string str;
                std::shared_ptr<ResourceFile> pointer;
 
                protected:

        };
    };

#endif 

//  Умные указатели:
//         Создай класс Resource, который управляет некоторым ресурсом (например, открытым файлом или сетевым соединением). 
//         Используй std::shared_ptr для управления этим ресурсом 
//         и реализуй функции для создания, копирования и перемещения 
//         объектов. Обеспечь корректное управление ресурсами.
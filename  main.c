#include <stdio.h>
#include <unistd.h>

void* my_malloc(size_t size) {
    return sbrk(size); // Запрашиваем у sbrk `size` байт
}



int main([[maybe_unused]]int argc,[[maybe_unused]] char **argv) 
{
    
    int s = 9;
// const int &f  = s;
// biba::MemoryManager<int> e{10};

 int* array = (int*)my_malloc(10 * sizeof(int));


// biba::MemoryManager<int> f(s);


// std::cout << sizeof(intptr_t); 

return 0;
}
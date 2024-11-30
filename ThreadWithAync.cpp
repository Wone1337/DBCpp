#include <iostream>
//#include <thread>
//#include <future>
#include <cmath>
#include <string>
#include <vector>
//#include <atomic>
//#include <mutex>
//#include <chrono>
//#include <typeinfo>
//#include <type_traits>



class Complex
{
public:
Complex() = default;
Complex(int comp_a , int comp_b):a(comp_a),b(comp_b) {}
Complex &operator=(const Complex &param) = default;

const bool operator==(const Complex &param) const
{ 
     return module() == param.module();
}
const bool operator!=(const Complex &param) const
{ 
     return module() != param.module();
}
const bool operator<(const Complex &param) const
{ 
     return module() < param.module();
}
const bool operator>(const Complex &param) const
{ 
     return module() > param.module();
}

const double module() const noexcept
{
   double z = 0;

   z = sqrt((a*a) + (b*b));
   
   return z;
}

const void print() const noexcept
{
   std::cout << a  <<  '+' <<  b << "i\n";
}

private:
int a = 0;
int b = 0;

};



int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv)
{
   
   Complex sas(1,4);
   Complex sos(2,3);

   if(sas == sos)
   {
      std::cout << "==\n";
   }


   if(sas != sos)
   {
      std::cout << "!=\n";
   }

   if(sas > sos)
   {
      std::cout << ">\n";
   }

   if(sas < sos)
   {
      std::cout << "<\n";
   }

   sos.print();
   sas.print();

   return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "main.hpp"
#include <filesystem>
#include "main2.hpp"



int main([[maybe_unused]]int argc,[[maybe_unused]] char **argv) 
{
   res::Resource e("/home/boba/Documents/myau/sosal.txt");
   res::Resource t("/home/boba/Documents/myau/sisi.txt");

   e.REF();
   t.REF();

   res::XCHNG(e,t);



   //e.WRIF(1,"ывафвыаывафмывафывамфвыма");
   e.REF();
   t.REF();
  

  





return 0;
}

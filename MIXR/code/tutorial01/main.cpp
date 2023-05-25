
#include <iostream>

#include "mixr/base/String.hpp"

int main(int argc, char* argv[])
{
	// creates a new string using MIXR String class
   const auto str = new mixr::base::String("Hello world\n");

   // prints out the string
   std::cout << str->getString();

   // set str to a new string
   str->setStr("Goodbye world\n");

   // prints out the new string
   std::cout << str->getString();

   // deletes the string object
   str->unref();

   return 0;
}

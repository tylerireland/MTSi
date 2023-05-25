
#include <iostream>

#include "Rng.hpp"

int main(int argc, char* argv[])
{
   // RNG = Random Number Generator
   std::cout << "Creating Rng object" << std::endl;
   const auto rng = new Rng();
   std::cout << "Rng object created" << std::endl;

   // the seed decides where in the random list to start
   rng->setSeed(25);

   // prints out ten random numbers
   for (int i=0; i<10; i++)
      std::cout << rng->num() << std::endl;

   // delete rng object
   std::cout << "Unref'ing rng object\n";
   rng->unref();
   std::cout << "Rng object unref'd\n";

   return 0;
}

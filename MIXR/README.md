# Working with MIXR (Mixed Reality Simulation Platform)

### **_Table of Contents_**
- [MIXR Basics](#mixr-basics)
- [Opening MIXR in Visual Studio](#opening-mixr-in-visual-studio)
- [Running an Example](#running-an-example)
- [Tutorials](#tutorials)
- [MainSim1 example](#mainsim1-example)
- [References](#references)


In this write up :
- I will explain how to open up MIXR with Visual Studio
- I will show how to add and run some examples
- I will go through the provided tutorials and explain each one
- I will record my process in creating a simple graphical simulation  

By the end I hope to a have solid understanding of mixr and how each component works together.

### Goal
I am working with the mainSim1 example, which is a simple simulation of an aircraft flying at a set speed. I plan to track it's position and output it to a graphical display. Eventually, I may try to find ways to interact with the aircrafts velocity and heading and also output that to a display.

## MIXR Basics
MIXR is a framework used to develop simulation applications. It is not itself an exectuable, but a collection of libraries used to create applications. It is an very object-oiented framework that uses it's object class to initialize eveyrthing, from strings to players (aircrafts).  

MIXR was previously named OpenEaagles, an open source version of Eaagles. These links below will provide much more information on MIXR's history and framework.  
- [The Mixed Reality Simulation Platform (MIXR)](https://www.mixr.dev/assets/pages/docs/the-mixed-reality-simulation-platform-csc-2018.pdf)  
- [MIXR Overview](https://www.mixr.dev/overview.html)
- [MIXR Documentation](https://www.mixr.dev/docs.html)

## Opening MIXR in Visual Studio
1. First, download the current release [**_here_**](https://www.mixr.dev/downloads.html)
    - you will need to download the **Framework, Examples, Example Data,** and **32-Bit 3rd Party Libraries**
2. Extract all files into one folder.
3. Open ` mixr / build / vs2017 / mixr.sln ` in visual studios.
 
## Running an Example
Once mixr is opened in visual studio:
1. Select File > Add > Existing Project
2. In the file explorer, select ` mixr_examples / build / vs2017 / mainSim1.vcxproj `
3. This should add the project into the solution.
4. Before running the project, open up the mixr_examples folder once again, but this time select the folder with the same name as your project
5. Double Click ` make-edl.cmd `. This will create any required .edl files to run the program
6. Back in Visual Studo, right click on your project and select ` Set as Startup Project ` and the run the solution
7. The project should build and run successfully

## Tutorials
I will be going through each of the 8 tutorials below  

[Tutorial 1 - Hello World](#tutorial-1)  
[Tutorial 2 - Random Number Generator](#tutorial-2)  
[Tutorial 3 - Factories and Builders](#tutorial-3)  
[Tutorial 4 - AbstractRng](#tutorial-4)  
[Tutorial 5 - Classes](#tutorial-5)  
[Tutorial 6 - Components](#tutorial-6)  
[Tutorial 7 - Glut Display](#tutorial-7)  
[Tutorial 8 - Pagers](#tutorial-8)
  

### Tutorial 1
The first tutorial is a simple "Hello World" program using MIXR's **String** class.  

```cpp
const auto str = new mixr::base::String("Hello world\n");
std::cout << str->getString();
```
- A new String object named `str` is being created using MIXR's String class. It's string is then outputted to the console.

```cpp
 str->setStr("Goodbye world\n");
 std::cout << str->getString();
```
- The String object's string value is reset to "Goodbye world\n" and then printed to the console.

```cpp
str->unref();
```
- Since the string variable is a new object located in the heap, it must be deleted to prevent memory leaks. This unref() command will delete the string object.

[Tutorial 1 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial01)

### Tutorial 2
The second tutorial creates a random number generator object and outputs 10 random numbers.

```cpp
const auto rng = new Rng();
```
- A new Rng (Random number generator) object is being created using the Rng class.

```cpp
rng->setSeed(25);
```
- The seed is an arbirtrary number that will let the random generator know which 'random' numbers to output. Random numbers are not actually random. You can think of it as a really larger list of numbers with no particular order. The seed will determine where to start reading from the list. This program will not output new random numbers each time I run this if I do not change the seed.

```cpp
for (int i=0; i<10; i++)
      std::cout << rng->num() << std::endl;
```
- This loop outputs 10 random numbers from the Rng object.

```cpp
rng->unref();
```
- The object is deleted to prevent memory leaks.

[Tutorial 2 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial02)

### Tutorial 3
Tutorial 3 start to create objects using factories and builders. 

```cpp
mixr::base::Object* factory(const std::string& name)
{
   mixr::base::Object* obj{};
   
   if ( name == Rng::getFactoryName() ) {
      obj = new Rng;
   }

   if (obj == nullptr) obj = mixr::base::factory(name);
   return obj;
}
```
- This factory class essentially creates a new Rng object

```cpp
Rng* builder(const std::string& filename)
{
   int num_errors{};
   mixr::base::Object* obj{mixr::base::edl_parser(filename, factory, &num_errors)};
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
```
- Inside the builder function, an input file is read into a parser. The parser will take those inputs given from the file and connect them with the object being created using a slot table. It also uses the factory class to create the correct object.

```cpp
    if (obj == nullptr) {
        std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
        std::exit(EXIT_FAILURE);
   }
```
- Checks to make sure an object was created and fails if not.

```cpp
    const auto pair = dynamic_cast<mixr::base::Pair*>(obj);
    if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
    }
```
- Checks for a Pair. A pair connects a variable name from the class to a variable name from the input file.

```cpp
    const auto random = dynamic_cast<Rng*>(obj);
    if (random == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    return random;
}
```
- This will attampt to cast to a proper object

```cpp
int main(int argc, char* argv[])
{
   std::string configFilename = "file0.edl";
   Rng* rng{builder(configFilename)};
```
- A string named "file0.edl" is passed into the builder function. This .edl file is created from the input file. It contains the variales required for the random number generator.

```cpp
for (int i=0; i<10; i++) {
      std::cout << rng->num() << std::endl;
   }

   rng->unref();
```
- Just like the last example, random numbers are printed out and the Rng object is deleted.

[Tutorial 3 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial03)

### Tutorial 4
This tutorial is similar to the previous one. Instead of creating a regular Rng object, it creates AbstractRng Objects such as Exponential, Lognormal, and Uniform.  

[Tutorial 4 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial04)

### Tutorial 5
Tutorial 5 creates it's own class called MyObj. It inherits MIXR's Object class. Inside MyObj are member functions, such as setColorTable, setTextColor, and setMessage. 

- This provides the basic layout of a class and how to use it. 
- Each class requires a header file and a source file. The header file will declare the name of the class, as well as all the member functions and variables. There are no definitions in the header file. The source file will include the definition of those member functions. 
- You can think of the header file as a template for the class and the source file would be the template once it is all filled in. 
- Taking a look at the header file, there are a few member functions, as well as objects created that will be used in the slot table. The slot table is what connects the input file to the code. You will declare different variables in the input files that will then be put into the slot table.
- Now looking at the source file, there is a ` SLOTTABLE ` and a ` SLOT_MAP `. Inside the slot table are different variables, such as, ` colorTable `, ` textColor `, ` vector `, etc. These will be defined in the input file and later assigned to these slots with the slot map.
- After the slot table and slot map are the definitions for all the member functions.
- The .edl file contains all the information required for the object. All of those variables in the slot table are defined in this file. Once this file is read in and all slots are assigned, all of the member functions can be called in main.
- Inside main.cpp, I can see that there is a factory and builder here as well. The factory and builder is creating the MyObj object before it can be used. The dumpContents() method is called on myObj which will print out all of the objects assets in the slot table.
- Lastly, the object is deleted before the program ends.

[Tutorial 5 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial05)
### Tutorial 6
This tutorial creates a new component class named MyComp that inherits from the Component class. 
- Component classes allow objects to have time-critical and regular processes.
- Time-critical tasks are those that need to finish executing in a certain amount of time, like math calculations.
- Regular tasks are not time-critical, they will be executed after the time-critical tasks are finished executing, tasks like writing data to a log.
- MyComp intializes just like other classes, with a factory and build function.
- In the main function, builder creates the MyComp object and then two functions are called; the first one being tcFrame, which executes a time-critical 'frame', and the second one being updateData, which executes a background frame.
- The output shows all the time critical frames being executed first.

[Tutorial 6 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial06)

### Tutorial 7
This tutorial creates a Glut display and displays different colored worms that bounce around the screen. 
- The main file contains a factory and builder for the worms and Glut display. 
- In the main loop, the glutDisplay is built and creates a window using the createWindow() member function. 
- A timer is set and then the MainLoop is called. 
- The worms are created in the builder method. Their speed, angles and colors are provided in the input file.


[Tutorial 7 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial07)

### Tutorial 8

[Tutorial 8 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial08)


## MainSim1 example

### main.cpp
- many class files are included, such as the Station, edl_parser, Pair, Integer, etc.
- many factory classes are included as well

### test0.epp
- location: ` mixr_examples / mainSim1 / configs ` 
- There is a copy of the file on my repo [**_here_**](https://github.com/tylerireland/MTSi/blob/main/test0.epp)  

- At first glance, this file is really small. There are not many line at all. The description says that it is a single aircraft player (player being the aircraft).
- A station is initialized and within the station contains an image generator, an interoperability interface, and a simulation scenario. 
    - Both interfaces are commented out, so I believe that they are not too important for the prgram to run.
- Looking at the simualtion scenario, there is a lat/postion, as well as a player that continase the aircraft name, id, type, signature, XPos, Ypos, altitude,
  heading, velocity, and side.
- The player is an blue-sided F-16A Aircraft, with an altitude of 20000 feet, and a velocity of 250 (mph?)
- In this simulation, there is an aircraft flying at 250 (mph?). I am going to find a way to track his position and update it to the console. Once completed, I will try to output the positon to a GLUT display.

### test0.edl




## References
- [The Mixed Reality Simulation Platform (MIXR)](https://www.mixr.dev/assets/pages/docs/the-mixed-reality-simulation-platform-csc-2018.pdf)  
- [MIXR Documentation](https://www.mixr.dev/docs.html)  
- [Design & Implementation of Virtual Simulations](https://www.mixr.dev/assets/pages/docs/iitsec-2008-tutorial.pdf)
- [MIXR Overview](https://www.mixr.dev/overview.html)

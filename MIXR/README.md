# Working with MIXR (Mixed Reality Simulation Platform)

[//]: # (comment)

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
2. In the file explorer, select ` mixr_examples / build / vs2017 / exampleProj.vcxproj `
3. This should add the project into the solution.
4. Before running the project, open up the mixr_examples folder once again, but this time select the folder with the same name as your project
5. Double Click ` make-edl.cmd `. This will create any required .edl files to run the program
6. Back in Visual Studo, right click on your project and select ` Set as Startup Project ` and the run the solution
7. The project should build and run successfully

# Tutorials
I will be going through each of the 8 tutorials below  

[Tutorial 1 - Hello World](#tutorial-1---hello-world)  
[Tutorial 2 - Using Objects](#tutorial-2---using-objects)  
[Tutorial 3 - Factories and Builders](#tutorial-3---factories-and-builders)  
[Tutorial 4 - Mulitple Objects](#tutorial-4---mulitple-objects)  
[Tutorial 5 - Classes](#tutorial-5---classes)  
[Tutorial 6 - Components](#tutorial-6---components)  
[Tutorial 7 - Glut Display](#tutorial-7---glut-display)  
[Tutorial 8 - Pagers](#tutorial-8---pagers)
  

## Tutorial 1 - Hello World
The first tutorial is a simple "Hello World" program using MIXR's **String** class.  

### main.cpp
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

## Tutorial 2 - Using Objects
The second tutorial creates a random number generator object and outputs 10 random numbers.

### main.cpp
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

## Tutorial 3 - Factories and Builders
Tutorial 3 start to create objects using factories and builders. 

### Factory

- A factory will create the object based on the name passed in. The name can be found in the correspoding source file of that object here:
```cpp
IMPLEMENT_SUBCLASS(MyObj, "MyObj")
```
- "MyObj" is the name of the object being passed into the factory. It will check the value of that string and create the object accordingly.
```cpp
mixr::base::Object* factory(const std::string& name)
{
   mixr::base::Object* obj{};
   
   if ( name == MyObj::getFactoryName() ) obj = new MyObj;
```
- The main `Factory` class contains all of the possible objects that can be created in the same form as the example above. Since `MyObj` is a new class, it needs to be implemented in the factory class.      

```cpp
   if (obj == nullptr) obj = mixr::base::factory(name);
   return obj;
}
```
- This will check the `mixr::base::factory` class in case the name does not match `MyObj::getFactoryName()`.  


### Builder

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

### main.cpp

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

## Tutorial 4 - Mulitple Objects
This tutorial is similar to the previous one. Instead of creating a just one Rng object, it is creating three different AbstractRng objects. Inside the .edl file there is 3 different _'objects'_; a Lognormal, a Uniform, and a Exponential. 

[Tutorial 4 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial04)

## Tutorial 5 - Classes
Tutorial 5 creates a custom object class.


### MyObj.hpp
```cpp
class MyObj final: public mixr::base::Object {
```
- `MyObj` is the new class being created. It is inheriting from the `Object` class.

```cpp
   DECLARE_SUBCLASS(MyObj, mixr::base::Object)
```
- This is a MIXR macro. There is caution to trying to learn these macros. It it recommended to think of them as 'black boxes'.

- The rest of the header file contains all of the member functions and variables.

### MyObj.cpp

```cpp
IMPLEMENT_SUBCLASS(MyObj, "MyObj")
```
- This is another MIXR macro. The string "MyObj" is the `name` variable that is being passed into the factory class. It checks to make sure that the string matches the name of a class, and creates the corresponding class. This is shown in main.cpp

```cpp
BEGIN_SLOTTABLE(MyObj)
   "colorTable",         // 1: The Color table     <PairStream>
   "textColor",          // 2: Text color          <Identifier>
   "backColor",          // 3: Background color    <Identifier>
   "vector",             // 4: Vector              <List>
   "visible",            // 5: Visibility flag     <Number>
   "message",            // 6: The message         <String>
END_SLOTTABLE(MyObj)
```
- This is a slot table. This declares all of the variables in the `MyObj` class. These will be defined in the input file that will be read in with the parser.


```cpp
BEGIN_SLOT_MAP(MyObj)
   ON_SLOT(1, setSlotColorTable, mixr::base::PairStream)
   ON_SLOT(2, setSlotTextColor,  mixr::base::Identifier)
   ON_SLOT(3, setSlotBackColor,  mixr::base::Identifier)
   ON_SLOT(4, setSlotVector,     mixr::base::List)
   ON_SLOT(5, setSlotVisible,    mixr::base::Number)
   ON_SLOT(6, setSlotMessage,    mixr::base::String)
END_SLOT_MAP()
```
- This slot map is what is setting those variables to those slots. Each slot corresponds to a setter function which will set those variables to the values given in the input file.

- The rest of the source file is defining all of the member functions.

### mian.cpp

```cpp
   std::string configFilename = "file0.edl";
   
   MyObj* myObj{builder(configFilename)};
```
- The `myObj` object is being initialized using the builder function

```cpp
 myObj->dumpContents();

 myObj->unref();
 ```
- All of the contents of the object are printed out to the screen and then it is deleted.

[Tutorial 5 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial05)

## Tutorial 6 - Components
This tutorial creates a custom component class

### MyComp.hpp
```cpp
class MyComp final: public mixr::base::Component {
   DECLARE_SUBCLASS(MyComp, mixr::base::Component)
```
- A new components is defined here, inheriting from the `Component` class. Just like the Object classes, `DECLARE_SUBCLASS` should be considered a "block box".

- The rest of the header file contains the member function declarations.

### MyComp.cpp
```cpp
IMPLEMENT_SUBCLASS(MyComp, "MyComp")
```
- This is the same macro as the object classes. This string variable is passed into the factory to create the correct component.

```cpp
BEGIN_SLOTTABLE(MyComp)
  "str"
END_SLOTTABLE(MyComp)

BEGIN_SLOT_MAP(MyComp)
  ON_SLOT(1, setSlotStr, mixr::base::String)
END_SLOT_MAP()
```
- "str" is the component being created here. It is the only slot on the slot table. 
- Just like the object classes, the string is the variable of the component located in the slot table. The slot map is what assigns the value in the input file to the variable name.

- The rest of this source file contains the definitions of the member functions.


### main.cpp
```cpp
std::string configFilename = "file0.edl";

MyComp* myComp{builder(configFilename)};
```
- A new component is being created with the builder function

```cpp
const double dt{1.0 / static_cast<double>(frameRate)};
```
- Creates a delta time for the time critical and regular processes

```cpp
myComp->tcFrame(dt);     // time critical
myComp->updateData(dt);  // non-time critical

myComp->reset();

myComp->tcFrame(dt);     // time critical
myComp->updateData(dt);  // non-time critical
```
- Time critical and regular processes are being executed in this code

```cpp
myComp->unref();
```
- The component is deleted at the end of the program

[Tutorial 6 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial06)

## Tutorial 7 - GLUT Display
This tutorial creates a Glut display and displays different colored worms that bounce around the screen. 

### Worms.hpp
```cpp
class Worm final: public mixr::graphics::Graphic
{
   DECLARE_SUBCLASS(Worm, mixr::graphics::Graphic)
```
- Similar to the other classes looked at. The subclass macro is declared as well as the member functions
### Worms.cpp
```cpp
IMPLEMENT_SUBCLASS(Worm, "Worm")
EMPTY_DELETEDATA(Worm)

BEGIN_SLOTTABLE(Worm)
   "speed",            // 1: speed
   "startAngle",       // 2: starting angle (off X axis)
END_SLOTTABLE(Worm)

BEGIN_SLOT_MAP(Worm)
   ON_SLOT(1, setSlotSpeed, mixr::base::Number)
   ON_SLOT(2, setSlotAngle, mixr::base::Angle)
   ON_SLOT(2, setSlotAngle, mixr::base::Number)
END_SLOT_MAP()

BEGIN_EVENT_HANDLER(Worm)
END_EVENT_HANDLER()

Worm::Worm()
{
   STANDARD_CONSTRUCTOR()
   setSpeed(10.0);
}
```
- The Worm source file is similar to other source files. There is a slot table that contains all of the variables, as well as a map to map those variables from the input file. `BEGIN_EVENT_HANDLER` is also a MIXR macro, so I assume that it will keep track of the worms and keep updating them.

###  main.cpp
```cpp

const int frameRate{20};
mixr::glut::GlutDisplay* glutDisplay{};

// timerFunc() -- Time critical stuff)
void timerFunc(int)
{
   const double dt{1.0 / static_cast<double>(frameRate)};
   const int millis{static_cast<int>(dt * 1000)};
   glutTimerFunc(millis, timerFunc, 1);

   mixr::base::Timer::updateTimers(static_cast<float>(dt));
   mixr::graphics::Graphic::flashTimer(static_cast<double>(dt));
   glutDisplay->tcFrame(static_cast<double>(dt));
}
```
- This is a new timer function right above the factory class. It is used for time critical processes

```cpp
glutInit(&argc, argv);

std::string configFilename = "file0.edl";

glutDisplay = builder(configFilename);

glutDisplay->createWindow();
```
- Under the main function, these lines will craete the Glut display and generate a window.

```cpp
 const double dt{1.0 / static_cast<double>(frameRate)};
   const int millis{static_cast<int>(dt * 1000)};
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();
   ```
   - A timer is set and the main loop for the glut display is called to keep the windown updated.



[Tutorial 7 Files](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial07)

## Tutorial 8 - Pagers

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

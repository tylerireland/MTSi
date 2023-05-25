# Working with MIXR (Mixed Reality Simulation Platform)

### **_Table of Contents_**
- [Opening MIXR in Visual Studio](#opening-mixr-in-visual-studio)
- [Running an Example](#running-an-example)
- [MIXR Basics](#mixr-basics)
- [Tutorials](#tutorials)
- [mainSim1 example](#mainsim1-example)
- [Additional Links](#additional-links)


In this write up :
- I will explain how to open up Mixr with Visual Studio
- I will show how to add and run some examples
- I will record my process in creating a simple graphical simulation  

By the end I hope to a have solid understanding of mixr and how each component works together.

### Goal
I am working with the mainSim1 example, which is a simple simulation of an aircraft flying at a set speed. I plan to track it's position and output it to a graphical display. Eventually, I may try to find ways to interact with the aircrafts velocity and heading and also output that to a display.


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

## MIXR Basics
These two links provide a good amount of information on MIXR, like the history and overview, as well as the framework.
- [The Mixed Reality Simulation Platform (MIXR)](https://www.mixr.dev/assets/pages/docs/the-mixed-reality-simulation-platform-csc-2018.pdf)  
- [Mixr Documentation](https://www.mixr.dev/docs.html)

## Tutorials
Below are the 8 tutorials provided. I will be writing what each tutorial consists of.

Links to the files:  
[Tutorial 1](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial01) &emsp;&emsp; [Tutorial 2](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial02) &emsp;&emsp; [Tutorial 3](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial03) &emsp;&emsp; [Tutorial 4](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial04)   
[Tutorial 5](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial05) &emsp;&emsp; [Tutorial 6](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial06) &emsp;&emsp; [Tutorial 7](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial07) &emsp;&emsp; [Tutorial 8](https://github.com/tylerireland/MTSi/tree/main/MIXR/code/tutorial08)
       
 
  

### Tutorial 1
The first tutorial is a simple "Hello World" program using their **String** class.
- To access the string, we have to use the `->` symbol to call a function within the string class, i.e ` str->getString() `.
- Next, the program set that string variable to a new string using the command ` str->setString("Goodbye World\n") `.
- Since we created a new object in the heap, we have to make sure we delete it when done. We do that by using the ` unref() ` command, ` str->unref() `.

### Tutorial 2
The second tutorial creates a random number generator object and outputs 10 random numbers.
- You can create a new rng object wiht ` const auto rng = new Rng() `.
- The next line sets a ` seed `. The seed is an arbirtrary number that will let the random generator know which 'random' numbers to output. Random numbers are not actually random. You can think of it as a really larger list of numbers with no particular order. The seed will determine where to start reading from the list. This program will not output new random numbers each time I run this if I do not change the seed.
- The next line is a loop that outputs 10 random numbers.
- Lastly, the object is deleted.

### Tutorial 3
Tutorial 3 start to create objects using factories and builders. From what I understand, a factory will read in the inputs from the input files and deal with them accordingly. With this example, it looks like it checks to make sure that the Rng object is the correct object to create based on the given name.
- The factory and builder are defined in main.cpp. Starting with the factory class, they are crating a new object to store the Rng into it. First though, it checks to make sure ` name == Rng::getFactoryName() `. This is what I am not too sure about. It looks like name is defined within one of the files while the builder method is being executed. In broad terms, it looks like the factory is essentially creating a new Rng object.
- The builder is reading in the .edl file, which was created from the .epp (input) file. It will create the slot tables required based on the inputs in the file.
- In main, once the builder is finished, it runs the same loop from the last tutorial and prints out ten random numbers. The seed is in the .edl file, meaning that the Rng class has a 'seed' slot in the slot table.
- The object is deleted at the end of the program.

### Tutorial 4
### Tutorial 5
### Tutorial 6
### Tutorial 7
### Tutorial 8



## mainSim1 example

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




### Additional Links
- [The Mixed Reality Simulation Platform (MIXR)](https://www.mixr.dev/assets/pages/docs/the-mixed-reality-simulation-platform-csc-2018.pdf)  
- [Mixr Documentation](https://www.mixr.dev/docs.html)  
- [Design & Implementation of Virtual Simulations](https://www.mixr.dev/assets/pages/docs/iitsec-2008-tutorial.pdf)

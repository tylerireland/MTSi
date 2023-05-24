- I am going to interact with the mainSim1 mixr example and attempt to connect a graphic to the simulation. 
- I will be writing down all the step and my journey to accomplish this task.
- I will format this document later, after I get a few things done!
- This is the [.epp](https://github.com/tylerireland/MTSi/blob/main/test0.epp) file that I will be manipulating.


# Beginning

- I first opened the example as well as the epp file to see how they go together
- 
### Running the Example
1. To run an example, open up the mixr.sln file into Visual Studio.
2. Select File > Add > Existing Project
3. In the file explorer, select ` mixr_examples / build / vs2017 / mainSim1.vcxproj `
4. This should add the project into the solution.
5. Before running the project, open up the mixr_examples folder once again, but this time select the folder with the same name as your project
6. Double Click ` make-edl.cmd `. This will create any required .edl files to run the program
7. Back in Visual Studo, right click on your project and select ` Set as Startup Project ` and the run the solution
8. The project should build and run successfully

### The epp file
1. The .epp file is located in ` mixr_examples / mainSim1 / configs `
- At first glance, this file is really small. There are not many line at all. The description says that it is a single aircraft player (player being the aircraft).
- A station is initialized and within the station contains an image generator, an interoperability interface, and a simulation scenario. 
    - Both interfaces are commented out, so I believe that they are not too important for the prgram to run.
- Looking at the simualtion scenario, there is a lat/postion, as well as a player that continase the aircraft name, id, type, signature, XPos, Ypos, altitude,
  heading, velocity, and side.
- The player is an blue-sided F-16A Aircraft, with an altitude of 20000 feet, and a velocity of 250 (mph?)
- In this simulation, this aircraft is flying at 250 (mph?), so I am going to find a way to track his position and update it to the console. Once completed, I will try to output the positon to a GLUT display.


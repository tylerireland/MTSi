# Setting up Visual Studio and C++ Compiler

This is a guide on setting up visual studio and the c++ compiler.

### Installing VSCode

1. Download Visual Studio Code -- I selected the x64 System Installer to install it to the machine. Link to download [**_here_**](https://code.visualstudio.com/download)  

### Configuring the C++ Compiler

2. Open up VSCode and select the extensions tab on the left hand side -- this is where we will find the c compiler to download.

3. Search "c++" and select the 'C/C++' and install.

4. Download MSYS2 to install MinGW -- this will install the g++ compiler to the system. Link to installer [**_here_**](https://github.com/msys2/msys2-installer/releases/download/2022-06-03/msys2-x86_64-20220603.exe)

5. Once installed, open up the MSYS2 Terminal and run ` pacman -S mingw-w64-ucrt-x86_64-gcc ` to install MinGW.

6. Next run ` pacman -S --needed base-devel mingw-w64-x86_64-toolchain ` to install the gdb debugger.

7. Once both commands complete, search 'Edit environment variables for your account' in the Windows search bar.

8. Select the Path user variable, and then select Edit > New, and enter the path to mingw, default is ` C:\msys64\mingw64\bin `.

9. Once completed, open up windows command prompt and test these three commands, 'gcc --version', 'g++ --version', and 'gdb --version' to make sure they are
	successfully installed.

10. Now, create a new folder and open it in VSCode.

11. Create a new file in that folder named 'helloworld.cpp' and create a program that outputs "hello world".

12. Select Terminal > Run Build Task and select the ` C/C++:g++.exe build active file ` task.

13. Select Terminal > New Terminal and run `./helloworld `!



 ||| About the Project |||
	This project was started as a way to better familiarize myself with
C++, and to create something visually interesting. This particular
goal was ripped straight from Daniel Shiffman's CodingTrain video
series on the Fourier Transform. 

 ||| Compilation |||
 Dependencies
 	A working C++ build environment
 		libstdc++, compiler, linker, assmebler, etc, etc.
 	SDL2	- just the base, none of the extras for images or sound
 
 Makefiles
 	Linux -- The standard file builds for Linux targets, and expects
 	SDL to be installed to the system (/usr/include/SDL/*.h). 
 	If it is not, the appropriate options must be added to tell
 	the compiler and linker where the files are located
 	
 	Windows -- Because I'm working on a Linux host, I had to grab a
 	MinGW compiler, and a copy of SDL Windows binaries (the DLL's and such). These
 	have been put in the SDL_src directory in my project. This directory
 	has been excluded from the git repo, however, and must be downloaded
 	if you want to build for Windows. See the SDL downloads page: 
 	[[[ https://www.libsdl.org/download-2.0.php ]]]
 	If you are on a Windows host, or have your windows-compatible SDL
 	source/headers located outside the project directory, you should
 	modify the INCLUDE_PATHS and LIBRARY_PATHS variables to point to
 	the appropriate location. Don't forget that SDL.dll must be included with
 	the output binary, if it isn't installed to the system (and it probably isn't). 
 	This also means that the Makefile.windows may not actually 
 	produce a functioning binary! I have no way to test it. 
 

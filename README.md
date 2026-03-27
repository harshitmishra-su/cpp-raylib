# cpp-raylib

Some example programs using raylib in c++.

## How to use

Download the latest release for your OS and then run the executables inside it after unzipping it.

## How to build it yourself  

*YOU NEED TO HAVE CMAKE AND MAKE AND A C++ COMPILER INSTALLED AND ALSO ZIG INSTALLED IF YOU WANT TO CROSS COMPILE FOR DIFFERENT OS'S*  

1. Clone the repository
2. Go to the project directory.  
   All the programs are inside the src/ directory.
3. Build the .cpp file you want with cmake by providing it the source file name.

```bash
cmake -B build -D SOURCE_FILE=<source_file>.cpp
cmake --build build
```
### If you want to build it for a different OS

```bash
cmake -B build -D SOURCE_FILE=<source_file>.cpp -D TARGET=<target_triplet_of_the_os_you_want_to_build_for>
cmake --build build
```
*TARGET TRIPLET*
FOR WINDOWS - x86_64-windows-gnu
FOR LINUX - x86_64-linux-musl

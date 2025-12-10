# raylib-cpp
Some example programs using raylib in c++.

## How to use
### For linux
Download the latest release for linux, unzip it and then run the executables inside it.
### For windows
Download the latest release for windows, unzip it and then run the .exe files inside it

## How to build it yourself
### For linux
First install the raylib package from your package manager if available for your distribution,
or download the latest release of raylib for linux and install on your computer from 
(https://github.com/raysan5/raylib) if not available.
#### For Fedora or similar distributions
```bash
sudo dnf install raylib-devel
sudo dnf install gcc_c++ #to install the g++ compiler
```
#### For Debian/Ubuntu or similar distributions
```bash
sudo add-apt-repository ppa:texus/raylib
sudo apt update
sudo apt install libraylib5-dev
sudo apt install build-essential
```
Compile and run using
```bash
g++ <source> -o <executable> -lraylib
./<executable>
```
### For windows
Download the latest release of raylib for windows from (https://github.com/raysan5/raylib),
unzip it, then place the include and lib folders inside it at say, C:\include and C:\lib,
respectively.

Then, compile and run the files
```powershell
g++ <source> -o <executable> -IC:\include -LC:\lib -lraylib -lopengl32 -lgdi32 -lwinmm
./<executable>
```
Thank you for checking this repository out.

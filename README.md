# Production Unit Test - prodUtest

prodUtest is a framework for production testing of electronic products

## Building in Windows

* Install TDM64 (or TDM32) - https://jmeubank.github.io/tdm-gcc/ (last confirmed working build was with TDM64-9.2)
* Install MSYS2 - https://www.msys2.org/
* Add the following to your environment path (with correct directory based on your install)
  * `C:\TDM-GCC-64\bin`
  * `C:\msys64\usr\bin`
* From an MSYS shell, run `pacman -S base-devel`
* In `C:\TDM-GCC-64\bin` rename, or copy and rename, `mingw32-make.exe` to `make.exe`
* Clone the repo, then next steps are in the cloned repo directory
* `bash autogen.sh`
* `bash ./configure build=i686-pc-linux-gnu CFLAGS=-m32 CXXFLAGS=-m32 LDFLAGS=-m32` (this configures for a 32-bit compile with 64-bit TDM)
* Edit the generated Makefile and change `MKDIR_P = /usr/bin/mkdir -p` to be `MKDIR_P = mkdir -p`
* `make`
* `make check`

### Some things you could do differently

* Install TDM32 instead (that may actually be simpler)
* To compile for 64-bit run `bash ./configure` without any parameters

## Referencing in your project

* In the project Makefile set the `CPPUTEST_HOME` to point to your prodUtest directory

## Debugging

* You can debug with GDB
* If you've compiled for 32-bit then install TDM32 and use the 32-bit GDB

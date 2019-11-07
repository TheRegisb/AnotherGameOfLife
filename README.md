# Another Game of Life
A cross-platform implementation of the John Horton Conway's “Game of Life” for both graphic and graphicless environment.

# Prerequisite
[CMake](https://cmake.org/) version 3.1 or greater and a C++ supporting C++11 is required.
The compiler must support 64bits compilations.

[SFML](https://www.sfml-dev.org/index.php) version 2.5.1 packages are required for compiling and running this game on UNIX platforms.
When downloading releases from repositories, selected the *-dev package for compilation.

The `conio.h` library must be available when compiling for Windows.

# Compilation
## UNIX Platform
Change directory to the root of the project, then run the following into the command line:
```
mkdir build && cd build && cmake .. && cmake --build .
```
If no errors took place, a program named `agof` should be located at the root of the `build` folder.

## Windows Platform
The resulting program can only be 64bits.


Change directory to the root of the project, then run the following into the command line, assuming the compiler is Visual C++:
```
mkdir build && cd build && cmake -G "Visual Studio [VERSION] [YEAR] [ARCHITECTURE (old)]" [ARCHITECTURE] && cmake --build . --target ALL_BUILD --config Release
```
Where [VERSION] and [YEAR] are the version and its year of Visual Studio and [ARCHITECTURE] is either `-A x64` for VS16 and greater or `win64` for previous version.
Example:
`cmake -G "Visual Studio 16 2019" -A x64` or `cmake -G "Visual Studio 15 2017 win64"`

# Usage
`agof [OPTIONS]`

where OPTIONS are:
```
  -H, --help
		Display this help message
  -a, --about
		Display version number, author and licensing
  -h, --height X
		Height of the board, must be greater than zero, 50 by default
  -w, --width Y
		Width of the board, must be greater than zero, 50 by default
  -n, --nox
		Render the game in stdout in a animated fashion
```

# License
SFML is licensed under thz zlib/png license.
Every other project files in this repository is licensed under the Apache License 2.0.


Please see the LICENSE file for more information.

# Credits
Régis BERTHELOT, 2019, as part of his master degree at the UVT.
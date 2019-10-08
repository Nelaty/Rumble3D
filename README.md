# Rumble3D
## 1. Building

**Visual Studio 2017**

To build the library, open the visual studio solution, select the desired platform and configuration and press <kbd>F7</kbd>.

**CMake**

Install the following packages:
```
apt-get install \
  cmake \
  g++ \
  libglm-dev
```

Create and navigate to your desired build directory (in this example `./build`) and run cmake:
```
mkdir build
cd build
cmake ..
```

Now just run `make` in your build directory.

The library will be created in the `lib` subdirectory (`./build/lib`)

## 2. Installation

**Visual Studio 2017**

Nuget packages:
* glm

Additional include directories:
* *Rumble3D/include*

Additional dependencies:
* Rumble3D.lib

## 3. Documentation
* [Doxygen](https://nelaty.github.io/Rumble3D/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/Rumble3D/UserManual/Rumble3D_UserManual.pdf)


**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
* Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"

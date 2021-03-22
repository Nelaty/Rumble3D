# Rumble3D
This 3D physics engine is based on the [cyclone physics engine](https://github.com/idmillington/cyclone-physics) by Ian Millington.

## 1. Building

The Rumble3D physics engine uses the hunter package manager. Dependencies will automatically be built when generating the project files with CMake.

**Linux**
```
cd <PROJECT_ROOT>
mkdir build
cd build
cmake ..
make -j
```

**Windows**
```
cd <PROJECT_ROOT>
mkdir build
cd build
cmake ..
cmake --build .
```

**Dependencies**
* glm


## 2. Installation
The built library can be installed using the command
```
make install
```
in the build directory (here ./build).

## 3. Documentation
* [Doxygen](https://nelaty.github.io/Rumble3D/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/Rumble3D/UserManual/Rumble3D_UserManual.pdf)

**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
2. Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"

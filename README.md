# Rumble3D
This 3D physics engine is based on the [cyclone physics engine](https://github.com/idmillington/cyclone-physics) by Ian Millington.

## 1. Overview
Available modules:
* Particle engine
* Rigid body engine

TBD

## 2. Building

Rumble3D provides a `CMakeSettings.json` file to configure, build and test the project. It uses the ninja build system by default. Dependecies are managed through git submodules.

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
* Catch2


## 3. Documentation
* [Doxygen](https://nelaty.github.io/Rumble3D/DoxygenDoc/html/index.html)
* [User manual](https://nelaty.github.io/Rumble3D/UserManual/Rumble3D_UserManual.pdf)

**Doxygen note:**
1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
2. Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"

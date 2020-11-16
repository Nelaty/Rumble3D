# Rumble3D
## 1. Building

**Dependencies**

* glm

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

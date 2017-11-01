# Installation and Reuse

There are a few different ways of installing/reusing `mp::inplace_string` in your project 

## Copy

`mp::inplace_string` is a standalone header-only library without any additional dependencies.
It can be simply copied to your source tree and used as a regular header file.

## cmake

To use `mp::inplace_string` as a `cmake` imported library exported as `cmake` target via `cmake`
configuration files following steps may be done.

### cmake install

```bash
mkdir build && cd build
cmake ../src -DCMAKE_INSTALL_PREFIX=<your_cmake_installation_dir> <your_cmake_configuration>
cmake --build . --target install <your_cmake_configuration>
```

To use such `cmake` target in your project it is enough to add following line to your `CMakeList.txt` file

```cmake
find_package(inplace_string CONFIG REQUIRED)
```

and configure it with

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=<your_cmake_installation_dir> <your_cmake_configuration>
```

### cmake + conan

To use `mp::inplace_string` with `cmake` via `conan` it is enough to:
- add following remote to your local `conan` instance

```bash
conan remote add conan-mpusz https://bintray.com/mpusz/conan-mpusz
```

- add following dependency to your `conanfile.txt` or `conanfile.py` files:

```python
requires = "inplace_string/0.0.3@mpusz/stable"
```


# Full build, unit testing and installation

In case you would like to build all the code in that repository and run all unit tests before
installation you can perform any of the following actions

## conan

```bash
conan test_package <username>/<channel> --build=missing <your_profile_and_settings>
```

## cmake

1. Manually install `gtest` with the same configuration to your preferred `CMAKE_INSTALL_PREFIX`
directory (e.g. `"~/local"`).

For example you can download `googletest` sources from [github](https://github.com/google/googletest)
and build them with:

```bash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<your_cmake_installation_dir> <your_cmake_configuration>
cmake --build . --target install <your_cmake_configuration>
```

2. Build, test and install `mp::inplace_string`

```bash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<your_cmake_installation_dir> <your_cmake_configuration>
cmake --build . <your_cmake_configuration>
ctest <your_ctest_configuration>
cmake --build . --target install <your_cmake_configuration>
```

## cmake + conan

```bash
mkdir build && cd build
conan install .. <your_profile_and_settings>
cmake .. <your_cmake_configuration>
cmake --build .
ctest
conan export -p .. <username>/<channel>
```

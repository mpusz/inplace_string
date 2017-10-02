[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg?maxAge=3600)](https://raw.githubusercontent.com/mpusz/in_place_string/master/LICENSE)
[![Travis CI](https://img.shields.io/travis/mpusz/inplace_string/master.svg?label=Travis%20CI)](https://travis-ci.org/mpusz/inplace_string)
[![AppVeyor](https://img.shields.io/appveyor/ci/mpusz/inplace-string/master.svg?label=AppVeyor)](https://ci.appveyor.com/project/mpusz/inplace-string)
[![Codecov](https://img.shields.io/codecov/c/github/mpusz/inplace_string/master.svg)](https://codecov.io/github/mpusz/inplace_string?branch=master)

# `mp::inplace_string<CharT, MaxSize, Traits>`

`mp::inplace_string<CharT, MaxSize, Traits>` is a `std::string`-like class template with the difference
that the text content is always stored in-place inside the class (like in SSO case in `std::string`).

# Repository structure

That repository contains 3 `cmake`-based projects:
 - `./src` - header-only project for `mp::inplace_string`
 - `.` - project wrapping `./src` project and adding unit tests for it
 - `./test_package` - project used in installed package verification process
 
Please note that all projects depend on some `cmake` modules in `./cmake` directory.

# Building, testing and installation

For detailed information on project compilation, testing and reuse please refer to
[INSTALL.md](install.md).

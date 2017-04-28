[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg?maxAge=3600)](https://raw.githubusercontent.com/mpusz/in_place_string/master/LICENSE)
[![Travis CI](https://img.shields.io/travis/mpusz/in_place_string/master.svg?label=Travis%20CI)](https://travis-ci.org/mpusz/in_place_string)
[![AppVeyor](https://img.shields.io/appveyor/ci/mpusz/in_place_string/master.svg?label=AppVeyor)](https://ci.appveyor.com/project/mpusz/in_place_string)
[![Codecov](https://img.shields.io/codecov/c/github/mpusz/in_place_string/master.svg)](https://codecov.io/github/mpusz/in_place_string?branch=master)

# `in_place_string<CharT, MaxSize, Traits>`

`in_place_string<CharT, MaxSize, Traits>` is a `std::string`-like class template with the difference
that the text content is always stored in-place inside the class (like in SSO case in `std::string`).

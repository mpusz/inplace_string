from conans import ConanFile, CMake

class InplaceString(ConanFile):
    name = "inplace_string"
    version = "0.0.3"
    author = "Mateusz Pusz"
    license = "https://github.com/mpusz/inplace_string/blob/master/LICENSE"
    description = "`std::string`-like class template that stores text content in-place inside the class"
    url = "https://github.com/mpusz/inplace_string"
    settings = "os", "compiler", "build_type", "arch"
    requires = "gtest/1.7.0@lasote/stable"
    default_options = "gtest:shared=False"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ["inplace_string"]

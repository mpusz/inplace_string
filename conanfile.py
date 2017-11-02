from conans import ConanFile, CMake

class InplaceStringConan(ConanFile):
    name = "inplace_string"
    version = "0.0.3"
    author = "Mateusz Pusz"
    license = "https://github.com/mpusz/inplace_string/blob/master/LICENSE"
    url = "https://github.com/mpusz/inplace_string"
    description = "`std::string`-like class template that stores text content in-place inside the class"
    settings = "os", "compiler", "build_type", "arch"
    build_requires = "gtest/1.7.0@lasote/stable"
    default_options = "gtest:shared=False"
    generators = "cmake"
    exports_sources = "src/*", "cmake/common/cmake/tools.cmake", "cmake/common/cmake/simple_package-config.cmake.in"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/src" % self.source_folder)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["inplace_string"]

    def package_id(self):
        self.info.header_only()

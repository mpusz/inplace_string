from conans import ConanFile, CMake

class InplaceStringTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "gtest/1.7.0@lasote/stable"
    default_options = "gtest:shared=False"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')

    def test(self):
        cmake = CMake(self)
        self.run("ctest -VV -C %s" % cmake.build_type)

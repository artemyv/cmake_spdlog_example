mkdir build
cmake -G "Visual Studio 17 2022" -H. -Bbuild -DCMAKE_GENERATOR_INSTANCE="D:\msbuild_test",version=17.7.34031.279
cmake --build build
mkdir build
cmake -H. -Bbuild 
cmake --build build --config Release --verbose
cmake --install build --prefix Release --config Release
ctest -G
ctest -VV -C Release
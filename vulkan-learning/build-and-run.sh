rm ./cmake-build-debug/vulkan

cmake -B cmake-build-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --fresh
cmake --build cmake-build-debug --target vulkan -j 18


./cmake-build-debug/vulkan

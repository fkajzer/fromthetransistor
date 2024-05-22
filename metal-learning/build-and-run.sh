rm -rf ./cmake-build-debug/src

cmake -B cmake-build-debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 --fresh
cmake --build cmake-build-debug -j 18

cmake --build build
rm -f ./images/$1.ppm
./build/one-weekend >> ./images/$1.ppm
open ./images/$1.ppm

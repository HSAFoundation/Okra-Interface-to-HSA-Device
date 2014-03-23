g++ -g -O0 -I../dist/include -Isrc/cpp -L../dist/bin -o ./dist/$1 src/cpp/$1/$1.cpp -lokra_x86_64
cp src/cpp/$1/$1.hsail dist

g++ -c set.cpp
g++ -c set.hpp
g++ -c -I../boost source.cpp
g++ -o set source.o set.o

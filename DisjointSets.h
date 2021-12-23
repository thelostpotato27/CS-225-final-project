#pragma once

#include <vector>

class DisjointSets {
    public: // function decs from doxygen
        void addelements(short num);// add an element
        short find(short elem);// find 
        short size(short elem);// get size
        void setunion(short a, short b);// make part of same set
    private:
        std::vector<short> elems; // we need a vector of parents
};
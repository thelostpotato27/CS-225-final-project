#include "DisjointSets.h"

void DisjointSets::addelements(short num){
    elems.resize(elems.size()+num, -1); // add num -1's to the end of elems
}

short DisjointSets::find(short elem){
    if(elems[elem]<0) return elem; // we found the root (stores negative size)
    else return elems[elem] = find(elems[elem]); // otherwise update current node to compress path, then return
}

void DisjointSets::setunion(short a, short b){
    a = find(a); // get roots
    b = find(b);
    if(a==b) return; // nothing to do, sets already the same
    if(elems[a]>elems[b]){ // else check smaller of two sets
        elems[b] += elems[a]; // add smaller's size to bigger's
        elems[a] = b; // make small point to big
    }
    else{
        elems[a] += elems[b];
        elems[b] = a;
    }
}

short DisjointSets::size(short elem){
    return -elems[find(elem)]; // negative size is stored in the root
}
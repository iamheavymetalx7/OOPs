#ifndef VECTOR_H
#define VECTOR_H
//no leave
#pragma once
#include <iostream>
using namespace std;
//basic file containing the header file


class Vector{
    public:
         double *A;
         int size;
         Vector();
         Vector(int);

};

 Vector::Vector(){
    size = 0;
 }

 Vector::Vector(int s){
    size = s;
    A = new double[size];
 }

#endif

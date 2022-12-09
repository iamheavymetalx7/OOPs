
#ifndef POINTS_H
#define POINTS_H
#pragma once
#include <iostream>
#include <vector>
#include "AD.h"
#include "Vector.h"
#include "Matrix.h"
using namespace std;

class DP{
     public:
         int i;
         int j;
         double x_coord;
         double y_coord;
         AD ad_object;
         DP();
         DP( int, int, double, double);
};

DP ::DP(){
     i = 0;
     j = 0;
     x_coord = 0;
     y_coord = 0;
}

DP :: DP(int i1, int j1, double x, double y){
     i = i1;
     j = j1;
     x_coord = x;
     y_coord = y;
     AD ad_object;
}

#endif
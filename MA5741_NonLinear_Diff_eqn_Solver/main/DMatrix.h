#ifndef DMATRIX_H
#define DMATRIX_H

#pragma once
#include <iostream>
#include "Points.h"
using namespace std;


class Discrete{
     public:
         int m;   //   total m rows
         int n;   //  total n cols
         double a,b,c,d;
         double del_X;
         double del_Y;
         //BP denotes the boundary points
         vector<DP> Points;
         vector<DP> BP_a;
         vector<DP> BP_b;
         vector<DP> BP_c;
         vector<DP> BP_d;
         Discrete( double, double, double, double, int, int);
         DP get_point(int, int);
         void setVal(vector<double>);

};

Discrete :: Discrete(double a1, double b1, double c1, double d1, int nx, int ny){
     m = nx;
     n = ny;
     a = a1;
     b = b1;
     c = c1;
     d = d1;
     del_X = (b-a)/m;
     del_Y = (d-c)/n;

     for(int i=0; i<=m; i++){
         for( int j=0; j<=n; j++){
             if( i == 0){ 
                DP temp( i, j, a + del_X * i, c + del_Y * j );
                AD temp2(0, (m-1)*(n-1));
                temp.ad_object = temp2;
                BP_a.push_back(temp);
             }
             else if( i == m){
                DP temp( i, j, a + del_X * i, c + del_Y * j );
                AD temp2(0, (m-1)*(n-1));
                temp.ad_object = temp2;
                BP_b.push_back(temp);

             }
             else if( j == 0){
                DP temp( i, j, a + del_X * i, c + del_Y * j );
                AD temp2(0, (m-1)*(n-1));
                temp.ad_object = temp2;
                BP_c.push_back(temp);

             }
             else if( j == n){
                DP temp( i, j, a + del_X * i, c + del_Y * j );
                AD temp2(0, (m-1)*(n-1));
                temp.ad_object = temp2;
                BP_d.push_back(temp);

             }
             else{
                DP temp( i, j, a + del_X * i, c + del_Y * j );
                AD temp2(0, (i-1)*(n-1) + j-1, (m-1)*(n-1));
                temp.ad_object = temp2;
                Points.push_back(temp);
             }
         }
     }



}

DP Discrete :: get_point(int ii, int jj){

    if( ii == 0){
         return BP_a[jj];
    }
    else if( ii == m){
         return BP_b[jj];
    }
    else if( jj == 0){
         return BP_c[ii - 1];
    }
    else if( jj == n){
         return BP_d[ii - 1];
    }
    else{
      int k = (ii-1)*(n-1) + jj - 1 ;
      return Points[k];
    }
}

void Discrete :: setVal( vector<double> values){
     for( int k = 0; k < Points.size(); k++){
        Points[k].ad_object.change_value_of_ind_var(values[k]);
     }
}

#endif

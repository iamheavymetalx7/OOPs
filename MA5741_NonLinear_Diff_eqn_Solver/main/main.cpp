#include<iostream>
#include<fstream>
#include "AD.h"
#include "LinearSolver.h"
#include "Non_linear.h"
#include "Matrix.h"
#include "Vector.h"
#include "Points.h"
#include "DMatrix.h"

#include<iomanip>
using namespace std;

/*
in case the newton method doesn't work, please go for the broyden method.
Also, the newton method sometimes fails to give the GridPoints.csv in that case also try the broyden method!!
Since newton method was failing in some cases, I have used the broyden method as my default choice.

One can edit the same by choosing choice as 1, if you want newton method! and any other integer for broyden method.

Similarly the default choice for linear system solver is Gauss seidel which is number 5, (but for third qn, 1st worked well!!)
one can choose other integer to use a certain linear solver.

Basically, if something is not working keep doing trial and error among the linear solver and non-linear solver.
input for q3 as E = "-1*(u^2-x^4-2*x^2-x+2)"
*/

int main(){
    string A,B,C,D,E;
    A = "1";
    B = "1";
    C = "u";
    D = "1";
    E = "-1*(u^2-x^4-2*x^2-x+2)";
    double a,b,c,d;
    a = 0;
    b = 2;
    c = 0;
    d = 1;
    string f1,f2,g1,g2;
    f1 = "0";
    f2 = "0";
    g1 = "0";
    g2 = "0";
    int nx,ny;
    nx = 10;
    ny = 10;
    int choice1;
    /*
    Input choice 1 = 1 -----> Newton Method
    Input choice 1 = any other integer ---->  Broyeden Method
    */
    choice1 = 12;

    int choice2;
    /*
    Input choice 2 = 1 -----> Gauss Elimination
    Input choice 2 = 2 -----> LU Decomposition
    Input choice 2 = 3 -----> TriDiagonal Method
    Input choice 2 = 4 ----->  Gauss Jacobi Method
    Input choice 2 = 5 -----> Gauss-Seidel Method
    Input choice 2 = 6 ----->  SOR Method
    */
    choice2=2;
     //Generating Postfix for all Expressions
     PostfixAll Postfix(A,B,C,D,E,f1,f2,g1,g2);
     
     Discrete Dpoints(a,b,c,d,nx,ny);
    
     // Setting Initial Guess
     //Initial guess 1.0 for all entries
     vector<double> random_;
     for (int k=0; k<(nx-1)*(ny-1); k++){
         random_.push_back(1.0);       
     }
    
     Dpoints.setVal(random_);
    
     if(choice1 == 1){

         Dpoints = Newton( Postfix, Dpoints, choice2, 0);
         cout<<endl<<"The answer is in the Points.csv file "<<endl;         

     }
     else{
         Dpoints = Broyeden( Postfix, Dpoints,choice2);
         cout<<"\n The answer is in the Points.csv file"<<endl;           }
   


    
     // Making a CSV (comma separated values) file
     fstream fout;
     fout.open("GridPoints_Qn3.csv", ios::out | ios::app);
     fout<<"x,"<<"y,"<<"z"<<endl;

     for(int i = 0; i<=nx; i++ ){
           for(int j = 0; j<=ny; j++){
                 fout<<Dpoints.get_point(i,j).x_coord<<","<<Dpoints.get_point(i,j).y_coord<<","<<Dpoints.get_point(i,j).ad_object.getf()<<","<<"\n";
           }
     }

 return 98128310939123981231;
}
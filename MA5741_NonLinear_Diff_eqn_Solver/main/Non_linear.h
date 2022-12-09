#ifndef NONLINEAR_H
#define NONLINEAR_H

#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include "AD.h"
#include "Matrix.h"
#include "LinearSolver.h"
#include "Vector.h"
#include "stacked.h"
#include "Points.h"
#include "DMatrix.h"
#define MAX 1000
using namespace std;



class charList {
private:
    string elements[MAX];
public:
    charList();
    charList(int);
    charList inf_to_post(string);
    AD eval( double, double, int, AD); //used to eval the expression
    void display(); 
    void addElement(string);
    void setElement(int, string);
    string getElement(int);
    int charPri(char); //the charPri for different operators
};



//charList
charList::charList() {
    for (int i = 0; i < MAX; i++) {
        elements[i] = "";
    }
}

void charList::display() {
    for (int i = 0; elements[i] != ""; i++) {
         if (elements[i] != "#") {
            cout << elements[i]<<"  ";
        }

    }
    cout << endl;
}

void charList::addElement(string j) {
    int i = 0;
    while (elements[i] != "") {
        i++;
    }
    elements[i] = j;
}

void charList::setElement(int i, string j) {
    this->elements[i] = j;
}

string charList::getElement(int i) {
    return elements[i];
}


int charList::charPri(char i) {
    if (i == '+' || i == '-') {
        return 1;
    }
    else if (i == '*' || i == '/') {
        return 2;
    }
    else if (i == '^') {
        return 3;
    }
    else if (i == '(') {
        return 4;
    }
    else if (i == ')') {
        return 5;
    }
    else if( (i >= 'a' && i <='z') || (i>= 'A' && i<='Z') || i=='_'){
       return 6;
    }
    else if( (i >= '0' && i <='9') || i== '.'){
       return 7;
    }
    else{
       return 0;
    }
}

charList charList ::inf_to_post( string Expression){

    string sym_ind_var[] = {"x","y","u"};

    int len = Expression.size();

    for( int i=0; i<len; i++){
       if( charPri(Expression[i]) < 6 && charPri(Expression[i]) != 0){
          string s = "";
          s.push_back(Expression[i]);
          addElement(s);
       }

       else if( charPri(Expression[i]) == 7){
          string num = "";
          while( charPri(Expression[i]) == 7 && i<len){
             num.push_back(Expression[i]);
             i++;
          }
          i--;
          addElement(num);
       }

       else if( charPri(Expression[i]) == 6){
          string word = "";
          while( charPri(Expression[i]) >= 6 && Expression[i] != '.' && i<len){
             word.push_back(Expression[i]);
             i++;
          }
          i--;
          addElement(word);
       }

   }


//Converting infix to postfix expression
    stacked<string> temp;
    charList postfix;

    for (int i = 0; elements[i] != ""; i++) {

       if ( charPri(elements[i][0]) == 7) {   
          postfix.addElement(elements[i]);
       }

       else if( charPri(elements[i][0]) == 6){ 
          int k = 0;
          for( int j=0; j<3; j++){
             if( elements[i] == sym_ind_var[j]){    
                postfix.addElement(elements[i]);
                k++;
             }
          }
          if (k == 0){
             temp.push(elements[i]);
          }
       }
       else if ( elements[i][0] == '(') {     
          temp.push(elements[i]);
       }
       else if ( elements[i][0] == ')') {
             while ((temp.getTopElement()[0] != '(') && (!temp.isEmpty())) {
                string x = temp.pop();
                postfix.addElement(x);
             }
             if (temp.getTopElement()[0] == '(') {
                   string x = temp.pop();
                   if( charPri(temp.getTopElement()[0]) == 6 ){
                      string y = temp.pop();
                      postfix.addElement(y);
                   }
             }

        }
       else if (charPri(elements[i][0]) < 3) {

          if (  !temp.isEmpty() && charPri(elements[i][0]) <= charPri(temp.getTopElement()[0]) ) {

             while ( !temp.isEmpty() && charPri(elements[i][0]) <= charPri(temp.getTopElement()[0]) && temp.getTopElement()[0] != '(') {
                   string x = temp.pop();
                   postfix.addElement(x);
             }
          }
            temp.push(elements[i]);

       }
       else if (charPri(elements[i][0])==3){

                if (charPri(elements[i][0]) < charPri(temp.getTopElement()[0]) && !temp.isEmpty() ) {
                   while ( !temp.isEmpty() && charPri(elements[i][0]) <= charPri(temp.getTopElement()[0]) && temp.getTopElement()[0] != '(') {
                      string x = temp.pop();
                      postfix.addElement(x);
                   }
             }

            temp.push(elements[i]);

         }
    }

    while (!temp.isEmpty()) {
        string x = temp.pop();
        postfix.addElement(x);
    }

    return postfix;


 }


AD charList::eval( double x, double y, int count_ind_var, AD u) {

    AD answer;
    stacked<AD> temp;

    string sym_ind_var[] = {"x","y","u"};
    AD x_cons(x, count_ind_var);
    AD y_cons(y, count_ind_var);
    AD ind_var[] = {x_cons, y_cons, u};

    for (int i = 0; elements[i] != ""; i++) {

       if (charPri(elements[i][0]) == 7) {
            double number = 0;
            int a = 0;
            int size = elements[i].size();

            for( int j=0; j<size; j++){
                if( elements[i][j] != '.'){
                      if( a == 0){
                         number = number * 10 + ( elements[i][j] - '0');
                      }
                      else{
                         number = number + (elements[i][j] - '0') * pow(10,a);
                      }
                }
                else if( elements[i][j] == '.'){
                       a--;
                }
            }
            AD cons(number, count_ind_var);
            temp.push(cons);
      }

       else if( charPri(elements[i][0]) == 6){
          int a = 0;

          for( int j = 0; j<count_ind_var; j++){
             if( elements[i] == sym_ind_var[j]){
                 temp.push(ind_var[j]);
                 a++;
             }
          }

          if( a == 0){
             AD y = temp.pop();
             AD z;

             if( elements[i] == "sin"){
                z = sin(y);
                a++;
             }
             else if( elements[i] == "cos"){
                z = cos(y);
                a++;
             }
             else if( elements[i] == "tan"){
                z = tan(y);
                a++;
             }
             else if( elements[i] == "cosec"){
                z = cosec(y);
                a++;
             }
              else if( elements[i] == "sec"){
                z = sec(y);
                a++;
             }
             else if( elements[i] == "cot"){
                z = cot(y);
                a++;
             }
             else if( elements[i] == "arcsin"){
               z = arcsin(y);
               a++;
             }
             else if( elements[i] == "arccos"){
                z = arccos(y);
                a++;
             }
             else if( elements[i] == "arctan"){
                z = arctan(y);
                a++;
             }
             else if( elements[i] == "sinh"){
                z = sinh(y);
                a++;
             }
             else if( elements[i] == "cosh"){
                z = cosh(y);
                a++;
             }
             else if( elements[i] == "tanh"){
                z = tanh(y);
                a++;
             }
             else if( elements[i] == "log"){
                z = log(y);
                a++;
             }
             else if( elements[i] == "exp"){
                z = exp(y);
                a++;
             }
             else if( elements[i] == "abs"){
                z = abs(y);
                a++;
             }

             temp.push(z);
          }
          if ( a == 0){
             cout<<"Invalid";
             abort();
          }

      }

      else if( charPri(elements[i][0]) <= 3) {
            AD y = temp.pop();
            AD x;
            if( !temp.isEmpty()){
               AD m = temp.pop();
               x=m;
            }
            else{
               AD m(0,count_ind_var);
               x=m;
            }
            AD z;

            if (elements[i][0] == '+') {
                z = x + y;
            }
            else if (elements[i][0] == '-') {
                z = x - y;
            }
            else if (elements[i][0] == '*') {
                z = x * y;
            }
            else if (elements[i][0] == '/') {
                z = x / y;
            }
            else if (elements[i][0] == '^') {
                z = x ^ y;
            }
            temp.push(z);
      }
    }
    answer = temp.getTopElement();
    return answer;
}


//Cost function globally defined
double Costfunc(vector<double> xold, vector<double> xnew){
      double temp = 0;
      int length = xold.size();
      for( int i = 0; i<length; i++){
        temp += pow(xold[i]-xnew[i],2);
      }
      temp = sqrt(temp);
      return temp;
}





// evaluation of postfix for all the given expressions
class PostfixAll{
   public:
        charList A_postfix;
        charList B_postfix;
        charList C_postfix;
        charList D_postfix;
        charList E_postfix;
        charList f1_postfix;
        charList f2_postfix;
        charList g1_postfix;
        charList g2_postfix;

        PostfixAll(string, string, string, string, string, string, string, string, string);
};

PostfixAll :: PostfixAll(string A, string B, string C, string D, string E, string f1, string f2, string g1, string g2  ){
       A_postfix = A_postfix.inf_to_post(A);
       B_postfix = B_postfix.inf_to_post(B);
       C_postfix = C_postfix.inf_to_post(C);
       D_postfix = D_postfix.inf_to_post(D);
       E_postfix = E_postfix.inf_to_post(E);

       f1_postfix = f1_postfix.inf_to_post(f1);
       f2_postfix = f2_postfix.inf_to_post(f2);
       g1_postfix = g1_postfix.inf_to_post(g1);
       g2_postfix = g2_postfix.inf_to_post(g2);
}



//Non Linear

//Newton function function
Discrete Newton( PostfixAll Postfix, Discrete Dpoints, int choice2, int iteration_count){

   cout<<"Newton Iteration count "<<iteration_count<<" : "<<endl;
   int count_ind_var = Dpoints.Points.size();

   //Boundary Points
   for( int j=0; j<= Dpoints.n; j++){
       double x_val = Dpoints.get_point(0,j).x_coord;
       double y_val = Dpoints.get_point(0,j).y_coord;
       AD non_use(0,count_ind_var);
       AD f1val = Postfix.f1_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_a[j].ad_object = f1val;
   }

   for( int j=0; j<= Dpoints.n; j++){
       double x_val = Dpoints.get_point(Dpoints.m,j).x_coord;
       double y_val = Dpoints.get_point(Dpoints.m,j).y_coord;
       AD non_use(0,count_ind_var);
       AD f2val = Postfix.f2_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_b[j].ad_object = f2val;
   }

   for( int i=0; i< Dpoints.m - 1; i++){
       double x_val = Dpoints.get_point(i+1,0).x_coord;
       double y_val = Dpoints.get_point(i+1,0).y_coord;
       AD non_use(0,count_ind_var);
       AD g1val = Postfix.g1_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_c[i].ad_object = g1val;
   }

   for( int i=0; i< Dpoints.m -1 ; i++){
       double x_val = Dpoints.get_point(i+1,Dpoints.n).x_coord;
       double y_val = Dpoints.get_point(i+1,Dpoints.n).y_coord;
       AD non_use(0,count_ind_var);
       AD g2val = Postfix.g2_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_d[i].ad_object = g2val;
   }

   // Set of Non-Linear Equations stored as fns array
   AD *fns;
   fns = new AD[count_ind_var];
   vector <double> Func;

   vector <double> xold;
   for( int i = 0; i< (Dpoints.m - 1)*(Dpoints.n - 1); i++){
     xold.push_back(Dpoints.Points[i].ad_object.getf()) ;
    }

    //Generating non Linear Equations
   for( int k=0; k < count_ind_var; k++){

       double x_val = Dpoints.Points[k].x_coord;
       double y_val = Dpoints.Points[k].y_coord;

       AD coeff_A = Postfix.A_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_B = Postfix.B_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_C = Postfix.C_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_D = Postfix.D_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_E = Postfix.E_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);




       int i = Dpoints.Points[k].i;
       int j = Dpoints.Points[k].j;


       AD FirstTerm = ( Dpoints.get_point(i+1,j).ad_object - 2 * Dpoints.get_point(i,j).ad_object + Dpoints.get_point(i-1,j).ad_object ) / ( Dpoints.del_X * Dpoints.del_X ) ;
       AD SecTerm = ( Dpoints.get_point(i,j+1).ad_object - 2 * Dpoints.get_point(i,j).ad_object + Dpoints.get_point(i,j-1).ad_object ) / ( Dpoints.del_Y * Dpoints.del_Y ) ;

       AD ThirTerm = ( Dpoints.get_point(i+1,j).ad_object - Dpoints.get_point(i-1,j).ad_object ) / ( 2 * Dpoints.del_X ) ;
       AD Fourterm = ( Dpoints.get_point(i,j+1).ad_object - Dpoints.get_point(i,j-1).ad_object ) / ( 2 * Dpoints.del_Y ) ;

       fns[k] = coeff_A * FirstTerm + coeff_B * SecTerm + coeff_C * ThirTerm + coeff_D * Fourterm + coeff_E;


       Func.push_back(-1 * fns[k].getf());
   }

   //Finding Jacobian
   Matrix Jacobian = getJacobian(fns);
//solving linear equation
    vector<double> y ;

    if( choice2 == 1){
        y = GaussElimination_solve(Jacobian,Func);
    }
    else if( choice2 == 2){
        y = LU_Decomposition_solve(Jacobian,Func);
    }
    else if( choice2 == 3){
        y = TriDiagonal_solve(Jacobian,Func);
    }
    else if( choice2 == 4){
        y = Gauss_Jacobi_solve(Jacobian,Func);
    }
    else if( choice2 == 5){
        y = Gauss_Seidal_solve(Jacobian,Func);
    }
    else if( choice2 == 6){
        y = SOR_solve(Jacobian,Func);
    }

   vector<double> xnew(xold.size());

   for( int i = 0; i<xold.size(); i++){
      xnew[i] = xold[i] + y[i];
   }


    cout<<"Cost Function = "<<Costfunc(xold,xnew)<<endl;
    cout<<endl<<endl;
   if( Costfunc(xold,xnew) < 0.01){
        cout<<"End of Iterations"<<endl;
       return Dpoints;
   }
   else{
    return Newton( Postfix, Dpoints, choice2, iteration_count+1);
   }


}




///Broyeden function implementation globally


Discrete Broyeden( PostfixAll Postfix, Discrete Dpoints, int choice2)
{
 int iteration_count;
 int count_ind_var = Dpoints.Points.size();

 vector<double> x_prev(count_ind_var);   
 vector <double> x_cur(count_ind_var);    
 vector<double> x_nex(count_ind_var);    
 

 AD *fns;
 fns = new AD[count_ind_var];


 Matrix mat_Func_cur(count_ind_var,1);  
 Matrix mat_Func_prev(count_ind_var,1);

 Matrix mat_x_cur(count_ind_var,1);           
 Matrix mat_x_prev(count_ind_var,1);
 Matrix mat_x_nex(count_ind_var,1);

 Matrix mat_A_inverse_cur(count_ind_var,count_ind_var);
 Matrix mat_A_inverse_prev(count_ind_var,count_ind_var);


 for( iteration_count = 0; iteration_count == 0 || Costfunc(x_cur,x_nex) > 0.001; iteration_count++){

   cout<<"Broyden Iteration count "<<iteration_count<<" : "<<endl;

   

   for( int j=0; j<= Dpoints.n; j++){
       double x_val = Dpoints.get_point(0,j).x_coord;
       double y_val = Dpoints.get_point(0,j).y_coord;
       AD non_use(0,count_ind_var);
       AD f1val = Postfix.f1_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_a[j].ad_object = f1val;
   }
   for( int j=0; j<= Dpoints.n; j++){
       double x_val = Dpoints.get_point(Dpoints.m,j).x_coord;
       double y_val = Dpoints.get_point(Dpoints.m,j).y_coord;
       AD non_use(0,count_ind_var);
       AD f2val = Postfix.f2_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_b[j].ad_object = f2val;
   }
   for( int i=0; i< Dpoints.m - 1; i++){
       double x_val = Dpoints.get_point(i+1,0).x_coord;
       double y_val = Dpoints.get_point(i+1,0).y_coord;
       AD non_use(0,count_ind_var);
       AD g1val = Postfix.g1_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_c[i].ad_object = g1val;
   }
    for( int i=0; i< Dpoints.m -1 ; i++){
       double x_val = Dpoints.get_point(i+1,Dpoints.n).x_coord;
       double y_val = Dpoints.get_point(i+1,Dpoints.n).y_coord;
       AD non_use(0,count_ind_var);
       AD g2val = Postfix.g2_postfix.eval(x_val, y_val, count_ind_var, non_use);
       Dpoints.BP_d[i].ad_object = g2val;
   }

       for( int i = 0; i< (Dpoints.m - 1)*(Dpoints.n - 1); i++){
       x_cur[i] =  Dpoints.Points[i].ad_object.getf() ;
       mat_x_cur.setElement(i,0, x_cur[i]);
    }
    for( int k=0; k < count_ind_var; k++){

       double x_val = Dpoints.Points[k].x_coord;
       double y_val = Dpoints.Points[k].y_coord;

       AD coeff_A = Postfix.A_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_B = Postfix.B_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_C = Postfix.C_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_D = Postfix.D_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);
       AD coeff_E = Postfix.E_postfix.eval(x_val, y_val, count_ind_var, Dpoints.Points[k].ad_object);

       int i = Dpoints.Points[k].i;
       int j = Dpoints.Points[k].j;


       AD FirstTerm = ( Dpoints.get_point(i+1,j).ad_object - 2 * Dpoints.get_point(i,j).ad_object + Dpoints.get_point(i-1,j).ad_object ) / ( Dpoints.del_X * Dpoints.del_X ) ;
       AD SecTerm = ( Dpoints.get_point(i,j+1).ad_object - 2 * Dpoints.get_point(i,j).ad_object + Dpoints.get_point(i,j-1).ad_object ) / ( Dpoints.del_Y * Dpoints.del_Y ) ;

       AD ThirTerm = ( Dpoints.get_point(i+1,j).ad_object - Dpoints.get_point(i-1,j).ad_object ) / ( 2 * Dpoints.del_X ) ;
       AD Fourterm = ( Dpoints.get_point(i,j+1).ad_object - Dpoints.get_point(i,j-1).ad_object ) / ( 2 * Dpoints.del_Y ) ;

       fns[k] = coeff_A * FirstTerm + coeff_B * SecTerm + coeff_C * ThirTerm + coeff_D * Fourterm + coeff_E;

       mat_Func_cur.setElement(k,0,fns[k].getf());
   }

    if ( iteration_count == 0){

       for( int i = 0; i<count_ind_var; i++){
          
          Matrix Jacobian = getJacobian(fns);
          vector<double> col(count_ind_var);  
          vector<double> col_zeroes_one(count_ind_var,0);
          col_zeroes_one[i] = 1;
          

          if( choice2 == 1){
              col = GaussElimination_solve(Jacobian, col_zeroes_one);
          }
          else if( choice2 == 2){
              col = LU_Decomposition_solve(Jacobian, col_zeroes_one);
          }
           else if( choice2 == 3){
              col = TriDiagonal_solve(Jacobian, col_zeroes_one);
          }
          else if( choice2 == 4){
             col = Gauss_Jacobi_solve(Jacobian, col_zeroes_one);
          }
          else if( choice2 == 5){
             col = Gauss_Seidal_solve(Jacobian, col_zeroes_one);
          }
          else if(  choice2 == 6){
             col = SOR_solve(Jacobian, col_zeroes_one);
          }



          for(int j = 0; j<count_ind_var; j++){
             mat_A_inverse_cur.M[j][i] = col[j]; 
          }
       }
    }
   
    else{
       Matrix mat_s_0 = mat_x_cur - mat_x_prev;
       Matrix mat_y_0 = mat_Func_cur - mat_Func_prev;

       Matrix mat_s_0_transpose = Transpose(mat_s_0);
       Matrix mat_Term = mat_s_0_transpose * mat_A_inverse_prev * mat_y_0;
       
       double term = mat_Term.getElement(0,0);

       mat_A_inverse_cur = mat_A_inverse_prev + ( mat_s_0 - mat_A_inverse_prev * mat_y_0 ) * (mat_s_0_transpose * mat_A_inverse_prev) / (term) ;    
      
    }


    // x_next= x_prev - A_inverse * F(x_prev)

    mat_x_nex = mat_x_cur -  mat_A_inverse_cur * mat_Func_cur;

    
    for( int i = 0; i<count_ind_var; i++){
       x_nex[i] = mat_x_nex.getElement(i,0);
    }


    Dpoints.setVal(x_nex);

    for( int i = 0; i<count_ind_var; i++){
          mat_x_prev.M[i][0] = x_cur[i]; 
    }
    
    for( int i = 0; i<count_ind_var; i++){
          mat_Func_prev.M[i][0] = mat_Func_cur.M[i][0]; 
    } 

    for( int i = 0; i<count_ind_var; i++){
       for( int j = 0; j<count_ind_var; j++){ //updating
         mat_A_inverse_prev.M[i][j] = mat_A_inverse_cur.M[i][j];
       }
    }

    

    cout<<"Cost Function = "<<Costfunc(x_cur,x_nex)<<endl;
    cout<<endl<<endl;

 }

 return Dpoints;



 }


#endif































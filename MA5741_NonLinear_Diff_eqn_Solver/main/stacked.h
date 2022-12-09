#ifndef STACKED_H
#define STACKED_H
#pragma once
#include <iostream>
#define MAX 1000

#include "Matrix.h"

template <class M>
class stacked{
   private:
      M elements[MAX];
      int size;
   public:
      stacked();
      bool isEmpty();
      M getTopElement();
      void push(M value);
      M pop();
      int getSize();
};




//stack
template <class M>
stacked<M> :: stacked(){
   size = 0;
}

template <class M>
bool stacked<M> ::isEmpty(){
   if(size==0){
      return true;
   }
   return false;
}

template <class M>
int stacked<M> ::getSize(){
   return size;
}

template <class M>
M stacked<M> ::getTopElement(){
   return elements[size-1];
}

template <class M>
void stacked<M> ::push(M value){
   size++;
   elements[size-1] = value;
}

template <class M>
M stacked<M> ::pop(){
   size--;
   return elements[size];
}


#endif



/*************************************************************************
	> File Name: rb-tree.cpp
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 五  8/17 22:53:46 2018
 ************************************************************************/

#include<iostream>
using namespace std;

#include "rb-tree.h"

//prereq: pivot!=NULL and pivot->right !=NULL 
//and pivot->right->left != NULL
void RBTree::left_rotate(Node* pivot){
   Node* pivot_right = pivot->right;
   pivot->right = pivot_right->left;
   pivot_right->left->parent = pivot;
   pivot_right->parent = pivot->parent;

   if(pivot->parent==NULL){
        root = pivot_right;
   }else{
       if(pivot->parent->left==pivot){
           pivot->parent->left = pivot_right;
       }else{
           pivot->parent->right = pivot_right;
       }
   }
   
   pivot->parent = pivot_right;
   pivot_right->left = pivot;
}

//prereq:: pivot!=NULL and pivot->right != NULL
//and pivot->left->right != NULL
void RBTree::right_rotate(Node* pivot){
    Node* pivot_left = pivot->left;
    pivot->left = pivot_left->right;
    pivot_left->parent = pivot->parent;
    pivot_left->right->parent = pivot->parent;
    
    if(pivot->parent==NULL){
        root = pivot_left;  
    }else{
       if(pivot->parent->left==pivot){
           pivot->parent->left = pivot_right;
       }else{
           pivot->parent->right = pivot_right;
        }
    }
    pivot->parent = pivot_left;
    pivot_left->right = pivot;
}


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


void RBTree::Insert(int val){
    
    Node* node = new Node(val);
    
    if(root == NULL){
        node->color = Color::BLACK;
        root = node;
        return;
    }

    Node* parent = NULL;
    Node* ptr = root;
    //insert like a normal bst
    while(ptr!=NULL){
        parent = ptr; 
        if(ptr->val == val) return;
        if(ptr->val<val)
            ptr = ptr->right;
        if(ptr->val>val)
            ptr = ptr->left;
    }

    if(parent->val>val) {
        parent->left = node;
    }else{
        parent->right = node;
    }
                         
    node->parent = parent;

    //insert_rebalance
    insert_rebalance(node);
}

void RBTree::insert_rebalance(Node* cur_node){

    if(cur_node->Parent()==NULL){
        cur_node->color = Color::BLACK;
    }else if(cur_node->Parent()->color==Color::BLACK){
        return;
    }else if(cur_node->Uncle()!=NULL&&cur_node->Uncle()->color==Color::RED){
        cur_node->Parent()->color = Color::BLACK; 
        cur_node->Uncle()->color = Color::BLACK; 
        cur_node->Ancestor()->Color = Color::RED;
        insert_rebalance(cur_node->Ancestor());
    }
    //(cur_node->Uncle()==NULL||cur_node->Uncle()->color==Color::BLACK)
    else{
        if(cur_node==cur_node->Parent()->right&&cur_node->Parent()==cur_node->Ancestor()->left){
            left_rotate(cur_node->Parent());
            cur_node = cur_node->left;
            insert_rebalance(cur_node);
        }else if(cur_node==cur_node->Parent()->left&&cur_node->Parent()==cur_node->Ancestor()->right){
            right_rotate(cur_node->Parent());
            cur_node = cur_node->right;
            insert_rebalance(cur_node);

        }else if(cur_node==cur_node->Parent()->right&&cur_node->Parent()==cur_node->Ancestor()->right){
            cur_node->Parent()->color =  Color::BLACK;
            cur_node->Ancestor()->color =  Color::RED;
            left_rotate(cur_node->Ancestor());
        }else{
            cur_node->Parent()->color =  Color::BLACK;
            cur_node->Ancestor()->color =  Color::RED;
            right_rotate(cur_node->Ancestor());
        }

         
    }
}



/*************************************************************************
	> File Name: rb-tree.cpp
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 五  8/17 22:53:46 2018
 ************************************************************************/

#include<iostream>
using namespace std;

#include "rb-tree.h"

bool IsBlack(Node* node){
    return node==NULL||node->color == Color::BLACK;
}

//prereq: pivot!=NULL and pivot->right !=NULL 
void RBTree::left_rotate(Node* pivot){
   Node* pivot_right = pivot->right;
   pivot->right = pivot_right->left;
   if(pivot_right->left!=NULL) 
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
void RBTree::right_rotate(Node* pivot){
    Node* pivot_left = pivot->left;
    pivot->left = pivot_left->right;

    if(pivot_left->right!=NULL)
        pivot_left->right->parent = pivot->parent;

    pivot_left->parent = pivot->parent;
    
    if(pivot->parent==NULL){
        root = pivot_left;  
    }else{
       if(pivot->parent->left==pivot){
           pivot->parent->left = pivot_left;
       }else{
           pivot->parent->right = pivot_left;
        }
    }
    pivot->parent = pivot_left;
    pivot_left->right = pivot;
}


void RBTree::Insert(int val){
    
    Node* node = new Node(val);
    node->color = Color::RED;
    
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
        //val is already in the tree
        if(ptr->val == val) {
            delete node;
            return;
        }
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
        return; 
    }else if(cur_node->Parent()->color==Color::BLACK){
        return;
    }else if(cur_node->Uncle()!=NULL&&cur_node->Uncle()->color==Color::RED){
        cur_node->Parent()->color = Color::BLACK; 
        cur_node->Uncle()->color = Color::BLACK; 
        cur_node->Ancestor()->color = Color::RED;
        insert_rebalance(cur_node->Ancestor());
    }
    //(cur_node->Uncle()==NULL||cur_node->Uncle()->color==Color::BLACK)
    //when p.color==red, p.p.color must be not null
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

Node* RBTree::find_node(int val){
    Node* ptr = root;
    while(ptr!=NULL){
        if(ptr->val > val) ptr = ptr->left;
        else if(ptr->val < val) ptr = ptr->right;
        else return ptr;
    }

    return ptr;
}

bool RBTree::IsContains(int val){
    return find_node(val) != NULL;
}

Node* RBTree::find_post_successor(Node* cur_node){
    Node* ptr = cur_node->right;
    while(ptr->left!=NULL){
        ptr = ptr->left;
    }
    return ptr;
}

bool RBTree::Delete(int val){

    Node* del_node = find_node(val);
    //未找到要删除的节点
    if(del_node==NULL) return false;

    Node* real_node = NULL;
    Node* repl_node = NULL;
    if(del_node->left==NULL||del_node->right==NULL){
        real_node = del_node;   
    }else{
        real_node = find_post_successor(del_node);
    }

    if(real_node->left!=NULL){
        repl_node = real_node->left;
    }else {
        repl_node = real_node->right;
    }

    repl_node->parent = real_node->parent; 
    if(real_node->parent==NULL){
       root = repl_node; 
    }else{
        if(real_node==real_node->parent->left){
            real_node->parent->left = repl_node;
        }else{
            real_node->parent->right = repl_node;
        }
    }
    if(real_node!=del_node){
        del_node->val = real_node->val;
    }

    if(real_node->color==Color::BLACK){
        delete_rebalance(repl_node);
    }

    return true;
}

void RBTree::delete_rebalance(Node* cur_node){
    if(cur_node->parent==NULL) {
        cur_node->color = Color::BLACK;
        return;
    }
    Node* sibling = NULL;
    while(cur_node!=root&& cur_node->color==Color::BLACK){
        if(cur_node->Parent()->left!=cur_node)
            sibling = cur_node->Parent()->left;
        else
            sibling = cur_node->Parent()->right;
        if(sibling->color == Color::RED){
            cur_node->Parent()->color = Color::RED;  
            sibling->color = Color::BLACK;
            left_rotate(cur_node->Parent());
        }else{
            if(IsBlack(sibling->left)&&IsBlack(sibling->right)){
                sibling->color = Color::RED;
                cur_node = cur_node->parent;
            }else if(IsBlack(sibling->right)){
                //!IsBlack(sibling->left) 
                sibling->right->color = Color::RED;
                sibling->left->color = Color::BLACK;
                right_rotate(sibling);
                sibling = cur_node->Sibling();
            }else{
                //!IsBlack(sibling->right)
                sibling->left->color = Color::RED;
                cur_node->parent->color = Color::BLACK;
                left_rotate(cur_node->Parent());
                cur_node = root;
            }

        }
    }
}

int main(int argc, char** argv){
    
    return 0;
}


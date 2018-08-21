/*************************************************************************
	> File Name: rb-tree.h
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 一 12/26 10:34:42 2016
 ************************************************************************/

#ifndef _RBTREE_H
#define _RBTREE_H

#include <vector>
enum Color{ RED, BLACK } ;

class Node{
  public:
    
      Node* Parent(){
          return parent;
      }

      Node* Ancestor(){
          return parent->parent; 
      }

      Node* Uncle(){
          if(parent->parent->left==parent) return parent->parent->right; 
          return parent->parent->left;
      }

      Node* Sibling(){
          if(parent->left==this) return parent->right;
          return parent->left;
      }
    
    Node* left;
    Node* right;
    Node* parent;
    int val;
    Color color;
    Node(int val):val(val){
        parent = left = right = NULL;
        color = Color::RED;
    }

};

class RBTree{
    public: 
        RBTree():root(NULL){}
        void Insert(int val);
        bool Delete(int val);
        bool IsContains(int val);
        bool CheckOrder();

    private:
        void insert_rebalance(Node* cur_node);
        void delete_rebalance(Node* cur_node);
        Node* find_node(int val);
        Node* find_post_successor(Node* cur_node);
        void left_rotate(Node* cur_node); 
        void right_rotate(Node* cur_node);

        std::vector<int> get_all_nums();
        Node* root;
};

//check left rotate
//check right rotate
//check insert
//check delete
//stress testing


}



#endif

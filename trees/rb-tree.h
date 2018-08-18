/*************************************************************************
	> File Name: rb-tree.h
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 一 12/26 10:34:42 2016
 ************************************************************************/

#ifndef _RBTREE_H
#define _RBTREE_H

enum Color{ RED, BLACK };

struct Node{
    Node* left;
    Node* right;
    Node* parent;
    int val;
    Color color;
    Node(){
        parent = left = right = NULL;
        color = Color::RED;
    }

};

class RBTree{
    public: 
        RBTree():root(NULL){}
        bool Insert(int val);
        bool Delete(int val);
        bool IsContains(int val);
    private:
        void left_rotate(Node* cur_node); 
        void right_rotate(Node* cur_node);
        Node* root;

};


#endif

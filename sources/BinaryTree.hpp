//
// Created by Daniel Sela on 21/05/2021.
//
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
using namespace std;
namespace ariel {

    template<typename T>
    class BinaryTree {
        
//-----------------------------------------Node        
        struct Node {           
            T value;
            Node *left=nullptr;
            Node *right=nullptr;
            Node *parent= nullptr;
            Node(T v) 
                : value(v), left(nullptr), right(nullptr) , parent(nullptr){
                    value=v;
                }
            bool operator==(const Node &rhs) const {
                return rhs.value==this->value;
            }
            bool operator!=(const Node &rhs) const {
                return rhs.value!=this->value;
                       
            }
        };
        Node *root;

        public:
//------------------------------------------preorder     
        class iterator_pre { // pre 
            private:
                    Node* pointer_to_current_node;
                    stack<Node*> stack_node; // stack of node to save 
            public:
                    iterator_pre(Node* ptr=nullptr):pointer_to_current_node(ptr){ //Constructor
                        stack_node.push(ptr);
                    }
                    T& operator*() const{
                        return pointer_to_current_node->value;
                    }
                    T* operator->()const {
                        return &(pointer_to_current_node->value);
                    }
                    iterator_pre& operator++(){
                       if (!stack_node.empty()) {
                            stack_node.pop();
                            //get next node
                            if (pointer_to_current_node->right != nullptr) {
                                stack_node.push(pointer_to_current_node->right);
                            }
                            if (pointer_to_current_node->left != nullptr) {
                                stack_node.push(pointer_to_current_node->left);
                            }
                            // change the pointer 
                            if (stack_node.empty()) {
                                pointer_to_current_node = nullptr;
                            } else {
                                pointer_to_current_node = stack_node.top();
                            }
                        }
                        if (stack_node.empty()) {
                            pointer_to_current_node = nullptr;
                        }
                        return *this;
                    }
                   iterator_pre operator++(int){
                        const iterator_pre tmp = *this;
                        ++*this;
                        return tmp;
                    }
                    bool operator==(const iterator_pre& rhs) const{
                        return pointer_to_current_node==rhs.pointer_to_current_node;
                    }
                    bool operator!=(const iterator_pre& rhs) const{
                        return pointer_to_current_node!=rhs.pointer_to_current_node;
                    }
        };


//--------------------------------------------- post ------------------------------------------------------------------------------------------------------------
        class iterator_postorder { // post 
            private:
                    Node* pointer_to_current_node;
                    stack<Node*> stack_node; // stack of node to save
            public:
                    iterator_postorder(Node* ptr=nullptr):pointer_to_current_node(ptr){
                        if(ptr!= nullptr) {
                            stack<Node*> temp;
                            temp.push(ptr);
                            while (!temp.empty()) { //enter all node to stack 
                                Node *node = temp.top();
                                temp.pop();
                                stack_node.push(node);
                                if (node->left) {
                                    temp.push(node->left);
                                }
                                if (node->right) {
                                    temp.push(node->right);
                                }
                            }
                            pointer_to_current_node = stack_node.top();
                        }else{
                            pointer_to_current_node= nullptr;
                        }
                    }
                    iterator_postorder(stack<Node*> node_stk){ // for opertor ++this 
                        this->stack_node = node_stk;
                        this->pointer_to_current_node = node_stk.top();
                    }
                    T& operator*() const{
                        return pointer_to_current_node->value;
                    }
                    T* operator->()const {
                        return &(pointer_to_current_node->value);
                    }
                    iterator_postorder& operator++(){ 
                        if(!stack_node.empty()) {
                            this->stack_node.pop();
                        }
                        if(!stack_node.empty()) {
                            pointer_to_current_node=this->stack_node.top();
                        }else{
                            pointer_to_current_node= nullptr;
                        }
                        return *this;
                    }
                   iterator_postorder operator++(int){
                        const iterator_postorder tmp{this->stack_node};
                        ++*this;
                        return tmp;
                    }
                    bool operator==(const iterator_postorder& rhs) const{
                        return pointer_to_current_node==rhs.pointer_to_current_node;
                    }
                    bool operator!=(const iterator_postorder& rhs) const{
                        return pointer_to_current_node!=rhs.pointer_to_current_node;
                    }
        };


//--------------------------------------------- IN ------------------------------------------------------------------------------------------------------------
        class iterator_in { // post 
            private:
                    Node* pointer_to_current_node;
                    stack<Node*> stack_node;
            public:
                    iterator_in(Node* ptr=nullptr):pointer_to_current_node(nullptr){
                        Node*curr = ptr;
                        while(curr!= nullptr){
                            stack_node.push(curr);
                            curr = curr->left;
                        }
                        if(stack_node.empty()){
                            pointer_to_current_node= nullptr;
                        }else{
                            pointer_to_current_node= stack_node.top();
                        }
                    }

                    T& operator*() const{
                        return pointer_to_current_node->value;
                    }
                    T* operator->()const {
                        return &(pointer_to_current_node->value);
                    }
                    iterator_in& operator++(){
                        if(!stack_node.empty()) {
                            Node *temp = stack_node.top();
                            stack_node.pop();
                            if (temp->right != nullptr) {
                                stack_node.push(temp->right);
                                temp = temp->right->left;
                                while (temp != nullptr) {
                                    stack_node.push(temp);
                                    temp = temp->left;
                                }
                            }
                            if(stack_node.empty()){
                                pointer_to_current_node = nullptr;
                            }else{
                                pointer_to_current_node = this->stack_node.top();
                            }
                        }else{
                            pointer_to_current_node = nullptr;
                        }
                        return *this;
                    }
                   iterator_in operator++(int){
                        const iterator_in tmp = *this;
                        ++*this;
                        return tmp;
                    }
                    bool operator==(const iterator_in& rhs) const{
                        return rhs.pointer_to_current_node==this->pointer_to_current_node;
                    }
                    bool operator!=(const iterator_in& rhs) const{
                        return rhs.pointer_to_current_node!=this->pointer_to_current_node;
                    }
        };


        BinaryTree<T>():root(nullptr){ //CONSTRUCTOR
            root = nullptr;
        }

        BinaryTree<T> &add_root(const T& value){       
            if(root != nullptr){
                root->value = value;
            }else{
                root= new Node(value);
            }
            return *this;
        }
        
        Node *search(Node* node,T val){
            if(node == nullptr){
                return nullptr;
            }
            if(val==node->value){
                return node;
            }
            Node* left= nullptr;
            Node* right= nullptr;
            if(node->left!= nullptr){
                left = search(node->left,val);
            }
            if(node->right!= nullptr){
                right = search(node->right,val);
            }
            if(left!= nullptr){
                return left;
            }
            return right;
        };
       
        Node *search(T val){
            if(val==root->value){
                return root;
            }
            return search(root,val);
        };
       
        BinaryTree<T> &add_left(const T& exist,const T& new_left){
            Node* pNode = search(root,exist);
            if(pNode==nullptr){
                throw  std::invalid_argument("Cannot add new right child");
            }
            if(pNode->left== nullptr) {
                pNode->left = new Node(new_left);
                pNode->left->parent = pNode;
            } else{
                pNode->left->value=new_left;
            }
            return *this;
        }
      
        BinaryTree<T> &add_right(const T& exist,const T& new_right){
            Node* pNode = search(this->root,exist);
            if(pNode==nullptr){
                throw  std::invalid_argument("Cannot add new left child");
            }
            if(pNode->right== nullptr) {
                pNode->right = new Node(new_right);
                pNode->right->parent = pNode;
            }else{
                pNode->right->value=new_right;
            }
            return *this;
        }
//--------------------------------------------------------------
        iterator_pre begin_preorder(){
            return iterator_pre{root};
        }   
        iterator_pre end_preorder(){
            return iterator_pre{nullptr};
        }
//--------------------------------------------------------------
        iterator_in begin_inorder(){
            return iterator_in{root};
        }
        iterator_in end_inorder(){
            return iterator_in{nullptr};
        }
//--------------------------------------------------------------        
        iterator_postorder begin_postorder(){
            return iterator_postorder{root};
        }
        iterator_postorder end_postorder(){
            return iterator_postorder{nullptr};
        } 
//--------------------------------------------------------------
        iterator_in begin(){
            return iterator_in{root};
        }                         
        iterator_in end(){
            return iterator_in{nullptr};
        } 
//--------------------------------------------------------------          
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree<T> &tree){
                // print in pre order 
                os<<"__________________\nprint tree\n";
                if (tree.root == nullptr){return os;}
                    
                stack<Node*> s;
                s.push(tree.root);
            
                while (!s.empty()) {
                    Node* node = s.top();
                    os<<node->value<<" ";
                    s.pop();
                    if (node->right)
                        {s.push(node->right);}
                    if (node->left)
                        {s.push(node->left);}
                }
                os<<"\n__________________\n";
                return os;
        }   


        void delete_tree(Node *node) { // func to delet tree
            if(node != nullptr){
                delete_tree(node->right);
                delete_tree(node->left);
                delete node;
            }
        }

        void copy_constructor(Node* this_tree_node, const Node* other_tree_node) { // copy CONSTRUCTOR 
            if(other_tree_node->left != nullptr){
                this_tree_node->left = new Node(other_tree_node->left->value);
                copy_constructor(this_tree_node->left, other_tree_node->left);
            }
            if(other_tree_node->right != nullptr){
                this_tree_node->right = new Node(other_tree_node->right->value);
                copy_constructor(this_tree_node->right, other_tree_node->right);
            }
        }
        
        BinaryTree(const BinaryTree& bt) { // for copy constructor
            if(bt.root!= nullptr){
                this->root = new Node(bt.root->value);
                copy_constructor(root,bt.root);
            }
        }
        BinaryTree(BinaryTree &&bt) noexcept{ //move constructor
            this->root = bt.root;
            bt.root = nullptr;
        } 
        BinaryTree& operator =(const BinaryTree& other) {//copy assignment
            if(other.root!= nullptr){
                *this=BinaryTree(other);
            }
            return *this;
        }
        BinaryTree& operator =( BinaryTree&& other) noexcept{ // move assignment
            if(other.root!= nullptr){
                std::swap(root,other.root);
            }
            return *this;
        }
 
        ~BinaryTree(){
            delete_tree(this->root);
        } 

        
    };
        
}
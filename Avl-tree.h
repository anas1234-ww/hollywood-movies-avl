#pragma once
#include <string>
#include <iostream>
template <typename T>
struct TreeNode{
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode() : left(nullptr) , right(nullptr){}
    TreeNode(T value) : value(value) , left(nullptr) , right(nullptr){}
};
template <typename T>
class Avl{
    private:
      TreeNode<T>* root;
       /* functoin hight tree */
       int hieght(TreeNode<T>* cur){
           if (cur == nullptr) return 0;
           return 1 + std::max(hieght(cur->left) , hieght(cur->right));
       }
       /* balance factor */
       int balance_factor(TreeNode<T>* cur){
           if (cur == nullptr) return 0;
           return hieght(cur->left) - hieght(cur->right); 
       }
      /* right rotatoin */
      TreeNode<T>* right_rotaion(TreeNode<T>* cur){
          TreeNode<T>* new_root = cur->left;
          TreeNode<T>* rst = new_root->right;
          
          
          new_root->right = cur;
          cur->left = rst;
          return new_root;
      } 
      /* left rotatoin */  
      TreeNode<T>* left_rotaion(TreeNode<T>* cur){
           TreeNode<T>* new_root = cur->right;
           TreeNode<T>* rst = new_root->left;
           
          
          new_root->left = cur;
          cur->right = rst;
          return new_root;
      }
      /* function insert  */
      void insert_P(T value , TreeNode<T>*& root){
          /* root = nullptr insert value number one */
          if (root == nullptr){
              root = new TreeNode<T>(value);
              return;
          }
          /* insert new value if root != nullpt*/
          else {
              /* insert value if Less than root->value */
               if(value.id < root->value.id){
                  insert_P(value , root->left);
              }
              /* insert value if Bigger than root->value */
              else if (value.id > root->value.id){
                  insert_P(value , root->right);
              }
              /* Ignorance value if Equal root->value */
              else return;
              /* The process of balancing the tree */
              int BF = balance_factor(root);
              /* left left rotatoin */
              if (BF > 1 && root->left->value.id > value.id){
                  root = right_rotaion(root);
              }
              /* left right rotatoin */
              else if (BF > 1 && root->left->value.id < value.id){
                  root->left = left_rotaion(root->left);
                  root = right_rotaion(root);
              }
              /* right right rotatoin */
              else if (BF < -1 && root->right->value.id < value.id){
                  root = left_rotaion(root);
              }
              /* right left rotatoin */
              else if (BF < -1 && root->right->value.id > value.id){
                  root->right = right_rotaion(root->right);
                  root = left_rotaion(root);
              }
          }
      }
    /* Search functoin */
    TreeNode<T>* Search_P(T value , TreeNode<T>* const root){
        /* root = nullptr tree is empty */
        if (root == nullptr) return nullptr;
        /* root-> Equal value stop */
        if (root->value.id == value.id) return root;
        /* Search process */
        else{
            if (value.id < root->value.id){
                return Search_P(value , root->left);
            }
            else {
                return Search_P(value , root->right);
            }
        }
    }
    /* functoin minvalue */
      TreeNode<int>* minvalue(TreeNode<int>* cur){
          if(cur == nullptr) return 
          cur;
			/*
			if(cur->left == nullptr) return cur;
			else return minvalue(cur->left);*/
          while (cur->left != nullptr) cur = cur->left;
          return cur;
      }
    /* Delete functoin */
      TreeNode<T>* Delete_Node(TreeNode<T>* cur, T value){
        if (cur == nullptr) return nullptr;
          
/* The process of searching for the target element is to delete it. */
        if (value.id < cur->value.id){
            cur->left = Delete_Node(cur->left ,value);
        }
        else if(value.id > cur->value.id){
            cur->right = Delete_Node(cur->right , value);
        }
        /* The process delete */  
        else {
            /* Delete the item if it has a child on the right or no children. */
            if (cur->left == nullptr){
                TreeNode<T>* temp = cur->right;
                delete cur;
                return temp;
            }
            /* Delete the item if it has a child on the left */
            else if (cur->right == nullptr){
                TreeNode<T>* temp = cur->left;
                delete cur;
                return temp;
            }
            /* Delete the item if it has two children */
            else{
                TreeNode<T>* temp = minvalue(cur->right);
                cur->value = temp->value;
                cur->right = Delete_Node(cur->right , temp->value);
            }
        }
          int bf = balance_factor(cur);
          if (bf > 1){
              if (balance_factor(cur->left) >= 0){
           return right_rotaion(cur);
              }
              else {
                  cur->left = left_rotaion(cur->left);
                  return right_rotaion(cur);
              }
          }
          else if (bf < -1){
              if (balance_factor(cur->right) <= -1){
                  return left_rotaion(cur);
              }
              else {
                  cur->right = right_rotaion(cur->right);
                  return left_rotaion(cur);
              }
          }
          return cur;
}
    public:
      Avl() : root(nullptr){}
    void insert(T value){
       insert_P(value ,root);
   }
    TreeNode<T>* Search(T value){
       return Search_P(value , root);
    }
    void pop(T value){
        root = Delete_Node(root , value); 
    }
    TreeNode<T>*& RetRoot(){
        return root;
    }
};

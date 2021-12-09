#ifndef OCTOPUS_GAMES_TREENODE_H
#define OCTOPUS_GAMES_TREENODE_H

#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "Utils.h"

#define LEFT 1
#define ROOT 0
#define RIGHT -1
#define NULL_HEIGHT -1


using namespace std;

namespace WET1 {
    template<class K, class T>
    class TreeNode {
        K key;
        T data;
        TreeNode<K,T> *parent;
        TreeNode<K,T> *right;
        TreeNode<K,T> *left;
        int height;


        int leftHeight() const;
        int rightHeight() const;
        int BF() const;
        void updateHeight();
        void rollLeft();
        void rollRight();
        int whoAmI() const;
        void rollLL();
        void rollRR();
        void rollRL();
        void rollLR();
        void roll();
        TreeNode<K,T> *fix(bool stop_at_root = false);
        void gulag();
        void toSortedArrayAux(K sortedArr_K[], T sortedArr_T[], int *idx, int size=-1) const;
        static TreeNode<K,T> *arrayToTreeAux(const K sortedArr_K[], const T sortedArr_T[], int startIdx, int size, TreeNode<K,T> *parent);
        void print2DUtil(int space) const;

    public:
        TreeNode() = delete;
        TreeNode(const K& key, const T& data);
//        TreeNode(const TreeNode& tree);
//        TreeNode<K,T>& operator=(const TreeNode<K,T>& tree);
        ~TreeNode()=default;

        bool isLeaf() const;
        K& getKey();
        T& getData();
        TreeNode<K,T>* getParent();
        TreeNode<K,T>* find(const K& key);
        void insert(const K& key, const T& data);
        TreeNode<K,T>* remove(const K& key);
        TreeNode<K,T>* removeNode(const K& key);
        TreeNode<K,T>* getMax();
        void toSortedArray(K sortedArr_K[], T sortedArr_T[], int size=-1) const;
        static TreeNode<K,T>* arrayToTree(const K sortedArr_K[], const T sortedArr_T[], int size);
        static TreeNode<K,T>* merge(const TreeNode<K,T> *tree1, const TreeNode<K,T> *tree2, int size1, int size2);
        void print2D() const;
        void removeAll(TreeNode<K,T>* node);

        template <typename P>
        void query(P pred, T* dest_arr, int size, int* found){
            if(*found >= size){
                return;
            }

            if(this->left != nullptr){
                return this->left->query(pred, dest_arr, size, found);
            }

            if(pred(this->data)){
                dest_arr[(*found)++] = this->data;
            }

            if(this->right != nullptr){
                return this->right->query(pred, dest_arr, size, found);
            }
        }

        template<typename P>
        void apply(P pred, void* arg){
            pred(this->data, arg);

            if(this->left != nullptr){
                this->left->apply(pred, arg);
            }

            if(this->right != nullptr){
                this->right->apply(pred, arg);
            }
        }

    };

    template <class K, class T>
    TreeNode<K,T>::TreeNode(const K& key, const T& data)
        : key(key), data(data), parent(nullptr), left(nullptr), right(nullptr), height(0)
    {}

//    template <class K, class T>
//    TreeNode<K,T>::~TreeNode(){
//        if(this == nullptr){
//            return;
//        }
//
//        delete this->left;
//        delete this->right;
//
////        T* tmp = &(this->data);
// //       this->gulag();
////        delete tmp;
//    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::getParent(){
        return this->parent;
    }

    template <class K, class T>
    K& TreeNode<K,T>::getKey() {
        return this->key;
    }

    template <class K, class T>
    T& TreeNode<K,T>::getData() {
        return this->data;
    }

    template <class K, class T>
    bool TreeNode<K,T>::isLeaf() const{
        return this->left == nullptr && this->right == nullptr;
    }

    template <class K, class T>
    int TreeNode<K,T>::leftHeight() const{
        return this->left == nullptr ? NULL_HEIGHT : this->left->height;
    }

    template <class K, class T>
    int TreeNode<K,T>::rightHeight() const{
        return this->right == nullptr ? NULL_HEIGHT : this->right->height;
    }

    template <class K, class T>
    int TreeNode<K,T>::BF() const{
        return this->leftHeight() - this->rightHeight();
    }

    template <class K, class T>
    void TreeNode<K,T>::rollLeft(){
        if(this->right == nullptr)
            return;

        TreeNode<K,T> * right_left = this->right->left;
        TreeNode<K,T> * old_parent = this->parent;
        TreeNode<K,T> * old_son = this->right;
        if(old_parent != nullptr)
        {
            int who_am_i = this->whoAmI();
            if(who_am_i == LEFT){
                old_parent->left = old_son;
            }
            else{
                old_parent->right = old_son;
            }
        }

        this->right->left = this;
        this->parent = this->right;
        this->right = right_left;
        if(right_left!= nullptr){
            right_left->parent=this;//new
        }
        this->parent->parent=old_parent;

    }

    template <class K, class T>
    void TreeNode<K,T>::rollRight(){
        if(this->left == nullptr)
            return;

        TreeNode<K,T> * left_right = this->left->right;
        TreeNode<K,T> * old_parent = this->parent;
        TreeNode<K,T> * old_son = this->left;

        if(old_parent != nullptr)
        {
            int who_am_i = this->whoAmI();
            if(who_am_i == LEFT){
                old_parent->left = old_son;
            }
            else{
                old_parent->right = old_son;
            }
        }

        this->left->right = this;
        this->parent = this->left;
        this->left = left_right;
        if(left_right!= nullptr){
            left_right->parent= this;//new
        }
        this->parent->parent=old_parent;
    }

    template <class K, class T>
    int  TreeNode<K,T>::whoAmI() const{
        if(this->parent != nullptr)
        {
            if(parent->right == this)
            {
                return RIGHT;
            }
            return LEFT;
        }
        return ROOT;
    }

    template <class K, class T>
    void TreeNode<K,T>::rollLL(){
        this->rollRight();
    }

    template <class K, class T>
    void TreeNode<K,T>::rollRR(){
        this->rollLeft();
    }

    template <class K, class T>
    void TreeNode<K,T>::rollRL(){
        this->right->rollRight();
        this->rollLeft();
    }

    template <class K, class T>
    void TreeNode<K,T>::rollLR(){
        this->left->rollLeft();
        this->rollRight();
    }

    template <class K, class T>
    void TreeNode<K,T>::roll(){
        if(this->BF()==2){
            if(this->left->BF()==1){
                this->rollLL();
            }
            else{
                this->rollLR();
            }
        } else{
            if(this->right->BF()==1){
                this->rollRL();
            }
            else{
                this->rollRR();
            }
        }
    }

    template <class K, class T>
    void TreeNode<K,T>::updateHeight(){
        this->height = 1 + MAX(this->leftHeight(), this->rightHeight());
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::find(const K& key){
        if(this->key == key){
            return this;
        }

        if(this->isLeaf()){
            return nullptr;
        }

        if(!(this->key < key)){
            if(this->left == nullptr){
                return nullptr;
            }
            else{
                return this->left->find(key);
            }
        }

        if(this->right == nullptr){
            return nullptr;
        }
        else{
            return this->right->find(key);
        }
    }

    template <class K, class T>
    void TreeNode<K,T>::insert(const K& key, const T& data){
        if(!(this->key < key)){
            if(this->left == nullptr){
                TreeNode<K,T>* new_tree = new TreeNode<K,T>(key, data);
                this->left = new_tree;
                new_tree->parent = this;
                this->fix();
            }
            else {
                this->left->insert(key, data);
            }
        }
        else {
            if(this->right == nullptr){
                TreeNode<K,T>* new_tree = new TreeNode<K,T>(key, data);
                this->right = new_tree;
                new_tree->parent = this;
                this->fix();
            }
            else {
                this->right->insert(key, data);
            }
        }
    }

    template <class K, class T>
    void TreeNode<K,T>::gulag(){
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::removeNode(const K& key){ //can return null
        TreeNode<K,T>* temp = this->find(key);
        if(temp->isLeaf()){
            TreeNode<K,T>* temp_parent = temp->parent;

            int who_am_i = temp->whoAmI();
            if(who_am_i == LEFT){
                temp_parent->left = nullptr;
            }
            if(who_am_i == RIGHT){
                temp_parent->right = nullptr;
            }

            temp->gulag();
            //delete temp;
            return temp_parent;
        }

        if(temp->left != nullptr && temp->right != nullptr){//has two sons
            TreeNode<K,T>* replace = temp->right;
            TreeNode<K,T>* to_return = nullptr;
            if(replace->left == nullptr){
                replace->left=temp->left;
                replace->parent=temp->parent;
                temp->left->parent=replace;

                int who_am_i = temp->whoAmI();
                if(who_am_i == LEFT){
                    temp->parent->left = replace;
                }
                if(who_am_i == RIGHT){
                    temp->parent->right = replace;
                }

                temp->gulag();
                 //delete temp;
                return replace;
            }
            else{
                while(replace->left != nullptr){
                    replace = replace->left;
                }
                to_return = replace->parent;

                if(replace->right != nullptr){
                    replace->right->parent = replace->parent;

                }
                replace->parent->left = replace->right;
            }

            replace->right = temp->right;
            replace->left = temp->left;
            temp->right->parent = replace;
            temp->left->parent = replace;
            replace->parent = temp->parent;

            int who_am_i = temp->whoAmI();
            if(who_am_i == LEFT){
                temp->parent->left = replace;
            }
            if(who_am_i == RIGHT){
                temp->parent->right = replace;
            }

            temp->gulag();
          //delete temp;
            return to_return;
        }

        TreeNode<K,T> * temp_parent = temp->parent;
        int who_am_i = temp->whoAmI();
        if(temp->left != nullptr && temp->right == nullptr){
            if(who_am_i == LEFT){
                temp_parent->left = temp->left;
            }
            if(who_am_i == RIGHT){
                temp_parent->right = temp->left;
            }

            temp->left->parent = temp_parent;
            TreeNode<K,T> * temp_left = temp->left;
            temp->gulag();
            //delete temp;
            return temp_left;
        }

        if(who_am_i == LEFT){
            temp_parent->left = temp->right;
        }
        if(who_am_i==RIGHT){
            temp_parent->right = temp->right;
        }
        temp->right->parent = temp_parent;
        TreeNode<K,T> * temp_right = temp->right;

        temp->gulag();
        //delete temp;
        return temp_right;
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::remove(const K& key){
        TreeNode<K,T> * removed = this->removeNode(key);
        return removed->fix(true);
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::fix(bool stop_at_root){
        if(this== nullptr){
            return nullptr;
        }
        if(abs(this->BF()) == 2){
            this->roll();
        }

        int oldHeight = this->height;
        this->updateHeight();
        if((!stop_at_root && this->height == oldHeight) || this->parent == nullptr){
            return this;
        }

        return this->parent->fix(stop_at_root);
    }


    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::getMax(){
        if(this == nullptr){
            return nullptr;
        }
        if(this->right == nullptr){
          return this;
            //return new T(this->data);
        }
        return this->right->getMax();
    }

    template <class K, class T>
    void TreeNode<K,T>::toSortedArray(K dist_arr_K[], T dist_arr_T[], int size) const{
        int idx = 0;
        return this->toSortedArrayAux(dist_arr_K, dist_arr_T, &idx, size);
    }

    template <class K, class T>
    void TreeNode<K,T>::toSortedArrayAux(K sortedArr_K[], T sortedArr_T[], int* idx, int size) const{
        if(size != -1 && (*idx) >= size){
            return;
        }

        if(this->left != nullptr){
            this->left->toSortedArrayAux(sortedArr_K, sortedArr_T, idx, size);
        }

        sortedArr_K[(*idx)] = this->key;
        sortedArr_T[(*idx)++] = this->data;
//        dist_arr[(*idx)++] = this->data;

        if(this->right != nullptr){
            this->right->toSortedArrayAux(sortedArr_K, sortedArr_T, idx, size);
        }
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::merge(const TreeNode<K,T> *tree1, const TreeNode<K,T> *tree2, int size1, int size2){
        if(!size1 && !size2){
            return nullptr;
        }
        if(!size1 && size2){
            auto arr2_K = new K[size2];
            auto arr2_T = new T[size2];
            tree2->toSortedArray(arr2_K, arr2_T);
            return TreeNode<K,T>::arrayToTree(arr2_K, arr2_T, size2);
        }
        if(size1 && !size2){
            auto arr1_K = new K[size1];
            auto arr1_T = new T[size1];
            tree1->toSortedArray(arr1_K, arr1_T);
            return TreeNode<K,T>::arrayToTree(arr1_K, arr1_T,  size1);
        }

        auto arr1_K = new K[size1];
        auto arr1_T = new T[size1];
        auto arr2_K = new K[size2];
        auto arr2_T = new T[size2];

        tree1->toSortedArray(arr1_K, arr1_T);
        tree2->toSortedArray(arr2_K, arr2_T);


        auto arr_merge_K = new K[size1 + size2];
        auto arr_merge_T = new T[size1 + size2];

        Utils::mergeArrays(arr_merge_K, arr_merge_T, arr1_K, arr1_T, arr2_K, arr2_T, size1, size2);

        delete[] arr1_K;
        delete[] arr1_T;
        delete[] arr2_K;
        delete[] arr2_T;

        TreeNode<K,T>* t = TreeNode<K,T>::arrayToTree(arr_merge_K, arr_merge_T, size1 + size2);

        delete[] arr_merge_K;
        delete[] arr_merge_T;

        return t;
    }

//    template <class K, class T>
//    TreeNode<K,T>* TreeNode<K,T>::merge(const TreeNode<K,T> *tree1, const TreeNode<K,T> *tree2, int size1, int size2){
//        if(!size1 && !size2){
//            return nullptr;
//        }
//        if(!size1 && size2){
//            T* arr2 = new T[size2];
//            tree2->toSortedArray(arr2);
//            return TreeNode<K,T>::arrayToTree(arr2, size2);
//        }
//        if(size1 && !size2){
//            T* arr1 = new T[size1];
//            tree1->toSortedArray(arr1);
//            return TreeNode<K,T>::arrayToTree(arr1,  size1);
//        }
//
//        T* arr1 = new T[size1];
//        T* arr2 = new T[size2];
//
//        tree1->toSortedArray(arr1);
//        tree2->toSortedArray(arr2);
//
//
//        T* arr_merge = new T[size1 + size2];
//        Utils::mergeArrays(arr_merge, arr1, arr2, size1, size2);
//        delete[] arr1;
//        delete[] arr2;
//        TreeNode<K,T>* t = TreeNode<K,T>::arrayToTree(arr_merge, size1 + size2);
//        delete [] arr_merge;
//        return t;
//    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::arrayToTree(const K sortedArr_K[], const T sortedArr_T[], int size){
        return arrayToTreeAux(sortedArr_K, sortedArr_T, 0, size, nullptr);
    }

    template <class K, class T>
    TreeNode<K,T>* TreeNode<K,T>::arrayToTreeAux(const K sortedArr_K[], const T sortedArr_T[], int startIdx, int size, TreeNode<K,T>* parent){
        if(size == 0){
            return nullptr;
        }

        int mid = (size - 1) / 2 + startIdx;
        TreeNode<K,T>* sub_root = new TreeNode<K,T>(sortedArr_K[mid], sortedArr_T[mid]);
        sub_root->parent = parent;

        int half_size = size / 2;
        int left_size = size % 2 == 0 ? half_size - 1 : half_size;
        sub_root->left = TreeNode<K,T>::arrayToTreeAux(sortedArr_K, sortedArr_T, startIdx, left_size, sub_root);
        sub_root->right = TreeNode<K,T>::arrayToTreeAux(sortedArr_K, sortedArr_T, mid + 1, half_size, sub_root);
        sub_root->updateHeight();

        return sub_root;
    }


    // Function to print binary tree in 2D
    // It does reverse inorder traversal
    template <class K, class T>
    void TreeNode<K,T>::print2DUtil(int space) const
    {
        // Base case
        if (this == nullptr)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        if(this->right != nullptr){
            this->right->print2DUtil(space);
        }

        // Print current node after space
        // count
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << this->key << " : " << this->data << "\n";

        // Process left child
        if(this->left != nullptr){
            this->left->print2DUtil(space);
        }
    }

// Wrapper over print2DUtil()
    template <class K, class T>
    void TreeNode<K,T>::print2D() const{
        // Pass initial space count as 0
        this->print2DUtil(0);
    }

    template <class K, class T>
    void TreeNode<K,T>::removeAll(TreeNode<K,T> * node){
        if(node!= nullptr)
        {
            removeAll(node->left) ;
            removeAll(node->right) ;
            delete node;
        }
    }

//    template <class K, class T>
//    TreeNode<K,T>::~TreeNode() {
//        T * tmp= &data;
//        this->gulag();
//        if(tmp!= nullptr){
//            delete tmp;
//        }
//    }

}


#endif //OCTOPUS_GAMES_TREENODE_H

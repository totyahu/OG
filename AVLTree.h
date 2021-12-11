#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <memory>
#include "TreeNode.h"
#include "Utils.h"

#define LEFT 1
#define ROOT 0
#define RIGHT -1


using namespace std;

namespace WET1 {

    template<class K, class T>
    class AVLTree {
        TreeNode<K,T>* root;
        int size;
        TreeNode<K,T>* max;

    public:
        AVLTree();
        AVLTree(const K& key, const T &data);
        AVLTree(TreeNode<K,T>* tree, int size, TreeNode<K,T>* max=nullptr);
        ~AVLTree();
        T* find(const K &key) const;
        bool exists(const K &key) const;
        void insert(const K &key, const T &data);
        void remove(const K &key);
        T* getMax();
        void updateMax();
        int getSize() const;
        void toSortedArray(K sortedArr_K[], T sortedArr_T[], int size = -1) const;
//        static shared_ptr<AVLTree<K,T>> merge(const AVLTree<K,T> *tree1, const AVLTree<K,T> *tree2);
        static unique_ptr<AVLTree<K,T>> merge(const AVLTree<K,T>& tree1, const AVLTree<K,T>& tree2);
        void print2D() const;

        template<typename P>
        bool query(T* dest_arr, P pred, int find_size){
            int found = 0;
            this->root->query(pred, dest_arr, find_size, &found);
            return found == find_size;
        }

        template<typename P>
        void apply(P pred, void* arg){
            if(this->root != nullptr){
                this->root->apply(pred, arg);
            }
        }

    };

//    AVLTree implementation
    template<class K, class T>
    AVLTree<K,T>::AVLTree() {
        this->root = nullptr;
        this->size = 0;
        this->max = nullptr;
    }

    template<class K, class T>
    AVLTree<K,T>::AVLTree(const K &key, const T &data) {
        this->root = new TreeNode<K,T>(key, data);
        this->size = 1;
        this->max = this->root;
    }

    template<class K, class T>
    AVLTree<K,T>::AVLTree(TreeNode<K,T>* tree, int size, TreeNode<K,T>* max) {
        this->size = size;
        this->root = tree;
        if(max == nullptr && tree != nullptr){
            this->updateMax();
        }
        else{
            this->max = max;
        }
    }

    template<class K, class T>
    AVLTree<K,T>::~AVLTree(){
//        if(this->root && this->size){
//            this->size = 0;
//            delete this->root;
//            this->root = nullptr;
//        }
        if(this->root){
            this->max = nullptr;
            this->root->TreeNode<K,T>::removeAll(this->root);
//            delete this->root;
            this->root = nullptr;
        }
    }


    template<class K, class T>
    T* AVLTree<K,T>::find(const K &key) const {
        if(!this->size){
            return nullptr;
        }

        TreeNode<K,T>* res = this->root->find(key);
        if (res == nullptr) {
            return nullptr;
        }

        return &(res->getData());
    }

    template<class K, class T>
    bool AVLTree<K,T>::exists(const K &key) const {
        if(this->root == nullptr){
            return false;
        }
        return this->root->find(key) != nullptr;
    }

    template<class K, class T>
    void AVLTree<K,T>::insert(const K &key, const T &data) {
        this->size += 1;
        if (this->root == nullptr) {
            this->root = new TreeNode<K,T>(key, data);
            this->max = this->root;
        }
        else {
            this->root->insert(key, data);
            TreeNode<K,T> *parent = this->root->getParent();
            while(parent != nullptr) {
                this->root = parent;
                parent = parent->getParent();
            }
            this->updateMax();
        }
    }

    template<class K, class T>
    void AVLTree<K,T>::remove(const K& key) {
        if(this->root){
            this->size -= 1;
            this->root = this->root->remove(key);
            this->updateMax();
        }
    }

    template<class K, class T>
    void AVLTree<K,T>::toSortedArray(K dist_arr_K[], T dist_arr_T[], int size) const{
        this->root->toSortedArray(dist_arr_K, dist_arr_T, size);
    }

//    template<class K, class T>
//    shared_ptr<AVLTree<K,T>> AVLTree<K,T>::merge(const AVLTree<K,T>* tree1, const AVLTree<K,T>* tree2) {
//        TreeNode<K,T>* new_tree = TreeNode<K,T>::merge(tree1->root, tree2->root, tree1->size, tree2->size);
//        return make_shared<AVLTree<K,T>>(new_tree, tree1->size + tree2->size);
//    }

    template<class K, class T>
    unique_ptr<AVLTree<K,T>> AVLTree<K,T>::merge(const AVLTree<K,T>& tree1, const AVLTree<K,T>& tree2) {
        TreeNode<K,T>* new_tree = TreeNode<K,T>::merge(tree1.root, tree2.root, tree1.size, tree2.size);
        return unique_ptr<AVLTree<K,T>>(new AVLTree<K,T>(new_tree, tree1.size + tree2.size));
    }

    template<class K, class T>
    T* AVLTree<K,T>::getMax(){
        return this->max ? &(this->max->getData()) : nullptr;
    }

    template<class K, class T>
    void AVLTree<K,T>::updateMax(){
        if(!size){
            this->max = nullptr;
        }
        this->max = this->root->getMax();
    }

    template<class K, class T>
    int AVLTree<K,T>::getSize() const{
        return this->size;
    }

    template<class K, class T>
    void AVLTree<K,T>::print2D() const {
        if(this->root){
            this->root->print2D();
        }
    }

}

#endif
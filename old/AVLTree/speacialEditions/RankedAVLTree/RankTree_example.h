#ifndef RANKTREE_H
#define RANKTREE_H

#include <stdlib.h>
#include <stdexcept>
#include <iostream>


#define NULL_HEIGHT -1

class RankTree;

class RankNode {
public:
    int key;
    int data;
    RankNode *left_son;
    RankNode *right_son;
    RankNode *parent;
    int height;
    int w1; //sum of data of the sub tree
    int w2; //sum of (key * data) of the sub tree

    RankNode()
            : key(), data(), left_son(nullptr), right_son(nullptr), parent(nullptr),
              height(0), w1(0), w2(0) {};

    RankNode(int key1, int data1, RankNode *parent = nullptr) :
            key(key1), data(data1),left_son(nullptr),
            right_son(nullptr),parent(parent),height(0),w1(data), w2(key*data) {};

    ~RankNode() = default ;

    bool operator==(const RankNode &node) const {
        return (this->key == node.key);
    }

    bool operator!=(const RankNode &node) const {
        return (this->key != node.key);
    }

    bool operator<(const RankNode &node) const {
        return (this->key < node.key);
    }

    bool operator>(const RankNode &node) const {
        return (this->key > node.key);
    }

    bool operator<=(const RankNode &node) const {
        return (this->key <= node.key);
    }

    bool operator>=(const RankNode &node) const {
        return (this->key >= node.key);
    }

};

class RankTree {
public:
    RankNode *root;
    int size;

    RankTree() : root(nullptr), size(0) {};

    void postOrderDelete(RankNode *root) {
        if (root == nullptr) {
            return;
        }
        postOrderDelete(root->left_son);
        postOrderDelete(root->right_son);
        delete root;
    }

    ~RankTree(){
        postOrderDelete(this->root);
    }

    void fixW1W2(RankNode* v)
    {
            v->w1 = getW1(v->left_son) + getW1(v->right_son) + v->data;
            v->w2 = getW2(v->left_son) + getW2(v->right_son) + v->data * v->key;
    }

    int calcBF(RankNode *v) {
        if (v == nullptr) {
            return -1;
        }
        if (v->left_son == nullptr && v->right_son == nullptr) {
            return 0;
        }
        if (v->left_son == nullptr) {
            return -(v->right_son->height + 1);
        }
        if (v->right_son == nullptr) {
            return v->left_son->height + 1;
        }
        return v->left_son->height - v->right_son->height;
    }

    void rrRotate(RankNode *v) {
        if (v == nullptr) {
            return;
        }
        RankNode *tmp = v->right_son;
        if (root == v) {
            root = tmp;
        }
        v->right_son = tmp->left_son;
        if (tmp->left_son != nullptr) {
            tmp->left_son->parent = v;
        }
        tmp->left_son = v;
        tmp->parent = v->parent;
        if (tmp->parent != nullptr) {
            if (tmp->parent->left_son == v) {
                tmp->parent->left_son = tmp;
            } else {
                tmp->parent->right_son = tmp;
            }
        }
        v->parent = tmp;
        fixHeight(v);
        fixHeight(v->parent);
        fixW1W2(v);
        fixW1W2(v->parent);
    }

    void llRotate(RankNode *v) {
        if (v == nullptr) {
            return;
        }
        RankNode *tmp = v->left_son;
        if (root == v) {
            root = tmp;
        }
        v->left_son = tmp->right_son;
        if (tmp->right_son != nullptr) {
            tmp->right_son->parent = v;
        }
        tmp->right_son = v;
        tmp->parent = v->parent;
        if (tmp->parent != nullptr) {
            if (tmp->parent->left_son == v) {
                tmp->parent->left_son = tmp;
            } else {
                tmp->parent->right_son = tmp;
            }
        }
        v->parent = tmp;
        fixHeight(v);
        fixHeight(v->parent);
        fixW1W2(v);
        fixW1W2(v->parent);
    }

    void lrRotate(RankNode *v) {
        rrRotate(v->left_son);
        llRotate(v);
    }

    void rlRotate(RankNode *v) {
        llRotate(v->right_son);
        rrRotate(v);
    }

    RankNode *findKey(int key1) const {
        RankNode *current = this->root;
        RankNode *parent = nullptr;

        while (current != nullptr) {
            if (current->key == key1) {
                return current;
            }
            if (key1 > current->key) {
                parent = current;
                current = current->right_son;
                continue;
            } else if (key1 < current->key) {
                parent = current;
                current = current->left_son;
                continue;
            }
        }
        return parent;
    }

    int getW1(RankNode* node) const
    {
        if(node == nullptr)
        {
            return 0;
        }
        return node->w1;
    }

    int getW2(RankNode* node) const
    {
        if(node == nullptr)
        {
            return 0;
        }
        return node->w2;
    }

    int getSum1(int key1) const
    {
        RankNode *current = this->root;
        int s = 0;
        while (current != nullptr) {
            if (current->key == key1) {
                s+=getW1(current->left_son)+current->data;
                return s;
            }

            if (key1 > current->key) {
                s+=getW1(current->left_son)+current->data;
                current = current->right_son;
                continue;
            } else if (key1 < current->key) {
                current = current->left_son;
                continue;
           } 
        }
        return s;
    }

  /*  int getSum2(int key1) const
    {
        RankNode *current = this->root;
        int s = 0;
        while (current != nullptr) {
            if (current->key == key1) {
                s+=getW2(current->left_son)+current->data*current->key;
                return s;
            }

            if (key1 > current->key) {
                current = current->right_son;
                continue;
            } else if (key1 < current->key) {
                current = current->left_son;
                s+=getW2(current->right_son)+current->data*current->key;
                continue;
            }
        }
            return s;
    }*/

    int sumOfGreaterLevels(int k)//find the leve
    {
        RankNode* current = root;
        int sum = 0;
        while(current != nullptr)
        {
            if(k<=0) return sum;
            int c1 = getW1(current->right_son);
            int c2 = c1 + current->data;
            if(k >= c2)
            {
                sum+= (getW2(current->right_son) + current->data*current->key);
                k-=c2;
                current = current->left_son;
            }
            else if(k < c1)
            {
                current = current->right_son;
            }
            else
            {
                sum+= (getW2(current->right_son) + current->key * (k-c1));
                return sum;
            }
        }
        return sum;
    }
    RankNode *insert_aux(int key1, int data1) {
        RankNode *node = findKey(key1);
        RankNode *newNode = new RankNode(key1, data1, node);
        if (node == nullptr) {
            root = newNode;
            root->parent = nullptr;
            size++;
            return newNode;
        }
        if(node->key==key1){
            delete newNode;
            return nullptr;
        }
        if (key1 < node->key) {
            node->left_son = newNode;
        } else if (key1 >= node->key) {
            node->right_son = newNode;
        }
        newNode->parent = node;
        size++;
        return newNode;
    }

    RankNode* insert(int key1, int data1) {
        RankNode *v = insert_aux(key1, data1);
        if(v== nullptr){
            return nullptr;
        }
        RankNode* node = v;
        while (v != root) {
            RankNode *p = v->parent;
            p->height = getHeight(v) + 1;
            fixW1W2(p);
            makeBalance(p);
            v = p;
        }
        return node;
    }

    void swapAndFree(RankNode *source, RankNode *replaced) {
       RankNode* deleted=source;
       RankNode* swapped=replaced;
       if(swapped->parent == deleted){
           if(deleted->parent == nullptr){
               root=swapped;
           } else {
               if (deleted->parent->left_son == deleted) {
                   deleted->parent->left_son = swapped;
               } else {
                   deleted->parent->right_son = swapped;
               }
           }
           swapped->parent=deleted->parent;
           swapped->left_son=deleted->left_son;
           swapped->left_son->parent= swapped;
           size--;
           delete deleted;
           return;
       }

       if(swapped->right_son != nullptr){
           swapped->right_son->parent=swapped->parent;
           swapped->parent->left_son=swapped->right_son;
       } else {
           swapped->parent->left_son= nullptr;
       }
       if( deleted->parent != nullptr){
           if(deleted->parent->left_son == deleted){
               deleted->parent->left_son= swapped;
           } else {
               deleted->parent->right_son= swapped;
           }
       }
       swapped->parent=deleted->parent;
       swapped->left_son=deleted->left_son;
       swapped->right_son=deleted->right_son;
       if(swapped->left_son != nullptr){
           swapped->left_son->parent=swapped;
       }
       swapped->right_son->parent=swapped;
       size--;
       if(deleted == root)
       {
           root = swapped;
       }
       delete deleted;
    }

    bool remove_aux(int key1, RankNode** swapped_parent) {
        RankNode *node = findKey(key1);
        if(node == nullptr || node->key != key1){
            return false;
        }
        if(node->left_son == nullptr && node->right_son == nullptr){
            if(node->parent != nullptr && node->parent->left_son==node){
                node->parent->left_son= nullptr;
            } else if(node->parent!= nullptr){
                node->parent->right_son= nullptr;
            }
            size--;
            delete node;
            if(size==0){
                root= nullptr;
            }
            return true;
        }

        if(node->left_son == nullptr){
            if(node->parent == nullptr){
                node->right_son->parent= nullptr;
                root=node->right_son;
            } else {
                node->right_son->parent=node->parent;
                if(node->parent->right_son == node){
                    node->parent->right_son=node->right_son;
                } else {
                    node->parent->left_son= node->right_son;
                }
            }
            size--;
            delete node;
            if(size==0){
                root= nullptr;
            }
            return true;
        }
        if(node->right_son == nullptr){
            if(node->parent == nullptr){
                node->left_son->parent= nullptr;
                root=node->left_son;
            } else {
                node->left_son->parent=node->parent;
                if(node->parent->right_son == node){
                    node->parent->right_son=node->left_son;
                } else {
                    node->parent->left_son= node->left_son;
                }
            }
            size--;
            delete node;
            if(size==0){
                root= nullptr;
            }
            return true;
        }

        RankNode* tmp=node->right_son;
        while(tmp->left_son!= nullptr){
            tmp=tmp->left_son;
        }
        if(tmp == node->right_son)
        {
            *swapped_parent = tmp;
        }
        else{
            *swapped_parent = tmp->parent;
        }
        swapAndFree(node,tmp);
        return true;
    }

    bool remove(int key1) {
        RankNode* swapped_parent = nullptr;
        bool is_removed = remove_aux(key1, &swapped_parent);
        if(!is_removed){
            return is_removed;
        }
        RankNode *v;
        if(swapped_parent != nullptr)
        {
            v = swapped_parent;
        }
        else{
            v = findKey(key1);
        }
        while (v != nullptr) {
            fixHeight(v);
            fixW1W2(v);
            //int temp = getHeight(v);
            if (makeBalance(v)) {
                v = v->parent;
                v = v->parent;
                continue;
            }
           /* if (temp == getHeight(v)) {
                return is_removed;
            }*/
            v = v->parent;
        }
        // update w1 and w2
        return is_removed;
    }

    void inOrderPrint(RankNode *root) {
        if (root == nullptr) {
            return;
        }
        inOrderPrint(root->left_son);
        std::cout << root->key << std::endl;
        inOrderPrint(root->right_son);

    }

    void printTree() {
        inOrderPrint(this->root);
    }

    bool makeBalance(RankNode *root) {
        fixHeight(root);
        if (calcBF(root) == 2) {
            if (calcBF(root->left_son) >= 0) {
                llRotate(root);
                return true;
            } else if (calcBF(root->left_son) == -1) {
                lrRotate(root);
                return true;
            }
        } else if (calcBF(root) == -2) {
            if (calcBF(root->right_son) <= 0) {
                rrRotate(root);
                return true;
            } else if (calcBF(root->right_son) == 1) {
                rlRotate(root);
                return true;
            }
        }
        return false;
    }

    void fixHeight(RankNode *root) {
        int hr = getHeight(root->right_son);
        int hl = getHeight(root->left_son);
        root->height = (hr > hl ? hr : hl) + 1;
    }

    int getHeight(RankNode *root) {
        if (root == nullptr) {
            return NULL_HEIGHT;
        }
        return root->height;
    }

    RankNode* getMaxLeaf(RankNode *root)
    {
        RankNode* ptr=this->root;
        while(ptr->right_son !=nullptr)
        {
            ptr=ptr->right_son;
        }
        return ptr;
    }
    RankNode* getMinLeaf(RankNode *root)
    {
        RankNode* ptr=this->root;
        while(ptr->left_son !=nullptr)
        {
            ptr=ptr->left_son;
        }
        return ptr;
    }
};

    


#endif
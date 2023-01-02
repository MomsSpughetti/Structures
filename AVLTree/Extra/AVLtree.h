#ifndef INC_2_AVLTREE_H
#define INC_2_AVLTREE_H
//love
#include <stdlib.h>
#include <stdexcept>
#include <iostream>


#define NULL_HEIGHT -1

template<class Key, class Data>
class AVLTree;

template<class Key, class Data>
class AVLNode {
public:
    Key key;
    Data data;
    AVLNode<Key,Data> *left_son;
    AVLNode<Key,Data> *right_son;
    AVLNode<Key,Data> *parent;
    int height;

   explicit AVLNode<Key,Data>()
            : key(), data(), left_son(nullptr), right_son(nullptr), parent(
            nullptr),
              height(0) {};

   explicit AVLNode<Key,Data>(const Key &key1, const Data &data1, AVLNode<Key,Data> *parent = nullptr) :
            key(key1), data(data1),left_son(nullptr),
            right_son(nullptr),parent(parent),
            height(0) {};

    ~AVLNode<Key,Data>() = default ;

    bool operator==(const AVLNode<Key,Data> &node) const {
        return (this->key == node.key);
    }

    bool operator!=(const AVLNode<Key,Data> &node) const {
        return (this->key != node.key);
    }

    bool operator<(const AVLNode<Key,Data> &node) const {
        return (this->key < node.key);
    }

    bool operator>(const AVLNode<Key,Data> &node) const {
        return (this->key > node.key);
    }

    bool operator<=(const AVLNode<Key,Data> &node) const {
        return (this->key <= node.key);
    }

    bool operator>=(const AVLNode<Key,Data> &node) const {
        return (this->key >= node.key);
    }

    void findNextAndPrevInOrder(AVLNode<Key, Data>** prev, AVLNode<Key, Data>** next)
    {
        (*prev) = PrevInOrder(this);
        (*next) = NextInOrder(this);
    }

};

template<class Key, class Data>
class AVLTree {
public:
    AVLNode<Key, Data> *root;
    int size;

   explicit AVLTree<Key,Data>() : root(nullptr), size(0) {};
   explicit AVLTree<Key,Data>(AVLNode<Key, Data> *root, int size) : root(root), size(size) {};

    void postOrderDelete(AVLNode<Key, Data> *root) {
        if (root == nullptr) {
            return;
        }
        postOrderDelete(root->left_son);
        postOrderDelete(root->right_son);
        delete root;
    }

    ~AVLTree<Key,Data>(){
        postOrderDelete(this->root);
    }

    int calcBF(AVLNode<Key, Data> *v) {
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

    void rrRotate(AVLNode<Key, Data> *v) {
        if (v == nullptr) {
            return;
        }
        AVLNode<Key, Data> *tmp = v->right_son;
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
    }

    void llRotate(AVLNode<Key, Data> *v) {
        if (v == nullptr) {
            return;
        }
        AVLNode<Key, Data> *tmp = v->left_son;
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
    }

    void lrRotate(AVLNode<Key, Data> *v) {
        rrRotate(v->left_son);
        llRotate(v);
    }

    void rlRotate(AVLNode<Key, Data> *v) {
        llRotate(v->right_son);
        rrRotate(v);
    }

    AVLNode<Key, Data> *findKey(const Key &key1) const {
        AVLNode<Key, Data> *current = this->root;
       AVLNode<Key, Data> *parent = nullptr;

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

    bool isExixst(const Key &key) const{
        AVLNode<Key,Data>* ptr = this->findKey(key);
        if(ptr == NULL ||key != ptr->key){
            return false;
        }
        return true;
    }

    AVLNode<Key, Data> *insert_aux(const Key &key1, const Data &data1) {
        AVLNode<Key, Data> *node = findKey(key1);
        AVLNode<Key, Data> *newNode = new AVLNode<Key, Data>(key1, data1, node);
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

    AVLNode<Key, Data> * insert(const Key &key1, const Data &data1) {
        AVLNode<Key, Data> *v = insert_aux(key1, data1);
        if(v== nullptr){
            return nullptr;
        }
        AVLNode<Key,Data>* node = v;
        while (v != root) {
            AVLNode<Key, Data> *p = v->parent;
            if (getHeight(p) >= getHeight(v) + 1) {
                return node;
            }
            p->height = getHeight(v) + 1;
            makeBalance(p);
            v = p;
        }
        return node;
    }

    void swapAndFree(AVLNode<Key, Data> *source, AVLNode<Key, Data> *replaced) {
       AVLNode<Key,Data>* deleted=source;
       AVLNode<Key,Data>* swapped=replaced;
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
       if(source->key == root->key)
       {
           root=swapped;
       }
       delete deleted;
    }


    bool remove_aux(AVLNode<Key,Data>* node, Key key1) {
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

        AVLNode<Key,Data>* tmp=node->right_son;
        while(tmp->left_son!= nullptr){
            tmp=tmp->left_son;
        }
        swapAndFree(node,tmp);
        if(size==0){
            root= nullptr;
        }
        return true;
    }

    bool remove(AVLNode<Key,Data>* v, Key Key1) {

        AVLNode<Key,Data>* parentOfDeleted = v->parent;

        bool is_removed = remove_aux(v, Key1);
        if(!is_removed){
            return is_removed;
        }

        v = parentOfDeleted;

        while (v != nullptr) {
            fixHeight(v);
            int temp = getHeight(v);
            if (makeBalance(v)) {
                v = v->parent;
                v = v->parent;
                continue;
            }
            if (temp == getHeight(v)) {
                return is_removed;
            }
            v = v->parent;
        }
        return is_removed;
    }

    bool remove(const Key &key1)
    {
        
        AVLNode<Key,Data>* NodeToDelete = findKey(key1);
        return remove(NodeToDelete, key1);

    }

    void inOrderPrint(AVLNode<Key, Data> *root) {
        if (root == nullptr) {
            return;
        }
        inOrderPrint(root->left_son);
        std::cout << root->key << std::endl;
        inOrderPrint(root->right_son);

    }

    void inOrderArray(AVLNode<Key, Data> *root , Data* array, int* place, int size) {
        if (root == nullptr || (*place) >= size) {
            return;
        }
        inOrderArray(root->left_son, array, place, size);
        array[*place] = root->data;
        (*place)++;
        inOrderArray(root->right_son, array, place, size);
    }

    void TreeToArray(Data* array, int size)
    {
        int place = 0;
        inOrderArray(this->root, array, &place, size);
    }

    void inOrderArrayWithRange(AVLNode<Key, Data> *root , Data* array, int* place, int size, int MinKey, int MaxKey) {
        if (root == nullptr || (*place) >= size) {
            return;
        }

        if(root->key > MinKey)
            inOrderArrayWithRange(root->left_son, array, place, size, MinKey, MaxKey);

        if(root->key >= MinKey && root->key <= MaxKey)
        {
            array[*place] = root->data;
            (*place)++;
        }
        if(root->key < MaxKey)
            inOrderArrayWithRange(root->right_son, array, place, size, MinKey, MaxKey);
    }

    int TreeToArrayWithRange(Data* array, int size, int MinKey, int MaxKey)
    {
        int place = 0;
        inOrderArrayWithRange(this->root, array, &place, size, MinKey, MaxKey);
        return place;
    }

    void count(AVLNode<Key, Data> *root, int* c)
    {
        if (root == nullptr) {
            return;
        }
        count(root->left_son, c);
        (*c)++;
        count(root->right_son, c);
    }

    int getNumberOfNodes()
    {
        int numberOfNodes = 0;
        count(this->root, &numberOfNodes);
        return numberOfNodes;
    }
    
    void printTree() {
        inOrderPrint(this->root);
    }

    bool makeBalance(AVLNode<Key, Data> *root) {
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

    void makeEveryNodeBalanced(AVLNode<Key, Data>* root)
    {
        if(root == nullptr)
            return;

        makeEveryNodeBalanced(root->left_son);
        makeEveryNodeBalanced(root->right_son);
        makeBalance(root);

    }

    void BalanceTree()
    {
        makeEveryNodeBalanced(this->root);
    }
    
    void fixHeight(AVLNode<Key, Data> *root) {
        int hr = getHeight(root->right_son);
        int hl = getHeight(root->left_son);
        root->height = (hr > hl ? hr : hl) + 1;
    }

    int getHeight(AVLNode<Key, Data> *root) {
        if (root == nullptr) {
            return NULL_HEIGHT;
        }
        return root->height;
    }

    AVLNode<Key, Data>* getRoot() const
    {
        return this->root;
    }

};

template<class Key, class Data>
AVLNode<Key,Data>* getMaxLeaf(AVLNode<Key,Data>* root)
{
    if(root == nullptr)
        return root;

    AVLNode<Key,Data>* ptr = root;
    while(ptr->right_son != nullptr)
    {
        ptr=ptr->right_son;
    }
    return ptr;
}

template<class Key, class Data>
AVLNode<Key,Data>* getMinLeaf(AVLNode<Key,Data>* root)
{
    if(root == nullptr)
        return root;

    AVLNode<Key,Data>* ptr = root;
    while(ptr->left_son != nullptr)
    {
        ptr=ptr->left_son;
    }
    return ptr;
}

    template<class Key, class Data>
    void inOrderToArray_aux(AVLNode<Key, Data> *root, Data* array, int num, int* index)
    {
        if (*index >= num || root == nullptr) {
            return;
        }
        inOrderToArray_aux(root->left_son,array,num,index);
        array[*index] = root->data;
        (*index)++;
        inOrderToArray_aux(root->right_son,array,num,index);
    }

    template<class Key, class Data>
    void inOrderToArray(AVLNode<Key, Data> *root, Data* array, int num)
    {
        int index = 0;
        return inOrderToArray_aux(root,array,num,&index);
    }

    template<class Key, class Data>
    AVLNode<Key, Data>* PrevInOrder(AVLNode<Key, Data>* n)
    {

        // step 1 of the above algorithm
        if (n->left_son != NULL)
            return getMaxLeaf(n->left_son);
    
        // step 2 of the above algorithm
        AVLNode<Key, Data>* p = n->parent;
        while (p != NULL && n == p->left_son) {
            n = p;
            p = p->parent;
        }
        return p;
    }
    
    template<class Key, class Data>
    AVLNode<Key, Data>* NextInOrder(AVLNode<Key, Data>* n)
    {

        // step 1 of the above algorithm
        if (n->right_son != NULL)
        {
            return getMinLeaf(n->right_son);
        }
    
        // step 2 of the above algorithm
        AVLNode<Key, Data>* p = n->parent;
        while (p != NULL && n == p->right_son) {
            n = p;
            p = p->parent;
        }
        return p;
    }

    template<class Key, class Data>
    void transfertolist(AVLNode<Key,Data>* root)
    {
    if (root == NULL || (root->left_son == NULL && root->right_son == NULL))
        return;
    if (root->left_son != NULL) {

        transfertolist(root->left_son);
        AVLNode<Key,Data>* helpRight = root->right_son;
        root->right_son = root->left_son;
        root->left_son = NULL;
        AVLNode<Key,Data>* t = root->right_son;
        while (t->right_son != NULL)
            t = t->right_son;
        t->right_son = helpRight;
    }
    // now call the same function for root->right
    transfertolist(root->right_son);
   }



#endif //INC_2_AVLTREE_H
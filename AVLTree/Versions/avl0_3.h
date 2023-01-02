#include <algorithm>
#include <iostream>

template <typename Key, typename Data>
class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  void Insert(const Key& key, const Data& data) {
    root_ = Insert(root_, key, data);
  }

  void Remove(const Key& key) {
    root_ = Remove(root_, key);
  }

  Data* Search(const Key& key) {
    AVLNode* p = root_;
    while (p != nullptr) {
      if (key == p->key_) {
        return &p->data_;
      } else if (key < p->key_) {
        p = p->left_;
      } else {
        p = p->right_;
      }
    }
    return nullptr;
  }

  void Print() const {
    Print(root_, 0);
  }

 private:
  struct AVLNode {
    Key key_;
    Data data_;
    int height_;
    AVLNode* left_;
    AVLNode* right_;

    AVLNode(const Key& key, const Data& data)
        : key_(key),
          data_(data),
          height_(1),
          left_(nullptr),
          right_(nullptr) {}
  };

  AVLNode* root_;

  int Height(AVLNode* p) const {
    return p == nullptr ? 0 : p->height_;
  }

  void UpdateHeight(AVLNode* p) {
    p->height_ = 1 + std::max(Height(p->left_), Height(p->right_));
  }

  int BalanceFactor(AVLNode* p) const {
    return Height(p->right_) - Height(p->left_);
  }

  AVLNode* RotateRight(AVLNode* p) {
    AVLNode* q = p->left_;
    p->left_ = q->right_;
    q->right_ = p;
    UpdateHeight(p);
    UpdateHeight(q);
    return q;
  }

  AVLNode* RotateLeft(AVLNode* q) {
    AVLNode* p = q->right_;
    q->right_ = p->left_;
    p->left_ = q;
    UpdateHeight(q);
    UpdateHeight(p);
    return p;
  }

  AVLNode* Balance(AVLNode* p) {
    UpdateHeight(p);
    if (BalanceFactor(p) == 2) {
      if (BalanceFactor(p->right_) < 0) {
        p->right_ = RotateRight(p->right_);
      }
      return RotateLeft(p);
    }
    if (BalanceFactor(p) == -2) {
      if (BalanceFactor(p->left_) > 0) {
        p->left_ = RotateLeft(p->left_);
      }
      return RotateRight(p);
    }
    return p;
  }

  AVLNode* Insert(AVLNode* p, const Key& key, const Data& data) {
    if (p == nullptr) {
      return new AVLNode(key, data);
    }
    if (key < p->key_) {
      p->left_ = Insert(p->left_, key, data);
    } else {
      p->right_ = Insert(p->right_, key, data);
    }
    return Balance(p);
  }

  AVLNode* FindMin(AVLNode* p) {
    return p->left_ == nullptr ? p : FindMin(p->left_);
  }

  AVLNode* RemoveMin(AVLNode* p) {
    if (p->left_ == nullptr) {
      return p->right_;
    }
    p->left_ = RemoveMin(p->left_);
    return Balance(p);
  }

  AVLNode* Remove(AVLNode* p, const Key& key) {
    if (p == nullptr) {
      return nullptr;
    }
    if (key < p->key_) {
      p->left_ = Remove(p->left_, key);
    } else if (key > p->key_) {
      p->right_ = Remove(p->right_, key);
    } else {
      AVLNode* q = p->left_;
      AVLNode* r = p->right_;
      delete p;
      if (r == nullptr) {
        return q;
      }
      AVLNode* min = FindMin(r);
      min->right_ = RemoveMin(r);
      min->left_ = q;
      return Balance(min);
    }
    return Balance(p);
  }

  void Print(AVLNode* p, int level) const {
    if (p != nullptr) {
      Print(p->right_, level + 1);
      for (int i = 0; i < level; i++) {
        std::cout << "   ";
      }
      std::cout << p->key_ << " " << p->data_ << std::endl;
      Print(p->left_, level + 1);
    }
  }
};

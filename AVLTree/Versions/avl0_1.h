template <typename K, typename V>
class AVLTree {
private:
  struct Node {
    K key;
    V value;
    int height;
    Node* left;
    Node* right;

    Node(K k, V v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  int height(Node* n) {
    if (n == nullptr) return 0;
    return n->height;
  }

  void updateHeight(Node* n) {
    n->height = std::max(height(n->left), height(n->right)) + 1;
  }

  int balanceFactor(Node* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
  }

  Node* leftRotate(Node* n) {
    Node* x = n->right;
    Node* t2 = x->left;

    x->left = n;
    n->right = t2;

    updateHeight(n);
    updateHeight(x);

    return x;
  }

  Node* rightRotate(Node* n) {
    Node* x = n->left;
    Node* t2 = x->right;

    x->right = n;
    n->left = t2;

    updateHeight(n);
    updateHeight(x);

    return x;
  }

  Node* insert(Node* n, K key, V value) {
    if (n == nullptr) return new Node(key, value);

    if (key < n->key) {
      n->left = insert(n->left, key, value);
    } else if (key > n->key) {
      n->right = insert(n->right, key, value);
    } else {
      n->value = value;
      return n;
    }

    updateHeight(n);

    int balance = balanceFactor(n);

    if (balance > 1 && key < n->left->key) {
      return rightRotate(n);
    }

    if (balance < -1 && key > n->right->key) {
      return leftRotate(n);
    }

    if (balance > 1 && key > n->left->key) {
      n->left = leftRotate(n->left);
      return rightRotate(n);
    }

    if (balance < -1 && key < n->right->key) {
      n->right = rightRotate(n->right);
      return leftRotate(n);
    }

    return n;
  }

  Node* findMin(Node* n) {
    while (n->left != nullptr) {
      n = n->left;
    }
    return n;
  }

  Node* remove(Node* n, K key) {
    if (n == nullptr) return n;

    if (key < n->key) {
      n->left = remove(n->left, key);
    } else if (key > n->key) {
      n->right = remove(n->right, key);
    } else {
      if (n->left == nullptr || n->right == nullptr) {
        Node* temp = (n->left != nullptr) ? n->left : n->right;
        if (temp == nullptr) {
          temp = n;
          n = nullptr;
        } else {
          *n = *temp;
        }
        delete temp;
      } else {
        Node* temp = findMin(n->right);
        n->key = temp->key;
        n->value = temp->value;
        n->right = remove(n->right, temp->key);
      }
    }

    if (n == nullptr) return n;

    updateHeight(n);

    int balance = balanceFactor(n);

    if (balance > 1 && balanceFactor(n->left) >= 0) {
      return rightRotate(n);
    }

    if (balance > 1 && balanceFactor(n->left) < 0) {
      n->left = leftRotate(n->left);
      return rightRotate(n);
    }

    if (balance < -1 && balanceFactor(n->right) <= 0) {
      return leftRotate(n);
    }

    if (balance < -1 && balanceFactor(n->right) > 0) {
      n->right = rightRotate(n->right);
      return leftRotate(n);
    }

    return n;
  }

public:
  AVLTree() : root(nullptr) {}

  void insert(K key, V value) {
    root = insert(root, key, value);
  }

  void remove(K key) {
    root = remove(root, key);
  }

  V find(K key) {
    Node* n = root;
    while (n != nullptr) {
      if (key == n->key) return n->value;
      if (key < n->key) n = n->left;
      else n = n->right;
    }
    throw std::invalid_argument("Key not found in the tree");
  }
};


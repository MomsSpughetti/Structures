template <typename Key, typename Value>
class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  void Insert(const Key& key, const Value& value) {
    root_ = InsertHelper(root_, key, value);
  }

  void Remove(const Key& key) {
    root_ = RemoveHelper(root_, key);
  }

  Value* Find(const Key& key) {
    return FindHelper(root_, key);
  }

  int GetHeight() const {
    return GetHeightHelper(root_);
  }

 private:
  struct Node {
    Key key;
    Value value;
    int height;
    Node* left;
    Node* right;

    Node(const Key& k, const Value& v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  Node* InsertHelper(Node* node, const Key& key, const Value& value) {
    if (!node) {
      return new Node(key, value);
    }

    if (key < node->key) {
      node->left = InsertHelper(node->left, key, value);
    } else if (key > node->key) {
      node->right = InsertHelper(node->right, key, value);
    } else {
      node->value = value;
    }

    node->height = std::max(GetHeightHelper(node->left), GetHeightHelper(node->right)) + 1;
    int balance_factor = GetBalanceFactor(node);

    if (balance_factor > 1 && key < node->left->key) {
      return RightRotate(node);
    }

    if (balance_factor < -1 && key > node->right->key) {
      return LeftRotate(node);
    }

    if (balance_factor > 1 && key > node->left->key) {
      node->left = LeftRotate(node->left);
      return RightRotate(node);
    }

    if (balance_factor < -1 && key < node->right->key) {
      node->right = RightRotate(node->right);
      return LeftRotate(node);
    }

    return node;
  }

  Node* RemoveHelper(Node* node, const Key& key) {
    if (!node) {
      return nullptr;
    }

    if (key < node->key) {
      node->left = RemoveHelper(node->left, key);
    } else if (key > node->key) {
      node->right = RemoveHelper(node->right, key);
    } else {
      if (!node->left || !node->right) {
        Node* temp = node->left ? node->left : node->right;
        if (!temp) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
        }
        delete temp;
      } else {
        Node* temp = FindMinNode(node->right);
        node->key = temp->key;
        node->value = temp->value;
node->right = RemoveHelper(node->right, temp->key);
}
}

if (!node) {
  return node;
}

node->height = std::max(GetHeightHelper(node->left), GetHeightHelper(node->right)) + 1;
int balance_factor = GetBalanceFactor(node);

if (balance_factor > 1 && GetBalanceFactor(node->left) >= 0) {
  return RightRotate(node);
}

if (balance_factor > 1 && GetBalanceFactor(node->left) < 0) {
  node->left = LeftRotate(node->left);
  return RightRotate(node);
}

if (balance_factor < -1 && GetBalanceFactor(node->right) <= 0) {
  return LeftRotate(node);
}

if (balance_factor < -1 && GetBalanceFactor(node->right) > 0) {
  node->right = RightRotate(node->right);
  return LeftRotate(node);
}

return node;
}

Value* FindHelper(Node* node, const Key& key) {
if (!node) {
return nullptr;
}

if (key == node->key) {
  return &node->value;
} else if (key < node->key) {
  return FindHelper(node->left, key);
} else {
  return FindHelper(node->right, key);
}

}

int GetHeightHelper(Node* node) const {
if (!node) {
return 0;
}
return node->height;
}

int GetBalanceFactor(Node* node) const {
if (!node) {
return 0;
}
return GetHeightHelper(node->left) - GetHeightHelper(node->right);
}

Node* RightRotate(Node* node) {
Node* temp = node->left;
node->left = temp->right;
temp->right = node;
node->height = std::max(GetHeightHelper(node->left), GetHeightHelper(node->right)) + 1;
temp->height = std::max(GetHeightHelper(temp->left), GetHeightHelper(temp->right)) + 1;
return temp;
}

Node* LeftRotate(Node* node) {
Node* temp = node->right;
node->right = temp->left;
temp->left = node;
node->height = std::max(GetHeightHelper(node->left), GetHeightHelper(node->right)) + 1;
temp->height = std::max(GetHeightHelper(temp->left), GetHeightHelper(temp->right)) + 1;
return temp;
}

Node* FindMinNode(Node* node) {
while (node->left) {
node = node->left;
}
return node;
}
};

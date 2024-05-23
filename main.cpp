#include<iostream>
usingnamespace std;

classNode {
public:
int key;
Node* left;
Node* right;
int height;
};

int max(inta, intb);

// Calculate height
int height(Node* N) {
if (N == NULL)
return 0;
returnN->height;
}

int max(inta, intb) {
return (a>b) ? a : b;
}

// New node creation
Node* newNode(intkey) {
Node* node = newNode();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
return (node);
}

// Rotate right
Node* rightRotate(Node* y) {
Node* x = y->left;
Node* T2 = x->right;
    x->right = y;
y->left = T2;

// Update heights
y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
return x;
}

// Rotate left
Node* leftRotate(Node* x) {
Node* y = x->right;
Node* T2 = y->left;
    y->left = x;
x->right = T2;

// Update heights
x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node* N) {
if (N == NULL)
return 0;
return height(N->left) - height(N->right);
}

// Insert a node
Node* insertNode(Node* node, intkey) {
// 1. Perform the normal BST insertion
// Find the correct postion and insert the node
if (node == NULL)
return (newNode(key));
if (key<node->key)
node->left = insertNode(node->left, key);
elseif (key>node->key)
node->right = insertNode(node->right, key);
else
returnnode;
// End of normal BST insertion

// 2. Update height of this ancestor node
// Update the balance factor of each node and balance the tree
node->height = 1 + max(height(node->left), height(node->right));


// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
int balanceFactor = getBalanceFactor(node);

// If this node becomes unbalanced, then there are 4 cases  

// Left Left Case  
if (balanceFactor > 1 &&key<node->left->key)
return rightRotate(node);

// Right Right Case  
if (balanceFactor < -1 &&key>node->right->key)
return leftRotate(node);

// Left Right Case  
if (balanceFactor > 1 &&key>node->left->key)
    {
node->left = leftRotate(node->left);
return rightRotate(node);
    }

// Right Left Case  
if (balanceFactor < -1 &&key<node->right->key)
    {
node->right = rightRotate(node->right);
return leftRotate(node);
    }

returnnode;
}

// Node with minimum value
Node* nodeWithMimumValue(Node* node) {
Node* current = node;
while (current->left != NULL)
        current = current->left;
return current;
}

// Delete a node
Node* deleteNode(Node* root, intkey) {
// STEP 1: PERFORM STANDARD BST DELETE 
// Find the node and delete it
if (root == NULL)
returnroot;
if (key<root->key)
root->left = deleteNode(root->left, key);
elseif (key>root->key)
root->right = deleteNode(root->right, key);
else {
// node with only one child or no child
if ((root->left == NULL) || (root->right == NULL)) {
Node* temp = root->left ? root->left : root->right;
// No child case 
if (temp == NULL) {
                temp = root;
root = NULL;
            }
else// One child case 
                *root = *temp;
            free(temp);
        }
else {
Node* temp = nodeWithMimumValue(root->right);
root->key = temp->key;
root->right = deleteNode(root->right, temp->key);
        }
    }

if (root == NULL)
returnroot;

// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
// Update the balance factor of each node and balance the tree
root->height = 1 + max(height(root->left), height(root->right));
int balanceFactor = getBalanceFactor(root);
// Left Left Case  
if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
return rightRotate(root);

// Left Right Case  
if (balanceFactor > 1 && getBalanceFactor(root->left) < 0)
    {
root->left = leftRotate(root->left);
return rightRotate(root);
    }

// Right Right Case  
if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
return leftRotate(root);

// Right Left Case  
if (balanceFactor < -1 && getBalanceFactor(root->right) > 0)
    {
root->right = rightRotate(root->right);
return leftRotate(root);
    }

returnroot;
}

// Print the tree
void printTree(Node* root, stringindent, boollast) {
if (root != nullptr) {
        cout <<indent;
if (last) {
            cout <<"R----";
indent += "   ";
        }
else {
            cout <<"L----";
indent += "|  ";
        }
        cout <<root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
Node* root = NULL;
    root = insertNode(root, 33);
    root = insertNode(root, 13);
    root = insertNode(root, 53);
    root = insertNode(root, 21);
    root = insertNode(root, 61);
    root = insertNode(root, 8);
    root = insertNode(root, 11);
    printTree(root, "", true);
    root = insertNode(root, 9);
    printTree(root, "", true);
    root = deleteNode(root, 13);
    cout <<"After deleting "<< endl;
    printTree(root, "", true);
}

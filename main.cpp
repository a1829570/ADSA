#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


struct Node {

    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {};
};

// Utility function to get the height of the tree
int treeHeight(Node *N) {
    return (N == nullptr) ? 0 : N->height;
}

// Utility function to get the balance factor of the node
int getBalanceFactor(Node *N) {
    return (N == nullptr) ? 0 : treeHeight(N->left) - treeHeight(N->right);
}

// Right rotation utility
Node* RR(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(treeHeight(y->left), treeHeight(y->right)) + 1;
    x->height = max(treeHeight(x->left), treeHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotation utility
Node* LR(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(treeHeight(x->left), treeHeight(x->right)) + 1;
    y->height = max(treeHeight(y->left), treeHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Insert function according to the pseudocode
Node* insertNode(Node* node, int key) {
    // 1. Perform the normal BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else  // Equal keys are not allowed in BST
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + max(treeHeight(node->left), treeHeight(node->right));

    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalanceFactor(node);

    // 4. If the node becomes unbalanced, then there are 4 cases

    // Case 1 - Left Left (LL Rotation)
    if (balance > 1 && key < node->left->key)
        return RR(node);

    // Case 2 - Right Right (RR Rotation)
    if (balance < -1 && key > node->right->key)
        return LR(node);

    // Case 3 - Left Right (LR Rotation)
    if (balance > 1 && key > node->left->key) {
        node->left = LR(node->left);
        return RR(node);
    }

    // Case 4 - Right Left (RL Rotation)
    if (balance < -1 && key < node->right->key) {
        node->right = RR(node->right);
        return LR(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Utility function to find the node with the minimum key value found in that tree
Node* minimumValueNode(Node* node) {
    Node* current = node;
    
    // Loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Utility function to find the node with the maximum key value found in that tree
Node* maximumValueNode(Node* node) {
    Node* current = node;
    
    // Loop down to find the rightmost leaf
    while (current->right != nullptr)
        current = current->right;

    return current;
}

// Delete function
Node* deleteNode(Node* root, int key) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == nullptr)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // If the key is the same as the root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        } else {
            // Node with two children: Get the inorder predecessor (largest in the left subtree)
            Node* temp = maximumValueNode(root->left);

            // Copy the inorder predecessor's data to this node
            root->key = temp->key;

            // Delete the inorder predecessor
            root->left = deleteNode(root->left, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(treeHeight(root->left), treeHeight(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalanceFactor(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Case 1 - Left Left (LL Rotation)
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return RR(root);

    // Case 2 - Left Right (LR Rotation)
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = LR(root->left);
        return RR(root);
    }

    // Case 3 - Right Right (RR Rotation)
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return LR(root);

    // Case 4 - Right Left (RL Rotation)
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = RR(root->right);
        return LR(root);
    }

    return root;
}


void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

int main() {

    Node* root = nullptr; // initialise an empty avl tree
    string line; // declare a line to contain the entire line of input


    // Read the entire line of input and store it in line
    getline(cin, line);


    // allows you to parse the string piece by piece
    stringstream ss(line);

    // declares a string to temporarily contain each move when each is extracted from the stream
    string newmove;

    // Each modification move will be stored into this vector
    vector<string> moves;

    // Each modification move is stored into the moves vector via looping through the stringstream ss and extracting each move. 
    while (ss >> newmove) {
        moves.push_back(newmove);
    }

    // Loop through the modification moves vector and excecute each one.

    for (size_t i = 0; i < moves.size() - 1; i++) {

        char insertordelete = moves[i][0];
        int value = stoi(moves[i].substr(1));

        if (insertordelete == 'A') {
            root = insertNode(root, value);
        }

        else if (insertordelete == 'D') {
            root = deleteNode(root, value);
        }
    }
    


    // Finishing move

    string finishingMove = moves.back();

    if (finishingMove == "PRE") {
        if (root == nullptr) {
            cout << "EMPTY";
        } else {
            preOrder(root);
        }
    } else if (finishingMove == "POST") {
        if (root == nullptr) {
            cout << "EMPTY";
        } else {
            postOrder(root);
        }
    } else if (finishingMove == "IN") {
        if (root == nullptr) {
            cout << "EMPTY";
        } else {
            inOrder(root);
        }
    }
    
    cout << endl;
    return 0;
    


}


#include <iostream>
using namespace std;

typedef struct node {
    int data;
    node *left;
    node *right;
    node *parent;
}node;

void insertInBST(node **root, int val) {
    if (*root != NULL) {
        if (val <= (*root)->data) {
            if ((*root)->left == NULL) {
                (*root)->left = (node *)malloc(sizeof(node));
                (*root)->left->data = val;
                (*root)->left->left = NULL;
                (*root)->left->right = NULL;
                (*root)->left->parent = (*root);
            } else {
                insertInBST(&(*root)->left, val);
            }
        } else {
            if ((*root)->right == NULL) {
                (*root)->right = (node *)malloc(sizeof(node));
                (*root)->right->data = val;
                (*root)->right->left = NULL;
                (*root)->right->right = NULL;
                (*root)->right->parent = (*root);
            } else {
                insertInBST(&(*root)->right, val);
            }
        }
    } else {
        *root = (node*)malloc(sizeof(node));
        (*root)->data = val;
        // cout << (*root)->data << endl;
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->parent = NULL;
    }
}

void showBST(node *root) {
    // cout << (root->data) << endl;
    // cout << "chal rha hu mai bhi" << endl;
    if(root != NULL) {
        showBST(root->left);
        cout << root->data << " ";
        showBST(root->right);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    node *root = NULL;
    int i, temp;
    for (i = 0; i < n; i++) {
        cin >> temp;
        insertInBST(&root, temp);
    }
    showBST(root);
}

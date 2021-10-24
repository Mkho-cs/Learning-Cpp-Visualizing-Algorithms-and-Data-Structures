/*
This program inserts integers from the input files created by make_n_integers.cpp
and searches 10 unsearchable integers.
Objective: Measure AVL tree search time
*/

#include <bits/stdc++.h>
using namespace std;

// Structure of individual nodes in AVL
struct node{
    node (int k): key(k), left(NULL), right(NULL), height(1){}    // constructor
    int key;
    node * left;
    node * right;
    int height;
};

/*
AVL Tree class
Similar to BST but with rotations
*/
class AVL{
private:
    node * insert(node * avlNode , int k);
    void search(node * avlNode, int k);
    int getNodeHeight(node * avlNode);
    int getTreeHeight(node * avlNode);
    int newNodeHeight(node * avlNode);

    // Balancing utility functions
   node * rightRotate(node * avlNode);
   node * leftRotate(node * avlNode);

public:
    AVL();
    node * root;
    void insert(int k){
        root = insert(root, k);
    }

    void search(int k){
        return search(root, k);
    }

    int getHeight(){
        return getTreeHeight(root);
    }
};

AVL::AVL(){
    root = NULL;
}

int AVL::getTreeHeight (node * avlNode){
    if(avlNode == NULL){return -1;}     // height doesn't include root
    return 1 + max(getTreeHeight(avlNode->left), getTreeHeight(avlNode->right));
}

int AVL::getNodeHeight(node * avlNode){
    if (avlNode == NULL){return 0;}
    return avlNode->height;
}

int AVL::newNodeHeight(node * avlNode){
    return 1 + max(getNodeHeight(avlNode->left), getNodeHeight(avlNode->right));
}

node * AVL::rightRotate(node * parent){
    node * child = parent->left;
    node * tempNode = child->right;
    //Rotate
    child->right = parent;
    parent->left = tempNode;
    // Update node heights
    parent->height = newNodeHeight(parent);
    child->height = newNodeHeight(child);

    return child;
}

node * AVL::leftRotate(node * parent){
    node * child = parent->right;
    node * tempNode = child->left;
    // Rotate
    child->left = parent;
    parent->right = tempNode;
    // Update node heights
    parent->height = newNodeHeight(parent);
    child->height = newNodeHeight(child);

    return child;
}

node * AVL::insert(node * curNode, int val){
    if (curNode == NULL){
        node * tempNode = new node(val);
        return tempNode;
    }
    // Usual insert like BST
    if (val > curNode->key){
        curNode->right = insert(curNode->right, val);
    }
    else if (val < curNode->key){
        curNode->left = insert(curNode->left, val);
    }
    // Update inserted height
    curNode->height = newNodeHeight(curNode);
    // Balance the tree
    int bFactor = getNodeHeight(curNode->left) - getNodeHeight(curNode->right);
    if (bFactor > 1){   // left imbalance
        if (val < curNode->left->key){  // left-left 
            return rightRotate(curNode);
        }
        else{   // left-right
            curNode->left = leftRotate(curNode->left);
            return rightRotate(curNode);
        }
    }
    else if(bFactor < -1){  // right imbalance
        if (val > curNode->right->key){     // right-right
            return leftRotate(curNode);
        }
        else{   // right-left
            curNode->right = rightRotate(curNode->right);
            return leftRotate(curNode);
        }
    }
    return curNode;
}

 
void AVL::search (node * avlNode, int val){
    if (avlNode == NULL){
        cout << "Not found";
        return;
    }

    if (avlNode->key == val){
        cout << "Value search found";
        return;
    }
    // When searched value larger than current node
    if (avlNode->key < val){
        return search(avlNode->right, val);
    }
    else{   // when larger
        return search(avlNode->left, val);
    }
    
}

// Same as task 5, but with AVL tree
int main(){
  
    // Change file names accordingly
    string inputFileName = "input_avl_search_1000.txt";     
    string outputFileName = "output_avl_search_1000.txt";

    ifstream inputFile;
    inputFile.open(inputFileName);

    ofstream outputFile;
    outputFile.open(outputFileName);

    AVL tree;
    vector<int> unsearchable(10);
    // Read each line of input file
    int totalLine = 0;
    int curNum;

    // Insert to BST
    cout << "Inserting nodes..." << endl;
    while (inputFile >> curNum){
        tree.insert(curNum);
        totalLine++;
        //cout << totalLine << endl;
        // tree.search(curNum);
        // cout << endl;
    }
    inputFile.close();
    cout << "Insertion done!" << endl;

    // Fill in unsearchable array
    int interval = (totalLine / 8  + totalLine / 9 + totalLine / 10) / 3;    // somewhat equal intervals
    int temp;
    int minEdge = 0;    // minimum edge case (since smallest number on tree is 1)
    unsearchable[0] = minEdge;
    for (int i = 1; i <= 8; i++){
        temp = i * interval * 2;
        unsearchable[i] = temp;
    }
    int maxEdge = 2 * totalLine;    // maximum edge case
    unsearchable[unsearchable.size() - 1] = maxEdge; 
    
    // Start searching
    cout << "Searching..." << endl;
    double totalTime = 0;
    for (int j : unsearchable){
        auto begin = chrono::high_resolution_clock::now();
        tree.search(j);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> curDuration = end - begin;  // measured time in milliseconds 
        totalTime += curDuration.count();
        cout << " " << j << "\t" << curDuration.count() << " ms" << endl;
        outputFile << j << endl;
    }
    cout << "Searching done!" << "\n" << endl;
    double avrTime = totalTime / unsearchable.size();
    cout << "total time: " << totalTime << " ms" << endl;
    outputFile << "total time: " << totalTime << " ms" << endl;
    cout << "average time: " << avrTime << " ms" << endl;
    outputFile << "average time: " << avrTime << " ms";
    cout << "tree height: " << tree.getHeight() << endl;
    outputFile.close();
}
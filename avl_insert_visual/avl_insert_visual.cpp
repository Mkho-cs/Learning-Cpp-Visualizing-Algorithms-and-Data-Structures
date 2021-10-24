/*
This program takes an input of integers and insert them into an AVL tree.
After each insert, the tree is displayed on console and output file to visualize rotations.
*/

#include <bits/stdc++.h>
#include <fcntl.h>
#include <io.h>

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
    
    // Display util
    void display(const wchar_t * level, node * bstNode, bool isLeft, wofstream & output);
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

    void display(wofstream & output){
        return display(L"", root, false, output);
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

// Display the tree
// Unicode is used for the box drawing characters to make the tree pretty
// Reference: https://en.wikipedia.org/wiki/Box-drawing_character
void AVL::display(const wchar_t * level, node * avlNode, bool isLeft, wofstream & output){
    if (avlNode != NULL){
        wcout << level;
        output << level;
        // Print type of branch based on position
        wchar_t leftBranch[10] = L"\x251C\x2500\x2500"; // left branch, equivalent to "├──"
        wchar_t rightBranch[10] = L"\x2514\x2500\x2500";    // right branch, equivalent to "└──"
        if (isLeft){
            wcout << leftBranch;
            output << leftBranch;
        }
        else{
            wcout << rightBranch;
            output << rightBranch;
        }
        wcout << avlNode->key << endl;   // print value after branch
        output << avlNode->key << endl;


        //Print next levels recursively
        wchar_t leftLevel[10], rightLevel[10]; 
        wcscpy(leftLevel, level);
        wcscat(leftLevel, L"\x2502");
        wcscat(leftLevel, L"   ");

        wcscpy(rightLevel, level);
        wcscat(rightLevel, L"   ");

        
        
        if (isLeft){
            // Next level for left, output current level + "│   "
            display(leftLevel, avlNode->left, true, output);
            display(leftLevel, avlNode->right, false, output);
        }
        else{
            // Next level for right, output current level + "    "
            display(rightLevel, avlNode->left, true, output);
            display(rightLevel, avlNode->right, false, output);
        }
    }
}

// Driver vode similar to Num 2
// Change input and output file names accordingly
// Utf8 encoding for console and file ouput is enabled to print out the special unicode characters
int main(){
    const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());   // set locale utf8 for output file
    _setmode(_fileno(stdout), _O_U8TEXT);   // set utf8 for printing to console
    string inputFileName = "input_avl_insert_9.txt";
    string outputFileName = "output_avl_insert_9.txt";
    ifstream inputFile (inputFileName);
    wofstream outputFile(outputFileName);
    outputFile.imbue(utf8_locale);  // enable writing utf8 encoding to output file
    AVL tree;

    int num;
    while (inputFile >> num){
        tree.insert(num);
        tree.display(outputFile);
        wcout << L"\n";
        outputFile << L"\n";
    }
    return 0;
}
// *********************************************************
// Program: num8_BinaryKnapsackDynamicProgramming_result_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1V
// Trimester: 2110
// Year: 2021/22 Trimester 1
// Member_1: ID | NAME | EMAIL | PHONES
// Member_2: ID | NAME | EMAIL | PHONES
// Member_3: ID | NAME | EMAIL | PHONES
// Member_4: ID | NAME | EMAIL | PHONES
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************
#include <bits/stdc++.h>

using namespace std;

/*
The code below up to parseFile (line 85) are copied from num7.
These functions share the exact same functionalities to process input files.
*/
// Utility function to check whether string can be a number
bool isNumber(const string& s){
    for (char const &c : s){
        if (isdigit(c) == 0) return false;
    }
    return true;
}

// Basic structure of a knapsack object
struct knapsack{
    int n;
    int maxLoad;
    vector<int> itemNum;
    vector<int> itemWeight;
    vector<int> itemBen;
};

/*
This functions parses a text file (based on given demo format) and returns a knapsack object
Params:
    fileName: A string indicating the file name to parse or the directory of the file

Return:
    A knapsack object containing the parsed data for further processing.
*/
knapsack parseFile(string fileName){
    vector<int> integers;
    fstream currentFile;
    currentFile.open(fileName, ios::in);
    string currentObject;
    // Read text file line by line; store each line as string
    while (!currentFile.eof()){
        getline(currentFile, currentObject);
        // Store the appropriate strings as integers
        if (isNumber(currentObject)){
            int currentNum = stoi(currentObject);
            integers.push_back(currentNum);
        }
    }
    currentFile.close();
    // Initialize and populate the knapsack
    knapsack kSack;
    kSack.n = integers[0];
    kSack.maxLoad = integers[1];
    // Loop per n times after index 1 for the items
    for (int i = 2; i < (2 + kSack.n); i++){  // populate number of items
        kSack.itemNum.push_back(integers[i]);
    }

    int secondInterval = 2 + kSack.n;
    for (int j = secondInterval; j < (secondInterval + kSack.n); j++){  // populate weights
        kSack.itemWeight.push_back(integers[j]);
    }

    for (int k = secondInterval + kSack.n; k < integers.size(); k++){ // populate benefits
        kSack.itemBen.push_back(integers[k]);
    }

    return kSack;
}

// Function to output table as formatted
void outputTable(int** table, knapsack ks, ofstream& outputFile){
    cout << "item\t";
    outputFile << "item\t";
    for (int i = 0; i < ks.maxLoad + 1; i++){
        cout << i << "\t";
        outputFile << i << "\t";
    }
    for (int j = 0; j < ks.n + 1; j++){
        cout << "\nk = " << j << "\t";
        outputFile << "\nk = " << j << "\t";

        for(int k = 0; k < ks.maxLoad + 1; k++){
            cout << table[j][k] << "\t";
            outputFile << table[j][k] << "\t";
        }
    }

}

// Function to create a dp table to calculate optimized results
void dpAlgo(string outputFileName, knapsack ks){
    // Initialize 2D array
    int ** dpTable = new int *[ks.n + 1];     //include item num = 0 (no items)
    for (int i = 0; i < ks.n + 1; i++){
        dpTable[i] = new int [ks.maxLoad + 1];  // include 0 load
    }

    // Populate the dp table
    for (int j = 0; j < ks.n + 1; j++){
        for (int k = 0; k < ks.maxLoad + 1; k++){
        // Base case of item num = 0 or max load = 0
            if (j == 0 || k == 0){
                dpTable[j][k] = 0;
            }
            // Take previous item's benefit if weight of previous item num is greater than current max load
            else if (ks.itemWeight[j - 1] > k){
                dpTable[j][k] = dpTable[j - 1][k];
            }
            // Calculate max of previous value against new value (Recursion)
            else{
                int a = dpTable[j - 1][k];  // value from previous item based on current max load
                // value from previous item based on possible load plus benefit of previous item
                int b = dpTable[j - 1][k - ks.itemWeight[j - 1]] + ks.itemBen[j - 1];   
                dpTable[j][k] = max(a, b);
            
            }
        }
    }
    // Print and write to file results
    ofstream outputFile;
    outputFile.open(outputFileName);
    outputTable(dpTable, ks, outputFile);
    // Trace back item selection for optimized solution
    vector<int> selection;
    int traceRow = ks.n;
    int traceCol= ks.maxLoad;
    while (traceRow != 0){     // start from optimized cell (final index of column and row)
        // trace back until table[0][0]
        if (dpTable[traceRow][traceCol] != dpTable[traceRow - 1][traceCol]){
            selection.push_back(traceRow);
            traceCol = traceCol - ks.itemWeight[traceRow - 1];  // subtract into possible weight columns after each selection
        }
        traceRow--;
    }
    cout << "\n\nmax total benefit: " << dpTable[ks.n][ks.maxLoad];
    outputFile << "\n\nmax total benefit: " << dpTable[ks.n][ks.maxLoad];
    cout << "\nitem numbers =>";
    outputFile << "\nitem numbers =>";
    for (auto m = selection.rbegin(); m != selection.rend(); m++){
        cout << " "<< *m;
        outputFile << " " << *m; 
    }
}

// Driver code
int main (){
    string inputFile = "input_6.txt";
    knapsack k = parseFile(inputFile);

    string outputFile = "output_6_dp.txt";
    dpAlgo(outputFile, k);
}


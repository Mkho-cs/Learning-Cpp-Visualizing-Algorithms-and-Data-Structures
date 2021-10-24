#include <bits/stdc++.h>

using namespace std;

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

// Function to print and write the combinations
void outputComb(ofstream& outputFile, int k, vector<int> itemNumArr, int weight, int ben){
    cout << "k:\t" << k << " => ";
    outputFile << "k:\t" << k << " => ";

    for (auto i = itemNumArr.begin(); i != itemNumArr.end(); i++){
        cout << *i << " ";
        outputFile << *i << " ";
    }

    cout << "\ntotal weight: " << weight;
    outputFile << "\ntotal weight: " << weight;

    cout << "\ntotal benefit: " << ben << "\n\n";
    outputFile << "\ntotal benefit: " << ben << "\n\n";
}

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

/*
This function mainly computes the number of combinations of items based on the number of items in the knapsack.
    Weights and benefits from the knapsack are computed respectively.
    Then the maximum combination is recorded.
Params:
    ks: a knapsack object containing parsed information
References:
    https://stackoverflow.com/questions/9430568/generating-combinations-in-c
*/
void combAlgo (string outputFileName, knapsack ks){
    int totalComb = 0;
    int maxComb = 0;
    int maxBen = 0;
    vector<int> maxCombArr;
    ofstream outputFile;
    outputFile.open(outputFileName); //open new file

    // Start combination algorithm for each number of chosen items
    for (int i = 1; i <= ks.n; i++){
        // Container for the combinations
        vector<bool> combArr(ks.n);
        fill(combArr.begin(), combArr.begin() + i, true);
        do{
            // Record the results for each combination
            vector <int> currentItemNumArr;
            int currentTotalWeight = 0;
            int currentTotalBen = 0;
            for (int j = 0; j < ks.n; j++){
                if (combArr[j]){
                    currentTotalWeight += ks.itemWeight[j];
                    currentTotalBen += ks.itemBen[j];
                    currentItemNumArr.push_back(ks.itemNum[j]);
                }
            }
            totalComb ++;
            // Output current combination
            outputComb(outputFile, totalComb, currentItemNumArr, currentTotalWeight, currentTotalBen);
            // Record maximum combination and benefit where appropriate
            if(currentTotalBen > maxBen && currentTotalWeight <= ks.maxLoad){
                maxBen = currentTotalBen;
                maxComb = totalComb;
                maxCombArr = currentItemNumArr;
            }
        }while(prev_permutation(combArr.begin(), combArr.end()));
       
    }
    // Display and write the best combinations
    cout << "max total benefit: " << maxBen;
    outputFile << "max total benefit: " << maxBen;

    cout << "\nmax k:\t" << maxComb << " => ";
    outputFile << "\nmax k:\t" << maxComb << " => ";

    for (auto m = maxCombArr.begin(); m != maxCombArr.end(); m++){
        cout << *m << " ";
        outputFile << *m << " ";
    }
    outputFile.close();
}

// Driver Code
int main(){
    string inputFile = "input_6.txt";
    knapsack k = parseFile(inputFile);

    string outputFile = "output_6_combi.txt";
    combAlgo(outputFile, k);

    return 0;
}
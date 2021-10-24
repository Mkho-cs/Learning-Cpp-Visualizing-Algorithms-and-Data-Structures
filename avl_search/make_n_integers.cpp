#include <bits/stdc++.h>

using namespace std;

/*
Function to generate even odd numbers starting from 1 to 2n
Note: 
    1. The arrangement for each n does not change (for consistency of time comparison)

    2. Only odd numbers are used so that the unsearchable integers in task 5 and 6 will be even numbers
        This means for n = 250,000, odd numbers from 1 to 500,000 (499,999 to be exact) will be used
        Its easier so that 0 and 2n can be used for the edge cases for task 5 and 6.
*/ 
int main(){
    int n = 1000;     // change this to any integer you'd like
    string fileName = "input_avl_search_1000.txt"; // change based on n
    cout << "Processing... ";

    vector<int> numArr(n);  // create vector of size n
    int start = -1;    // first element will be -1 + 2 = 1
    generate(numArr.begin(), numArr.end(), [&start]{return start += 2;});    // fill in vector with odd numbers starting from 1
    shuffle(numArr.begin(), numArr.end(), mt19937{random_device{}()});  // shuffle with Mersene Twister 19937 generator

    // Write to file
    ofstream outputFile;
    outputFile.open(fileName);
    for(auto i = numArr.begin(); i != numArr.end() - 1; i++){
        outputFile << *i << "\n";
    }
    outputFile << numArr[n - 1];    // prevent \n after final element
    outputFile.close();
    cout << "Done!";
}

 

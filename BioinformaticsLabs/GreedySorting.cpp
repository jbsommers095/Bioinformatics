//
//  main.cpp
//  SequencePermutations
//
//  Created by Jeremy Sommers on 11/14/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}
int abs(int a) {
    return a < 0 ? a * -1 : a;
}
vector<vector<int>> perms(vector<int> arr) {
    vector<int> identity = arr;
    vector<vector<int>> result;
    for (int i = 0; i < identity.size(); i++) {
        identity[i] = abs(identity[i]);
    }
    sort(identity.begin(), identity.begin() + identity.size());
    int index = 0;
    while (arr != identity) {
        bool swapUsed = false;
        int currVal = index + 1;
        if (arr[index] == identity[index] || arr[index] == identity[index] * -1) {
            if (arr[index] == identity[index] * -1) {
                arr[index] *= -1;
                swapUsed = true;
            }
            index++;
        }
        else {
            swapUsed = true;
            for (int i = index; i < identity.size(); i++) {
                if (arr[i] == identity[index] || arr[i] == identity[index] * -1) {
                    int begin = index;
                    int end = i;
                    while (begin <= end) {
                        swap(arr[begin], arr[end]);
                        if (begin == end) {
                            arr[begin] *= -1;
                        }
                        else {
                        arr[begin] *= -1;
                        arr[end] *= -1;
                        }
                        begin++;
                        end--;
                    }
                }
            }
            index = 0;
        }
        if (swapUsed) {
           // cout << "(";
            result.push_back(arr);
       /* for (int i : arr) {
            if (i == arr[arr.size() - 1]) {
                if (i > 0)
                   cout << "+" << i;
                else
                    cout << i;
            }
            else {
            if (i > 0)
            cout << "+" << i << " ";
            else
                cout << i << " ";
            }
        }
            cout << ")" << endl;*/
        }
    }
    /*for (vector<int> i : result) {
        for (int j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }*/
    //cout << result.size() << endl;
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> shorter = {-3, 4, 1, 5, -2};
    vector<int> pies = {1, -7, 6, -10, 9, -8, 2, -11, -3, 5, 4};
    vector<int> arr;
    vector<vector<int>> solution;
    vector<int> solPart;
    string num = "";
        fstream inputFile;
        inputFile.open("rosalind_ba6a.txt");
        if (!inputFile)
            cerr << "The file can't be opened" << endl;
        else
        {
            while (inputFile.good())
            {
                char c = (char) inputFile.get();
                
                if (c != '\377') {
                if (c != ' ') {
                    if (c != ')' && c != '(')
                    num += charToString(c);
                    else {
                        if (c == ')') {
                            if (num[0] == '-') {
                                arr.push_back(stoi(num.substr(1, num.size() - 1)) * -1);
                            }
                            else {
                                arr.push_back(stoi(num.substr(1, num.size() - 1)));
                            }
                            num = "";
                        }
                    }
                }
                else {
                   // cout << num << endl;
                    if (c != '\337') {
                        if (num[0] == '-') {
                            arr.push_back(stoi(num.substr(1, num.size() - 1)) * -1);
                        }
                        else {
                            arr.push_back(stoi(num.substr(1, num.size() - 1)));
                        }
                    }
                    num = "";
                }
            }
            }
        }
    num = "";
    inputFile.close();
    fstream iFile;
    iFile.open("longTestAns.txt");
    if (!iFile)
        cerr << "File won't open" << endl;
    else {
            while (iFile.good())
            {
                char c = (char) iFile.get();
                
                if (c != '\377') {
                    if (c != ' ') {
                        if (c != '(' && c != ')') {
                            num += charToString(c);
                        }
                        else {
                            if (c == ')') {
                                if (num[0] == '-') {
                                    solPart.push_back(stoi(num.substr(1, num.size() - 1)) * -1);
                                }
                                if (num[0] == '+') {
                                    solPart.push_back(stoi(num.substr(1, num.size() - 1)));
                                }
                                solution.push_back(solPart);
                                solPart.clear();
                                num = "";
                            }
                        }
                    }
                    else {
                        if (num[0] == '-') {
                            solPart.push_back(stoi(num.substr(1, num.size() - 1)) * -1);
                        }
                        if (num[0] == '+') {
                            solPart.push_back(stoi(num.substr(1, num.size() - 1)));
                        }
                        num = "";
                    }
               }
            }
        
    }
        iFile.close();
    vector<vector<int>> res = perms(arr);
    for (int i = 0; i < res.size(); i++) {
        cout << "(";
        for (int j = 0; j < res[i].size(); j++) {
            if (j < res[i].size() - 1) {
            if (res[i][j] > 0)
        cout << "+" << res[i][j] << " ";
            else
                cout << res[i][j] << " ";
            }
            else {
                if (res[i][j] > 0)
                    cout << "+" << res[i][j];
                else
                    cout << res[i][j];
            }
        }
        cout << ")" << endl;
    }
    return 0;
}
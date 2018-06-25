//
//  main.cpp
//  Peptites
//
//  Created by Jeremy Sommers on 9/29/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include<sstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;

const vector<int> weights = {0, 57, 71, 87, 97, 99, 101, 103, 113, 113, 114, 115, 128, 128, 129, 131, 137, 147, 156, 163, 186};
const int numPeptides = weights.size();
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
vector<vector<int>> subPeptide(vector<int> subPepts) {
    vector<vector<int>> subs;
    subs.push_back(subPepts);
    vector<int> addPepts = subPepts;
    if (subPepts.size() > 2) {
        for (int i = 0; i < subPepts.size() - 2; i++) {
            addPepts.push_back(subPepts[i]);
        }
    }
    for (int i = 0; i < subPepts.size(); i++) {
        for (int j = 0; j < subPepts.size() - 1; j++) {
            vector<int> candidates;
            for (int k = i; k < i + j + 1; k++) {
                candidates.push_back(addPepts[k]);
            }
            subs.push_back(candidates);
        }
    }
    return subs;
}
vector<vector<int>> linearSubPeptide(vector<int> subPepts) {
    vector<vector<int>> result;
    for (int i = 0; i < subPepts.size(); i++) {
        for (int j = 0; j < subPepts.size() - i; j++) {
            vector<int> subSubPepts;
            for (int k = i; k < i + j + 1; k++) {
                subSubPepts.push_back(subPepts[k]);
            }
            result.push_back(subSubPepts);
        }
    }
    return result;
}
vector<vector<int>> expand(vector<vector<int>> pepts) {
    vector<vector<int>> newSpect;
    for (vector<int> s : pepts) {
        for (int i : weights) {
            vector<int> mass;
            for (int j : s) {
                mass.push_back(j);
            }
            mass.push_back(i);
            newSpect.push_back(mass);
        }
    }
    return newSpect;
}
vector<int> getSpectrum(vector<int> spectrum, bool isLinear) {
    vector<vector<int>> subPepts = isLinear ? linearSubPeptide(spectrum) : subPeptide(spectrum);
    vector<int> spect;
    spect.push_back(0);
    for (vector<int> i : subPepts) {
        int mass = 0;
        for (int j : i) {
            mass += j;
        }
        spect.push_back(mass);
    }
    sort(spect.begin(), spect.begin() + spect.size());
    return spect;
}
vector<vector<int>> trim(vector<vector<int>> pepts, vector<int> spect) {
    vector<vector<int>> consistentPepts;
    for (vector<int> i : pepts) {
        vector<int> linear = getSpectrum(i, true);
        vector<int> curr;
        for (int m : spect) {
            curr.push_back(m);
        }
        bool isConsistent = true;
        for (int j : linear) {
            auto iterator = find(curr.begin(), curr.end(), j);
            if (iterator != curr.end()) {
                curr.erase(iterator);
            }
            else {
                isConsistent = false;
                break;
            }
        }
        if (isConsistent) {
            consistentPepts.push_back(i);
        }
    }
    return consistentPepts;
}
vector<vector<int>> checkedCandidates(vector<vector<int>> candidates, vector<int> spect) {
    vector<vector<int>> result;
    for (vector<int> i : candidates) {
        if (getSpectrum(i, false) == spect) {
            result.push_back(i);
        }
    }
    return result;
}
vector<vector<int>> buildSpectrum(vector<int> spect) {
    vector<vector<int>> pepts;
    vector<int> empty;
    pepts.push_back(empty);
    
    vector<vector<int>> result;
    while(!pepts.empty()) {
        pepts = expand(pepts);
        vector<vector<int>> check = checkedCandidates(pepts, spect);
        for (vector<int> i : check) {
            result.push_back(i);
        }
        pepts = trim(pepts, spect);
    }
    return result;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream inFile;
    vector<int> spect;
    string num;
    string shortName = "shortTest.rtf";
    string longName = "rosalind_ba4e.txt";
    inFile.open(longName);
    if (!inFile) {
        cerr << "Unable to open file" << endl;
        exit(1); // terminate with error
    }
    
    while (inFile.good()) {
        char c = (char) inFile.get();
            if (c != ' ' && c != '\377') {
                num += charToString(c);
            }
            else {
                spect.push_back(stoi(num));
                num = "";
            }
    }
    inFile.close();
    vector<vector<int>> spt = buildSpectrum(spect);
    set<vector<int>> ans;
    for (vector<int> i : spt) {
        ans.insert(i);
    }
    for (vector<int> i : ans) {
        for (int j = 0; j < i.size(); j++) {
            if (j == i.size() - 1)
            cout << i[j];
            else
                cout << i[j] << "-";
        }
        cout << endl;
    }
    /*for (vector<int> i : c) {
        for (int j : i)
        cout << j << ", ";
        cout << endl;
    }
    /*for (vector<int> i : spectrum) {
        for (int j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
    vector<vector<int>> e = expand({{}});
    vector<vector<int>> f = checkedCandidates(e, spect);
    vector<vector<int>> h = subPeptide(spect);
    for (vector<int> i : f) {
        for (int j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
    for (vector<int> i : h) {
        for (int j : i)
        cout << j << ", ";
        cout << "ln" << endl;
    }*/
    return 0;
}
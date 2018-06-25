//
//  main.cpp
//  GapPenalty
//
//  Created by Jeremy Sommers on 10/26/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;
const int GAP_OPEN = 11;
const int GAP_EXTEND = 1;
const int TWO_BILLION = -2000000000;
const string ALPHA = "ACDEFGHIKLMNPQRSTVWY";
string charToString(char c) {
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return s;
}
map<string, int> fillMap() {
    map<string, int> map;
    for (int i = 0; i < ALPHA.length(); i++) {
        map[charToString(ALPHA[i])] = i;
    }
    return map;
}
map<string, int> bMap = fillMap();
const int BLOSUM[20][20] = {{4,0,-2,-1,-2,0,-2,-1,-1,-1,-1,-2,-1,-1,-1,1,0,0,-3,-2},{0,9,-3,-4,-2,-3,-3,-1,-3,-1,-1,-3,-3,-3,-3,-1,-1,-1,-2,-2},{-2,-3,6,2,-3,-1,-1,-3,-1,-4,-3,1,-1,0,-2,0,-1,-3,-4,-3},{-1,-4,2,5,-3,-2,0,-3,1,-3,-2,0,-1,2,0,0,-1,-2,-3,-2},{-2,-2,-3,-3,6,-3,-1,0,-3,0,0,-3,-4,-3,-3,-2,-2,-1,1,3},{0,-3,-1,-2,-3,6,-2,-4,-2,-4,-3,0,-2,-2,-2,0,-2,-3,-2,-3},{-2,-3,-1,0,-1,-2,8,-3,-1,-3,-2,1,-2,0,0,-1,-2,-3,-2,2},{-1,-1,-3,-3,0,-4,-3,4,-3,2,1,-3,-3,-3,-3,-2,-1,3,-3,-1},{-1,-3,-1,1,-3,-2,-1,-3,5,-2,-1,0,-1,1,2,0,-1,-2,-3,-2},{-1,-1,-4,-3,0,-4,-3,2,-2,4,2,-3,-3,-2,-2,-2,-1,1,-2,-1},{-1,-1,-3,-2,0,-3,-2,1,-1,2,5,-2,-2,0,-1,-1,-1,1,-1,-1},{-2,-3,1,0,-3,0,1,-3,0,-3,-2,6,-2,0,0,1,0,-3,-4,-2},{-1,-3,-1,-1,-4,-2,-2,-3,-1,-3,-2,-2,7,-1,-2,-1,-1,-2,-4,-3},{-1,-3,0,2,-3,-2,0,-3,1,-2,0,0,-1,5,1,0,-1,-2,-2,-1},{-1,-3,-2,0,-3,-2,0,-3,2,-2,-1,0,-2,1,5,-1,-1,-3,-3,-2},{1,-1,0,0,-2,0,-1,-2,0,-2,-1,1,-1,0,-1,4,1,-2,-3,-2},{0,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,0,-1,-1,-1,1,5,0,-2,-2},{0,-1,-3,-2,-1,-3,-3,3,-2,1,1,-3,-2,-2,-3,-2,0,4,-3,-1},{-3,-2,-4,-3,1,-2,-2,-3,-3,-2,-1,-4,-4,-2,-3,-3,-2,-3,11,2},{-2,-2,-3,-2,3,-3,2,-1,-2,-1,-1,-2,-3,-1,-2,-2,-2,-1,2,7}};

void globalAlignmentGraph(string a, string b) {
    int aLen = (int) a.length() + 1;
    int bLen = (int) b.length() + 1;
    int graph[3][aLen][bLen]; // 0 = match, 1 = gap opening, 2 = gap extension
    int directions[3][aLen][bLen];
    for (int i = 0; i < aLen; i++) {
        for (int j = 0; j < bLen; j++) {
            if (i == 0 || j == 0) {
                if (i == 0 && j == 0) {
                    for (int k = 0; k < 3; k++) {
                        graph[k][i][j] = 0;
                        directions[k][i][j] = 0;
                    }
                }
                else {
                if (i == 0) {
                    graph[0][i][j] = -1 * (GAP_OPEN + (j - 1) * GAP_EXTEND);
                    graph[1][i][j] = -10 * GAP_OPEN;
                    graph[2][i][j] = -1 * (GAP_OPEN + (j - 1) * GAP_EXTEND);
                    for (int k = 0; k < 3; k++) {
                        directions[k][i][j] = 1;
                    }
                }
                else {
                if (j == 0) {
                    graph[0][i][j] = -1 * (GAP_OPEN + (i - 1) * GAP_EXTEND);
                    graph[1][i][j] = -1 * (GAP_OPEN + (i - 1) * GAP_EXTEND);
                    graph[2][i][j] = -10 * GAP_OPEN;
                    for (int k = 0; k < 3; k++) {
                        directions[k][i][j] = 0;
                    }
                }
            }
                }
            }
            else {
                int downMatch = graph[0][i - 1][j] - GAP_OPEN;
                int downExtend = graph[1][i - 1][j] - GAP_EXTEND;
                if (downExtend > downMatch) {
                    graph[1][i][j] = downExtend;
                    directions[0][i][j] = 0;
                }
                else {
                    graph[1][i][j] = downMatch;
                    directions[0][i][j] = 1;
                }
                int upMatch = graph[0][i][j - 1] - GAP_OPEN;
                int upOpen = graph[2][i][j - 1] - GAP_EXTEND;
                if (upOpen > upMatch) {
                    graph[2][i][j] = upOpen;
                    directions[2][i][j] = 0;
                }
                else {
                    graph[2][i][j] = upMatch;
                    directions[2][i][j] = 1;
                }
                int matchMatch = graph[0][i - 1][j - 1] + BLOSUM[bMap[charToString(a[i - 1])]][bMap[charToString(b[j - 1])]];
                int matchExtend = graph[1][i][j];
                int matchOpen = graph[2][i][j];
                graph[0][i][j] = matchExtend;
                directions[1][i][j] = 0;
                if (matchMatch > graph[0][i][j]) {
                    graph[0][i][j] = matchMatch;
                    directions[1][i][j] = 1;
                }
                if (matchOpen > graph[0][i][j]) {
                    graph[0][i][j] = matchOpen;
                    directions[1][i][j] = 2;
                }
    }
        }
    }
    for (int i = 0; i < 3; i++) {
        cout << i << ":" << endl;
        for (int j = 0; j < aLen; j++) {
            for (int k = 0; k < bLen; k++) {
                cout << directions[i][j][k] << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }
    string aAlign = "";
    string bAlign = "";
    int i = aLen - 1;
    int j = bLen - 1;
    int maxPtr = max(graph[0][i][j], max(graph[1][i][j], graph[2][i][j]));
    int bestDirection = 0;
    if (maxPtr == graph[0][i][j])
        bestDirection = 1;
    if (maxPtr == graph[2][i][j])
        bestDirection = 2;
    int maxScore = maxPtr;
    cout << bestDirection << endl;
    while (i > 0 && j > 0) {
        if (bestDirection == 0) {
            if (directions[bestDirection][i][j] == 1) {
                bestDirection = 1;
            }
            aAlign.insert(0, charToString(a[i - 1]));
            bAlign.insert(0, "-");
            i--;
        }
        else {
            if (bestDirection == 1) {
                if (directions[bestDirection][i][j] == 0) {
                    bestDirection = 0;
                }
                else {
                    if (directions[bestDirection][i][j] == 2) {
                        bestDirection = 2;
                    }
                    else {
                        aAlign.insert(0, charToString(a[i - 1]));
                        bAlign.insert(0, charToString(b[j - 1]));
                        i--;
                        j--;
                    }
                }
            }
            else {
                if (directions[bestDirection][i][j] == 1) {
                    bestDirection = 1;
                }
                aAlign.insert(0, "-");
                bAlign.insert(0, charToString(b[j - 1]));
                j--;
            }
        }
    }
    string partA = aAlign.substr(0, a.length() - (a.length() - i));
    string partB = bAlign.substr(0, b.length() - (b.length() - j));
    while (i > 0) {
        //string part = aAlign.substr(0, a.length() - (a.length() - i));
        partA.insert(0, "-");
        i--;
    }
    while (j > 0) {
        partB.insert(0, "-");
        j--;
    }
    cout << maxScore << endl;
    cout << aAlign << endl;
    cout << bAlign << endl;
}



int main(int argc, const char * argv[]) {
    string a = "ACTACA";
    string b = "ACAA";
    string c = "AAT";
    string d = "ACACT";
    string e = "PRTEINS";
    string f = "PRTWPSEIN";
    string g = "YHFDVPDCWAHRYWVENPQAIAQMEQICFNWFPSMMMKQPHVFKVDHHMSCRWLPIRGKKCSSCCTRMRVRTVWE";
    string h = "YHEDVAHEDAIAQMVNTFGFVWQICLNQFPSMMMKIYWIAVLSAHVADRKTWSKHMSCRWLPIISATCARMRVRTVWE";
    string n = "RCVSNQHPICWFMLVDGLLKCVELPARCLCQCGQGDHKFKNRKPFGWWCIHIGRCEMSGCCFLPMIAQGGEFPFVMKILQ";
    string m = "RCVSNQHVYYEPICWFMLVDGLLKCVELPARCLCQCGNGDHKFHWCIHIGRHMEWHSIQGFLPMKHQGGEFPFVMRLI";
    globalAlignmentGraph(m, n);
    return 0;
}
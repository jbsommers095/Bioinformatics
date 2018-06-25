//
//  main.cpp
//  brujin2
//
//  Created by Jeremy Sommers on 9/14/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


struct assoc {
    int index;
    string text;
};
bool operator < (const assoc &left, const assoc &right) {
    return left.index < right.index;
}

map<string, list<string>> digraph(string dna, int k) {
    vector<assoc> dnaSet;
    for (int i = 0; i <= dna.length() - k; i+=k) {
        string p = dna.substr(i, k);
        dnaSet.push_back({i / k, p});
    }
    map<assoc, vector<string>> graph;
    map<string, list<string>> kmers;
    for (assoc a : dnaSet) {
        if (graph.find(a) == graph.end())
        graph[a] = {a.text.substr(0, k - 1), a.text.substr(1, k - 1)};
        if (kmers.find(graph[a][0]) == kmers.end())
            kmers[graph[a][0]] = {graph[a][1]};
        else
            kmers[graph[a][0]].push_front(graph[a][1]);
    }
    map<string, vector<string>> vals;
    return kmers;
}
map<string, list<string>> bruj(list<string> dna) {
    map<string, list<string>> graph;
    return graph;
}
int main(int argc, const char * argv[]) {
    string p = "";
    ifstream inFile;
    
    string name = "LongString.txt";
    inFile.open(name);
    if (!inFile) {
        cerr << "Unable to open file" << endl;
        exit(1);
    }
    
    while (inFile.good()) {
        char c = inFile.get();
        if (c != '\377' && (int) c != 10) {
        p += c;
     }
    }
    inFile.close();
    map<string, list<string>> graph = digraph(p, 20);
    for (map<string, list<string>>::iterator iter = graph.begin(); iter != graph.end(); iter++) {
        cout << iter -> first << " -> ";
        for (list<string>::iterator it = graph[iter -> first].begin(); it != graph[iter -> first].end(); it++) {
            cout << *it;
            if (it != prev(graph[iter -> first].end()))
                cout << ", ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
    
}
//
//  main.cpp
//  LeafDistance
//
//  Created by Jeremy Sommers on 11/14/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;
const int LARGE = 100000;
struct edge {
    vector<int> out;
    vector<int> weight;
};

struct graph {
    map<int, edge> edges;
};

graph makeGraph(vector<int> inEdges, vector<int> outEdges, vector<int> weights) {
    graph g;
    bool flags[inEdges.size()];
    for (int i = 0; i < inEdges.size(); i++)
        flags[i] = false;
    for (int i = 0; i < inEdges.size(); i++) {
        if (!flags[i]) {
        vector<int> outers = {outEdges[i]};
        vector<int> mass = {weights[i]};
        vector<int> dist = {INT_MAX};
        edge e;
        e.out = outers;
        e.weight = mass;
            for (int j = i + 1; j < inEdges.size(); j++) {
                if (inEdges[i] == inEdges[j]) {
                    e.out.push_back(outEdges[j]);
                    e.weight.push_back(weights[j]);
                    flags[j] = true;
                }
            }
            g.edges[inEdges[i]] = e;
            flags[i] = true;
        }
    }
    return g;
}

vector<int> getLeafs(graph g) {
    vector<int> leafs;
    for (map<int, edge>::iterator iter = g.edges.begin(); iter != g.edges.end(); iter++) {
        if (g.edges[iter -> first].out.size() == 1) {
            leafs.push_back(iter -> first);
        }
    }
    return leafs;
}
// Assumes start and end exist in the graph and that start points directly at end
int getWeight(graph g, int start, int end) {
    edge e = g.edges[start];
    vector<int> outers = e.out;
    for (int i = 0; i < outers.size(); i++) {
        if (outers[i] == end) {
            return e.weight[i];
        }
    }
    return LARGE;
}
void floydWarshall(graph g) {
    int matDim = g.edges.size();
    int leafCount = getLeafs(g).size();
    int distMat[matDim][matDim];
        for (int i = 0; i < matDim; i++) {
            for (int j = 0; j < matDim; j++) {
                distMat[i][j] = LARGE;
                if (i == j) {
                    distMat[i][j] = 0;
                }
                else {
                    distMat[i][j] = getWeight(g, i, j);
                }
            }
        }
    for (int i = 0; i < matDim; i++) {
        for (int j = 0; j < matDim; j++) {
            for (int k = 0; k < matDim; k++) {
                if (distMat[j][i] + distMat[i][k] < distMat[j][k])
                    distMat[j][k] = distMat[j][i] + distMat[i][k];
            }
        }
    }
    for (int i = 0; i < leafCount; i++) {
        for (int j = 0; j < leafCount; j++) {
            if (distMat[i][j] == LARGE)
                cout << "I ";
            else
            cout << distMat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> longInput;
    vector<int> longOutput;
    vector<int> longWeights;
    
    ifstream inFile;
    inFile.open("rosalind_ba7a.txt");
    if (!inFile) {
        cerr << "Unable to open file!" << endl;
    }
    else {
        string num = "";
        while (inFile.good()) {
            char c = (char) inFile.get();
            if (c != '\377') {
            if (c - '0' >= 0 && c - '0' <= 9) {
                num += c;
            }
            else {
                if (c == '-') {
                    longInput.push_back(stoi(num));
                    num = "";
                }
                if (c == ':') {
                    longOutput.push_back(stoi(num));
                    num = "";
                }
                if (c == '\n') {
                    longWeights.push_back(stoi(num));
                    num = "";
                }
            }
        }
        }
    }
    inFile.close();
    graph h = makeGraph(longInput, longOutput, longWeights);
    graph g = makeGraph({0, 1, 2, 3, 4, 4, 4, 5, 5, 5}, {4, 4, 5, 5, 0, 1, 5, 4, 3, 2}, {11, 2, 6, 7, 11, 2, 4, 4, 7, 6});
    floydWarshall(h);
    return 0;
}
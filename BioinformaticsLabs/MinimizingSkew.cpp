//
//  main.cpp
//  Skew
//
//  Created by Jeremy Sommers on 9/1/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

void skew(string text) {
    int smallestDiff = 0;
    int posns[text.length()];
    int gDiffc = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text.at(i) == 'G')
            gDiffc++;
        if (text.at(i) == 'C')
            gDiffc--;
        
        posns[i] = gDiffc;
        
        if (gDiffc < smallestDiff)
            smallestDiff = gDiffc;
    }
    for (int i = 0; i < text.length(); i++) {
        if (posns[i] == smallestDiff)
            cout << i + 1 << ", " << posns[i] << endl;
    }
    
}

int main(int argc, const char * argv[]) {
    ifstream io;
     
     io.open("shortText.txt");
     
     if(!io) {
     cerr << "Can't find the file." << endl;
     exit(1);
     }
     string test = "";
     while (io.good()) {
     char a = io.get();
     if (a != '\377')
     test += a;
     }
     io.close();
     //sequenceFinder(test, 12);
     string t = "CATGGGCATCGGCCATACGCC";
     
     //int length = t.length();
    
    /*ifstream file;
     
     file.open("text.txt");
     if (!file) {
     cerr << "Can't find the file." << endl;
     exit(1);
     }
     string bigstring = "";
     while (file.good()) {
     char c = file.get();
     if (c != '\377')
     bigstring += c;
     }
     // cout << bigstring << endl;
     file.close();
     //sequenceFinder(bigstring, 5);
     string q = "CCTATCGGTGGATTAGCATGTCCCTGTACGTTTCGCCGCGAACTAGTTCACACGGCTTGATGGCAAATGGTTTTTCCGGCGACCGTAATCGTCCACCGAG";*/
    
    //skew(q);
    return 0;
}
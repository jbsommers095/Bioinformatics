//
//  main.cpp
//  SequenceFinder
//
//  Created by Jeremy Sommers on 9/1/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>

using namespace std;


void sequenceFinder(string text, int k) {
    map<string, int> freqs;
    int largestValue = 1;
    for (int i = 0; i <= text.length() - k; i++) {
        string s = text.substr(i, k);
        if (freqs.find(s) != freqs.end()) {
            freqs[s] += 1;
            if (freqs[s] > largestValue) {
                largestValue = freqs[s];
            }
        }
        else
            freqs[s] = 1;
    }
    for (map<string, int>::iterator iter = freqs.begin(); iter != freqs.end(); iter++) {
        if (iter -> second == largestValue)
            cout << iter -> first << " : " << iter -> second << endl;
    }
}
int main(int argc, const char * argv[]) {
    string s = "GAGTTAACGAACGCTTAAC";
    // sequenceFinder(s, 3);
    string a = "TheQuickBrownFoxJumpsOverTheLayDog";
    // sequenceFinder(a, 1);
    string m = "ACGTTGCATGTCGCATGATGCATGAGAGCT";
    sequenceFinder(m, 4);
    string txt = "CGGAAGCGAGATTCGCGTGGCGTGATTCCGGCGGGCGTGGAGAAGCGAGATTCATTCAAGCCGGGAGGCGTGGCGTGGCGTGGCGTGCGGATTCAAGCCGGCGGGCGTGATTCGAGCGGCGGATTCGAGATTCCGGGCGTGCGGGCGTGAAGCGCGTGGAGGAGGCGTGGCGTGCGGGAGGAGAAGCGAGAAGCCGGATTCAAGCAAGCATTCCGGCGGGAGATTCGCGTGGAGGCGTGGAGGCGTGGAGGCGTGCGGCGGGAGATTCAAGCCGGATTCGCGTGGAGAAGCGAGAAGCGCGTGCGGAAGCGAGGAGGAGAAGCATTCGCGTGATTCCGGGAGATTCAAGCATTCGCGTGCGGCGGGAGATTCAAGCGAGGAGGCGTGAAGCAAGCAAGCAAGCGCGTGGCGTGCGGCGGGAGAAGCAAGCGCGTGATTCGAGCGGGCGTGCGGAAGCGAGCGG";
    sequenceFinder(txt, 12);
    return 0;
}
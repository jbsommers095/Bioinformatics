//
//  main.cpp
//  BestMotif
//
//  Created by Jeremy Sommers on 9/6/17.
//  Copyright © 2017 Jeremy Sommers. All rights reserved.
//

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <fstream>
#include <map>
using namespace std;
bool comparator(double a, double b) {
    return a > b;
}
map<char, vector<double>> profile(vector<string> s) {
    map<char, vector<double>> freqs;
    char alphabet[4] = {'A', 'C', 'G', 'T'};
    double largestProbs[s.at(0).size()];
    set<string> candidates;
    for (char c : alphabet) {
        vector<double> percents;
        for (int i = 0; i < s.at(0).length(); i++) {
            int count = 0;
            for (int j = 0; j < s.size(); j++) {
                //cout << s.at(j)[i] << ", " << endl;
                if (s.at(j)[i] == c)
                    count++;
            }
            double quotient = (double) count / s.size();
            percents.push_back(quotient);
            if (quotient > largestProbs[i]) {
                largestProbs[i] = quotient;
            }
            //cout << c << ", " << quotient << endl;
        }
        freqs[c] = percents;
        
    }
    return freqs;
}
vector<string> split(string s, int k) {
    vector<string> arr;
    int divisor = s.length() / k;
    string t = "";
    for (int i = 0; i < s.length(); i++) {
        t += s[i];
        if ((i + 1) % divisor == 0 && (i + 1) != 0) {
            arr.push_back(t);
            t = "";
        }
    }
    return arr;
}
string candidate(vector<string> s) {
    if (s.empty())
        return "";
    map<char, vector<double>> freqs = profile(s);
    char alpha[] = {'A', 'C', 'G', 'T'};
    string ans = "";
    for (int i = 0; i < freqs['A'].size(); i++) {
        double largest = 0;
        char a = 'A';
        for (char c : alpha) {
            if (freqs[c].at(i) > largest) {
                a = c;
                largest = freqs[c].at(i);
            }
        }
        ans += a;
    }
    return ans;
}
double probability(string t, map<char, vector<double>> freqs) {
    double product = 1.0;
    for (int i = 0; i < t.length(); i++) {
        product *= freqs[t.at(i)].at(i);
    }
    return product;
}
int score(string t, vector<string> s) {
    if (s.empty() || t.empty())
        return 0;
    int value = 0;
    for (int i = 0; i < t.length(); i++) {
        for (int j = 0; j < s.size(); j++) {
            if (t[i] != s[j][i])
                value++;
        }
    }
    return value;
}
string mostProbable(string s, int k, map<char, vector<double>> freqs) {
    map<string, double> events;
    string profileMost;
    double largest = 0;
    for (int i = 0; i <= s.length() - k; i++) {
        string p = s.substr(i, k);
        double curr = probability(p, freqs);
        if (curr > largest) {
            profileMost = p;
            largest = curr;
        }
    }
    return profileMost;
}
vector<string> greedySearch(string s, int k, int t) {
    vector<string> dna = split(s, t);
    vector<string> no;
    vector<string> bestMotifs;
    for (int i = 0; i < t; i++) {
        bestMotifs.push_back(dna.at(i).substr(0, k));
    }
    for (int i = 0; i <= dna.at(0).length() - k; i++) {
       vector<string> motif = {(dna.at(0).substr(i, k))};
        for (int j = 1; j < t; j++) {
            map<char, vector<double>> chart = profile(motif);
            string probable = mostProbable(dna.at(j), k, chart);
            if (probable.empty()) {
         motif.push_back(dna.at(j).substr(0, k));
         }
         else {
            motif.push_back(probable);
         }
        }
        if (score(candidate(motif), motif) < score(candidate(bestMotifs), bestMotifs)) {
            bestMotifs = motif;
        }
    }
    
    return bestMotifs;
}

int main(int argc, const char * argv[]) {
    string strs[] = {"GGCGTTCAGGCA", "AAGAATCAGTCA", "CAAGGAGTTCGC", "CACGTCAATCAC", "CAATAATATTCG"};
    vector<string> dna;
    for (int i = 0; i < 5; i++) {
        dna.push_back(strs[i]);
    }
    char alpha[] = {'A', 'C', 'G', 'T'};
    vector<double> arr = {0.5, 0.875, 0.375, 0, 0.125, 0};
    vector<double> crr = {0.125, 0, 0.5, 0.625, 0.375, 0};
    vector<double> trr = {0.125, 0.125, 0, 0, 0.25, 0.875};
    vector<double> grr = {0.25, 0, 0.125, 0.375, 0.25, 0.125};
    map<char, vector<double>> probs;
    probs['A'] = arr;
    probs['C'] = crr;
    probs['T'] = trr;
    probs['G'] = grr;
    /*ifstream file;
    
    file.open("test.txt");
    if (!file) {
        cerr << "Can't find the file." << endl;
        exit(1);
    }
    string bigstring = "";
    while (file.good()) {
        char c = file.get();
        if (c != '\377')
            bigstring += c;
    }*/
    // cout << bigstring << endl;
    //file.close();
    string v = "GCCCAAGGCCTGAACCTATTCCTT";
    string s = "GCCAAGTAGGAAAGAACGATCTCAACGGTTACTAATAATTAGAATTAAACCCCCTCGGACTCTTAGGACTGTGTCCCTTATCTGTATGCCGTCTATATCATCGAGTCCCCTTTCCGGTAGGAAACTCAAATCATCTCAACTCCGGGCTTATACCTGAGCTAAGTAGACGGCTTATAACGCATGTCAAGATAATAGTCGTTAGGACGTTGCTATCGGGGAGCACCCCGTTCCAACGCCCGTTAAACAACTCGTTTGAGTTACCTTTACAGACCGGGCGATAATGCCAGCAATGCGGATTCGCAACGTCGGTCAGGTAATTTGCTACAGGTTCTAATAGAACATAGCCATGTTTCCAGATGGGGCTTATATTGGGGTGCTCGCTAGACTATCCTGTAGTGAGATTTCGGGAACTTAAGGAATATGGGTCACCAGGCGGATTCAGTGGCGGCGGCGTGGTTTTACCTTGTCGCCGCGGCTGAAGCATTAGGAGGGTCAACCTCTTTCGCCAATCGAAAAGGCTTATAACAGGTTCGGCGCCTCTAATCCTCATCCAACCAGGCACGGCCACTTGAACTGACTGAGTGGTGCGAGGAGTTGAGAGCCAATGGCTATGAGCCTGCGTCTGTCAGACTATGTGCATGCAGTCTTTGATAACTACGTATAGTATTAAGCGTTCCCCTATCCGGCTTATAGGCTAGGAAGGAGAGGCGAATTAACTTCGGAGTTCGACTAATACTCGATGTAACGACATTCAACCCTCAATACGGATAATCAGTGTAATATGAACCATTGCGATATGTTAAGGGCTTATATAAGCGGGAAATCGGTCTTGCCTGCCAGCGACACGGCCCGAGCCGGGTTGTGTGTCCTTTCGTCTGTTCTAGGGTTGGTTAACGGAGTACGGTGTCTATCTGGTTCGTCTGATCACACCCCGCGGGTCATTGAAGACCAATCCATCTGCTGTACCGGTTAAATATCTAGCACGGCTTATAGTCCGCGGAGAACCAGCGTTCTAACCTCGACGAACCGTTCAGGGCTTTGTTAATAAGGGTATCACACTTTGCCAATTTCATTCCGTATGACGAAGCTGTCCTGCGAAGAGTTCGCACCACAGCACTCCAAAGCTGTCAGCCGGATTATAGCAATTACTGACGAGCGACGGTCGTGGAACCAAACATTTCGTGAGGCCCTCAGCGCAGCAGGAGTGTGTCAGGGAGGCGATGCGGCTTATAATGACATTATAGGTTGCGTCAGGAATGGGTTGAGGAGGTGCGCCGCTGAGATAGATAAGGCCAGATAAGTAACCTCGGCACGAACGAAAACCAGCGTGCGTGGATTAAATCGGGCTTATAATTTTGCCAGGTGCAAATAAGAAGCCAGTTTAAGCCGTCCCCGGATTGTGGAAAATACCTCACATACCGTCTCACGGGCTTATAGCCGCAGTGGTCCACAACCGTCTGTGGAACCAATGCTGGCAGTCGAAGCCGCCTCTTCACTGTGTAATGAACCCGTTATGGACAATGGAAACAGCTGCCATGCGCTTCTGTGCCCCTCGTCAAACAGGATGCCCGCCGGGAGATCCAAACACCATGCCTGGTGGGAAGGCATCCACCCCCTCAATAAGAGAGTCATGGCTTATATGATCATTGTAAGGACAACATCGGTTGTTCCGACTGCTGGATCCCGCTGGCATCCTTCTACTCTCTGTGCTAAAAGCCAGTGGTCGTTCGGAACAGGGTGGCTGCCGGTTGCCCGATGTTAGTATTCTAAGAGGCTGAGGGATTCTTTGCCCTAGGTCGATTGTTCGCGAACGGCTTATATATTAGATCTTCCGCGGGACGCAGATACGGTGCTGCGGCACCCTTCTCTGACGTTAACATGTAGTGAATAATGGAAATGCTGTGTAGTGGCTTATAAAACCAAAGTTGCCGGTGACGAAACGCGAACATATGATGTGGGTACCGTGTGACCGGTGAGAGTCGGTATGCGTTTAACACTTCACTTGCCAGAAAGAAGCCGCGCGATCTTGGGACGATGCCGAAGTGGCTCCCAGTGTTAACTGAAGGCATGATATTGGATACATTTCCTATTGTTTGACGGTTACGTTAAGACTGCGAAACCCTAGGCTTATACCTCAGCCGAGCTTTAAACCCTCGGTAATGAGACCTTATTGCGGGTCGGATCCCTGGGGATGCGCGCCATTGGAATACGTCCAGACGAGGGCCGACGAAAAGGGGGGCCATCCTAACTTGGGATTTACGAACCATAGGCTTATAGCGAAAGGTATTATAGACTGATCATTCTGTGCACGGTTTTAGTCTGATAAGTGCTTACTTGCTAGGCTTATAGCCCGCTCCGACGAAGCCTATACTACTGGAGGATTTAAGAGTGGTCGAGTCAAAGCCTTGCCTGGATCGTTGTAACGATCGTCACCGAACGGATGGCAGCCCGCAGTATACGGGGCCGTCTCATGTTTATTGTTCCAAAGTTTTGCCTATCCGGGCTTCGATGACGCGGGAAGGCTTATACAATCCCTATCCAGTCCGCGTTTTTTGATCTCGTTTTACACGACAAATCCTGACAGTTGCTCTCCGTCCTGCTATTTGGAGAGATAACGGCAGCGGTTATTGAATACGATACTAATGCTCTTTATGTCCCGTGTCGACACTCTACCTTGAGCGCCCTTTGTCCAGGAGGTGGCACCTCAAAGAAGCGTTATCCGCAAAGGAACGTGGACCTTCCGAACCGGGAACTTAATCAGAAAACGGATTCTGCGGACGGGATGGCTTATAAAGATAGTATGACATAGGCTTATAGCGGTAAGACGGGTGTACTGCTCGAGCCGCGGTTGTGCTGACGGGACAACGCCGTCCCGATCATATTAAGCACAATTCGTATGCGACCGCAAGGTATTAGCACCGGACAAAGCCACCCTTCTACGGTCATGTCTCAGACAATGTTCAGAGAGGCTCCGCAGTCTAAGGCCACGCCCTCCGCAGGATCTGAGTATAGCAATTCCTAACGGGCTTATACCCGGCTGGCATCGTTAAAGGCGCAAATACGACGTTACTGCAACCTCTCGTTCTTCCGAGTATGATACGACACGCATACAGGCACTCGTAAGTCGGATGCCGCTCGCTACGGGTACCGGTGACAGTCCCGGTAGATTAATCTTAGCAGATCCGTGTTCTAGAACTGGCAGGCGGCTTATAGACGGGATATCTGAAGGACATTAGGAACTGCGGGCCTGGCGGGGCGAATAAGTTTGGGGTCTGTGGCTTATAGAGTAGCAAATATGTTCCCGTCGTCTTCATGTCTGGTGGCCATTCATTACCTAGTGTCTGAGACGTGTCGTACAAAGCATAACCGCTGGGTGATCTATAGGTGAACGCGGTGTGTCACGAGGAGTCGAGTTGGTAACCGTGAGGTTTTGGCTTATAATTAATACTCCATCTGTGACGGAGTTTCAGCATTGCATGCGTTCTTCCGCTAGACCCAGGGTTTGCGAAAGGTGCAGATTATCGTTCCTAGACCAATGCACGAAAGAGGTATAAGTCCGTATCCGCGCGCTTACTTCGTAGTAGCACTACTTGAAGAAACTGTGGGGTCCATTGCTACGCATAAGACTCCGACTGCGAAGAAGAAGCGTACGTAAACAAAATCAGTCAAATATTCTTACGGCCCGGCTTATAGCGGACGCACTCCCGCGATATTAATTTGACGCGATAGTCCTCCAGTCCGTCGATCGCCCATCCGTACCGAGGACAGAAAGCGTTACCACGCCTACTCCTCGTAACGCAGATTTCTTTACCGTGCAGGACGCGATTGCGAATATATCCCGGCTTATACGAGGACAAACAGACCAACCGGCGTCGCGCCTAATCGCAGATCGTTAGAAAC";
    //cout << s.length() << endl;
    //vector<string> text = split(s, 25);
    //string test = text.at(0);
    //probability(test, profile(test.split(1)));
    //cout << text.at(0).length() << endl;
    /*for (vector<string>::iterator iter = text.begin(); iter != text.end(); iter++) {
        cout << *iter << endl;
    }*/
    string b = "GGCGTTCAGGCAAAGAATCAGTCACAAGGAGTTCGCCACGTCAATCACCAATAATATTCG";
    string x = "GACCTACGGTTACAACGCAGCAACCGAAGAATATTGGCAATCATTATCGATAACGATTCGCCGGAGGCCATTGCCGCACAGGAGTCTGGTGAAGTGTGGGTTATGGGGCAGACTGGGAAAGAATCCGATAACTGACACCTGCTCTGGCACCGCTCTCATCAAGCGCGTAGGCGCGGCTTGGCATCTCGGTGTGTGGCCAAAATTGAAAGGCGCATCTTACTCTTTTCGCTTAAAATCAAAGGTATAGCCAGAAAGCGTAGTTAATTTCGGCTCCTGCCAATCTGTTGTTGCTAACACCGTTAAAGGCGGCGACGGCAACT";
    vector<string> team = split(b, 5);
    map<char, vector<double>> points = profile(team);
    //cout << stris << endl;
    //vector<string> team = greedySearch(b, 3, 5);
    /*for (char c : alpha) {
        cout << c << " : ";
        for (double d : points[c]) {
            cout << d  << ", ";
        }
        cout << endl;
    }
    for (char c : alpha) {
        cout << c << " : ";
        for (double d : toints[c]) {
            cout << d << ", ";
        }
        cout << endl;
    }*/
    /*for (int i = 0; i <= team.at(3).length() - 3; i++) {
        string f = team.at(3).substr(i, 3);
        cout << f << ", " << probability(f, profile(team)) << ", " << score(f, team) << endl;
        cout << candidate(t1) << score(candidate(t1), team) << endl;
    }*/
    /*cout << mostProbable(team.at(0), 3, profile(t1)) << ", " << score(mostProbable(team.at(0), 3, profile(t1)), t1) << endl;
    cout << candidate(t1) << ", " << score(candidate(t1), t1) << endl;*/
    //cout << score("TCGGGGATTTCC", split(w, 10)) << endl;;
    vector<string> trees = greedySearch(s, 12, 25);
    for (vector<string>::iterator iter = trees.begin(); iter != trees.end(); iter++) {
        cout << *iter << endl;
    }
    return 0;
}
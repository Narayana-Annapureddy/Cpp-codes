#include<bits/stdc++.h>
using namespace std;

string findMostFrequentCode(const string& input) {

    unordered_map<string, int> wordCounts;
    string word, mostFrequentCode;
    int maxCount = 0;
    
    for (int i=0; i<input.size(); i++) {

        if (input[i] == ' ' || i == input.size()-1) {
            wordCounts[word]++;
            if (maxCount < wordCounts[word]) {
                mostFrequentCode = word;
                maxCount = wordCounts[word];
            }
            word.clear();
        }
        word.push_back(input[i]);
    }
    
    return mostFrequentCode;
}

int main() {

    string input;
    getline(cin,input);

    string mostFrequentCode = findMostFrequentCode(input);
    std::cout << "Most frequent code: " << mostFrequentCode << std::endl;
    
    return 0;
}

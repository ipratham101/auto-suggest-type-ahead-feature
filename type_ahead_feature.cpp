#include<bits/stdc++.h>
using namespace std;
#define ALPHABET_SIZE 26
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isWordEnd;
};

TrieNode* getNode() {
    TrieNode* pNode = new TrieNode;
    pNode->isWordEnd = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

void insert(TrieNode* root, const string key) {
    TrieNode* pCrawl = root;
    for (int level = 0; level < key.length(); level++) {
        int index = key[level] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
}

bool isLastNode(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

void suggestionsRec(TrieNode* root, string currPrefix) {
    if (root->isWordEnd){
        // cout<<"yo"<<endl;
        reverse(currPrefix.begin(), currPrefix.end());
        cout << currPrefix<<" ";
    
        
    }
    if (isLastNode(root))
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char child = 'a' + i;
            suggestionsRec(root->children[i], currPrefix + child);
        }
    }
}

int printAutoSuggestions(TrieNode* root, const string query) {
    TrieNode* pCrawl = root;
    for (char c : query) {
        int ind = c - 'a';
        if (!pCrawl->children[ind])
            return 0;
        pCrawl = pCrawl->children[ind];
    }
    if (isLastNode(pCrawl)) {
        
        cout << query << endl;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}

int main() {
    cout<<"Enter size of input1: ";
    int n;
    cin >> n;
    cout << "Enter input1: ";
    vector<string> vec;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vec.push_back(s);
    }
    cout << "Enter input2: ";
    string s2;
    cin >> s2;
    string temp;
if(s2[0] == '*'){
    for(int i=1; i<s2.size(); i++){
        temp.push_back(s2[i]);
    }
    s2 = temp;
}

    TrieNode* root = getNode();
    for (int i = 0; i < n; i++) {
        string s = vec[i];
        reverse(s.begin(), s.end());
        insert(root, s);
    }
    reverse(s2.begin(), s2.end());
    cout<<"Output: ";
    int comp = printAutoSuggestions(root, s2);
    if (comp == -1)
        cout << "No matching found for this input\n";
    else if (comp == 0)
        cout << "No matching found for this input\n";
    return 0;
}

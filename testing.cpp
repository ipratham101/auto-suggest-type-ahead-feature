#include<pch.h>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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

void suggestionsRec(TrieNode* root, string currPrefix, vector<string>& result) {
    if (root->isWordEnd) {
        reverse(currPrefix.begin(), currPrefix.end());
        result.push_back(currPrefix);
    }
    if (isLastNode(root))
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char child = 'a' + i;
            suggestionsRec(root->children[i], currPrefix + child, result);
        }
    }
}

vector<string> printAutoSuggestions(TrieNode* root, const string query) {
    TrieNode* pCrawl = root;
    for (char c : query) {
        int ind = c - 'a';
        if (!pCrawl->children[ind])
            return {};
        pCrawl = pCrawl->children[ind];
    }
    vector<string> result;
    suggestionsRec(pCrawl, query, result);
    return result;
}

class TrieTest : public ::testing::Test {
protected:
    TrieNode* root;

    void SetUp() override {
        root = getNode();
        insert(root, "take");
        insert(root, "make");
        insert(root, "check");
        insert(root, "ack");
        insert(root, "rake");
    }

    void TearDown() override {
       
        deleteTrie(root);
    }

    void deleteTrie(TrieNode* root) {
        if (!root)
            return;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            deleteTrie(root->children[i]);
        delete root;
    }
};


TEST_F(TrieTest, BasicFunctionalityTest) {
 
    cout << "Enter size of input1: ";
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
    if (s2[0] == '*') {
        for (int i = 1; i < s2.size(); i++) {
            temp.push_back(s2[i]);
        }
        s2 = temp;
    }

   
    for (int i = 0; i < n; i++) {
        string s = vec[i];
        reverse(s.begin(), s.end());
        insert(root, s);
    }
    reverse(s2.begin(), s2.end());

    vector<string> result = printAutoSuggestions(root, s2);
    reverse(result.begin(), result.end());

    cout << "Output: ";
    for (const string& word : result)
        cout << word << " ";
    cout << endl;
}
TEST_F(TrieTest, NoMatchingSuggestionsTest) {
   
    cout << "Enter size of input1: ";
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

    vector<string> result = printAutoSuggestions(root, s2);

    cout << "Output: ";
    if (result.empty())
        cout << "No matching found for this input" << endl;
    else {
        for (const string& word : result)
            cout << word << " ";
        cout << endl;
    }
}

TEST_F(TrieTest, WildcardQueryTest) {
    cout << "Enter size of input1: ";
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
    if (s2[0] == '*') {
        for (int i = 1; i < s2.size(); i++) {
            temp.push_back(s2[i]);
        }
        s2 = temp;
    }

    for (int i = 0; i < n; i++) {
        string s = vec[i];
        reverse(s.begin(), s.end());
        insert(root, s);
    }
    reverse(s2.begin(), s2.end());

    vector<string> result = printAutoSuggestions(root, s2);
    reverse(result.begin(), result.end());

    cout << "Output: ";
    for (const string& word : result)
        cout << word << " ";
    cout << endl;
}

TEST_F(TrieTest, EmptyTrieTest) {
    TrieNode* emptyRoot = getNode(); 

    cout << "Enter input2: ";
    string s2;
    cin >> s2;

    vector<string> result = printAutoSuggestions(emptyRoot, s2);

    cout << "Output: ";
    if (result.empty())
        cout << "No matching found for this input" << endl;
    else {
        for (const string& word : result)
            cout << word << " ";
        cout << endl;
    }

    deleteTrie(emptyRoot); 
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

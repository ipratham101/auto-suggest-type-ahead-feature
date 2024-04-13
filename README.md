# Auto Suggest Type-Ahead Feature

## Overview
i used c++ to complete the assignment, using the TRIE data structure. Visual Studio was used to automate test cases using the gtest library.

## Approach
1. implemented a TRIE data structure to store a set of strings.
2. each node in the TRIE contains a character from the alphabet, with paths from the root to leaf nodes representing words.
3. reversed strings before inserting them into the TRIE.
4. after receiving input from the user, each input string was reversed.
5. built the TRIE in a manner that matches prefixes from the end of the input string.
6. utilized recursion to find all words matching the prefix.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <queue>

using namespace std;

class Dictionary
{
	private:
		static const int ALPHABET_SIZE = 26;

		struct Node
		{
			string word;
			string definition;
			Node* next[ALPHABET_SIZE];
		};
		
		typedef Node TrieNode;
		typedef TrieNode* Trie;
		
		Trie root;
		Trie reverse;;
		Trie lastAccessed;
		int creationIndex;
		queue<string> outDef;		
		queue<string> outWord;
		
	public:
		Dictionary();
		~Dictionary();
		Trie createTrie();
		bool insertTrie(string word, string definition);
		bool loadDictionary(string fileName);
		string lookup(string word);
		void deleteTrie(Trie traverse);
		void displayTrie();
		void printNode(Trie traverse);
		bool writeTrie(string fileName);
		void outTrie(Trie traverse);
};

#endif

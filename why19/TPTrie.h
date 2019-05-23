#ifndef TPTRIE_H_
#define TPTRIE_H_

#include "TPTrieNode.h"
#include <fstream>
#include <string>

class TPTrie {
public:
	TPTrie();
	
	TPTrieNode* TPTrie_head_get();
	TPTrieNode* TPTrie_insert(char*, TPNumber);
	bool TPTrie_delete(char*);
	TPTrieNode* TPTrie_find(char*, TPTrie*);
	bool TPTrie_emptyq();
	
	bool TPTrie_save(std::ofstream*, TPTrieNode*);
	bool TPTrie_load(std::ifstream*, char*);
	//void TPTrie_print(); i don't really need to print out a tree
	
	virtual ~TPTrie();
	
private:
	TPTrieNode* head;
	int size; //for loading; the amount of nodes in a trie
	
	int TPTrie_bit_get(char*, int);
	int TPTrie_bit_firstdif(char*, char*);
	bool TPTrie_compare_word(char*, char*);
	
	void TPTrie_print_node(TPTrieNode* node, bool, int);
	
	void TPTrie_destruction(TPTrieNode* node);

};

#endif /* TPTRIE_H_ */

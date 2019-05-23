#ifndef TPTRIENODE_H_
#define TPTRIENODE_H_

#include <cstdlib>
#include <cstring>
#include <iostream>

const int MAX_SIZE = 257;
typedef unsigned long long int TPNumber;

class TPTrieNode {
public:
    TPTrieNode();
	TPTrieNode(char*, TPNumber, int);
	void TPTrieNode_init(char*, TPNumber, int);
	
	TPNumber TPTrieNode_get_number();
	
    virtual ~TPTrieNode();

private:
	int id; //it's height basically not really  
	
	char* word;
	TPNumber number;
	int difbit;
	TPTrieNode* link[2];
	
	friend class TPTrie;
};

#endif /* TPTRIENODE_H_ */

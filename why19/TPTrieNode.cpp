#include "TPTrieNode.h"

TPTrieNode::TPTrieNode() :
	id(0), word(nullptr), number(0), difbit(0) {
	
	link[0] = this;
	link[1] = this;
		
}

TPTrieNode::TPTrieNode(char* w, TPNumber num, int dfb) :
	id(0), word(w), number(num), difbit(dfb) {
		
	link[0] = this;
	link[1] = this;
}

void TPTrieNode::TPTrieNode_init(char* w, TPNumber num, int bch) {
	id = 0;
	
	if (w) {
        word = (char*)strdup(w);
    }
    else {
        word = w;
    }
	
	number = num;
	difbit = bch;
	
	link[0] = this;
	link[1] = this;
}

TPNumber TPTrieNode::TPTrieNode_get_number() {
	return this->number;
}

TPTrieNode::~TPTrieNode() {
	if (this->word != nullptr)
		free(this->word); //array type hence square brackets
}

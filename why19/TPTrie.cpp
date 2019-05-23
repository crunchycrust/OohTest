#include "TPTrieNode.h"
#include "TPTrie.h"

TPTrie::TPTrie() : size(0) {
	//head is full of zeroes and the check bit is -1 which is kind of 0 actually
	head = new TPTrieNode(nullptr, 0, -1);
}

TPTrie::~TPTrie() {	
	TPTrie_destruction(head);
}

void TPTrie::TPTrie_destruction(TPTrieNode* node) {
	if (node->link[0]->difbit > node->difbit)
		TPTrie_destruction(node->link[0]);
		
	if (node->link[1]->difbit > node->difbit)
		TPTrie_destruction(node->link[1]);
		
	delete node;
}

TPTrieNode* TPTrie::TPTrie_head_get() {
	return head;
}

bool TPTrie::TPTrie_emptyq() {
	//head's links are going back to head
	return (head->link[0] == head) && (head->link[1] == head);
}

int TPTrie::TPTrie_bit_get(char* word, int bit) { 
	if (bit < 0)
        bit = 0;
   
    int count = 7 - (bit & 7);

    
    return ((word[bit >> 3] >> count) & 1U);
}

bool TPTrie::TPTrie_compare_word (char* word_1, char* word_2) { 
	if (!word_1 || !word_2)
		return false;
	
	int same = strcmp(word_1, word_2);
    if (same == 0)
        return true;
    else
		return false;
}

int TPTrie::TPTrie_bit_firstdif(char* word_1, char* word_2) { 
       
	
	if ((!word_1) || (!word_2)) 
		return 0;
		
	int where = 0;
	
	size_t len_1 = std::strlen(word_1) * 8;
	size_t len_2 = std::strlen(word_2) * 8;
	
	size_t minlen = len_1 < len_2 ? len_1 : len_2;
	size_t maxlen = len_1 > len_2 ? len_1 : len_2;	
    //finding first different character
    while ((word_1[where] == word_2[where]) && where < minlen)
        where++;
    where *= 8;
    maxlen *= 8;
    while (TPTrie_bit_get(word_2, where) == TPTrie_bit_get(word_1, where) && where < maxlen)
        //finding first different bit
        where++;
    return where;
}

TPTrieNode* TPTrie::TPTrie_find(char* word_o, TPTrie* trie) {

    if (trie->TPTrie_emptyq())
        return nullptr;
	
    TPTrieNode* now = trie->head; //previous checked node (so it's PREFix)
    TPTrieNode* nxt = trie->head->link[0]; //currently checking node

    while (now->difbit < nxt->difbit) {
        now = nxt;
        nxt = now->link[TPTrie_bit_get(word_o, now->difbit)];
    }
    
    
    
    if (!TPTrie_compare_word(word_o, nxt->word))
        return nullptr;

    return nxt;
}

TPTrieNode* TPTrie::TPTrie_insert(char* word_o, TPNumber number) {
    TPTrieNode* now = head; 
    TPTrieNode* nxt = head->link[0]; 
    
    
    while (now->difbit < nxt->difbit) {
        now = nxt;
        nxt = now->link[TPTrie_bit_get(word_o, now->difbit)];
    }

    if (TPTrie_compare_word(word_o, nxt->word))
        return nullptr;

    int difbit_o = TPTrie_bit_firstdif(word_o, nxt->word);
    now = head;
    nxt = head->link[0];
    while ((now->difbit < nxt->difbit) && (nxt->difbit < difbit_o)) {
        now = nxt;
        nxt = now->link[TPTrie_bit_get(word_o, nxt->difbit)];
    }

    TPTrieNode* node_new = new TPTrieNode();
    node_new->TPTrieNode_init(word_o, number, difbit_o);
   
    int node_new_link = TPTrie_bit_get(word_o, difbit_o);
    
  
    now->link[TPTrie_bit_get(word_o, now->difbit)] = node_new;
    node_new->link[node_new_link] = node_new;
    node_new->link[1 - node_new_link] = nxt;
    
    this->size++;
    
    return node_new;
}

bool TPTrie::TPTrie_delete(char* k) {
	
	
    TPTrieNode *grandParent = nullptr; //grand parent  lies before parent
    //SEARCH START
    TPTrieNode *parent = head; 
    TPTrieNode *del = head->link[0]; 
	
    while (parent->difbit < del->difbit) {
        grandParent = parent;
        parent = del;
        del = del->link[TPTrie_bit_get(k, del->difbit)];
    }
	
    if (!TPTrie_compare_word(k, del->word))
        return false;    //no such key in trie
	//SEARCH FINISH
	if (del != parent) {
		
		if (parent->word == nullptr)
        del->word = nullptr;

		else {
			
			del->number = parent->number; 
       

			if (std::strlen(del->word) < std::strlen(parent->word)) {
				del->word = (char*)realloc(del->word, 1 + strlen(parent->word));
			}
    
			std::strcpy(del->word, parent->word);

			del->number = parent->number;
    
		}
    }
        //so now deleting 'parent' !!! p - parent; q - del


    if (((parent->link[0]->difbit) > (parent->difbit))
            || (parent->link[1]->difbit > parent->difbit)) { //if there is a link to another node

       
        if (parent != del) { //if r is deeper than first child
			// SEARCH R START
			//r has a backward pointer to p? yeah?...
            TPTrieNode* parentOfParent = parent; // r in the end
            TPTrieNode* tmp = parent->link[TPTrie_bit_get(parent->word,
                    parent->difbit)]; // our initial parent in the end 
            char* key = parent->word;
          
            while (parentOfParent->difbit < tmp->difbit) {
                parentOfParent = tmp;
                tmp = parentOfParent->link[TPTrie_bit_get(key, parentOfParent->difbit)];
            }
			
            if (!TPTrie_compare_word(key, tmp->word)) {
                std::cout
                        << "ERROR: logical error while deleting";
                std::cout << std::endl;
                return false;
            } //if it's suddenly pointing somewhere else well balls
			//SEARCH R FINISH
            parentOfParent->link[TPTrie_bit_get(key, parentOfParent->difbit)] = del;

        }

        if (grandParent != parent)
			
            grandParent->link[TPTrie_bit_get(k, grandParent->difbit)] = parent->link[1
                    - TPTrie_bit_get(k, parent->difbit)];

    } else {// there is AT LEAST ONE selfpointer
		
        if (grandParent != parent) {//all is well
			
            if (parent->link[0] == parent) {//there is a selfpointer in 0
              
                grandParent->link[TPTrie_bit_get(k, grandParent->difbit)] =
                           parent->link[1]; //}
			} 
			else //there is a selfpointer in 1
				
				grandParent->link[TPTrie_bit_get(k, grandParent->difbit)] =
                        parent->link[0];
            }
    }
    this->size--;
    
    delete parent;
    return true;
	
}

bool TPTrie::TPTrie_save(std::ofstream* file, TPTrieNode* root) {
    
    int length = 0;
    
   
    
    if(head->link[0] == head) {
        return true;
    }
    if (root->word == nullptr)
		length =  0;
	else
		length = strlen(root->word);
   
    
    file->write((char*)&length, sizeof(int));
    file->write(root->word, sizeof(char)*length);
    file->write((char*)&root->number, sizeof(TPNumber));
    
    if (root->difbit < root->link[1]->difbit ) {
        if(!TPTrie_save(file, root->link[1]))
            return false;
        
    }

    if ( root->difbit < root->link[0]->difbit ) {
        if(!TPTrie_save(file, root->link[0])) 
            return false;
        
    }
    
    return true;
}

bool TPTrie::TPTrie_load(std::ifstream* file, char* word) {
    
    if (!TPTrie_emptyq()) {
		TPTrie_destruction(head->link[0]);
		head->link[0] = head;
		
	}
    TPNumber number = 0;
    int length = 0;
    
    while(!file->eof()) {
        file->read((char*)&length,sizeof(int));
        file->read(word, length*sizeof(char));
        word[length] = '\0';
        file->read((char*)&number,sizeof(TPNumber));
        
        TPTrie_insert(word, number);
    }
    
    return true;
    
}

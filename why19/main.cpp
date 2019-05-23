#include <fstream>
#include <iostream>
#include <cstring>
#include "TPTrie.h"

void Lowercase(char *str) {
    int len = std::strlen(str);
    for (int i = 0; i < len; ++i)
        str[i] = std::tolower(str[i]);
}

int main(int argc, char** argv) {
    //files
    std::ofstream fout;
    std::ifstream fin;

    char word[MAX_SIZE];
    TPNumber number;
    
    //int i = 0;

    TPTrie* trie = new TPTrie();
    TPTrieNode* node;
    std::string c;
	std::cin.clear();
	std::cin.sync();    
	
    while (std::cin >> c) {
        //error during input
        if (!std::cin) {
            std::cout << "ERROR: options could not be read " << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        //add word
        if (c == "+") {

            std::cin >> word ;
            
            if (std::strlen(word) > MAX_SIZE) {
				std::cout << "ERROR: word is too long" << std::endl;
				std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
			}
	
			if (!(std::cin >> number)) {
				std::cout << "ERROR: Incorrect number" << std::endl;
				continue;
			}
			
			
			if (!std::cin) {
                std::cout << "ERROR: word/number could not be read" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
            Lowercase(word);
            std::cout << (trie->TPTrie_insert(word, number) ? "OK" : "Exist");
            std::cout << std::endl;

        }
        
        else if (c == "-") {

            std::cin >> word;
            std::cin.ignore(100,'\n');
            
            if (!std::cin) {
                std::cout << "ERROR: word could not be read" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
            
         
            Lowercase(word);
            
            
            std::cout << (trie->TPTrie_delete(word) ? "OK" : "NoSuchWord");
            std::cout << std::endl;

        }
		
		else if (c == "!") {
			std::cin >> word;
            if (!std::strcmp(word, "Save")) {
                std::cin >> word;
                 if (!std::cin) {
					std::cout << "ERROR: word could not be read" << std::endl;
					std::cin.clear();
					std::cin.ignore();
					continue;
				}
				std::ofstream file(word, std::ofstream::binary);
                if(!file) {
					std::cout << "ERROR: can't open file!" << std::endl;
					continue;
					
				}
				
				std::cout << (trie->TPTrie_save(&file, trie->TPTrie_head_get()) ? "OK" : "ERROR: could not save" );
				std::cout << std::endl;
				
				file.close();

            } else if(!strcmp("Load", word)) {
				std::cin >> word;
				 if (!std::cin) {
					std::cout << "ERROR: word could not be read" << std::endl;
					std::cin.clear();
					std::cin.ignore();
					continue;
				}
				if(std::cin.eof()) {
					std::cout << "ERROR: EOF recieved!" << std::endl;
					continue;
					
				}
				std::ifstream file(word, std::ofstream::binary);
				if(!file) {
					std::cout << "ERROR: can't open file!" << std::endl;
					continue;
					
				}
				
				std::cout << (trie->TPTrie_load( &file, word) ? "OK" : "ERROR: could not load");
				std::cout << std::endl;
				file.close();
			}
            else {
                std::cout << "ERROR: input option can not be read" << std::endl;
                continue;
            }
            
            
			
		}
		
		else {
			strcpy(word, c.c_str()); 
			Lowercase(word);
            node = trie->TPTrie_find(word, trie);
            if (!node)
                std::cout << "NoSuchWord";
            else
                std::cout << "OK: " << node->TPTrieNode_get_number();
            std::cout << std::endl;
			
		}
   
    }
    delete trie;
    return 0;
}


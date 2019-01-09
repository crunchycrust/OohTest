#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>
#include <string>

#include "Hexagon.h"
#include "TNTreeItem.h"

class TNTree {
public:
    TNTree(); //Default constructor. Our tree is alive
    TNTree(const TNTree& orig); //Overload constructor !!treeobject is the parameter
	//Mutator functions
    void Insert(TNTree* tree, std::string parent_id, std::string id, Hexagon &hexagon); //inserto hexagoniO
    void Remove(std::string id); //remove via id
    void node_remove(TNTreeItem* TNTree, std::string id); //remove an item via id
    void PrintTree(TNTreeItem* treeit, size_t num); //print le tree
    void PrintItem(TNTree* tree, std::string id); //print itemu 
    void SetNull(TNTreeItem* t); //set our treeto to nullptr
    
	TNTreeItem* getHead(); //pointer to the head of our tree
    bool IsEmpty(); //is it empty?? ooo, mistery

    virtual ~TNTree(); //Destructor

private:
	//Member variables
    TNTreeItem* head; 
    TNTreeItem* FindNode(TNTreeItem* node, std::string id);
};
#endif /* TNTREE_H */

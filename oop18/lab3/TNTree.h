#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>
#include <string>
#include <memory>

#include "TNTreeItem.h"
#include "Triangle.h"
#include "Hexagon.h"
#include "Octagon.h"

class TNTree {
public:
    TNTree(); //Default constructor. Our tree is alive
    TNTree(const TNTree& orig); //Overload constructor !!treeobject is the parameter
	
	friend std::ostream &operator<<(std::ostream os, const TNTree &tree);
	//Mutator functions
    void Insert(std::string parent_id, std::string id, std::shared_ptr<Figure> &figure); //inserto figureiO
    void Remove(std::string id); //remove via id
    //void node_remove(TNTreeItem* TNTree, std::string id); //remove an item via id
    void PrintTree(); //print le tree
    void PrintItem(std::string id); //print itemu 
    void SetNull(std::shared_ptr<TNTreeItem> treeItem); //set our treeto to nullptr
    void Des(); //ass
    
	std::shared_ptr<TNTreeItem> getHead(); //Accessor funciton
	bool IsEmpty(); //is it empty?? ooo, mistery

    virtual ~TNTree(); //Destructor

private:
	//Member variables
    std::shared_ptr<TNTreeItem> head; 
    std::shared_ptr<TNTreeItem> FindNode(std::shared_ptr<TNTreeItem> node, std::string id);
	void print_nodes(std::shared_ptr<TNTreeItem> treeItem, size_t num);
	void node_remove(std::shared_ptr<TNTreeItem> treeItem, std::string id);
};
#endif /* TNTREE_H */

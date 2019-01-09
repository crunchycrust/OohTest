#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>
#include <string>
#include <memory>
#include <future>
#include <mutex>
#include <thread>
#include <functional>

#include "TNTreeItem.h"
#include "TIterator.h"

#include "Triangle.h"
#include "Hexagon.h"
#include "Octagon.h"

template <class T>
class TNTree {
public:
    TNTree(); //Default constructor. Our tree is alive
    TNTree(const TNTree<T>& orig); //Overload constructor !!treeobject is the parameter
	
	//	friend std::ostream &operator<<(std::ostream os, const TNTree &tree);
	//Mutator functions
    void Insert(std::string parent_id, std::string id, std::shared_ptr<T> &figure); //inserto figureiO
    void Remove(std::string id); //remove via id
    //void node_remove(TNTreeItem* TNTree, std::string id); //remove an item via id
    void PrintTree() const; //print le tree
    void PrintTreeVal() const; //print le tree
    void PrintItem(std::string id); //print itemu 
    void RemS(double Sq);
    void SetNull(std::shared_ptr<TNTreeItem<T>> treeItem); //set our treeto to nullptr
    void Des(); //ass
    
	std::shared_ptr<TNTreeItem<T>> getHead(); //Accessor funciton
	bool IsEmpty() const; //is it empty?? ooo, mistery

	TIterator<TNTreeItem<T>, T> begin();
	TIterator<TNTreeItem<T>, T> end();

    virtual ~TNTree() {}; //Destructor

private:
	//Member variables
	std::mutex mutex;
	
    std::shared_ptr<TNTreeItem<T>> head; 
    std::shared_ptr<TNTreeItem<T>> FindNode(std::shared_ptr<TNTreeItem<T>> node, std::string id);
	void print_nodes(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num) const;
	void print_nodesval(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num) const;
	void node_remove(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id);
	void remS_node(std::shared_ptr<TNTreeItem<T>>, double Sq);
};
#endif /* TNTREE_H */

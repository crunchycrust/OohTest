#ifndef TTREE_H
#define TTREE_H

#include <iostream>
#include <memory>

#include "Figure.h"

template <class Q, class O> class TTree {
private:
	class Node {
	public:
		Q data;
		std::shared_ptr<Node> son;
		std::shared_ptr<Node> sibling;
		Node();
		Node(const O&);
		int itemsInNode;
	};

	std::shared_ptr<Node> root;

	void RemByType(std::shared_ptr<Node>&, const int&);
	void Insert(std::shared_ptr<Node>&, const O&);
	void Inorder(const std::shared_ptr<Node>&);
	void InorderP(const std::shared_ptr<Node>&);
	void RemLesser(std::shared_ptr<Node>&, const double&);
public:
	TTree();

	void insert(const O&);
	void inorder(); 
	void inorderp();
	void removeByType(const int&);
	void removeLesser(const double&);
  
	bool IsEmpty() const;
	void Des();
};

#include "TTree.hpp"
#endif

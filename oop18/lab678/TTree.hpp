#ifdef TQUEUE_H

template class TTree<TQueue<Figure>, std::shared_ptr<Figure>>;

template <class Q, class O> TTree<Q, O>::TTree() {
	root = std::make_shared<Node>(Node());
	root->son = std::make_shared<Node>(Node());
}

template <class Q, class O> TTree<Q, O>::Node::Node() {
	son = sibling = nullptr;
	itemsInNode = 0;
}

template <class Q, class O> TTree<Q, O>::Node::Node(const O& item) {
	data.Push(item);
	itemsInNode = 1;
}

template <class Q, class O> 
bool TTree<Q, O>::IsEmpty() const {
    return root == nullptr;
}

template <class Q, class O> 
void TTree<Q, O>::Des() {
	root = nullptr;
	root = std::make_shared<Node>(Node());
	root->son = std::make_shared<Node>(Node());
}

template <class Q, class O> 
void TTree<Q, O>::insert(const O& item) {
		Insert(root->son, item);
}

template <class Q, class O> 
void TTree<Q, O>::inorder() {
	Inorder(root->son);
}

template <class Q, class O> 
void TTree<Q, O>::inorderp() {
	InorderP(root->son);
}

template <class Q, class O> 
void TTree<Q, O>::removeByType(const int& type) {
	RemByType(root->son, type);
}

template <class Q, class O> 
void TTree<Q, O>::removeLesser(const double& sqr) {
	RemLesser(root->son, sqr);
}



template <class Q, class O> 
void TTree<Q, O>::Insert(std::shared_ptr<Node>& node, const O& item) {
	if (node->itemsInNode < 5) {
		node->data.Push(item);
		node->itemsInNode++;
	} 
	else {
		auto sibl = node;
    
		for (int i = 0; i < 3; i++) {
			if (!sibl->sibling) {
			sibl->sibling = std::make_shared<Node>(Node(item));
			printf("HELPME \n");
			return;
			}
    
			if (sibl->sibling->itemsInNode < 5) {
				Insert(sibl->sibling, item);
				return;
			}

			sibl = sibl->sibling;
		}
		printf("HELL\n");
		if (node->son) {
			Insert(node->son, item);
		} 
		else {
			node->son = std::make_shared<Node>(Node(item));
		}
	}	
}

template <class Q, class O> 
void TTree<Q, O>::Inorder(const std::shared_ptr<Node>& node) {
	if (node->itemsInNode) {
		node->data.sort();
		for (const auto& i: node->data) {
			i->Print();
		}
		printf("\n");
		if (node->sibling) {
			Inorder(node->sibling);
		}
		if (node->son) {
			Inorder(node->son);
		}
		
	}
}

template <class Q, class O> 
void TTree<Q, O>::InorderP(const std::shared_ptr<Node>& node) {
	if (node->itemsInNode) {
		node->data.sort_par();
		for (const auto& i: node->data) {
			i->Print();
		}
		printf("\n");
		if (node->sibling) {
			InorderP(node->sibling);
		}
		if (node->son) {
			InorderP(node->son);
		}
		
	}
}


template <class Q, class O> 
void TTree<Q, O>::RemByType(std::shared_ptr<Node>& node, const int& type) {
	if (node->itemsInNode) {

		for (int i = 0; i < 5; i++) {
			auto iter = node->data.begin();
      
			for (int k = 0; k < node->data.GetLength(); k++) {
				if (iter->type() == type) {
					node->data.Pop(k + 1);
					node->itemsInNode--;
					break;
				}
				++iter;
			}
		}
    
		if (node->sibling) {
			RemByType(node->sibling, type);
		}
		if (node->son) {
			RemByType(node->son, type);
		}

	}
}

template <class Q, class O> 
void TTree<Q, O>::RemLesser(std::shared_ptr<Node>& node, const double& sqr) {
	if (node->itemsInNode) {
		for (int i = 0; i < 5; i++) {
			auto iter = node->data.begin();
      
			for (int k = 0; k < node->data.GetLength(); k++) {
				if (iter->Square() < sqr) {
					node->data.Pop(k + 1);
					node->itemsInNode--;
					break;
				}
				++iter;
			}
		}
    
		if (node->sibling) {
			RemLesser(node->sibling, sqr);
		}
		if (node->son) {
			RemLesser(node->son, sqr);
		}

	}
}

#endif

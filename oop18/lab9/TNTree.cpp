#include <string>
#include <memory>

#include "TNTree.h"
#include "TNTreeItem.h"

template class TNTree<Figure>;

template <class T>
TNTree<T>::TNTree() { //our tree is alive and well
    head = nullptr;
}

template <class T>
TNTree<T>::TNTree(const TNTree<T>& orig) { //head = head of our trreee
    head = orig.head;
}
//done
template <class T>
void TNTree<T>::Insert(std::string parent_id, std::string id, std::shared_ptr<T> &figure) {
    if (!this->head) { //no item in head basically
        this->head = std::make_shared<TNTreeItem<T>>(id, figure); //in TNTreeItem.h
        return;
    }
    else { //oh my there is some stuff here
        std::shared_ptr<TNTreeItem<T>> parent_node = FindNode(this->head, parent_id); //so we look for a parent of where to put it
        if (parent_node) { //if there is an id for a parent
            if (!parent_node->GetSon()) { //if there is no son
                parent_node->SetSon(std::make_shared<TNTreeItem<T>>(id, figure)); //make a new one
            }
            else { //if there is a son
                std::shared_ptr<TNTreeItem<T>> brother = parent_node->GetSon();
                while (brother->Next()) {
                    brother = brother->Next(); //used to be GetBrother
                } //make bro
                brother->SetBrother(std::make_shared<TNTreeItem<T>>(id, figure));
            }
        }
        else { //if there is no parent_id found
            std::cout << "Error: invaild parent_id" << '\n';
        }
    }
}
//done
template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::FindNode(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { //find a pointer to our item
    if (treeItem->getId() == id) { //if our item has id we our looking for
        return treeItem;
    }
    if (treeItem->GetSon()) { //if our item has a son
        std::shared_ptr<TNTreeItem<T>>tr = FindNode(treeItem->GetSon(), id); //let's take a look at his son as an item
        if (tr != nullptr) { //success hence tr is what we are looking for
            return tr;
        }
    }
    if (treeItem->Next()) { //same as with son, but going through brothers
        std::shared_ptr<TNTreeItem<T>> tr = FindNode(treeItem->Next(), id);
        if (tr != nullptr) {
            return tr;
        }
    }
    return nullptr;
}

template <class T>
void TNTree<T>::SetNull(std::shared_ptr<TNTreeItem<T>> t) {//pointer to an item is nullptr
    t = nullptr;
}

template <class T>
bool TNTree<T>::IsEmpty() const { //empty treetio has a head of nullptr
    return head == nullptr;
}

template <class T>
void TNTree<T>::Des() {
	head = nullptr;
}
//doneso
template <class T>
void TNTree<T>::node_remove(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { //let's deletio our node
    if (treeItem->GetSon()) { //if there are sons we have to delete them as well
        if (treeItem->GetSon()->getId() == id) { //id of the son is the id we are looking for
            std::shared_ptr<TNTreeItem<T>> tr = treeItem->GetSon();
            treeItem->SetSon(treeItem->GetSon()->Next()); //use to be GetBrother() getting rid of the brothers
            SetNull(tr->Next());// = nullptr;
			//delete tr ! nope, cause shared_ptr
            return;
        }
        else {
			TNTree<T>::node_remove(treeItem->GetSon(), id);
        }
    }
    if (treeItem->GetBrother()) {
        if (treeItem->GetBrother()->getId() == id) {
            std::shared_ptr<TNTreeItem<T>> tr = treeItem->Next();
            treeItem->SetBrother(treeItem->Next()->Next());
            SetNull(tr->Next());// = nullptr;
            //delete tr; hohoho you know what i mean nudgenudge winkwink
            return;
        }
        else {
            TNTree<T>::node_remove(treeItem->Next(), id); //get bro!!!
        }
    }
}

template <class T>
void TNTree<T>::RemS(double Sq){ 
    if (this->head != nullptr) {
		remS_node(this->head, Sq);
	}
}

template <class T>
void TNTree<T>::remS_node(std::shared_ptr<TNTreeItem<T>> treeItem, double Sq) {
	if (treeItem) {
		if (treeItem->GetFigure()->Square() > Sq) {
			std::string ido = treeItem->getId();
			
			//std::cout << ido <<std::endl;
			Remove(ido);
			
		}
		if (treeItem->GetSon()) {
			remS_node(treeItem->GetSon(), Sq);
		}
		if (treeItem->Next()) {
			remS_node(treeItem->Next(), Sq);
		}
    }
}


template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::getHead() {//get pointer to a head of a tree
    return this->head;
}

template <class T>
void TNTree<T>::Remove(std::string id) { //remove by id
    if (head->getId() == id) {
        TNTree<T>::Des();
    } else {
        TNTree<T>::node_remove(head, id);
   }
}
//okok we are printing it through nodes this time 
template <class T>
void TNTree<T>::PrintTree() const{ 
    if (this->head != nullptr) {
		print_nodes(this->head, 0);
	}
}

template <class T>
void TNTree<T>::PrintTreeVal() const{ 
    if (this->head != nullptr) {
		print_nodesval(this->head, 0);
	}
}
//done
template <class T>
void TNTree<T>::print_nodes(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num) const {
	if (treeItem) {
        for (int i = 0; i < num; ++i) {
            printf("   ");
        }
        std::cout << treeItem->getId()<< '\n';
        if (treeItem->GetSon()) {
            print_nodes(treeItem->GetSon(), num + 1);
        }
        if (treeItem->Next()) {
            print_nodes(treeItem->Next(), num);
        }
    }	
}

template <class T>
void TNTree<T>::print_nodesval(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num) const {
	if (treeItem) {
        for (int i = 0; i < num; ++i) {
            printf("   ");
        }
        treeItem->GetFigure()->Print();
        if (treeItem->GetSon()) {
            print_nodesval(treeItem->GetSon(), num + 1);
        }
        if (treeItem->Next()) {
            print_nodesval(treeItem->Next(), num);
        }
    }	
}

template <class T>
void TNTree<T>::PrintItem(std::string id) {//let's print our item
    std::shared_ptr<TNTreeItem<T>> tmp = FindNode(this->head, id); //getting our pointer
    if(tmp) { //if there is a pointer
        tmp->GetFigure()->Print(); //print our fig
    }
    //delete tmp; ohh boii shared_ptr
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::begin() {
	if (head) { //if there is a head
		return TIterator<TNTreeItem<T>, T>(head);
	}
	else {
		return TIterator<TNTreeItem<T>, T>(nullptr);
	}	
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::end() {
	return TIterator<TNTreeItem<T>, T>(nullptr);	
}

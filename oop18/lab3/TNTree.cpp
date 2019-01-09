#include <string>

#include "TNTree.h"
#include "TNTreeItem.h"

TNTree::TNTree() { //our tree is alive and well
    head = nullptr;
}

TNTree::TNTree(const TNTree& orig) { //head = head of our trreee
    head = orig.head;
}
//done
void TNTree::Insert(std::string parent_id, std::string id, std::shared_ptr<Figure> &figure) {
    if (!this->head) { //no item in head basically
        this->head = std::make_shared<TNTreeItem>(id, figure); //in TNTreeItem.h
        return;
    }
    else { //oh my there is some stuff here
        std::shared_ptr<TNTreeItem> parent_node = FindNode(this->head, parent_id); //so we look for a parent of where to put it
        if (parent_node) { //if there is an id for a parent
            if (!parent_node->GetSon()) { //if there is no son
                parent_node->SetSon(std::make_shared<TNTreeItem>(id, figure)); //make a new one
            }
            else { //if there is a son
                std::shared_ptr<TNTreeItem> brother = parent_node->GetSon();
                while (brother->GetBrother()) {
                    brother = brother->GetBrother();
                } //make bro
                brother->SetBrother(std::make_shared<TNTreeItem>(id, figure));
            }
        }
        else { //if there is no parent_id found
            std::cout << "Error: invaild parent_id" << '\n';
        }
    }
}
//done
std::shared_ptr<TNTreeItem> TNTree::FindNode(std::shared_ptr<TNTreeItem> treeItem, std::string id) { //find a pointer to our item
    if (treeItem->getId() == id) { //if our item has id we our looking for
        return treeItem;
    }
    if (treeItem->GetSon()) { //if our item has a son
        std::shared_ptr<TNTreeItem>tr = FindNode(treeItem->GetSon(), id); //let's take a look at his son as an item
        if (tr != nullptr) { //success hence tr is what we are looking for
            return tr;
        }
    }
    if (treeItem->GetBrother()) { //same as with son, but going through brothers
        std::shared_ptr<TNTreeItem> tr = FindNode(treeItem->GetBrother(), id);
        if (tr != nullptr) {
            return tr;
        }
    }
    return nullptr;
}

bool TNTree::IsEmpty() { //empty treetio has a head of nullptr
    return head == nullptr;
}

void TNTree::Des() {
	head = nullptr;
}
//doneso
void TNTree::node_remove(std::shared_ptr<TNTreeItem> treeItem, std::string id) { //let's deletio our node
    if (treeItem->GetSon()) { //if there are sons we have to delete them as well
        if (treeItem->GetSon()->getId() == id) { //id of the son is the id we are looking for
            std::shared_ptr<TNTreeItem> tr = treeItem->GetSon();
            treeItem->SetSon(treeItem->GetSon()->GetBrother()); //getting rid of the brothers
            SetNull(tr->GetBrother());// = nullptr;
			//delete tr ! nope, cause shared_ptr
            return;
        }
        else {
            //delete treeItem; nope shared_ptr
        }
    }
    if (treeItem->GetBrother()) {
        if (treeItem->GetBrother()->getId() == id) {
            std::shared_ptr<TNTreeItem> tr = treeItem->GetBrother();
            treeItem->SetBrother(treeItem->GetBrother()->GetBrother());
            SetNull(tr->GetBrother());// = nullptr;
            //delete tr; hohoho you know what i mean nudgenudge winkwink
            return;
        }
        else {
            //delete treeItem; ooh yesss
        }
    }
}

void TNTree::SetNull(std::shared_ptr<TNTreeItem> t) {//pointer to an item is nullptr
    t = nullptr;
}

std::shared_ptr<TNTreeItem> TNTree::getHead() {//get pointer to a head of a tree
    return this->head;
}

void TNTree::Remove(std::string id) { //remove by id
    if (head->getId() == id) {
        TNTree::node_remove(head, id);
    } else {
        TNTree::node_remove(head, id);
   }
}
//okok we are printing it through nodes this time 
void TNTree::PrintTree() { 
    if (this->head != nullptr) {
		print_nodes(this->head, 0);
	}
}
//done
void TNTree::print_nodes(std::shared_ptr<TNTreeItem> treeItem, size_t num) {
	if (treeItem) {
        for (int i = 0; i < num; ++i) {
            printf("   ");
        }
        std::cout << treeItem->getId()<< '\n';
        if (treeItem->GetSon()) {
            print_nodes(treeItem->GetSon(), num + 1);
        }
        if (treeItem->GetBrother()) {
            print_nodes(treeItem->GetBrother(), num);
        }
    }	
}
void TNTree::PrintItem(std::string id) {//let's print our item
    std::shared_ptr<TNTreeItem> tmp = FindNode(this->head, id); //getting our pointer
    if(tmp) { //if there is a pointer
        tmp->GetFigure()->Print(); //print our fig
    }
    //delete tmp; ohh boii shared_ptr
}

TNTree::~TNTree() { //delete the tree = delete the head
    //delete head; OH GOD
}

#include <string>

#include "TNTree.h"
#include "TNTreeItem.h"

TNTree::TNTree() { //our tree is alive and well
    head = nullptr;
}

TNTree::TNTree(const TNTree& orig) { //head = head of our trreee
    head = orig.head;
}

void TNTree::Insert(TNTree* tree, std::string parent_id, std::string id, Hexagon &hexagon) {
    if (!tree->head) { //no item in head basically
        tree->head = new TNTreeItem(id, hexagon); //overload constructor in TNTreeItem.h
        return;
    }
    else { //oh my there is some stuff here
        TNTreeItem *parent_node = FindNode(tree->head, parent_id); //so we look for a parent of where to put it
        if (parent_node) { //if there is an id for a parent
            if (!parent_node->GetSon()) { //if there is no son
                parent_node->SetSon(new TNTreeItem(id, hexagon)); //make a new one
            }
            else { //if there is a son
                TNTreeItem *brother = parent_node->GetSon();
                while (brother->GetBrother()) {
                    brother = brother->GetBrother();
                } //make bro
                brother->SetBrother(new TNTreeItem(id, hexagon));
            }
        }
        else { //if there is no parent_id found
            std::cout << "Error: invaild parent_id" << '\n';
        }
    }
}

TNTreeItem* TNTree::FindNode(TNTreeItem* treeItem, std::string id) { //find a pointer to our item
    if (treeItem->getId() == id) { //if our item has id we our looking for
        return treeItem;
    }
    if (treeItem->GetSon()) { //if our item has a son
        TNTreeItem* tr = FindNode(treeItem->GetSon(), id); //let's take a look at his son as an item
        if (tr != nullptr) { //success hence tr is what we are looking for
            return tr;
        }
    }
    if (treeItem->GetBrother()) { //same as with son, but going through brothers
        TNTreeItem* tr = FindNode(treeItem->GetBrother(), id);
        if (tr != nullptr) {
            return tr;
        }
    }
    return nullptr;
}

bool TNTree::IsEmpty() { //empty treetio has a head of nullptr
    return head == nullptr;
}

void TNTree::node_remove(TNTreeItem* treeItem, std::string id) { //let's deletio our node
    if (treeItem->GetSon()) { //if there are sons we have to delete them as well
        if (treeItem->GetSon()->getId() == id) { //id of the son is the id we are looking for
            TNTreeItem *tr = treeItem->GetSon();
            treeItem->SetSon(treeItem->GetSon()->GetBrother()); //getting rid of the brothers
            SetNull(tr->GetBrother());// = nullptr;
            delete tr;
            return;
        }
        else {
            delete treeItem;
        }
    }
    if (treeItem->GetBrother()) {
        if (treeItem->GetBrother()->getId() == id) {
            TNTreeItem *tr = treeItem->GetBrother();
            treeItem->SetBrother(treeItem->GetBrother()->GetBrother());
            SetNull(tr->GetBrother());// = nullptr;
            delete tr;
            return;
        }
        else {
            delete treeItem;
        }
    }
}

void TNTree::SetNull(TNTreeItem* t) {//pointer to an item is nullptr
    t = nullptr;
}

TNTreeItem* TNTree::getHead() {//get pointer to a head of a tree
    return this->head;
}

void TNTree::Remove(std::string id) { //remove by id
    if (head->getId() == id) {
        head = head->GetSon();
    } else {
        TNTree::node_remove(head, id);
   }
}

void TNTree::PrintTree(TNTreeItem* treeItem, size_t num) { //let's print our tree
    if (treeItem) { //if there is a treeo
        for (int i = 0; i < num; ++i) { //beauty
            printf("   ");
        }
        std::cout << treeItem->getId()<< '\n'; //get id, print id
        if (treeItem->GetSon()) { // if there is son - go get the son
            PrintTree(treeItem->GetSon(), num + 1);
        }
        if (treeItem->GetBrother()) { //if there is bro - go get bro
            PrintTree(treeItem->GetBrother(), num);
        }
    }
}

void TNTree::PrintItem(TNTree* tree, std::string id) {//let's print our item
    TNTreeItem* tmp = FindNode(tree->head, id); //getting our pointer
    if(tmp) { //if there is a pointer
        tmp->GetHexagon().Print(); //print our hexagonion
    }
    delete tmp;
}


TNTree::~TNTree() { //delete the tree = delete the head
    delete head;
}

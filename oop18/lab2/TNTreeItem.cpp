#include <iostream>
#include <string>

#include "TNTreeItem.h"
#include "Hexagon.h"
//let's create an item
TNTreeItem::TNTreeItem() {
    this->brother = nullptr;
    this->son = nullptr;
    this->id = "";
}
//let's put our hexagon over here
TNTreeItem::TNTreeItem(std::string id, const Hexagon& hexagon) {
    this->hexagon = hexagon;
    this->brother = nullptr;
    this->son = nullptr;
    this->id = id;
}
//let's set our son
void TNTreeItem::SetSon(TNTreeItem* son) {
    this->son = son;
}
//let's set pur bro
void TNTreeItem::SetBrother(TNTreeItem* brother) {
    this->brother = brother;
}

Hexagon TNTreeItem::GetHexagon() const {
    return this->hexagon; //hexagonio
}

TNTreeItem* TNTreeItem::GetSon() {
    return this->son; //pointer to son return
}

TNTreeItem* TNTreeItem::GetBrother() {
    return this->brother; //pointer to brobro
}

std::string TNTreeItem::getId() {
    return this->id;
}

std::ostream& operator<<(std::ostream& os, const TNTreeItem& obj) {
    os << obj.hexagon << std::endl;
    return os; 
}
//let's deletO our item of a treetO
TNTreeItem::~TNTreeItem() {
    delete brother;
    delete son;
}

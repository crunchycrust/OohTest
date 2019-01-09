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
TNTreeItem::TNTreeItem(std::string id, const std::shared_ptr<Figure> &figure) { //only borrowing the resource smth* ish
    this->figure = figure;
    this->brother = nullptr;
    this->son = nullptr;
    this->id = id;
}
//let's set our son
void TNTreeItem::SetSon(std::shared_ptr<TNTreeItem> son) {
    this->son = son;
}
//increase reference counter, later - decrease
void TNTreeItem::SetBrother(std::shared_ptr<TNTreeItem> brother) {
    this->brother = brother;
}

std::shared_ptr<Figure> TNTreeItem::GetFigure() const {
    return this->figure; //
}

std::shared_ptr<TNTreeItem> TNTreeItem::GetSon() {
    return this->son; //pointer to son return
}

std::shared_ptr<TNTreeItem> TNTreeItem::GetBrother() {
    return this->brother; //pointer to brobro
}

std::string TNTreeItem::getId() {
    return this->id;
}

std::ostream& operator<<(std::ostream& os, const TNTreeItem& obj) {
    os << obj.figure << std::endl;
    return os; 
}
//let's deletO our item of a treetO
TNTreeItem::~TNTreeItem() {
   // delete brother;
   // delete son;
}

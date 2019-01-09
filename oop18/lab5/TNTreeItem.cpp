#include <iostream>
#include <string>

#include "TNTreeItem.h"
#include "Figure.h"

template class TNTreeItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const TNTreeItem<Figure> &obj);

//let's create an item
template <class T>
TNTreeItem<T>::TNTreeItem() {
    this->brother = nullptr;
    this->son = nullptr;
    this->id = "";
}
//let's put our figure over here
template <class T>
TNTreeItem<T>::TNTreeItem(std::string id, const std::shared_ptr<T> &figure) { //only borrowing the resource smth* ish
    this->figure = figure;
    this->brother = nullptr;
    this->son = nullptr;
    this->id = id;
}
//let's set our son
template <class T>
void TNTreeItem<T>::SetSon(std::shared_ptr<TNTreeItem<T>> son) {
    this->son = son;
}
//increase reference counter, later - decrease
template <class T>
void TNTreeItem<T>::SetBrother(std::shared_ptr<TNTreeItem<T>> brother) {
    this->brother = brother;
}

template <class T>
std::shared_ptr<T> TNTreeItem<T>::GetFigure() const {
    return this->figure; //
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::GetSon() {
    return this->son; //pointer to son return
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::GetBrother() {
    return this->brother; //pointer to brobro
}

template <class T>
std::string TNTreeItem<T>::getId() {
    return this->id;
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::Begin() {
	if (!this->son) {
		return this->shared_from_this();
	}
	else {
        auto iter = this->son;
        while (iter->son)
            iter = iter->son;
        return iter;
    }
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::Next() {
	if (this->brother)
		return this->brother;
	else
		return nullptr;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TNTreeItem<T>& obj) {
    os << obj.figure << std::endl;
    return os; 
}

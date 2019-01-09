#ifndef TNTREEITEM_H
#define TNTREEITEM_H

#include <string>
#include "Hexagon.h"

class TNTreeItem {
public:
    TNTreeItem(); //Default constructor
    TNTreeItem(std::string id, const Hexagon& hexagon); //Overload constructor
    friend std::ostream& operator<<(std::ostream& os, const TNTreeItem& obj);
    
	//Mutator functions
    void SetSon(TNTreeItem* son); //sets pointer to son
    void SetBrother(TNTreeItem* brother); //sets pointer to bro
    //Accessor functions
	TNTreeItem* GetSon(); //returns pointer to son
    TNTreeItem* GetBrother(); //returns pointer to bro
    Hexagon GetHexagon() const; //returns hexagon
    std::string getId(); //returns id 
    
    virtual ~TNTreeItem();

private:
	//Member variables
    Hexagon hexagon;
    std::string id; 
    TNTreeItem *son; //pointers
    TNTreeItem *brother;
};

#endif  /* TNTREEITEM_H */

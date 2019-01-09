#ifndef TNTREEITEM_H
#define TNTREEITEM_H

#include <string>
#include <memory>

#include "Figure.h"
#include "Hexagon.h"
#include "Triangle.h"
#include "Octagon.h"

class TNTreeItem {
public:
    TNTreeItem(); //Default constructor
    TNTreeItem(std::string id, const std::shared_ptr<Figure> &figure); //Overload constructor
    friend std::ostream& operator<<(std::ostream& os, const TNTreeItem& obj);
    
	//Mutator functions
    void SetSon(std::shared_ptr<TNTreeItem> son);
    void SetBrother(std::shared_ptr<TNTreeItem> brother); //sets pointer to bro
    //Accessor functions
	std::shared_ptr<TNTreeItem> GetSon();
    std::shared_ptr<TNTreeItem> GetBrother(); //returns pointer to bro
    std::shared_ptr<Figure> GetFigure() const; //returns figure
    std::string getId(); //returns id 
    
    virtual ~TNTreeItem();

private:
	//Member variables
    std::string id; 
    std::shared_ptr<Figure> figure;
	
	std::shared_ptr<TNTreeItem> son;
	std::shared_ptr<TNTreeItem> brother;
};

#endif  /* TNTREEITEM_H */

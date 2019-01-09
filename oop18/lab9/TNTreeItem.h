#ifndef TNTREEITEM_H
#define TNTREEITEM_H

#include <string>
#include <memory>

#include "TIterator.h"
#include "TAllocationBlock.h"

#include "Figure.h"
#include "Hexagon.h"
#include "Triangle.h"
#include "Octagon.h"

template <class T> class TNTree;

template <class T>
class TNTreeItem : public std::enable_shared_from_this<TNTreeItem<T>> {
public:
    TNTreeItem(); //Default constructor
    TNTreeItem(std::string id, const std::shared_ptr<T> &figure); //Overload constructor
   
    template <class U>
	friend std::ostream& operator<<(std::ostream& os, const TNTreeItem<U>& obj);
    
	//Mutator functions
    void SetSon(std::shared_ptr<TNTreeItem<T>> son);
    void SetBrother(std::shared_ptr<TNTreeItem<T>> brother); //sets pointer to bro
    //Accessor functions
	std::shared_ptr<TNTreeItem<T>> GetSon();
    std::shared_ptr<TNTreeItem<T>> GetBrother(); //returns pointer to bro
    std::shared_ptr<T> GetFigure() const; //returns figure
    std::string getId(); //returns id 
    
	std::shared_ptr<TNTreeItem<T>> Begin();
	std::shared_ptr<TNTreeItem<T>> Next();

	void *operator new(size_t size);
    void operator delete(void *ptr);

    virtual ~TNTreeItem() {};

private:
	//Member variables
    std::string id; 
    std::shared_ptr<T> figure;
	
	std::shared_ptr<TNTreeItem<T>> son;
	std::shared_ptr<TNTreeItem<T>> brother;
	
	static TAllocationBlock item_allocator;
};

#endif  /* TNTREEITEM_H */

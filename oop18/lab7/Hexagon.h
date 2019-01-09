#ifndef HEXAGON_H
#define HEXAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Hexagon : public Figure {
public:
	Hexagon(); //Default constructor
	//Overload constructors
	//Hexagon(std::istream &is); //istream object as a parameter
	Hexagon(const Hexagon& orig); //Hexagon obj as a parameter
	Hexagon(size_t i);

	friend std::ostream& operator<<(std::ostream& os, const Hexagon& obj); //returns ostream object . out
	friend std::istream& operator>>(std::istream& is, Hexagon& obj); //in
	Hexagon operator=(const Hexagon&); // def
	bool operator==(const Hexagon&) const;

	double Square() override;
	void Print() override;

	virtual ~Hexagon(){}; //Destructor
	
	int type() {return 3;}

private:
	size_t side_a; //Member variables
};

#endif //HEXAGON_H

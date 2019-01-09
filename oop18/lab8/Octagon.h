#ifndef OCTAGON_H
#define OCTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Octagon : public Figure {
public:
	Octagon();
	//Octagon(std::istream &is);
	Octagon(const Octagon& orig);
	Octagon(size_t);

	friend std::ostream& operator<<(std::ostream& os, const Octagon& obj); //returns ostream object . out
	friend std::istream& operator>>(std::istream& is, Octagon& obj); //in
	Octagon operator=(const Octagon&); // def
	bool operator==(const Octagon&) const;
	
	double Square() override;
	void Print() override;

	virtual ~Octagon(){};
	
	int type() {return 2;}

private:
	size_t side_a;
};
#endif //OCTAGON_H

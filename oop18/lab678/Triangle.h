#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Triangle : public Figure {
public:
	Triangle();
	//Triangle(std::istream &is);
	Triangle(const Triangle& orig);
	Triangle(size_t i, size_t j, size_t k);

	friend std::ostream& operator<<(std::ostream& os, const Triangle& obj); //returns ostream object . out
	friend std::istream& operator>>(std::istream& is, Triangle& obj); //in
	Triangle operator=(const Triangle&); // def
	bool operator==(const Triangle&) const;


	double Square() override;
	void Print() override;

	virtual ~Triangle(){};
	
	int type() {return 1;}

private:
	size_t side_a;
	size_t side_b;
	size_t side_c;
};

#endif  // TRIANGLE_H

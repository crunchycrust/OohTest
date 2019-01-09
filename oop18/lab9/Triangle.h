#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Triangle : public Figure {
public :
	Triangle();
	Triangle(std::istream &is);
	Triangle(const Triangle& orig);
	Triangle(size_t i, size_t j, size_t k);

	friend bool operator==(const Triangle& fst, const Triangle& snd);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& obj); 

	double Square() override;
	void Print() override;

	virtual ~Triangle();

private:
	size_t side_a;
	size_t side_b;
	size_t side_c;
};

#endif  // TRIANGLE_H

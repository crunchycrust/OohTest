#ifndef OCTAGON_H
#define OCTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Octagon : public Figure {
public:
	Octagon();
	Octagon(std::istream &is);
	Octagon(size_t i);

	double Square() override;
	void Print() override;

	virtual ~Octagon();

private:
	size_t side_a;
};
#endif //OCTAGON_H

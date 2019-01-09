#ifndef OCTAGON_H
#define OCTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Octagon : public Figure {
public:
	Octagon();
	Octagon(std::istream &is);
	Octagon(const Octagon& orig);
	Octagon(size_t);

	friend bool operator==(const Octagon& fst, const Octagon& snd);
	friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);

	double Square() override;
	void Print() override;

	virtual ~Octagon();

private:
	size_t side_a;
};
#endif //OCTAGON_H

#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {
}
Octagon::Octagon(size_t i) : side_a(i) {
}

Octagon::Octagon(const Octagon& orig) {
	side_a = orig.side_a;
}

/*Octagon::Octagon(std::istream &is) {
	std::cout << "PLEASE, one side of your octagon:\n";
	is >> side_a;
}*/

bool Octagon::operator==(const Octagon &obj) const
{
    return (this->side_a == obj.side_a);
}

Octagon Octagon::operator=(const Octagon &obj)
{
    if (&obj == this) {
        return *this;
    }
    side_a = obj.side_a;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
    os << obj.side_a << std::endl;
    return os;
}

std::istream& operator>>(std::istream &is, Octagon &obj)
{
    std::cout << "PLEASE, one side of your octagon:\n";
    is >> obj.side_a;
    return is;
}


double Octagon::Square() {
	return 2*(side_a)*(side_a)*(1+sqrt(2));
}

void Octagon::Print() {
	std::cout << "Octagon: a = " << this->side_a << "; Square = " << this->Square() <<std::endl;
}


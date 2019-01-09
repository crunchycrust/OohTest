#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() : Triangle(0, 0, 0) {
}
Triangle::Triangle(size_t i, size_t j, size_t k) : side_a(i), side_b(j), side_c(k) {
}

Triangle::Triangle(const Triangle& orig) { //copy of our triangle
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_c = orig.side_c;
}

/*Triangle::Triangle(std::istream &is) {
	std::cout << "Enter sides of your triangle:\n";
	is >> side_a;
	is >> side_b;
	is >> side_c;
}*/

bool Triangle::operator==(const Triangle& obj) const 
{
  return ((this->side_a == obj.side_a) && (this->side_b == obj.side_b)
          && (this->side_c == obj.side_c));
}

Triangle Triangle::operator=(const Triangle& obj) {
    if (this == &obj) return *this;

  side_a = obj.side_a;
  side_b = obj.side_b;
  side_c = obj.side_c;
  
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj) {
    if (obj == Triangle())
    return os;
  
  os << obj.side_a << " " << obj.side_b << " " << obj.side_c << " " << std::endl;
  
  return os;
}

std::istream& operator >>(std::istream &is, Triangle& obj)
{
    std::cout << "Enter sides of your triangle:\n";
    is >> obj.side_a >> obj.side_b >> obj.side_c;
    
     return is;
}

double Triangle::Square() {
	double p = double(side_a + side_b + side_c) / 2.0;
	return sqrt(p * (p - double(side_a))*(p - double(side_b))*(p - double(side_c)));
}

void Triangle::Print() {
	std::cout << "Triangle: a = " << this->side_a << ", b = " << this->side_b << ", c = " << this->side_c << "; Square = " << this->Square() << std::endl;
}

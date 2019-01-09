#include <cstdlib>
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"

using namespace std;

void help() {
	cout << "Choose:" << endl;
	cout << "1 - Create regular hexagon;" << endl;
	cout << "2 - Create regular octagon;" << endl;
	cout << "3 - Create triangle;" << endl;
	cout << "0 - Exit." << endl;
	cout << "--------------------------" << endl;	
}

int main() {
	int c;
	Figure *ptr = nullptr;
	help();
	
	while (cin >> c) {
	
		if (c == 1) {	
			cout << "Side of regular hexagon:" << endl;
			ptr = new Hexagon(cin);
			ptr->Print();
			cout << "Area of your hexagon = " << ptr->Square() << endl;
			delete ptr;
		}

		else if (c == 2) {
			cout << "Side of the relugar octagon:" << endl;
			ptr = new Octagon(cin);
			ptr->Print();
			cout << "Area of your octagon = " << ptr->Square() << endl;
			delete ptr;
		}
		else if (c == 3) {
			cout << "Sides of your triangle:" << endl;
			ptr = new Triangle(cin);
			ptr->Print();
			cout << "Area of your amazing triangle = " << ptr->Square() << endl;
			delete ptr;
		}
		else
			break;		
	} 
	return 0;
}


#include <iostream>

#include "TQueue.h"
#include "TTree.h"

#include "Octagon.h"
#include "Hexagon.h"
#include "Triangle.h"

int main(void) {
	TTree<TQueue<Figure>, std::shared_ptr<Figure>> tree;
	std::string c;
	int c1;

    std::cout << "'help' for help" << std::endl;
    while (1) {
        std::cin.clear();
        std::cin.sync();
        std::cout << ">";
        std::cin >> c;

        if (c == "e" || c == "exit") {
            break;
        } 
        else if (c == "t" || c == "triangle") {
            Triangle fig;

            std::cin >> fig;
            tree.insert(std::make_shared<Triangle>(fig));
        } 
        else if (c == "h" || c == "hexagon") {
            Hexagon fig;

            std::cin >> fig;
            tree.insert(std::make_shared<Hexagon>(fig));
        } 
        else if (c == "o" || c == "octagon") {
            Octagon fig;

            std::cin >> fig;
            tree.insert(std::make_shared<Octagon>(fig));
        } 
        else if (c == "r" || c == "remove") {
            std::cout << "'1' - type\n'2' - square\n";
            std::cin >> c1;
            if (c1 == 1) {
                std::cout << "'1' triangle\n'2' octagon\n'3' hexagon\n";
                std::cout << "Type:" << std::endl;
                std::cin >> c1;
                tree.removeByType(c1);
            } else if (c1 == 2) {
                double sqr = 0.0;
                std::cout << "Remove all squares less than:" << std::endl;
                std::cin >> sqr;
                tree.removeLesser(sqr);
            }
        } 
        else if (c == "ps" || c == "prints") {
			if (!tree.IsEmpty()) {
				tree.inorder();
			}
			else {
				std::cout << "The tree is empty" << std::endl;
			}
        }       
        else if (c == "pp" || c == "printp") {
			if (!tree.IsEmpty()) {
				tree.inorderp();
			}
			else {
				std::cout << "The tree is empty" << std::endl;
			}
        }       
        else if (c == "d" || c == "destroy") {
			if (!tree.IsEmpty()) {
                tree.Des();
            }
            else {
               std::cout << "The tree is already empty" << std::endl;
            }           
        } 
        else if (c == "help") {
            std::cout << "'help'               - help;" << std::endl;
			std::cout << "'t'   or 'triangle'  - insert triangle" << std::endl;
			std::cout << "'o'   or 'octagon'   - insert octagon;" << std::endl;
			std::cout << "'h'   or 'hexagon'   - insert hexagon;" << std::endl;
            std::cout << "'r'   or 'remove'    - remove figure;" << std::endl;
            std::cout << "'d'   or 'destroy'   - delete the tree;" << std::endl;
            std::cout << "'ps'  or 'prints'    - print the tree (normal sorting);" << std::endl;
            std::cout << "'pp'  or 'printp'    - print the tree (parallel sorting);" << std::endl;
            std::cout << "'e'   or 'exit'      - exit." << std::endl;
		}
    }
    return 0;
}

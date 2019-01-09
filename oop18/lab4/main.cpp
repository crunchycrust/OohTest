#include <iostream>
#include <string>

#include "TNTree.h"
#include "TNTreeItem.h"
#include "Figure.h"

int main(int argc, char** argv)
{
    TNTree<Figure> tree; //make an object
    std::string c;

    std::cout << "Type 'help' for help" << std::endl;
    while (1) {
        std::cin.clear();
        std::cin.sync();
        std::cout << ">";
        std::cin >> c;
       
        if (c == "e" || c == "exit") {
        //        delete tree;
            break;
        } 
		else if (c == "t" || c == "triangle") {
            std::shared_ptr<Figure> fig;
			std::string parent_id, id;
			
            std::cout << "Enter parent id: ";
            std::cin >> parent_id;
            std::cout << "Enter node id: ";
            std::cin >> id;

			fig = std::make_shared<Triangle> (std::cin);
        	tree.Insert(parent_id, id, fig);  
        }
		else if (c == "h" || c == "hexagon") {
			std::shared_ptr<Figure> fig;
			std::string parent_id, id;

			std::cout << "Enter parent id: ";
			std::cin >> parent_id;
			std::cout << "Enter node id: ";
			std::cin >> id;
			
			fig = std::make_shared<Hexagon> (std::cin);
			tree.Insert(parent_id, id, fig);
		}
		else if (c == "o" || c == "octagon") {
			std::shared_ptr<Figure> fig;
			std::string parent_id, id;

			std::cout << "Enter parent id: ";
			std::cin >> parent_id;
			std::cout << "Enter node id: ";
			std::cin >> id;

			fig = std::make_shared<Octagon> (std::cin);
			tree.Insert(parent_id, id, fig);
		} 
		else if (c == "r" || c == "remove") {
            if (!tree.IsEmpty()) {
				std::string id;
				std::cout << "Enter item id: ";
				if (!(std::cin >> id)) {
					std::cout << "Incorrect value" << std::endl;
					continue;
				}
				tree.Remove(id);
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
           //delete tree; //delete tree and make place for next
           //tree = new TNTree();
           //std::cout << "The tree was deleted." << std::endl;
        } 
		else if (c == "p" || c == "print") { //print the entire treeo
            if (!tree.IsEmpty()) {
                tree.PrintTree();
            }
            else {
                std::cout << "The tree is empty" << std::endl;
            }
        }
		else if (c == "pi" || c == "printi") { //printing an item
			if (!tree.IsEmpty()) {
				std::string id;
				std::cout << "Enter item id: ";
				std::cin >> id;

				tree.PrintItem(id); 
			}
			else {
				std::cout << "The tree is empty" << std::endl;
			}
        }
		else if (c == "help") {
            std::cout << "'help'            - help;" << std::endl;
			std::cout << "'t' or 'triangle' - insert triangle" << std::endl;
			std::cout << "'h' or 'hexagon'  - insert hexagon;" << std::endl;
			std::cout << "'o' or 'octagon'  - insert octagon;" << std::endl;
            std::cout << "'r'  or 'remove'  - remove figure;" << std::endl;
            std::cout << "'d'  or 'destroy' - delete the tree;" << std::endl;
            std::cout << "'p'  or 'print'   - print the tree;" << std::endl;
            std::cout << "'pi' or 'printi'  - print figure;" << std::endl;
            std::cout << "'e'  or 'exit'    - exit." << std::endl;
        }
    }
    
    return 0;
}


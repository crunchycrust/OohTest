#include <iostream>
#include <string>

#include "TNTree.h"
#include "Hexagon.h"

int main(int argc, char** argv)
{
    TNTree *tree = new TNTree(); //pointer to our alive tree
    std::string c;

    std::cout << "Type 'h' or 'help' for help" << std::endl;
    while (1) {
        std::cin.clear();
        std::cin.sync();
        std::cout << ">";
        std::cin >> c;
       
        if (c == "e" || c == "exit") {
                delete tree;
            break;
        } 
		else if (c == "i" || c == "insert") {
            size_t size_a;
            std::string parent_id, id;
            std::cout << "Enter parent id: ";
            std::cin >> parent_id;
            std::cout << "Enter node id: ";
            std::cin >> id;
            std::cout << "Enter Hexagon side:\n";
            if (!(std::cin >> size_a)) {
                std::cout << "Incorrect value" << std::endl;
                continue;
            }
            Hexagon* n = new Hexagon(size_a); //we made our hexagon and that's a pointer
            tree->Insert(tree, parent_id, id, *n); //let's insert hexagonnn
            delete n; //delete the pointer
        } 
		else if (c == "r" || c == "remove") {
            std::string id;
            std::cout << "Enter item id: ";
            if (!(std::cin >> id)) {
                std::cout << "Incorrect value" << std::endl;
                continue;
            }
            tree->Remove(id);
        } 
		else if (c == "d" || c == "destroy") {
            delete tree; //delete tree and make place for next
            tree = new TNTree();
            std::cout << "The tree was deleted." << std::endl;
        } 
		else if (c == "p" || c == "print") { //print the entire treeo
            if (!tree->IsEmpty()) {
                tree->PrintTree(tree->getHead(), 0);
            }
            else {
                std::cout << "The tree is empty" << std::endl;
            }
        }
		else if (c == "pi" || c == "printi") { //printing an item
            std::string id;
            std::cout << "Enter item id: ";
            std::cin >> id;

            tree->PrintItem(tree, id);
        }
		else if (c == "help" || c  == "h") {
            std::cout << "'h'  or 'help'       - help;" << std::endl;
            std::cout << "'r'  or 'remove'     - remove hexagon;" << std::endl;
            std::cout << "'d'  or 'destroy'    - delete the tree;" << std::endl;
            std::cout << "'p'  or 'print'      - print the tree;" << std::endl;
            std::cout << "'i'  or 'insert'     - insert hexagon into your tree;" << std::endl;
            std::cout << "'pi' or 'printi'     - print hexagon;" << std::endl;
            std::cout << "'e'  or 'exit'       - exit." << std::endl;
        }
    }
    
    return 0;
}


#include <iostream>
#include <string>
#include <cstdint>
#include <future>
#include <mutex>
#include <thread>
#include <functional>
#include <random>
#include <cstdlib>
#include <cstring>

#include "TNTree.h"
#include "TNTreeItem.h"
#include "TQueue.h"
#include "Figure.h"

int main(int argc, char** argv)
{
    TNTree<Figure> tree; //make an object
    std::string c;
	
	typedef std::function<void(void)> Command;
	TQueue<std::shared_ptr<Command>> comque;//
	std::mutex mtx;
	
	
	Command In = [&]() {
		std::lock_guard<std::mutex> guard(mtx);
		
		std::cout << ">Commencing Insert" << std::endl;
		
		uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distFigureParam(1, 10);
        
        std::shared_ptr<Figure> fig;
		std::string parent_id, id;
        
        for (int i = 0; i < 4; i++) {
			switch (i)	{	
				case (0): {					
					parent_id = "1";
					id = "1";
					
					size_t side_a = distFigureParam(generator);
					size_t side_b = distFigureParam(generator);
					size_t side_c = distFigureParam(generator);
					
					while((side_a+side_b < side_c) || (side_a+side_c< side_b) || (side_b+side_c < side_a)) {
						side_a = distFigureParam(generator);
						side_b = distFigureParam(generator);
						side_c = distFigureParam(generator);
					}
					
					fig = std::make_shared<Triangle> (side_a, side_b, side_c);
					tree.Insert(parent_id, id, fig);  

					std::cout << ">>Triangle Inserted" << std::endl;
					break;
				}
				case (1): {
					parent_id = "1";
					id = "2";
					
					size_t side_a = distFigureParam(generator);
					
					fig = std::make_shared<Octagon> (side_a);
					tree.Insert(parent_id, id, fig);  

					std::cout << ">>Octagon Inserted" << std::endl;
					break;
				}
				case (2): {
					parent_id = "1";
					id = "3";
					
					size_t side_a = distFigureParam(generator);
					
					fig = std::make_shared<Hexagon> (side_a);
					tree.Insert(parent_id, id, fig);  

					std::cout << ">>Hexagon Inserted" << std::endl;
					break;
				}
				case (3): {
					parent_id = "3";
					id = "4";
					
					size_t side_a = distFigureParam(generator);
					
					fig = std::make_shared<Octagon> (side_a);
					tree.Insert(parent_id, id, fig);  

					std::cout << ">>Octagon Inserted" << std::endl;
					break;
				}	
			}
		}
		std::cout << '\n';				
	};
	
	Command Printo = [&]() {
		std::lock_guard<std::mutex> guard(mtx);
        
        std::cout << ">Commencing Print" << std::endl;
	
		if (!tree.IsEmpty()) {
            tree.PrintTree();
        }
        else {
            std::cout << "The tree is empty" << std::endl;
        }
        
        std::cout << ">>Completed Print\n" << std::endl;
        
	
	};
	
	Command PrintoVal = [&]() {
		std::lock_guard<std::mutex> guard(mtx);
        
        std::cout << ">Commencing Print Values" << std::endl;
	
		if (!tree.IsEmpty()) {
            tree.PrintTreeVal();
        }
        else {
            std::cout << "The tree is empty" << std::endl;
        }
		
		std::cout << ">>Completed Print Values\n" << std::endl;
	};
	
	Command RemSq = [&]() {
		std::lock_guard<std::mutex> guard(mtx);
        
        std::cout << ">Commencing Remove more than 150" << std::endl;
		
		double Sq = 150;
		
		if (!tree.IsEmpty()) {
                tree.RemS(Sq);
            }
            else {
                std::cout << "The tree is empty" << std::endl;
            }
            
        std::cout << ">>Completed Remove more than 150\n" << std::endl;  
	};

    comque.Push(std::shared_ptr<Command>(&PrintoVal, [](Command*){}));
    comque.Push(std::shared_ptr<Command>(&RemSq, [](Command*){}));
    comque.Push(std::shared_ptr<Command>(&PrintoVal, [](Command*){}));
    comque.Push(std::shared_ptr<Command>(&Printo, [](Command*){}));
    comque.Push(std::shared_ptr<Command>(&In, [](Command*){}));
    
    
    while (!comque.IsEmpty()) {
		std::shared_ptr<Command> com = comque.Lasto();
		std::future<void> ft = std::async(*com);
        ft.get();
		comque.Pop();
	}
    
    return 0;
}


#include <iostream>
#include <array>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"
#include "../include/node/node.h"


int main() {

	// Create an instance of objects of classes Mouse and Node
 	rwa2::Mouse mouse;
 	rwa2::Node N;

	//Set goal as G1(7,7)
	mouse.set_goal({7,7});
	
	while(true) {
		
		// Clear all colors from maze
		API::clearAllColor();

		// Check walls around current node
		mouse.check_walls();

		// Search for a path applying Depth First Search Algorithm
		// A stack with all the nodes on the path found is created
		mouse.search_maze();

		// Loop to reverse the stack and store the contents in a new stack
		// The original stack is also emptied
		while(!mouse.get_stack().empty()) {
			mouse.push_inv_stack(mouse.get_stack().top());
			mouse.pop_stack();
		}

		// Remove the first element of the inverted stack
		if(!mouse.get_inv_stack().empty()) {
			mouse.pop_inv_stack();
		}

		// Loop to move the mouse based on the path found by the Depth First Search Algorithm
		while(true) {

			mouse.move_mouse();

			// Check break condition from the function to move mouse
			if(mouse.get_break_flag() == true) {
				break;
			}

			// Set the color and text for the goal cell
			API::setColor(mouse.get_goal().at(0), mouse.get_goal().at(1), 'c');
			API::setText(mouse.get_goal().at(0), mouse.get_goal().at(1), "G1");
			
		}

		mouse.set_break_flag(false);

		//Clear the visited nodes list
		mouse.clear_list();

	}

}
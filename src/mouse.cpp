#include "../include/mouse/mouse.h"  
#include "../include/node/node.h"
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>


void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}



bool rwa2::Mouse::search_maze() {

    if (n != g){
        if(s.empty()) {
            s.push(n);
            API::setColor(n.at(0),n.at(1), 'y'); //color the starting node
        }
    }

    else{
        return true; //return true if goal is reached
    }

    if (check_list(n,v)) {
        v.push_back(n); //add node to visited list
    }
    
	//Check validity for the node at the NORTH of the current node
    if(check_validity(direction::NORTH,0, 1)) {
        n.at(1) ++;
        s.push(n);
		if(!(n.at(0) == g.at(0) && n.at(1) == g.at(1))) {
        	API::setColor(n.at(0),n.at(1), 'y');
		}
    }

	//Check validity for the node at the EAST of the current node
    else if(check_validity(direction::EAST,1, 0)) {
        n.at(0) ++;
        s.push(n);
		if(!(n.at(0) == g.at(0) && n.at(1) == g.at(1))) {
        	API::setColor(n.at(0),n.at(1), 'y');
		}
    }

	//Check validity for the node at the SOUTH of the current node
    else if(check_validity(direction::SOUTH,0, -1)) {
        n.at(1) --;
        s.push(n);
		if(!(n.at(0) == g.at(0) && n.at(1) == g.at(1))) {
        	API::setColor(n.at(0),n.at(1), 'y');
		}
    }

	//Check validity for the node at the WEST of the current node
    else if(check_validity(direction::WEST,-1, 0)) {
        n.at(0) --;
        s.push(n);
		if(!(n.at(0) == g.at(0) && n.at(1) == g.at(1))) {
        	API::setColor(n.at(0),n.at(1), 'y');
		}
    }

    else {
        if(!s.empty()) {
            s.pop(); //no node is valid, backtrack
        }
        else {
            return false; //path not found
        }
    }

    if (!s.empty()) {
        n = s.top();
        search_maze(); //recursion to seach next node
    }
    else {
        return false; //path not found
    }
}


bool rwa2::Mouse::check_validity(int dir, int x, int y) {

    std::array<int,2> n_temp;
    if (n.at(0)+x > 15 || n.at(1)+y > 15 || n.at(1)+y < 0 || n.at(0)+x < 0) {return false;}
    else {
    n_temp.at(0)=n.at(0)+x;
    n_temp.at(1)=n.at(1)+y;
    bool cond1 = !(m_maze.at(n.at(0)).at(n.at(1)).is_wall(dir)); //check for wall condition
    bool cond2 = check_list(n_temp, v); //check for visited condition
    return cond1 && cond2; 
    }
    
}


bool rwa2::Mouse::check_list(std::array<int, 2> p, std::vector<std::array<int, 2>> v) {
    for (int i = 0; i < v.size(); i++) {
        if(p[0] == v[i][0] && p[1] == v[i][1]) {
            return false;
        }
    }
    return true;
}


void rwa2::Mouse::move_mouse() {
	
	//Instructions to move the mouse when it faces NORTH based on the coordinates of the next node
	//If the path is blocked by a wall, set break flag to be true
	if(m_direction == direction::NORTH) {
		if(s_inv.top().at(0) == m_x && ((s_inv.top().at(1) - m_y) == 1)) {
			if(!API::wallFront()) {
				API::moveForward();
				m_y += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;	
		}
		else if(((s_inv.top().at(0) - m_x) == 1) && s_inv.top().at(1) == m_y) {
			if(!API::wallRight()){
				API::turnRight();
				API::moveForward();
				m_direction = direction::EAST;
				m_x += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(s_inv.top().at(0) == m_x && (s_inv.top().at(1) - m_y) == -1) {
			API::turnRight();
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::SOUTH;
				m_y -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == -1) && s_inv.top().at(1) == m_y) {			
			if(!API::wallLeft()) {
				API::turnLeft();
				API::moveForward();
				m_direction = direction::WEST;
				m_x -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
	}

	//Instructions to move the mouse when it faces EAST based on the coordinates of the next node
	//If the path is blocked by a wall, set break flag to be true
	else if(m_direction == direction::EAST) {
		if(s_inv.top().at(0) == m_x && ((s_inv.top().at(1) - m_y) == 1)) {
			if(!API::wallLeft()) {
				API::turnLeft();
				API::moveForward();
				m_direction = direction::NORTH;
				m_y += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == 1) && s_inv.top().at(1) == m_y) {
			if(!API::wallFront()) {
				API::moveForward();
				m_x += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(s_inv.top().at(0) == m_x && (s_inv.top().at(1) - m_y) == -1) {
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::SOUTH;
				m_y -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == -1) && s_inv.top().at(1) == m_y) {
			API::turnRight();
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::WEST;
				m_x -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
	}


	//Instructions to move the mouse when it faces SOUTH based on the coordinates of the next node
	//If the path is blocked by a wall, set break flag to be true
	else if(m_direction == direction::SOUTH) {
		if(s_inv.top().at(0) == m_x && ((s_inv.top().at(1) - m_y) == 1)) {
			API::turnRight();
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::NORTH;
				m_y += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == 1) && s_inv.top().at(1) == m_y) {
			if(!API::wallLeft()) {
				API::turnLeft();
				API::moveForward();
				m_direction = direction::EAST;
				m_x += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(s_inv.top().at(0) == m_x && (s_inv.top().at(1) - m_y) == -1) {
			if(!API::wallFront()) {
				API::moveForward();
				m_y -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == -1) && s_inv.top().at(1) == m_y) {
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::WEST;
				m_x -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
	}


	//Instructions to move the mouse when it faces WEST based on the coordinates of the next node
	//If the path is blocked by a wall, set break flag to be true
	else if(m_direction == direction::WEST) {
		if(s_inv.top().at(0) == m_x && ((s_inv.top().at(1) - m_y) == 1)) {
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::NORTH;
				m_y += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == 1) && s_inv.top().at(1) == m_y) {
			API::turnRight();
			if(!API::wallRight()) {
				API::turnRight();
				API::moveForward();
				m_direction = direction::EAST;
				m_x += 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(s_inv.top().at(0) == m_x && (s_inv.top().at(1) - m_y) == -1) {
			if(!API::wallLeft()) {
				API::turnLeft();
				API::moveForward();
				m_direction = direction::SOUTH;
				m_y -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
		else if(((s_inv.top().at(0) - m_x) == -1) && s_inv.top().at(1) == m_y) {
			if(!API::wallFront()) {
				API::moveForward();
				m_x -= 1;
				n.at(0) = s_inv.top().at(0);
				n.at(1) = s_inv.top().at(1);
				s_inv.pop();
			}
			else break_flag = true;
		}
	}
	check_walls(); //check for walls after travelling to each node
}


void rwa2::Mouse::check_walls() {

	//Check for walls when the mouse is facing NORTH
	if(m_direction == direction::NORTH) {
		if(API::wallFront()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, true);
		}
		if(API::wallRight()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::EAST, true);
		}
		if(API::wallLeft()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::WEST, true);
		}	
	}

	//Check for walls when the mouse is facing EAST
	if(m_direction == direction::EAST) {
		if(API::wallLeft()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, true);
		}
		if(API::wallFront()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::EAST, true);
		}
		if(API::wallRight()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, true);
		}	
	}

	//Check for walls when the mouse is facing SOUTH
	if(m_direction == direction::SOUTH) {
		if(API::wallLeft()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::EAST, true);
		}
		if(API::wallFront()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, true);
		}	
		if(API::wallRight()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::WEST, true);
		}
	}

	//Check for walls when the mouse is facing WEST
	if(m_direction == direction::WEST) {
		if(API::wallRight()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, true);
		}
		if(API::wallLeft()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, true);
		}	
		if(API::wallFront()) {
			m_maze.at(m_x).at(m_y).set_wall(direction::WEST, true);
		}
	}

	display_walls(); //display the walls in the simulator
}



std::array<int,2> rwa2::Mouse::get_goal() {
    return g;
}


void rwa2::Mouse::set_goal(std::array<int,2> g_) {
	g = g_;
}



bool rwa2::Mouse::get_break_flag() {
	return break_flag;
}



void rwa2::Mouse::set_break_flag(bool break_flag_) {
	break_flag = break_flag_;
}



void rwa2::Mouse::clear_list() {
	v.clear();
}



std::stack<std::array<int, 2>> rwa2::Mouse::get_stack() {
	return s;
}



std::stack<std::array<int, 2>> rwa2::Mouse::get_inv_stack() {
	return s_inv;
}



void rwa2::Mouse::push_inv_stack(std::array<int, 2> s_top) {
	s_inv.push(s_top);
}



void rwa2::Mouse::pop_stack() {
	s.pop();
}



void rwa2::Mouse::pop_inv_stack() {
	s_inv.pop();
}
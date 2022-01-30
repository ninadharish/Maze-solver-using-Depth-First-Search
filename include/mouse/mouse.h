/**
 * @file mouse.h
 * @author Ninad Harishchandrakar (ninadh@umd.edu), Sai Sandeep Adapa (sadapa@umd.edu)
 * @brief The file contains the Mouse class
 * @version 0.1
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */

 /*! \mainpage Maze search algorithm
  *
  * This project consists of searching a path in a maze
  * and then task a mouse (robot) to follow the path.
  * - \subpage searchingPathPage "Searching a path"
  *
  * - \subpage followingPathPage "Following a path"
  *
  */

  /*! \page searchingPathPage Searching a path
   *
   * The search algorithm used for searching a path in a maze relies on
   * the depth-first search (DFS) approach. This algorithm is implemented in rwa2::Mouse::search_maze()
   *
   */

   /*! \page followingPathPage Following a path
    *
    * To follow a path generated by DFS, methods from the class API (api/api.h) must be used to interact
    * with the micromouse simulator.
    * - Methods of the API class are documented <a href="https://github.com/mackorone/mms#summary">here</a>.
    */


#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "../node/node.h"
#include "../util/util.h"
#include <array>
#include <vector>
#include <stack>

namespace rwa2 {
    /**
     * @brief This class is used to compute a path and execute the path.
     *
     */
    class Mouse {
        public:

        /**
         * @brief Construct a new MicroMouse object
         *
         * The robot is always at (0,0) and facing NORTH when the simulator starts
         */
        Mouse() :m_x{ 0 }, m_y{ 0 }, m_direction{ direction::NORTH }, break_flag{false} {
            //initialize the maze by placing around the perimeter of the maze
            for (int x = 0; x < m_maze_width; x += 1) {
                for (int y = 0; y < m_maze_height; y += 1) {
                    m_maze.at(x).at(y).set_wall(direction::NORTH, (y == m_maze_height - 1));
                    m_maze.at(x).at(y).set_wall(direction::EAST, (x == m_maze_width - 1));
                    m_maze.at(x).at(y).set_wall(direction::SOUTH, (y == 0));
                    m_maze.at(x).at(y).set_wall(direction::WEST, (x == 0));
                }
            }
        }

        // this method visually sets the walls in the simulator
        void display_walls();
        

        /**
         * @brief Implement DFS to compute a path between 2 nodes in a maze
         *
         * @return true A path is found
         * @return false A path is not found
         */
        bool search_maze();


        /**
         * @brief Check whether travelling to the next node is possible
         * 
         * @return true 
         * @return false 
         */
        bool check_validity(int, int , int);


        /**
         * @brief Check if the input array is part of the given list
         * 
         * @return true 
         * @return false 
         */
        bool check_list(std::array<int, 2> , std::vector<std::array<int, 2>>);


        /**
         * @brief Move the mouse in the simulator
         * 
         */
        void move_mouse();


        /**
         * @brief Check whether there are walls around the current node
         * 
         */
        void check_walls();


        /**
         * @brief Get the goal
         * 
         * @return std::array<int,2> 
         */
        std::array<int,2> get_goal();


        /**
         * @brief Set the goal object
         * 
         */
        void set_goal(std::array<int,2>);


        /**
         * @brief Get the break flag condition
         * 
         * @return true 
         * @return false 
         */
        bool get_break_flag();


        /**
         * @brief Change the value of the break flag condition
         * 
         */
        void set_break_flag(bool);


        /**
         * @brief Clear the list of visited nodes
         * 
         */
        void clear_list();


        /**
         * @brief Get the stack
         * 
         * @return std::stack<std::array<int, 2>> 
         */
        std::stack<std::array<int, 2>> get_stack();


        /**
         * @brief Get the inverted stack
         * 
         * @return std::stack<std::array<int, 2>> 
         */
        std::stack<std::array<int, 2>> get_inv_stack();


        /**
         * @brief Method to push new element in stack
         * 
         */
        void push_inv_stack(std::array<int, 2>);


        /**
         * @brief Method to pop the stack
         * 
         */
        void pop_stack();


        /**
         * @brief Method to pop the inverted stack
         * 
         */
        void pop_inv_stack();



        private:
        static const int m_maze_width{ 16 }; //width of the maze
        static const int m_maze_height{ 16 };//height of the maze
        int m_x; //x position of the robot in the maze
        int m_y; //y position of the robot in the maze
        int m_direction; //direction of the robot in the maze
        std::array<std::array<Node, m_maze_width>, m_maze_height> m_maze; //2D array maze object

        std::array<int, 2> g{}; //location of the goal
     	std::array<int, 2> n{}; //array to store the value of node to be used in the Depth First Search Algorithm
        
        std::stack<std::array<int, 2>> s; //stack of the path found with the Depth First Search Algorithm
        std::stack<std::array<int, 2>> s_inv; //inverted stack
        
    	std::vector<std::array<int, 2>> v; //list of visited nodes
        bool break_flag; //flag to break out of loop



    };
}
#endif
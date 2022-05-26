![alt text](/output/output.gif)

# Maze Solver usign Depth First Search

## Description

A maze solving algorithm in C++ using the MicroMouse Simulator. The Mouse starts searching at its initial position with no information about its walls. It updates the location of the walls only after visiting the cell. Each time the wall is updated, a new path (yellow) is calculated to the goal using the Depth First Search Algorithm keeping in mind the existing wall information. The goal is set to (7,7).

## Output

The Mouse begins searching at its start position.

![alt text](/output/output1.png)

Intermediate point in its search.

![alt text](/output/output2.png)

The Mouse reaches its goal position.

![alt text](/output/output3.png)


The Video Output can be found [here](https://drive.google.com/file/d/1MMMz3iHsMKDaRkGAD7gRIdvhdlXJwaFh/view?usp=sharing).


## Getting Started

### Dependencies

<p align="left"> 
<a href="https://www.cplusplus.com/" target="_blank" rel="noreferrer"> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/800px-ISO_C%2B%2B_Logo.svg.png" alt="cpp" width="40" height="40"/> &ensp;</a>

* [C++](https://www.cplusplus.com/)
* [MicroMouse Simulator](https://github.com/mackorone/mms)

### Installing

* Install ROS using the instructions on the [link](http://wiki.ros.org/Installation/Ubuntu).

### Executing program

* Clone the MicroMouse simulator and a set of maze files in the folder .../simulator
```
cd /simulator
git clone https://github.com/mackorone/mms.git
git clone https://github.com/micromouseonline/mazefiles.git
```

* Open the folder .../simulator/mms/bin and start the MicroMouse simulator:
```
cd /mms/bin
./mms
```

* Choose a maze from the Resources option.

* Click on the add file button. A window to specify certain details will open.

* Specify any name.

* In the Directory field, browse to the folder '.../src'.

* In the Build field, input "g++ api.cpp node.cpp mouse.cpp main.cpp".

* In the Run field, type "./a.out" and click 'OK'.

* Click 'Build' to compile the program in the simulator.

* After build is completed, adjust the mouse speed slider to get the desired speed.

* Click on 'Run'.

* The mouse starts its run and completes searching the maze to the goal location.


## Authors

👤 **Ninad Harishchandrakar**

* [GitHub](https://github.com/ninadharish)
* [Email](ninad.harish@gmail.com)
* [LinkedIn](https://linkedin.com/in/ninadharish)


## Acknowledgments

👤 **Mack Ward**

* [Website](https://www.mackorone.com/)
* [Email](mackorone@gmail.com)
* [GitHub](https://github.com/mackorone)
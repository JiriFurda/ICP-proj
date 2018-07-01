# Block Editor (ICP project)
Bachelor study at FIT VUT Brno  
4th semester - summer 2018  
Subject: **The C++ Programming Language (ICP)**

Similar project: *[Java Block Editor](https://github.com/Furdys/IJA-proj)*

## Authors
* Jiří Furda *(xfurda00) - Mostly GUI*
* Peter Havan *(xhavan00) - Mostly backend*

## Score
* Overall: **75/100**

### Details
*Acording to the score graph, everyone who fulfilled the requirements earned 75 points. Some people had even less but noone had more than 75.*

## Description
Block editor allows you to create a block scheme. It supports three unique value types (float, complex number and boolean) which are used by blocks for arithmetic (both real and complex) and by blocks for logic.
Every block has its input and output ports which can be connected to a port of another block. Created scheme can be saved to file and also loaded from file. When your scheme is done, you can execute whole calculation at once or you can use stepping, which caclulates only one block at the time. Any value can be read by hovering over a connection or by clicking on a block. Editor also prevents loops and incompatibile connections.

## Instalation
For compilation use `make` in the root folder. This creates file **blockeditor** in the same folder.   
If you also want to open the program, use `make run` instead.  
For generating Doxygen documentation use `make doxygen` in the root folder.

## Screenshots
![Block Editor screenshot](https://i.imgur.com/jlyVabw.png)
### Connecting blocks
![Connecting blocks example](https://imgur.com/nt92WvI.gif)
### Reading values
![Value reading example](https://imgur.com/fVrr3gp.gif)
### Moving block
![Moving block example](https://imgur.com/qxXU8tM.gif)
### Stepping
![Stepping example](https://imgur.com/ZTinNvF.gif)

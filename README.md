# CubicGraphKaszonyiFunctionProgram
Computes Kaszonyi function, parallel and serial resistance values for cubic graphs

## Installation guide
This is a simple installation guide, that can help you to go through the process of installing all tools required to run this program.
To run this program, you need:
- gcc compiler version 5 or higher (to run c++17)
- qt version 5 or higher
- cmake version VERSION 3.14 or higher
- CryptoMiniSat SAT solver

Now we will step-by-step show you how to install all those tools on (Ubuntu) Linux and then run the program.

### Installing GCC compiler and CMake

```
$ sudo apt update
$ sudo apt install build-essential cmake
```

You can also check your gcc and cmake versions with commands:
```
$ gcc --version
$ cmake --version
```

### Installing Qt visual library:
```
$ sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```

Or you can download qt from their official website: https://www.qt.io/download

### Installing CryptoMiniSat Solver
This may be the hardest part actually, but if you closely follow the instruction manual it should do just fine.
First, download CMSAT from https://github.com/msoos/cryptominisat (clone repository or download zip).
Extract files and move to the directory with CryptoMiniSat.
Compile CryptoMiniSat using the installation guide their page. We also copy-paste their installation guide here:

```
$ #not required but very useful
$ sudo apt install zlib1g-dev libboost-program-options-dev libm4ri-dev libsqlite3-dev help2man
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig
```

## Compiling and running the CubicGraphKaszonyiFunctionProgram
First, download the program from this webpage (clone repository or download zip).
Now go to the directory with the program and run those commands:
```
$ mkdir build-dir
$ #directory name can be anything you want
$ cd build-dir
$ cmake ..
$ make
$ ./CubicGraphKaszonyiFunctionProgram
```

# Program instruction manual
This manual helps you to better understand the program, how to use it, what is the expected input file format, etc.

## Basic program use-case
We believe the program GUI is rather intuitive to use, but nonetheless, we provide you with some basic information how to use it.

To run the program, you need to choose:
- one from the four computation options
- files you want to use
- output directory

### Parallel and serial resistance values
Computes the parallel and serial resistance values of the graphs given in files

### Parallel path
Computes the minimal graph path for parallel resistance.
Also computes parallel resistance values.
Rather experimental output format, only useful if you want to know how does the shortest graph path, where last graph is 3-edge-colorable looks like

### Serial path
Computes the minimal graph path for serial resistance.
Also computes serial resistance values.
Rather experimental output format, only useful if you want to know how does the shortest graph path, where last graph is 3-edge-colorable looks like


### Kaszonyi function original
First checks whether graph is 3-edge-colorable. 
For graphs that are not 3-edge-colorable computes the Kaszonyi function values for every edge of given graphs according to the original definition by L. Kaszonyi.

### Kaszonyi function times three
Computes the Kaszonyi function values for every edge of given graphs according to the definition by M.Zubčák in his bachelor thesis. 
For graphs that are not 3-edge-colorable the values is three times greater than value of the original Kaszonyi function. 

### Output directory
Place, where results are stored.

## Input file format
The input file has to contain these three parts:
- graph class information (optional)
- graph class size
- cubic graphs of given size in adjacency lists format

### Graph class information (optional)
In the beginning of a file you can include some information out the graph class located in the file using curly brackets.
You can include multiple lines of information but each of them has to start and end with curly brackets.
The output file will then begin with the information you provided in curly brackets.
This part is optional and can be omitted.
Example:

```
{This is a class of cubic graphs}
{it contains cubic graphs}
{}
{previous line is empty but it had to contain curly brackets so we can still type information here}
```

### Graph class size
Follow the graph class information (or beginning the file with), graph size of graphs in the file has to be provided.
For example, lets say you have a class of cubic graphs where every graph has 8 vertices. So you begin (or continue after information) the file with 8
Example:
```
8
```

Do note, every graph in the file must have the same size

### cubic graphs of given size in adjacency lists format
Following the graph class size number, you now can type any amount of graphs you want.
Each graph has to be in adjacency list format, needs to be cubic and only proper edges are allowed.
Graphs are divided by empty line.
For example, we will continue our file with five different graphs, each of them having 8 vertices.
Example:

```
5 6 7
2 3 4
1 3 4
1 2 5
1 2 6
0 3 7
0 4 7
0 5 6

5 6 7
2 3 4
1 3 5
1 2 6
1 5 7
0 2 4
0 3 7
0 4 6

4 5 6
2 3 4
1 3 5
1 2 6
0 1 7
0 2 7
0 3 7
4 5 6

5 6 7
2 3 4
1 5 6
1 5 7
1 6 7
0 2 3
0 2 4
0 3 4

4 5 7
2 3 4
1 5 6
1 5 7
0 1 6
0 2 3
2 4 7
0 3 6
```

The input file is then the concatenation of all three parts.

## Output file format
All files are stored in the output directory you choose before starting the computation.
The name of the output file will be "Input name" + "Format shortcut" where format shortcut is one of these, depending on used format:
- .res (parallel and serial resistance values)
- .ppath (parallel path)
- .spath (sequential path)
- .kas (Kaszonyi function original)
- .3kas (Kaszonyi function times three)

### Output format for parallel and serial resistance values
The output file will include (in following order):
- information from input file (if provided)
- size of every graph
- list of graphs. For every graph is provided:
  - SERIAL RESISTANCE: s
  - PARALLEL RESISTANCE: p
  - graph in adjacency lists format

s,p are values of serial and parallel resistance for given graph, if no parallel resistance exists for the graph, p = N/A.

The example is based on the file used as example for the input file format, but only first two graphs and the information part is also omitted:
```
8
SERIAL RESISTANCE: 0
PARALLEL RESISTANCE: 0
5 6 7
2 3 4
1 3 4
1 2 5
1 2 6
0 3 7
0 4 7
0 5 6

SERIAL RESISTANCE: 0
PARALLEL RESISTANCE: 0
5 6 7
2 3 4
1 3 5
1 2 6
1 5 7
0 2 4
0 3 7
0 4 6
```

### Output format for parallel/serial path
Different graphs from the input file are divided by:
```
############
#NEXT GRAPH#
############
```

For every graph there is written a graph path -- a list of graphs, each of them in adjacency list format.
Also, every graph in graph path has:
- depth (number of edges that has to be suppressed in order to obtain this graph from the original graph)
- unique id
- parent graph id

### Output format for Kaszonyi function original
The output file will include (in following order):
- information from input file (if provided)
- size of every graph
- list of graphs. For every graph is provided:
  - a notice if the graph is 3-edge-colorable
  - graph in adjacency lists format
  - Kaszonyi value for every edge, but only if the graph is not 3-edge-colorable

The example is based on the file used as example for the input file format, but only first two graphs and the information part is also omitted:
```
8
3-EDGE-COLORABLE GRAPH
5 6 7
2 3 4
1 3 4
1 2 5
1 2 6
0 3 7
0 4 7
0 5 6

3-EDGE-COLORABLE GRAPH
5 6 7
2 3 4
1 3 5
1 2 6
1 5 7
0 2 4
0 3 7
0 4 6
```

### Output format for Kaszonyi function times three
The output file will include (in following order):
- information from input file (if provided)
- size of every graph
- list of graphs. For every graph is provided:
  - graph in adjacency lists format
  - Kaszonyi value for every edge

The example is based on the file used as example for the input file format, but only first two graphs and the information part is also omitted:
```
8
5 6 7
2 3 4
1 3 4
1 2 5
1 2 6
0 3 7
0 4 7
0 5 6
Kaszonyi values:
(0, 5): 2
(0, 6): 2
(0, 7): 2
(1, 2): 2
(1, 3): 2
(1, 4): 2
(2, 3): 2
(2, 4): 2
(3, 5): 0
(4, 6): 0
(5, 7): 2
(6, 7): 2

5 6 7
2 3 4
1 3 5
1 2 6
1 5 7
0 2 4
0 3 7
0 4 6
Kaszonyi values:
(0, 5): 2
(0, 6): 1
(0, 7): 1
(1, 2): 1
(1, 3): 1
(1, 4): 2
(2, 3): 1
(2, 5): 2
(3, 6): 4
(4, 5): 1
(4, 7): 2
(6, 7): 1
```
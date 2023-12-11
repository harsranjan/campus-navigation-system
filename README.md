# Campus Navigation System

## Overview

The Campus Navigation System is a C program that utilizes the Floyd-Warshall algorithm to find the optimal route and total distance between two locations on a campus map. The program reads location and route information from an external file, allowing users to define the campus layout dynamically.

## Features

- **Dynamic Campus Definition**: The program allows users to define campus locations and routes by reading instructions from an external file ("functions.txt").
- **Optimal Route Calculation**: It employs the Floyd-Warshall algorithm to find the shortest path and total distance between any two locations on the campus.
- **User-Friendly Interface**: Users can input source and destination location indices to get the optimal route and total distance.

## How to Use

1. **Define Campus Layout**: Edit the "functions.txt" file to add locations and routes. Follow the format specified in the file for adding locations and routes.
    - Example:
        ```c
        addLocation(&graph, 0, "Main Gate")
        addLocation(&graph, 1, "Mac")
        addRoute(&graph, 0, 1, 5)
        ```

2. **Compile and Run**: Compile the program and run the executable. You will be prompted to enter the source and destination location indices.

3. **View Results**: The program will display the optimal route and total distance between the selected source and destination locations.

## Location Indices

The program uses numeric indices to represent different locations on the campus. Here is the mapping of indices to locations:

- 0: Main Gate
- 1: Mac
- 2: Library
- 3: Gandhi Chowk
- 4: 11th Block
- 5: Food Court

## File Structure

- **main.c**: Contains the main program logic, user interface, and the Floyd-Warshall algorithm implementation.
- **functions.txt**: External file for defining locations and routes. Edit this file to customize the campus layout.
- **README.md**: The documentation file you are currently reading.

## Compilation

Compile the program using a C compiler. For example:

```bash
gcc main.c -o campus_navigation

// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
public:
    maze(ifstream &fin);
    void print(int,int,int,int);
    bool isLegal(int i, int j);

    void setMap(int i, int j, int n);
    int getMap(int i, int j) const;
    void mapMazeToGraph(graph &g);
    bool findPathRecursive(graph&, int, int);

private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    int numNodes;

    stack<int> path;
    matrix<bool> value;
    matrix<int> map;      // Mapping from maze (i,j) values to node index values
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
    map[i][j] = n;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
    return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;

    char x;

    value.resize(rows,cols);
    for (int i = 0; i <= rows-1; i++)
        for (int j = 0; j <= cols-1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    map.resize(rows,cols);
    numNodes = 0;
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;

    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");

    for (int i = 0; i <= rows-1; i++)
    {
        for (int j = 0; j <= cols-1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
            if (i == currI && j == currJ)
                cout << "+";
            else
            if (value[i][j])
                cout << " ";
            else
                cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");

    return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
    // First add all the nodes to the graph
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (isLegal(i, j))
            {
                g.addNode(1);
                setMap(i, j, numNodes);
                numNodes++;
            }
        }
    }

    // Now we add all the edges
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Check if the position is valid
            if (isLegal(i, j))
            {
                // If so, check that the position to the top and to the
                // left is valid. If valid, add edge between current and
                // previous node
                if (i != 0 && value[i-1][j])
                    g.addEdge(i-1, j, 1);
                if (j != 0 && value[i][j-1])
                    g.addEdge(i, j-1, 1);
            }
        }
    }
}

bool maze::findPathRecursive(graph& g, int start, int goal)
{
   // If we are at the goal position (base case) return true
   if (start == goal)
   {
       path.push(start);
       return true;
   }
   else
   {
       // Set current position as visited
       g.visit(start);
       // Init finding path as false
       bool foundPath = false;
       // Loop for all nodes
       for (int i = start; i < numNodes; i++) {
           // If not visited, do DFS
           if (!g.isVisited(i))
           {
                foundPath = findPathRecursive(g, start, goal);
           }
           // Otherwise break from loop
           if (foundPath) break;
       }
       // If current position is a path, add it to path stack
       if (foundPath)
       {
           std::cout << start << '\n';
           path.push(start);
       }
       return foundPath;
   }
}

int main()
{
    char x;
    ifstream fin;

    // Read the maze from the file.
    string fileName = "/home/pineapple/algo_ws/proj5/maze1.txt";

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        graph g;
        while (fin && fin.peek() != 'Z')
        {
            maze moo(fin);
            moo.mapMazeToGraph(g);
            g.printEdges();
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }


}
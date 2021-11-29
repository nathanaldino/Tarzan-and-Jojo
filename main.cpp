#include<adjlist.h>
#include<iostream>
#include<fstream>

using namespace std;

int main() {
    
    //intialize variables
    vector< vector<Vertex> > maze;
    int rows, cols;
    int tarzanrow, tarzancol;
    int numvertices = 1;

    //readfile
    fstream input;
    input.open("input.txt");
    input >> rows >> cols;
    input >> tarzanrow >> tarzancol;
    
    //test
    cout << rows << cols << endl;
    cout << tarzanrow << tarzancol << endl;

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            string temp;
            input >> temp;
            Vertex newvertex;
            if (temp.compare("X") == 0) {
                maze[i][j] = newvertex;
            }
            else {
                newvertex = Vertex(numvertices);
                maze[i][j] = newvertex;
            }
        }
    }
    input.close();

    AdjList graph(numvertices);

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            if(maze[i][j].getid() == -1) 
                continue;
            
            
        }
    }


}

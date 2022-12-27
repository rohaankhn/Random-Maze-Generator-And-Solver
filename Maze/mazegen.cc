#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class cell {
    private:
        string content;
        string rightWall, downWall, leftWall, upWall;

    public:
        cell() {
            content = "   ";
            rightWall = leftWall = "|";
            downWall = upWall = "---";
        }
        string getRightWall() { return rightWall; }
        string getDownWall() { return downWall; }
        string getLeftWall() { return leftWall; }
        string getUpWall() { return upWall; }
        string getContent() { return content; }
        void setRightWall(string s) { rightWall = s; }
        void setDownWall(string s) { downWall = s; }
        void setLeftWall(string s) { leftWall = s; }
        void setUpWall(string s) { upWall = s; }
        void setContent(string s) { content = s; }

};

class maze {
    private:
        int rows, columns;
        vector< vector<cell> > grid;

    public:
        maze(int rows, int columns) {
            this->rows = rows;
            this->columns = columns;
            grid.resize(rows);
            for (int i = 0; i < rows; i++)
                grid[i].resize(columns);

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    grid[i][j] = cell();

            
        }

        void generateMaze(int row, int column, int seed) {
            if (row >= rows || column >= columns || row < 0 || column < 0 || grid[row][column].getContent() != "   ") 
                return;
            else {
                grid[row][column].setContent(" . ");
                srand(seed);
                int direction = rand() % 4;
                for(int i = 0; i < 4; i++) {
                    switch((direction + i) % 4) {
                        case 0: //right
                            if (column + 1 < columns && grid[row][column + 1].getContent() == "   ") {
                                grid[row][column].setRightWall(" ");
                                grid[row][column + 1].setLeftWall(" ");
                                generateMaze(row, column + 1, rand());
                                break;
                            }
                        case 1: //down
                            if (row + 1 < rows && grid[row + 1][column].getContent() == "   ") {
                                grid[row][column].setDownWall("   ");
                                grid[row + 1][column].setUpWall("   ");
                                generateMaze(row + 1, column, rand());
                                break;
                            }
                        case 2: //left
                            if (column - 1 >= 0 && grid[row][column - 1].getContent() == "   ") {
                                grid[row][column].setLeftWall(" ");
                                grid[row][column - 1].setRightWall(" ");
                                generateMaze(row, column - 1, rand());
                                break;
                            }
                        case 3: //up
                            if (row - 1 >= 0 && grid[row - 1][column].getContent() == "   ") {
                                grid[row][column].setUpWall("   ");
                                grid[row - 1][column].setDownWall("   ");
                                generateMaze(row - 1, column, rand());
                                break;
                            }
                    }
                }
            }
        }

        void resetVisited() {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    grid[i][j].setContent("   ");
        }

        bool solveMaze(int row, int column) {
            if (row >= rows || column >= columns || row < 0 || column < 0 || grid[row][column].getContent() != "   ")
                return false;
            else if (row == rows - 1 && column == columns - 1) {
                grid[row][column].setContent(" . ");
                return true;
            }
            else {
                grid[row][column].setContent(" . ");
                if (grid[row][column].getRightWall() == " " && solveMaze(row, column + 1))
                    return true;
                else if (grid[row][column].getDownWall() == "   " && solveMaze(row + 1, column))
                    return true;
                else if (grid[row][column].getLeftWall() == " " && solveMaze(row, column - 1))
                    return true;
                else if (grid[row][column].getUpWall() == "   " && solveMaze(row - 1, column))
                    return true;
                else {
                    grid[row][column].setContent("   ");
                    return false;
                }
            }
        }

        void printMaze() {
            for (int i = 0; i < rows; i++) {
                for(int k = 0; k < 3; k++) {
                    for(int j = 0; j < columns; j++) {
                        if(i == 0) {
                            if(j == 0) {
                                if(k == 1){
                                    cout << grid[i][j].getLeftWall() << grid[i][j].getContent() << grid[i][j].getRightWall();
                                } else {
                                    if(k == 0)
                                        cout << "+" << grid[i][j].getUpWall() << "+";
                                    else
                                        cout << "+" << grid[i][j].getDownWall() << "+"; 
                                }
                            } else {
                                if(k == 1){
                                    cout << grid[i][j].getContent() << grid[i][j].getRightWall();
                                } else {
                                    if(k == 0)
                                        cout << grid[i][j].getUpWall() << "+";
                                    else
                                        cout << grid[i][j].getDownWall() << "+"; 
                                }
                            }
                        } else {
                            if(j == 0) {
                                if(k == 1)
                                    cout << grid[i][j].getLeftWall() << grid[i][j].getContent() << grid[i][j].getRightWall();
                                else if(k == 2)
                                    cout << "+" << grid[i][j].getDownWall() << "+"; 
                            } else {
                                if(k == 1)
                                    cout << grid[i][j].getContent() << grid[i][j].getRightWall();
                                else if(k == 2)
                                        cout << grid[i][j].getDownWall() << "+"; 
                            }
                        }
                    }
                    if(!(i != 0 && k == 0))
                        cout << endl;
                }
            }
        }
};



int main(int argc, char* args[]) {
    if(argc < 3) {
        cout << "Usage: ./mazegen rows columns" << endl;
        return 0;
    } else {
        maze m(atoi(args[1]), atoi(args[2]));
        if(argc < 4) {
            srand(time(0));
            m.generateMaze(0, 0, rand());
        } else 
            m.generateMaze(0, 0, atoi(args[3]));
        
        m.resetVisited();
        m.solveMaze(0, 0);
        m.printMaze();
        return 0;

    }
}
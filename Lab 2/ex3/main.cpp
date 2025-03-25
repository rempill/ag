#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int n = 102;
int maze[n][n];
bool visited[n][n];
int start[2], finish[2];

bool dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] == 1 || visited[x][y]) {
        return false;
    }
    visited[x][y] = true;
    if (x == finish[0] && y == finish[1]) {
        maze[x][y] = 4; // Mark the finish point in the path
        return true;
    }
    if (dfs(x + 1, y) || dfs(x - 1, y) || dfs(x, y + 1) || dfs(x, y - 1)) {
        maze[x][y] = 4; // Mark the path
        return true;
    }
    return false;
}

int main() {
    ifstream fin("maze.txt");
    char s;
    int i=0,j=0;
    fin>>noskipws;
    while (!fin.eof()) {
        fin>>s;
        if (j>101) {
            ++i;
            j=0;
        } else {
            if (s==' ') {
                maze[i][j]=0;
                ++j;
            }
            else if (s=='S') {
                start[0]=i;
                start[1]=j;
                maze[i][j]=2;
                ++j;
            }
            else if (s=='F') {
                finish[0]=i;
                finish[1]=j;
                maze[i][j]=3;
                ++j;
            }
            else {
                maze[i][j]=1;
                ++j;
            }
        }
    }
    if (dfs(start[0],start[1])) {
        cout<<"Path found!"<<endl;
    } else {
        cout<<"no path found!"<<endl;
    }
    for (int k=0;k<=i;++k) {
        for (int l=0;l<=j;++l) {
            if (maze[k][l] == 4) {
                cout << "* "; // Mark the path with '*'
            } else if (maze[k][l] == 2) {
                cout << "S "; // Start point
            } else if (maze[k][l] == 3) {
                cout << "F "; // Finish point
            } else if (maze[k][l] == 1) {
                cout << "1 "; // Wall
            } else {
                cout << "  "; // Empty space
            }
        }
        cout << endl;
    }
    return 0;
}
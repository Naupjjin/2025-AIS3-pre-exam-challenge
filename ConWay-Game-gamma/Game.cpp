#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

class CellularAutomaton {
private:
    int rows, cols;
    vector<vector<int>> grid;

public:
    CellularAutomaton(int r, int c) : rows(r), cols(c), grid(r, vector<int>(c)) {
        srand(time(0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int rnd = rand() % 10;
                grid[i][j] = (rnd < 5) ? 0 : (rnd < 9) ? 1 : 2;
            }
        }
    }

    int count_alive_neighbors(int x, int y) {
        int neighbors[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                               {0, -1},         {0, 1},
                               {1, -1}, {1, 0}, {1, 1}};
        int count = 0;
        for (auto& n : neighbors) {
            int nx = x + n[0], ny = y + n[1];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 1) {
                count++;
            }
        }
        return count;
    }

    void update() {
        vector<vector<int>> new_grid = grid;
        for (int x = 0; x < rows; ++x) {
            for (int y = 0; y < cols; ++y) {
                int alive_neighbors = count_alive_neighbors(x, y);
                if (grid[x][y] == 1) { // Alive
                    if (!(alive_neighbors == 2 || alive_neighbors == 3)) {
                        new_grid[x][y] = (alive_neighbors == 1 || alive_neighbors == 4) ? 2 : 0;
                    }
                } else if (grid[x][y] == 2) { // Sleeping
                    if (alive_neighbors == 3 || alive_neighbors == 4) {
                        new_grid[x][y] = 1;
                    }
                } else { // Dead
                    if (alive_neighbors == 2 || alive_neighbors == 3) {
                        new_grid[x][y] = 2;
                    } else if (alive_neighbors == 4 || alive_neighbors == 5) {
                        new_grid[x][y] = 1;
                    }
                }
            }
        }
        grid = new_grid;
    }

    void print_grid() {
        system("clear");
        for (const auto& row : grid) {
            for (int cell : row) {
                cout << (cell == 0 ? " ." : cell == 1 ? " O" : " ~");
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    int rows = 5, cols = 5;
    CellularAutomaton ca(rows, cols);

    for (int i = 0; i < 20; ++i) {
        ca.print_grid();
        ca.update();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}
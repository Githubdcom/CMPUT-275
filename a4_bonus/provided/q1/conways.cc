#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Board {
  int rows;
  int cols;
  char **grid;

  void clear() {
    if (grid == nullptr) return;
    for (int r = 0; r < rows; ++r) {
      delete[] grid[r];
    }
    delete[] grid;
    grid = nullptr;
  }

  int countNeighbors(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        if (dr == 0 && dc == 0) continue;
        int nr = r + dr;
        int nc = c + dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
          if (grid[nr][nc] == 'O') {
            ++count;
          }
        }
      }
    }
    return count;
  }

public:
  Board() : rows(0), cols(0), grid(nullptr) {}

  ~Board() {
    clear();
  }

  void read() {
    string line;
    char **newGrid = nullptr;
    int newRows = 0;
    int newCols = -1;

    while (getline(cin, line)) {
      if (line == "x") break;
      if (newCols == -1) newCols = static_cast<int>(line.size());
      if (static_cast<int>(line.size()) != newCols) {
        clear();
        return;
      }

      char **tmp = new char*[newRows + 1];
      for (int i = 0; i < newRows; ++i) tmp[i] = newGrid[i];

      tmp[newRows] = new char[newCols];
      for (int c = 0; c < newCols; ++c) {
        tmp[newRows][c] = line[c];
      }

      delete[] newGrid;
      newGrid = tmp;
      ++newRows;
    }

    clear();
    grid = newGrid;
    rows = newRows;
    cols = newCols == -1 ? 0 : newCols;
  }

  void print() const {
    for (int i = 0; i < cols + 2; ++i) cout << '=';
    cout << '\n';
    for (int r = 0; r < rows; ++r) {
      cout << '|';
      for (int c = 0; c < cols; ++c) {
        cout << grid[r][c];
      }
      cout << "|\n";
    }
    for (int i = 0; i < cols + 2; ++i) cout << '=';
    cout << '\n';
  }

  void step() {
    if (rows == 0 || cols == 0) return;
    char **next = new char*[rows];
    for (int r = 0; r < rows; ++r) {
      next[r] = new char[cols];
      for (int c = 0; c < cols; ++c) {
        int n = countNeighbors(r, c);
        if (grid[r][c] == 'O') {
          next[r][c] = (n < 2 || n > 3) ? '.' : 'O';
        } else {
          next[r][c] = (n == 3) ? 'O' : '.';
        }
      }
    }

    clear();
    grid = next;
    // rows and cols unchanged
  }
};

int main() {
  Board b;
  b.read();

  string cmd;
  while (cin >> cmd) {
    if (cmd == "p") {
      b.print();
    } else if (cmd == "s") {
      b.step();
    }
  }
  return 0;
}
#include <iostream>
#include <string>
using namespace std;

class Board {
  int rows;
  int cols;
  char **grid;

  void clear() {
    if (!grid) return;
    for (int r = 0; r < rows; ++r) delete[] grid[r];
    delete[] grid;
    grid = nullptr;
  }

  static void stripCR(string &s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
  }

  static void rtrimSpaces(string &s) {
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t')) {
      s.pop_back();
    }
  }

  int countNeighbors(int r, int c) const {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        if (dr == 0 && dc == 0) continue;
        int nr = r + dr, nc = c + dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
          if (grid[nr][nc] == 'O') ++count;
        }
      }
    }
    return count;
  }

public:
  Board() : rows(0), cols(0), grid(nullptr) {}
  ~Board() { clear(); }

  void readGrid() {
    string line;
    char **newGrid = nullptr;
    int newRows = 0;
    int newCols = -1;

    while (getline(cin, line)) {
      stripCR(line);
      rtrimSpaces(line);

      if (line == "x") break;
      if (line.empty()) continue;

      if (newCols == -1) newCols = (int)line.size();
      if ((int)line.size() != newCols) {
        for (int i = 0; i < newRows; ++i) delete[] newGrid[i];
        delete[] newGrid;
        clear();
        rows = cols = 0;
        return;
      }

      char **tmp = new char *[newRows + 1];
      for (int i = 0; i < newRows; ++i) tmp[i] = newGrid[i];

      tmp[newRows] = new char[newCols];
      for (int c = 0; c < newCols; ++c) tmp[newRows][c] = line[c];

      delete[] newGrid;
      newGrid = tmp;
      ++newRows;
    }

    clear();
    grid = newGrid;
    rows = newRows;
    cols = (newCols == -1 ? 0 : newCols);
  }

  void print() const {
    for (int i = 0; i < cols; ++i) cout << '|';
    cout << '\n';

    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) cout << grid[r][c];
      cout << '\n';
    }

    for (int i = 0; i < cols; ++i) cout << '|';
    cout << '\n';
  }

  void step() {
    if (rows == 0 || cols == 0) return;

    char **next = new char *[rows];
    for (int r = 0; r < rows; ++r) {
      next[r] = new char[cols];
      for (int c = 0; c < cols; ++c) {
        int n = countNeighbors(r, c);
        if (grid[r][c] == 'O') next[r][c] = (n == 2 || n == 3) ? 'O' : '.';
        else next[r][c] = (n == 3) ? 'O' : '.';
      }
    }

    clear();
    grid = next;
  }
};

int main() {
  Board b;
  b.readGrid();

  string line;
  while (getline(cin, line)) {
    // commands are only 's' and 'p' (possibly combined like "spsp")
    for (char ch : line) {
      if (ch == 's') b.step();
      else if (ch == 'p') b.print();
    }
  }
  return 0;
}
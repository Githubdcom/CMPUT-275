#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

struct Maze {
    char **grid;
    int rows;
    int cols;
    int player_x;
    int player_y;
    int start_x;
    int start_y;
};

static char *copyString(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }

    char *copy = malloc((len + 1) * sizeof(char));
    if (copy == NULL) {
        return NULL;
    }

    for (int i = 0; i <= len; i++) {
        copy[i] = s[i];
    }

    return copy;
}

static void freeGrid(char **grid, int rows) {
    if (grid == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

static int inBounds(struct Maze *m, int x, int y) {
    return x >= 0 && x < m->cols && y >= 0 && y < m->rows;
}

static void locateTeleporter(struct Maze *m, int x, int y, char digit, int *tx, int *ty) {
    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->cols; c++) {
            if ((r != y || c != x) && m->grid[r][c] == digit) {
                *tx = c;
                *ty = r;
                return;
            }
        }
    }
    *tx = x;
    *ty = y;
}

struct Maze *readMaze() {
    char buffer[1000];
    char **grid = NULL;
    int rows = 0;
    int cols = -1;
    int startCount = 0;
    int goalCount = 0;
    int startX = -1;
    int startY = -1;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\0') {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        int len = (int)strlen(buffer);
        if (cols == -1) {
            cols = len;
        } else if (len != cols) {
            freeGrid(grid, rows);
            return NULL;
        }

        char *row = copyString(buffer);
        if (row == NULL) {
            freeGrid(grid, rows);
            return NULL;
        }

        char **newGrid = realloc(grid, (rows + 1) * sizeof(char *));
        if (newGrid == NULL) {
            free(row);
            freeGrid(grid, rows);
            return NULL;
        }
        grid = newGrid;
        grid[rows] = row;

        for (int c = 0; c < cols; c++) {
            if (grid[rows][c] == 'S') {
                startCount++;
                startX = c;
                startY = rows;
            } else if (grid[rows][c] == 'G') {
                goalCount++;
            }
        }

        rows++;
    }

    if (rows == 0 || startCount != 1 || goalCount < 1) {
        freeGrid(grid, rows);
        return NULL;
    }

    struct Maze *m = malloc(sizeof(struct Maze));
    if (m == NULL) {
        freeGrid(grid, rows);
        return NULL;
    }

    m->grid = grid;
    m->rows = rows;
    m->cols = cols;
    m->player_x = startX;
    m->player_y = startY;
    m->start_x = startX;
    m->start_y = startY;

    return m;
}

struct Pos makeMove(struct Maze *m, char direction) {
    struct Pos p;

    int dx = 0;
    int dy = 0;

    if (direction == 'n') {
        dy = -1;
    } else if (direction == 's') {
        dy = 1;
    } else if (direction == 'e') {
        dx = 1;
    } else if (direction == 'w') {
        dx = -1;
    }

    int nx = m->player_x + dx;
    int ny = m->player_y + dy;

    if (!inBounds(m, nx, ny) || m->grid[ny][nx] == 'X') {
        p.x = m->player_x;
        p.y = m->player_y;
        return p;
    }

    m->player_x = nx;
    m->player_y = ny;

    if (m->grid[ny][nx] >= '0' && m->grid[ny][nx] <= '9') {
        int tx, ty;
        locateTeleporter(m, nx, ny, m->grid[ny][nx], &tx, &ty);
        m->player_x = tx;
        m->player_y = ty;
        nx = tx;
        ny = ty;
    }

    while (m->grid[ny][nx] == 'I') {
        int nextx = nx + dx;
        int nexty = ny + dy;

        if (!inBounds(m, nextx, nexty) || m->grid[nexty][nextx] == 'X') {
            break;
        }

        nx = nextx;
        ny = nexty;
        m->player_x = nx;
        m->player_y = ny;

        if (m->grid[ny][nx] >= '0' && m->grid[ny][nx] <= '9') {
            int tx, ty;
            locateTeleporter(m, nx, ny, m->grid[ny][nx], &tx, &ty);
            m->player_x = tx;
            m->player_y = ty;
            nx = tx;
            ny = ty;
        }
    }

    if (m->grid[ny][nx] == 'G') {
        p.x = -1;
        p.y = -1;
    } else {
        p.x = m->player_x;
        p.y = m->player_y;
    }

    return p;
}

void reset(struct Maze *m) {
    m->player_x = m->start_x;
    m->player_y = m->start_y;
}

void printMaze(struct Maze *m) {
    for (int i = 0; i < m->cols + 2; i++) {
        printf("=");
    }
    printf("\n");

    for (int r = 0; r < m->rows; r++) {
        printf("|");
        for (int c = 0; c < m->cols; c++) {
            if (r == m->player_y && c == m->player_x) {
                printf("P");
            } else {
                printf("%c", m->grid[r][c]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < m->cols + 2; i++) {
        printf("=");
    }
    printf("\n");
}

struct Maze *destroyMaze(struct Maze *m) {
    if (m == NULL) {
        return NULL;
    }

    freeGrid(m->grid, m->rows);
    free(m);
    return NULL;
}
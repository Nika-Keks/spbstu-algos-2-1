#include <stdio.h>
#include "struct.h"
#define N 8

int Check_cell(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
//a function that checks if the cell with x and y coordinates belongs to the N * N board

void printSolution(int sol[N][N])
{
    printf("Solution matrix:\n 0 - the initial position of the knight\n -1 - cells in which the knight does not appear\n the sequence of moves is marked with numbers in the cells\n\n");
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}
//a function that prints the final chessboard showing the knight's move sequence


int Min_Steps_Count_To_Reach_Target(int knight_pos_x, int knight_pos_y, int target_pos_x, int target_pos_y)
{
    int dx[8] = { -2, -1, 1, 2, -2, -1, 1, 2 }; //all pairwise coordinates to which the knight can move
    int dy[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    struct cell cells[1000];
    int next = 1;
    int prev = 1;

    struct cell temp; //current cell

    temp.x = knight_pos_x; //x start coordinate
    temp.y = knight_pos_y; //y start coordinate
    temp.dist = 0;          //number of knight moves

    cells[prev] = temp;
    prev++;

    struct cell temp_next; //next cell

    int x, y;
    int visited_cells[N + 1][N + 1]; //a matrix of cells in which we mark visited cells

    for (int i = 1; i <= N; i++) //initially reset all cells (the knight has not been to them)
    {
        for (int j = 1; j <= N; j++)
        {
            visited_cells[i][j] = 0;
        }
    }

    visited_cells[knight_pos_x][knight_pos_y] = 1; //the cell on which the knight is originally located, mark that he was on it

    while (next != prev)
    {
        temp_next = cells[next];
        next++;

        // if current cell is equal to target cell then return its distance
        if (temp_next.x == target_pos_x && temp_next.y == target_pos_y)
        {
            printf("The minimum number of moves the knight to reach the target: %d\n\n", temp_next.dist);
            return temp_next.dist;
        }


        //try possible moves of the knight from the current cell
        for (int i = 0; i < 8; i++)
        {
            x = temp_next.x + dx[i];
            y = temp_next.y + dy[i];

            if (Check_cell(x - 1, y - 1, N) == 1 && visited_cells[x][y] != 1) //if after the move the knight is inside the board and he has not been to this cell yet
            {
                visited_cells[x][y] = 1; //put the flag on the cell that he was here
                temp.x = x;
                temp.y = y;
                temp.dist = temp_next.dist + 1; //increase the number of moves by 1
                cells[prev] = temp;
                prev++;
            }

        }
    }
}
//a function that returns the minimum number of knight moves it takes to reach the target


int Find_And_Print_Shortest_Path(int knight_pos_x, int knight_pos_y, int target_pos_x, int target_pos_y, int step_count)
{
    int solution_matrix[N][N];

    /* Initialization of solution matrix */
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            solution_matrix[x][y] = -1;

    int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    
    solution_matrix[knight_pos_x][knight_pos_y] = 0; //the cell on which the knight is originally located

    /* Knight starts from cell (0,0) and explores all paths using Find_Shortest_Path() */
       
    if (Find_Shortest_Path(knight_pos_x, knight_pos_y, target_pos_x, target_pos_y, 1, solution_matrix, dx, dy, step_count) == 0)
    {
        printf("Solution does not exist");
        return 0;
    }
    else
        printSolution(solution_matrix);

    return 1;
}

int Find_Shortest_Path(int x, int y, int target_pos_x, int target_pos_y, int current_step_count, int solution_matrix[N][N], int dx[N], int dy[N], int step_count)
{
    int next_x, next_y;

    //if the knight has reached the target and the number of his moves is equal to the minimum
    if ((x == target_pos_x) && (y == target_pos_y) && (current_step_count == step_count + 1))
        return 1;

    //try possible moves of the knight from the current cell
    for (int i = 0; i < 8; i++)
    {
        next_x = x + dx[i];
        next_y = y + dy[i];
        if (Check_cell(next_x, next_y, solution_matrix) && solution_matrix[next_x][next_y] == -1)
        {
            solution_matrix[next_x][next_y] = current_step_count;
            if (Find_Shortest_Path(next_x, next_y, target_pos_x, target_pos_y, current_step_count + 1, solution_matrix, dx, dy, step_count) == 1)
                return 1;
            else
                solution_matrix[next_x][next_y] = -1; // backtracking
        }
    }

    return 0;
}
//recursive function to find the shortest path


int main()
{
    int knight_pos_x = 2;
    int knight_pos_y = 0;
    int target_pos_x = 4;
    int target_pos_y = 7;
    int step_count = 0;

    step_count = Min_Steps_Count_To_Reach_Target(knight_pos_x + 1, knight_pos_y + 1, target_pos_x + 1, target_pos_y + 1);
    Find_And_Print_Shortest_Path(knight_pos_x, knight_pos_y, target_pos_x, target_pos_y, step_count);
    return 0;
}
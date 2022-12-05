#include <stdio.h>
#include "struct.h"
#include <locale.h>
#define N 8

int Check_cell(int x, int y)
{
    return (x >= 0 && x < N&& y >= 0 && y < N);
}


void printSolution(int sol[N][N])
{
    printf(" 0 - start position\n");
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}


int Min_Steps_Count_To_Reach_Target(int knight_pos_x, int knight_pos_y, int target_pos_x, int target_pos_y)
{
    int dx[8] = { -2, -1, 1, 2, -2, -1, 1, 2 }; 
    int dy[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    struct cell cells[1000];
    int next = 1;
    int prev = 1;

    struct cell temp;

    temp.x = knight_pos_x; 
    temp.y = knight_pos_y; 
    temp.dist = 0;        

    cells[prev] = temp;
    prev++;

    struct cell temp_next; 

    int x, y;
    int visited_cells[N + 1][N + 1]; 

    for (int i = 1; i <= N; i++) 
    {
        for (int j = 1; j <= N; j++)
        {
            visited_cells[i][j] = 0;
        }
    }

    visited_cells[knight_pos_x][knight_pos_y] = 1; 

    while (next != prev)
    {
        temp_next = cells[next];
        next++;

       
        if (temp_next.x == target_pos_x && temp_next.y == target_pos_y)
        {

            printf("Minimum number of moves: %d\n\n", temp_next.dist);
            return temp_next.dist;
        }


      
        for (int i = 0; i < 8; i++)
        {
            x = temp_next.x + dx[i];
            y = temp_next.y + dy[i];

            if (Check_cell(x - 1, y - 1, N) == 1 && visited_cells[x][y] != 1)
            {
                visited_cells[x][y] = 1; 
                temp.x = x;
                temp.y = y;
                temp.dist = temp_next.dist + 1;
                cells[prev] = temp;
                prev++;
            }

        }
    }
}


int Find_And_Print_Shortest_Path(int knight_pos_x, int knight_pos_y, int target_pos_x, int target_pos_y, int step_count)
{
    int solution_matrix[N][N];

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            solution_matrix[x][y] = -1;

    int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };


    solution_matrix[knight_pos_x][knight_pos_y] = 0; 

    

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

    
    if ((x == target_pos_x) && (y == target_pos_y) && (current_step_count == step_count + 1))
        return 1;

   
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
                solution_matrix[next_x][next_y] = -1; 
        }
    }

    return 0;
}
int main()
{
    int knight_pos_x = 3;
    int knight_pos_y = 0;
    int target_pos_x = 6;
    int target_pos_y = 4;
    int step_count = 0;

    step_count = Min_Steps_Count_To_Reach_Target(knight_pos_x + 1, knight_pos_y + 1, target_pos_x + 1, target_pos_y + 1);
    Find_And_Print_Shortest_Path(knight_pos_x, knight_pos_y, target_pos_x, target_pos_y, step_count);
    return 0;
}

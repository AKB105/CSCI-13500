#include <iostream>
#include <vector>

int main(){

    std::vector<std::vector<int>> grid = {
        { 4, 3, 2, -1 }, 
        { 3, 2, 1, -1 }, 
        {1, 1, -1, -2 }, 
        {-1, -1, -2,-3}
    };

    int negative_counter = 0;
    int num_rows = grid.size();
    int num_col = grid[0].size();

    int row = num_row - 1;
    int col = 0;

    while (row >= 0 && col < num_col){
        if(grid[row][col] < 0){
            negative_counter += (num_col - col);
            row--;
        } else {
            col++;
        }
    }

    std::cout << "output: " << negative_counter << '\n';
    std::cout << "Explanation: There are " << negative_counter <<  " negative number(s) in the matrix." << std::endl;

    return 0;
}
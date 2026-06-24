#include <iostream>
#include <vector>

int main(){

    //Task 0: Create a 3x3 2D array and a 6x6 2D array.
    int little_matrix [3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    int big_matrix [6][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
    };

    //task 1: Diagonal line
    std::cout << "Task 1: Modify the 3x3 and 6x6 matrices so that the upper right side of the diagonal is made of 1s." << std::endl;

    //task 1.1: Identify the anti-diagonal line and then changes values of every 0 in the right side
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (c <= 3 - r - 1) {
                little_matrix[r][c] = 1;
                std::cout << "|" << little_matrix[r][c] << "|";
            } else {
                little_matrix[r][c] = 0;
                std::cout << "|" << little_matrix[r][c] << "|";
            }
        }
        std::cout << std::endl;
    }

    std::cout << '\n';

    //task 1.2: Same procedure for the other array...
    for (int r = 0; r < 6; r++){
        for (int c = 0; c < 6; c++){
            if (c <= 6 - r - 1){
                big_matrix[r][c] = 1;
                std::cout << "|" << big_matrix[r][c] << "|";
            } else {
                big_matrix [r][c] = 0;
                std::cout << "|" << big_matrix[r][c] << "|";
            }
        }
        std::cout << std::endl;
    }
    
    //task 2: Make an X in the arrays made of 1s. 
    std::cout << "\nTask 2: Modify the 3x3 and 6x6 matrices to do an x shape with 1s within them." << std::endl;

    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (c == r || c == 3 - r - 1) {
                little_matrix[r][c] = 1;
                std::cout << "|" << little_matrix[r][c] << "|";
            } else {
                little_matrix[r][c] = 0;
                std::cout << "|" << little_matrix[r][c] << "|";
            }
        }
        std::cout << std::endl;
    }

    std::cout << '\n';

    for (int r = 0; r < 6; r++){
        for (int c = 0; c < 6; c++){
            if (c == r || c == 6 - r - 1){
                big_matrix[r][c] = 1;
                std::cout << "|" << big_matrix[r][c] << "|";
            } else {
                big_matrix [r][c] = 0;
                std::cout << "|" << big_matrix[r][c] << "|";
            }
        }
        std::cout << std::endl;
    }

    std::cout << '\n';

    //task 3: Sum the values in each row, then the values in each column, and then display both of them in a new matrix. Top row is for the sum of rows, bottom row is for the sum of columns.
    std::cout << "Task 3: Sum of rows and sum of columns in a vector displayed as separated rows in another vector." << std::endl;
    //Note: User input was used for testing purposes of different types of matrices with vectors. No actually needed for the assignment's instructions.

    //3.1: Variables declared for specific task
    int rows = 0;
    int cols = 0;
    int vec_values = 0;
    int diagonal_limit = 0;

    std::cout << "Enter number of rows:";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;
    
    //Note: This measures the limit of the diagonal to avoid it reaches out of bound.
    if (rows < cols){
        diagonal_limit = rows;
    } else{
        diagonal_limit = cols;
    }

    std::vector<std::vector<int>> matrix;

    //Note: The for-loop allows the user to create the matrix themselves, by assigning values to each position while at the same time the loop creates new rows according to the user dimensions.
    for(int i = 0; i < rows; i++){

        std::vector<int> new_row_made;

        for(int j = 0; j < cols; j++){
            std::cout << "Enter value for position (" << i << ", " << j << "):";
            std::cin >> vec_values;
            new_row_made.push_back(vec_values);
        }

        matrix.push_back(new_row_made);
    }

    std::cout << "\n";

    //Note: Sizes of rows are modified to avoid errors in the case of rectangular matrices where rows and cols are not equals
    std::vector<std::vector<int>> sum_results(2);
    sum_results[0].resize(rows, 0);
    sum_results[1].resize(cols, 0);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << "|" << matrix[i][j] << "|";

            sum_results[0][i] += matrix[i][j];
            sum_results[1][j] += matrix[i][j]; 
        }
        std::cout << std::endl;
    }

    std::cout << "\n";

    for (int x = 0; x < 2; x++){
        for (int y = 0; y < sum_results[x].size(); y++){
            std::cout << "|" << sum_results[x][y] << "|";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n";

    //Task 4: Sum of the values in the diagonal lines of the vector
    std::cout << "Task 4: Using the matrix from task 3, compute the sum of the values in the diagonal lines, then add both sums together, counting the center value once.\n";

    //4.1: Variable declaration for specific task
    int main_diagonal = 0;
    int anti_diagonal = 0;
    int total_sum = 0;

    for (int k = 0; k < diagonal_limit; k++){
                main_diagonal += matrix[k][k];
                anti_diagonal += matrix[k][cols - k - 1];
    }

    total_sum = main_diagonal + anti_diagonal;

    //Note: The if-statement makes possible to substract the center value IFF the diagonal lines intersect with each other in both square and rectangular matrices of mxn size.
    if ((cols % 2 == 1) && (cols / 2 < diagonal_limit)){
        total_sum -= matrix[cols/2][cols/2];
    }

    std::cout << "The sum of values in the main diagonal is: " << main_diagonal << std::endl;
    std::cout << "The sum of values in the anti-diagonal is: " << anti_diagonal << std::endl;
    std::cout << "The sum of the values in the X shape is: " << total_sum << std::endl;

    return 0;
}
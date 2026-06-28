#include <iostream>

// Reminder: Information about functions is on the specification PDF

void Print2DArray(const int matrix_local[][3], const int matrix_local_rows_total){

    // Function_Start message to terminal
    std::cout << "Initializing function: Print2DArray\n\n";

    // Body of the function. Do your magic!
    //Time complexity: O(n^2) since its a nested loop
    for(int i = 0; i < matrix_local_rows_total; i++){
        std::cout << "[";
        for (int j = 0; j < 3; j++){
            std::cout  << matrix_local[i][j];
            if(j < 2){
                std::cout << "|";
            }
        }
        std::cout << "]\n";
    }

    // Function_End message to terminal
    std::cout << "\nTerminating function: Print2DArray...\n\n";
}

void MatrixAddition(const int matrix_one[][3], const int matrix_one_rows_total,
                    const int matrix_two[][3], const int matrix_two_rows_total)
    {
        // Function_Start message to terminal
        std::cout << "Initializing function: MatrixAddition\n\n";

        //Body of function
        //Check for invalid sizes. If invalid, does an early return with the same function_end message. (This will happen for all functions needed.)
        if (matrix_one_rows_total != matrix_two_rows_total){
            std::cout << "Matrices must be of the same dimensions to be added.";
            std::cout << "\nTerminating function: MatrixAddition...\n\n";
            return ;
        }

        static int sum_result_matrix [3][3];

        //Time complexity: O(n^2), as it runs through every row and column to add values to the result.
        for(int row = 0; row < matrix_one_rows_total; row++){
            std::cout << "[";
            for(int col = 0; col < 3; col++){
                sum_result_matrix[row][col] = matrix_one[row][col] + matrix_two[row][col];
                std::cout << sum_result_matrix[row][col];
                if (col < 2){
                    std::cout << "|";
                }
            }
            std::cout << "]\n";
        }

        // Function_End message to terminal
        std::cout << "\nTerminating function: MatrixAddition...\n\n";
    }

void TransposeMatrix(const int matrix_local[][3], const int matrix_local_rows_total){
    // Function_Start message to terminal
    std::cout << "Initializing function: TransposeMatrix\n\n";

    // body of the function
    //Time Complexity: O (n * m), as the limits of each loop may variate if the matrix is non-square.
    for(int c = 0; c < 3; c++){
        std::cout << "[";
        for(int r = 0; r < matrix_local_rows_total; r++){
            // display resulting matrix
            // if the dimension of the resulting matrix doesn't match the print function, you could do it manually here
            // or modify the parameter of the print function so it doesn't cause errors
            std::cout << matrix_local[r][c];
            if(r < matrix_local_rows_total -1){
                std::cout << "|";
            }
        }
        std::cout << "]\n";
    }

    // Function_End message to terminal 
    std::cout << "\nTerminating function: TransposeMatrix...\n\n";
}

//The function's time complexity here is O(1) since there are no loops.
void Determinant(const int matrix_local[][3], const int size){
    // Function_Start message to terminal
    std::cout << "Initializing function: Determinant\n\n";

    //check for valid dimensions
    //body of the function 
    int determinant = 0;

    //Note: Since the project focuses on matrices of fixed size, the determinant formula of these fixed sizes was hardcoded.
    if (size == 2){
        determinant = (matrix_local[0][0] * matrix_local[1][1]) - (matrix_local[0][1] * matrix_local[1][0]);
    } else if (size == 3){
        //Note-to-self: Oh boy this will be a long one... Brace yourself!!
        determinant =   (matrix_local[0][0]*
                        ((matrix_local[1][1] * matrix_local[2][2]) - 
                        (matrix_local[1][2] * matrix_local[2][1]))) -
                        (matrix_local[0][1]*
                        ((matrix_local[1][0]*matrix_local[2][2]) - 
                        (matrix_local[1][2]*matrix_local[2][0]))) + 
                        (matrix_local[0][2]*
                        ((matrix_local[1][0]*matrix_local[2][1]) - 
                        (matrix_local[1][1]*matrix_local[2][0])));
    } else {
        std::cout << "You want me to find the determinant of a matrix beyond 3x3!? Hell nah.";
        std::cout << "\nTerminating function: Determinant...\n\n";
        return;
    }

    // print the determinant value on the terminal
    std::cout << "The determinant of the matrix is: " << determinant << std::endl;

    // Function_End message to terminal
    std::cout << "\nTerminating function: Determinant...\n\n";
}

void SearchValue(const int matrix_local[][3], const int rows, const int target){
    // Function_Start message to terminal 
    std::cout << "Initializing function: SearchValue\n\n";

    // body of the function
    bool value_found = false; 

    //Time complexity: O(n^2), reason is that it search every cell until the target is found.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < 3; j++){
            // found  or not
            if(matrix_local[i][j] == target){
                value_found = true;
                std::cout << "Target '" << target << "' was found at [" << i << "],[" << j << "]" << std::endl;
            }
        }
    }
    if(!value_found){
    std::cout << "Target was not found in the matrix.\n";
    }

    // Function_End message to terminal
     std::cout << "\nTerminating function: SearchValue...\n\n";
}

void MatrixMultiplication(const int matrix_a[][3], const int matrix_b[][3], 
                          const int rows_a, const int cols_a, 
                          const int rows_b, const int cols_b){
    
    // Function_Start message to terminal
    std::cout << "Initializing function: MatrixMultiplication\n\n";
    
    // check for valid arrays
    if(cols_a != rows_b){
        std::cout << "Matrix Multiplication cannot be performed." << std::endl;
        std::cout << "\nTerminating function: MatrixMultiplication...\n\n";
        return;
    }
    // Body of the function
    static int multiplication_matrix_result[3][3];
    
    // Print resulting matrix
    //Time complexity: O(n^3), as the matrices are mostly square matrices, giving the same limits for all loops.
    for(int row = 0; row < rows_a; row++){
        std::cout << "[";
        for (int col = 0; col < cols_b; col++){
            //Note: Third loop to iterate through, you might've guessed it, each cell holding the calculations of rows and columns.
            for(int cell = 0; cell < cols_a; cell++){
                multiplication_matrix_result[row][col] += matrix_a[row][cell] * matrix_b[cell][col];
            }
            std::cout << multiplication_matrix_result[row][col];
            if(col < 2){
            std::cout << "|";
            }
        }
        std::cout << "]\n";
    }

    // Function_End message to terminal
    std::cout << "\nTerminating function: MatrixMultiplication...\n\n";
}

int main(){
    // Use these two matrices for basic testing.

    int testing_matrix_one[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9},
    };

    int testing_matrix_two[3][3] = {
        {12,65,82},
        {83,2,8},
        {10,96,67}
    };


// Not used in this class, but it is nice to know other ways to find the size of primitive array.
// This method below is similar to how you will find the size of vectors (future material)
    // DO NOT USE IN THIS PROJECT FUNCTION, but you could test it yourselves.
    // int size_row_one = std::size(testing_matrix_one);
    // int size_col_one = std::size(testing_matrix_one[0]);


    // This is a way to find the dimensions of an array without hardcoding values.
    // It dynamically reflects the array's actual declared size, so if you change
    // the array dimensions, the calculation updates automatically.
    //
    // How it works:
    //
    // To find the number of ROWS:
    //   sizeof(testing_matrix_one)      = total bytes of the whole array = 3*9*4 = 108 bytes
    //   sizeof(testing_matrix_one[0])   = total bytes of one row         = 1*9*4 =  36 bytes
    //   108 / 36 = 3 rows
    
    int size_row_one = sizeof(testing_matrix_one)/sizeof(testing_matrix_one[0]);

    // To find the number of COLUMNS:
    //   sizeof(testing_matrix_one[0])      = total bytes of one row          = 1*9*4 = 36 bytes
    //   sizeof(testing_matrix_one[0][0])   = total bytes of one element(int) = 1*4   =  4 bytes
    //   36 / 4 = 9 cols
    
    int size_col_one = sizeof(testing_matrix_one[0])/sizeof(testing_matrix_one[0][0]);

    std::cout << "row: " << size_row_one<< " col: " << size_col_one<< std::endl << std::endl;

    Print2DArray(testing_matrix_one, size_row_one);

    MatrixAddition(testing_matrix_one, 3, testing_matrix_two, 3);

    TransposeMatrix(testing_matrix_one, size_row_one);

    Determinant(testing_matrix_two, 3);

    SearchValue(testing_matrix_one, 3, 2);

    MatrixMultiplication(testing_matrix_one, testing_matrix_two, size_row_one, size_col_one, 3, 3);

    return 0; 
}
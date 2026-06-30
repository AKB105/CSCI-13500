#include <iostream>
#include <vector>

//Note: Time complexity of this function is O(n), as the time might increase n times due to the for-loop using vector data, that may be n sized, as limit.
//Note 2: Space complexity is O(1), for no extra memory is used for the function to work, vector data already exist out of the function.
void removeCopies(std::vector<int>& data){

    // The vector is sorted in non-decreasing order.
    // Remove all duplicate values in-place so that
    // each value appears exactly once.
    //
    // Do not create another vector.
    // Modify the vector named "data" directly.
    //
    // Maybe two-pointer method? Hmm?
    // Hint: resize() function

    if(data.size() == 0){
        std::cout << "Data list in server is empty. Nothing to remove.\n";
        return;
    }

    int rewrite_index = 1;

    for (int i = 1; i < data.size(); i++){
        if(data[i] != data[rewrite_index -1]){
            data[rewrite_index] = data[i];
            rewrite_index++;
        }
    }
    data.resize(rewrite_index);
    std::cout << "\n\nERROR: Server data list should be as follow: \n";

}

//Note: Time complexity of this function is O(n), Because although there are two for-loops, the second one runs in a linear value of 26, thus running in O(26) = O(1).
//      Then, O(n) + O(1) = O(1n) = O(n), as big O notation ignore constant values.
//Note 2: Space complexity of this function is O(1), because the memory of vector alphabet is of a fixed size of 26, that is O(26), in other words, O(1).
void isAnagram(std::string officer_name, std::string spy_name){

    // Write code to see if the spy name is an anagram of the officer name 
    // Maybe a vector of size 26? Hmm?

    //Note: Easy way to keep track of the name of officer and the spy name that was entered. Also to know the function has begun properly.
    std::cout << "\nOfficer name is: " << officer_name << "\nThe spy name entered was: " << spy_name << std::endl;

    if(officer_name.length() != spy_name.length()){
        std::cout << "\n\nIMPOSTER!! IMPOSTER!! " << spy_name << " might be an imposter.\n\n";
        return;
    }

    std::vector<int> alphabet(26,0);

    for(int i = 0; i < officer_name.length(); i++){
        alphabet[officer_name[i] - 'a']++;
        alphabet[spy_name[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++){
        if (alphabet[i] != 0){
            std::cout << "IMPOSTER!! IMPOSTER!! " << spy_name << " might be an imposter.\n\n";
            return;
        }
    }

    std::cout << "No imposter detected!" << std::endl;

}

int main(){

    /*Use other test cases to make sure you program works*/
    std::vector<int> server = {1,1,2,2,2,3,3,4,5,6,6,6};

    /*Print out the original server vector before function called*/
     for (auto data : server){
        std::cout << data << " "; // 1,1,2,2,2,3,3,4,5,6,6,6
    }

    removeCopies(server);
    
    /*Print out the modification of the server vector after function called*/
    for (auto data : server){
        std::cout << data << " ";
    }

    std::cout << std::endl;

    /****************************TEST ANAGRAM*************************************/

    isAnagram("syeda", "aysed"); // No imposter detected!
    isAnagram("angelo", "annabeth"); // IMPOSTER! IMPOSTER!

    return 0;

}

//Overall time complexity of the program: O(n) + O(n) = O(n)
//Overall space complexity of the program: O(1) + O(1) = O(1)
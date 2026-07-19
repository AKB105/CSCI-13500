#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

//Note: Function to check if a punctuation mark is attached to a word, if so, the loop will erase the punctuation 
//from the hightlighted copy of the word, so that when is compared, it can be changed.
std::string IgnorePunctuationInWord(std::string word){
    for(int i=0; i < word.length(); i++){
         if(std::ispunct(static_cast<unsigned char>(word[i])) && word[i] != '\''){ //Note: We keep an eye for apostrophe because it may appear
                                                                                   //at the middle of a word.
             word.erase(i, 1);
             i--;
         } else{
             //Note: Reads a capitalized version of the word to compare so that the program is fully case insensitive.
             word[i] = std::toupper(static_cast<unsigned char>(word[i]));
         }
    }
    return word;
}

int main(){
    //1- Create variables
    std::string user_file = "";
    std::string target_word = "";
    std::string user_words = "";
    std::string new_file_name = "";
    int word_counter = 0;
    int target_word_counter = 0;
    double change_percentage = 0;
    bool word_found = false; //Note: Lets us know if user word even exists in the file

    //2- Prompt user for file name
    std::cout << "Enter file name to be read: ";
    std::getline(std::cin, user_file); //Note: In case the user's file is something like "Very large file name.docx"

    //2.1- Checks if the file is opened correctly and reads from it. If not, warns the user about possible wrong file name. 
    std::ifstream file_reader(user_file);
    while(!file_reader.is_open()){
        std::cout << "Something went wrong while trying to open the file. \nMake sure to write file name correctly): ";
        std::getline(std::cin,user_file);
        file_reader.clear(); //Note: To reset the fail flag
        file_reader.open(user_file); //Tries again with new answer to avoid infinite loop
    }

    //2.2- Prompt user for word to search.
    std::cout << "Ok, now enter the word you wish to look for: ";
    std::getline(std::cin, target_word);

    //Note: Turns user input into ALL CAPS to make the program case insensitive.
    for(int i=0; i < target_word.length(); i++){
        target_word[i] = std::toupper(target_word[i]);
    }
    
    //3- Note: First loop to check if word exists. Second reads file line by line. 
    //Third reads each word in each line to know what to change. Function to check for punctuation
    std::string line;
    std::string word_in_line;

    while(!word_found){
        file_reader.clear();
        file_reader.seekg(0);
        
        while(std::getline(file_reader, line)){ 
            std::stringstream line_reader(line);
            
            while(line_reader >> word_in_line){
                        
                IgnorePunctuationInWord(word_in_line);
                
                if(IgnorePunctuationInWord(word_in_line) == target_word){
                    word_found = true;
                    break;
                }
            }
            if (word_found){
                break; //Early break, as this nested loop is only to confirm that the target word exists at least once in the file
            }
        }

        //3.1- Edge case: if the user's word can't be found in the file, let them know.
        if(!word_found){
            std::cout << "The word you're looking for is not in this file. Enter a new one: ";
            std::getline(std::cin, target_word);
    
            for(int i=0; i < target_word.length(); i++){
                target_word[i] = std::toupper(target_word[i]);
            }
        }
    }
    
    //4- Prompt user for replacement word.
    std::cout << "Enter replacement word for the original word (or replacement sentence, if you want): ";
    std::getline(std::cin, user_words);
    
    //Exrta: Allow the user to customize the output file name.
    std::cout << "State a name for the modified file \n(don't worry about file extensions, you can customize them or not use any at all.): ";
    std::getline(std::cin, new_file_name);

    //5- Create a new, still emtpy, user-modified file.
    std::ofstream newFile (new_file_name);

    while (!newFile.is_open()) {
        std::cout << "The file could not be created. \nEnter another file name: ";        
        std::getline(std::cin, new_file_name);

        newFile.clear();
        newFile.open(new_file_name);
    }

    file_reader.clear();
    file_reader.seekg(0);

    //Note: The nested while loop structure is repeated twice. The first one was to read the file to search if the word existed
    //the second nested loop is to replace the word. 
    while(std::getline(file_reader, line)){ 
        std::stringstream line_reader(line);
 
        while(line_reader >> word_in_line){       
            word_counter++;         
            IgnorePunctuationInWord(word_in_line);

            if(IgnorePunctuationInWord(word_in_line) == target_word){
                //6- Count word.
                target_word_counter++;

                //Note: These lines preserve the punctuation marks in the text to avoid deleting it in the output.txt file.
                std::string modified_word = word_in_line; //copy to avoid modifying the original word.
                int punctuation_Keeper = modified_word.find_first_not_of(".,;:!?\"/|""''()[]{}@#^*-");
                modified_word.replace(punctuation_Keeper, target_word.length(), user_words);
                
                //7- Replace word with user's chosen word.
                newFile << "**" << modified_word << " ";
            } else{
                newFile << word_in_line << " ";
            }
        }
        newFile << "\n"; //Note: Once it is done reading the line in the file, starts a new line to maintain order and avoid writing the entire file in a single, very long and extensive line, just like this comment right here! That is probably becoming too tiresome to read.
    }
        
    //8- Display how many replacement were made, the total amount of words and the percentage of words that were changed out of the whole file.
    change_percentage = (static_cast<double>(target_word_counter)/word_counter) * 100;

    std::cout << "The number of times the word [ " << target_word << " ] was changed is: " << target_word_counter << std::endl;
    std::cout << "total number of words in the file are: " << word_counter << std::endl;
    std::cout << "Therefore," << change_percentage << " percent of the file's word were replaced." << std::endl;

    newFile.close();
    file_reader.close();

    return 0;
}
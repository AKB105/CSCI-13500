/*
    Week 7 Review: File I/O, Reading, Writing, and Modifying Text

    Good cheat-sheet ideas:
    - ifstream reads from a file.
    - ofstream writes to a file.
    - stringstream lets you process one line word by word.
    - clear() resets stream error flags.
    - seekg(0) sends an input file stream back to the beginning.
*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string NormalizeWord(std::string word) {
    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        if (std::ispunct(static_cast<unsigned char>(word[i])) && word[i] != '\'') {
            word.erase(i, 1);
            i--;
        } else {
            word[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(word[i])));
        }
    }
    return word;
}

bool OpenInputFile(std::ifstream& reader, const std::string& file_name) {
    reader.open(file_name);
    return reader.is_open();
}

int CountWordInFile(std::ifstream& reader, const std::string& target_word) {
    reader.clear();
    reader.seekg(0);

    std::string line;
    std::string word;
    int counter = 0;

    while (std::getline(reader, line)) {
        std::stringstream line_reader(line);
        while (line_reader >> word) {
            if (NormalizeWord(word) == target_word) {
                counter++;
            }
        }
    }

    return counter;
}

void ReplaceWordIntoNewFile(std::ifstream& reader,
                            std::ofstream& writer,
                            const std::string& target_word,
                            const std::string& replacement_word,
                            int& word_counter,
                            int& replacement_counter) {
    reader.clear();
    reader.seekg(0);

    std::string line;
    std::string word;

    while (std::getline(reader, line)) {
        std::stringstream line_reader(line);

        while (line_reader >> word) {
            word_counter++;

            if (NormalizeWord(word) == target_word) {
                replacement_counter++;
                writer << replacement_word << " ";
            } else {
                writer << word << " ";
            }
        }

        writer << "\n";
    }
}

int main() {
    std::string input_file_name = "sample_input.txt";
    std::string output_file_name = "sample_output.txt";
    std::string target_word = "CAT";
    std::string replacement_word = "tiger";

    std::ifstream reader;
    if (!OpenInputFile(reader, input_file_name)) {
        std::cout << "Could not open " << input_file_name << "\n";
        return 1;
    }

    std::ofstream writer(output_file_name);
    if (!writer.is_open()) {
        std::cout << "Could not create " << output_file_name << "\n";
        return 1;
    }

    int existing_matches = CountWordInFile(reader, target_word);
    int word_counter = 0;
    int replacement_counter = 0;

    ReplaceWordIntoNewFile(reader, writer, target_word, replacement_word,
                           word_counter, replacement_counter);

    std::cout << "Matches before replacement: " << existing_matches << "\n";
    std::cout << "Total words processed: " << word_counter << "\n";
    std::cout << "Total replacements written: " << replacement_counter << "\n";

    reader.close();
    writer.close();

    return 0;
}

#include "file_operations.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void file_operations::delete_transaction(int month, int year, std::vector<std::string> displayed_data) {
    char user_choice_c;
    int user_choice_i;
    std::string user_choice_s;
    int vector_max_index = displayed_data.size() - 1;
    std::string filename = "./data/transactions/" + std::to_string(year) + "/" + std::to_string(month) + ".txt";

    std::cout << "Please select the transaction 'No' that you want to remove: ";
    std::cin >> user_choice_i;
    while ((!std::cin.eof() && std::cin.fail()) || (user_choice_i < 1 || user_choice_i > vector_max_index)) {
            std::cout << "That is not a proper integer value for a transaction number.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> user_choice_i;
    }

    std::cout << "You selected this transaction: ";
    std::cout << displayed_data[user_choice_i] << std::endl;

    std::cout << "Are you sure you want to remove this transaction? Y/n: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
    std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
    user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character

    // Delete transaction only with a 'yes' input
    if (user_choice_c == 'Y' || user_choice_c == 'y') {
        displayed_data.erase(displayed_data.begin() + (user_choice_i));
        file_operations::writefile(filename, displayed_data);
    }
}


void file_operations::delete_category(std::string filename, std::vector<std::string> categories) {
    char user_choice_c;
    int user_choice_i;
    std::string user_choice_s;
    int vector_size = categories.size();
    int vector_max_index = categories.size() +1;

    std::cout << "Please select the category 'No' that you want to remove: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
    std::cin >> user_choice_i;
    while ((!std::cin.eof() && std::cin.fail())
           || (user_choice_i < 0 || user_choice_i > vector_max_index || user_choice_i == vector_size || user_choice_i == vector_size + 1 )) {
            std::cout << "That is not a proper integer value for a category number.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> user_choice_i;
    }

    std::cout << "You selected this category: ";
    std::cout << categories[user_choice_i] << std::endl;

    std::cout << "Are you sure you want to remove this category? Y/n: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
    std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
    user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character

    // Delete category only with a 'yes' input
    if (user_choice_c == 'Y' || user_choice_c == 'y') {
        categories.erase(categories.begin() + (user_choice_i));
        file_operations::writefile(filename, categories);
    }
}


std::vector<std::string> file_operations::readfile(std::string filename) {
    std::vector<std::string> read_data;
    std::ifstream read_transactions;

    read_transactions.open(filename);
    if (read_transactions.is_open()) {
        std::string line;
        while (getline(read_transactions, line)) {
            if (line.size() > 0) {
                read_data.push_back(line);
            }
        }
    }
    read_transactions.close();

    return read_data;
}


void file_operations::writefile(std::string filename, std::vector<std::string> vectorname) {
    std::ofstream write_transactions;

    write_transactions.open(filename);
    if (write_transactions.is_open()) {
        for (auto t = vectorname.begin(); t != vectorname.end(); t++) {
            write_transactions << *t << std::endl;
        }
    }
    write_transactions.close();
}

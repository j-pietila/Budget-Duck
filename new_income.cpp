#include "new_income.h"
#include "file_operations.h"
#include <algorithm>
#include <iostream>
#include <string>

new_income::new_income() {}


void new_income::set_category() {
    category_data = file_operations::readfile("./data/categories/income.txt");
    int vector_size = category_data.size();
    int vector_max_index = category_data.size() +1;
    int user_choice_i = 0;

    std::cout << std::endl;
    for (int i = 0; i < vector_size; i++) {
        std::cout << i << " - " << category_data[i] << std::endl;
    }
    std::cout << vector_size << " - Add a new category" << std::endl;
    std::cout << vector_size + 1 << " - Remove a category" << std::endl;
    std::cout << "Please select transaction category number from the list: ";
    std::cin >> user_choice_i;
    while ((!std::cin.eof() && std::cin.fail()) || (user_choice_i < 0 || user_choice_i > vector_max_index)) {
            std::cout << "That is not a proper integer value for a category.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> user_choice_i;
    }

    if (user_choice_i == vector_size) {
        std::cout << "Please input the name of the new category (max length is 22 chars): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the cin buffer until newline before call to getline()
        std::getline(std::cin, category); // Use getline instead of cin to be able to read string with whitespace
        if (category.size() > 22) { // Limit the maximum category size to 22 chars
            category.resize(22);
        }
        // Add new category to the categories file
        category_data.push_back(category);
        std::sort(category_data.begin(), category_data.end());
        file_operations::writefile("./data/categories/income.txt", category_data);
        new_income::set_category(); // This is needed to get the cin buffer to work correctly with the set_notes() function.
        return;                     // Cin buffer ignore is doubled otherwise and leads to skipping of input.
    } else if (user_choice_i == vector_size + 1) {
        if (category_data.size() > 0) { // Check if there is no data to be removed in the 'category_data' vector
            file_operations::delete_category("./data/categories/income.txt", category_data);
            new_income::set_category();
            return;
        } else {
            std::cout << "There is no category data to be removed." << std::endl;
            new_income::set_category();
            return;
        }
    } else {
        category = category_data[user_choice_i];
    }
    new_transaction_data += category + ",";
}


void new_income::set_sum() {
    std::cout << "Please input the income amount with '.' as a decimal separator: ";
    std::cin >> sum;
    while (!std::cin.eof() && std::cin.fail()) {
            std::cout << "That is not a proper numeric value for a sum.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> sum;
    }

    // Format the 'sum' double to two digits using substring
    // No rounding needed as this is already the highest possible accuracy for currency inputs
    std::string sum_s = std::to_string(sum);
    std::string sum_s_two_digits = sum_s.substr(0, sum_s.find(".") + 3);

    new_transaction_data += sum_s_two_digits;
}

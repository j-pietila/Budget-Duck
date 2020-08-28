#include "displayed_transactions.h"
#include "file_operations.h"
#include <iostream>
#include <sstream>
#include <string>


displayed_transactions::displayed_transactions(int m, int y) {
    month = m;
    year = y;
}


void displayed_transactions::load_data() {
    // Clear possible previous data before reading from a file
    transactions.clear();
    // Read data from file
    transactions = file_operations::readfile("./data/transactions/" + std::to_string(year)
                                             + "/" + std::to_string(month) + ".txt");
}


void displayed_transactions::printout() {
    char border = '*';
    char border2 = '-';
    char buffer = ' ';
    char wall = '|';
    int border_length = 80; // Border length needs to be same as in 'displayed_month' class

    // Print out the table definitions
    std::cout << border << " No " << wall << "    Date    " << wall << "        Category        "
              << wall << "         Notes         " << wall << "    Sum    " << border << "\n";
    std::cout << std::string(border_length, border) << std::endl;

    // If there is no transaction data found on a file for chosen month, print an empty box
    if (transactions.size() < 2) { // If there is a CSV header line, size will be 1 but there is still no actual data
        std::cout << border << std::string((border_length - 2), buffer)
                  << border << "\n";
        std::cout << border << std::string((border_length - 2 - 25) / 2, buffer) << "No transaction data found "
                  << std::string((border_length - 2 - 25) / 2, buffer) << border << "\n";
        std::cout << border << std::string((border_length - 2), buffer)
                  << border << "\n";
        std::cout << std::string(border_length, border) << std::endl;        
    // Else print out all the transaction data read from file to a vector 'transactions'
    } else {
        int vector_size = transactions.size();
        std::string line;
        std::string token;

        // Reset the 'total_expense' and 'total_income' variables before the for loop
        // Otherwise they are being incremented after every main() current view display load
        total_income = 0;
        total_expense = 0;
        // Loop the 'transactions' vector, one element equals one line of text data
        // Start from index 1 since 0 contains the CSV file definitions
        for (int i = 1; i < vector_size; i++) {
            // Get the read line split into tokens with ',' as separator using stringstream
            // and push those tokens to a vector 'transactions_line' to format the line output
            transactions_line.clear();
            line = transactions[i];
            std::stringstream input_stream(line);
            while (getline(input_stream, token, ',')) {
                transactions_line.push_back(token);
            }

            // Print the transaction number with its borders
            // If transactions No is one digit long, add 0 in front of it
            if (i < 10) {
                std::cout << border << " 0" << i << " " << wall;
            } else {
                std::cout << border << " " << i << " " << wall;
            }

            // Print Date with its borders, date box size is 12
            std::cout << " " << transactions_line[0] << std::string((12 - 1 - transactions_line[0].size()), buffer)
                      << wall;

            // Print Category with its borders, category box size is 24
            int category_size = transactions_line[1].size();
            if (category_size % 2 != 0) { // Centering check for the category string
                category_size += 1;
                transactions_line[1] += " ";
            }
            std::cout << std::string((24 - category_size) / 2, buffer)
                      << transactions_line[1] << std::string((24 - category_size) / 2, buffer) << wall;

            // Print Notes with its borders, notes box size is 23
            int notes_size = transactions_line[2].size();
            if (notes_size % 2 == 0) { // Centering check for the notes string
                notes_size += 1;
                transactions_line[2] += " ";
            }
            std::cout << std::string((23 - notes_size) / 2, buffer)
                      << transactions_line[2] << std::string((23 - notes_size) / 2, buffer) << wall;

            // Print Sum with its borders, sum box size is 11
            // Print a '+' sign in front of income transaction sums
            if (std::stod(transactions_line[3]) > 0) {
                std::cout << std::string((11 - 3 - transactions_line[3].size()), buffer) << "+" << transactions_line[3] << "€"
                          << " " << border << "\n";
            } else {
                std::cout << std::string((11 - 2 - transactions_line[3].size()), buffer) << transactions_line[3] << "€"
                          << " " << border << "\n";
            }

            if (i != vector_size - 1) { // Don't print the horizontal wall after the last transaction line
            std::cout << border << std::string((border_length - 2), border2) << border << "\n";
            }

            // Count monthly total income and expense from the for loop with double precision
            if (std::stod(transactions_line[3]) < 0) {
                total_expense += std::stod(transactions_line[3]);
            } else {
                total_income += std::stod(transactions_line[3]);
            }
        }

        // Print total monthly income and expense in a separate box at the bottom
        std::string total_income_s = std::to_string(total_income);
        std::string total_expense_s = std::to_string(total_expense);
        std::string balance_s = std::to_string(total_income + total_expense);

        if (total_expense < 0) { // Needs to be checked, otherwise 0.00 expense will be shown as -0.00
            total_expense_s = std::to_string(total_expense * -1);
        }

        // Format the double values to two digits using substring
        // No rounding needed as this is already the highest possible accuracy for currency inputs
        std::string total_income_s_two_digits = total_income_s.substr(0, total_income_s.find(".") + 3);
        std::string total_expense_s_two_digits = total_expense_s.substr(0, total_expense_s.find(".") + 3);
        std::string balance_s_two_digits = "";

        if (total_income + total_expense > 0) { // Add '+' in front of a positive balance
            balance_s_two_digits += "+";
        }

        std::string balance_s_subs = balance_s.substr(0, balance_s.find(".") + 3);
        balance_s_two_digits += balance_s_subs + "€";

        if ((balance_s_two_digits.size() + 17) % 2 != 0) { // Centering check for the balance string
            balance_s_two_digits += " ";
        }

        // Total income and Total expense are 24 chars long strings
        // Monthly balance is 17 + balance_s_two_digits.size() chars long string
        std::cout << std::string(border_length, border) << "\n";
        std::cout << border << std::string((border_length - 2 - 24) / 2, buffer) << "Total Income:  "
                  << std::string(8 - total_income_s_two_digits.size(), buffer)
                  << total_income_s_two_digits << "€"
                  << std::string((border_length - 2 - 24) / 2, buffer) << border << "\n";
        std::cout << border << std::string((border_length - 2 - 24) / 2, buffer) << "Total Expense: "
                  << std::string(8 - total_expense_s_two_digits.size(), buffer)
                  << total_expense_s_two_digits << "€"
                  << std::string((border_length - 2 - 24) / 2, buffer) << border << "\n";
        std::cout << border << std::string((border_length - 2), border2) << border << "\n";
        std::cout << border << std::string((border_length - 17 - balance_s_two_digits.size()) / 2, buffer) << "Monthly Balance: "
                  << balance_s_two_digits
                  << std::string((border_length - 17 - balance_s_two_digits.size()) / 2, buffer) << border << "\n";
        std::cout << std::string(border_length, border) << std::endl;
    }
}

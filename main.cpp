#include "displayed_month.h"
#include "displayed_transactions.h"
#include "file_operations.h"
#include "new_expense.h"
#include "new_income.h"
#include <iostream>
#include <string>

int main() {

    // INITIAL SET-UP TO DEFAULT VIEW

    // Set default transaction view to current month and year from system time
    displayed_month month;
    displayed_transactions displayed_transactions(month.month, month.year);

    // Create objects for income and expense to be used in the program
    new_income income;
    new_expense expense;

    // Print out default month and its transactions
    // Order the transactions by date from first to last as default
    system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
    month.printout();
    displayed_transactions.load_data();
    displayed_transactions.printout();
     // Print out welcome message
    std::cout << "\nWelcome to Budget Duck! Input 'h' to access help file for possible commands.\n";


    // APPLICATION LOOP
    char user_choice_c;
    std::string user_choice_s;
    bool app_running = true;

    while (app_running) {
        // Ask for user input
        std::cout << "\n";
        std::cout << "Please, enter a command: ";
        std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
        user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character to eliminate multiple fail messages
        std::cout << "\n";

        // Define possible user actions with switch-case structure
        switch (user_choice_c) {
            case 'p': // Select previous month
                month.previous();
                displayed_transactions.month = month.month;
                displayed_transactions.year = month.year;
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'n': // Select next month
                month.next();
                displayed_transactions.month = month.month;
                displayed_transactions.year = month.year;
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'c': // Select a month by user input
                month.change();
                displayed_transactions.month = month.month;
                displayed_transactions.year = month.year;
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'i': // Add new income transaction
                income.set_date();
                income.set_category();
                income.set_notes();
                income.set_sum();
                income.save_data();
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'e': // Add new expense transaction
                expense.set_date();
                expense.set_category();
                expense.set_notes();
                expense.set_sum();
                expense.save_data();
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'd': // Delete transaction line from current view
                file_operations::delete_transaction(month.month, month.year, displayed_transactions.transactions);
                system("clear"); // Linux specific, bad practice but use of other libraries than STD prohibited!
                month.printout();
                displayed_transactions.load_data();
                displayed_transactions.printout();
                break;
            case 'q':
                std::cout << "Are you sure you want to exit? Y/n: ";
                std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
                user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character
                if(user_choice_c == 'Y' || user_choice_c == 'y') {
                    std::cout << "\nSee you soon! Thank you for using Budget Duck!\n" << std::endl;
                    app_running = false;
                    break;
                } else {
                    break;
                }
            case 'h':
                std::cout << "Input the character inside parentheses for the command.\n";
                std::cout << "Change display: (p)revious, (n)ext, (c)hange - Changes currently viewed month.\n";
                std::cout << "Add a transaction: (i)ncome, (e)xpense"
                             " - Add income or expense to any date of choice.\n";
                std::cout << "Delete a transaction: (d)elete - Delete a transaction from the current view.\n";
                std::cout << "Exit program: (q)uit - Exits the program." << std::endl;
                break;
            default:
                std::cout << "Not a valid command. Please input 'h' for help with possible commands." << std::endl;
        }
    }

    return 0;
}

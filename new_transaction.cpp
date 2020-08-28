#include "new_transaction.h"
#include "file_operations.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sys/stat.h> // mkdir(), stat()

new_transaction::new_transaction() {}


void new_transaction::set_date() {
    // Clear the new transaction data before starting to enter new data
    new_transaction_data = "";

    std::cout << "Please enter the day, month and year of the transaction.\n";
    std::cout << "Day: ";
    std::cin >> day;
    while ((!std::cin.eof() && std::cin.fail()) || (day < 1 || day > 31)) {
            std::cout << "That is not a proper integer value for a day.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> day;
    }

    if (day < 10) { // Insert a leading zero for numbers under 10
        std::string day_s = "0" + std::to_string(day);
        new_transaction_data += day_s + "/";
    } else {
        new_transaction_data += std::to_string(day) + "/";
    }

    std::cout << "Month: ";
    std::cin >> month;
    while ((!std::cin.eof() && std::cin.fail()) || (month < 1 || month > 12)) {
            std::cout << "That is not a proper integer value for a month.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> month;
    }

    if (month < 10) { // Insert a leading zero for numbers under 10
        std::string month_s = "0" + std::to_string(month);
        new_transaction_data += month_s + "/";
    } else {
        new_transaction_data += std::to_string(month) + "/";
    }

    std::cout << "Year: ";
    std::cin >> year;
    while (!std::cin.eof() && std::cin.fail()) {
            std::cout << "That is not a proper integer value for a year.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> year;
    }

    new_transaction_data += std::to_string(year) + ",";
}


void new_transaction::set_notes() {
    char user_choice_c;
    std::string user_choice_s;
    std::string new_note = "";

    std::cout << "\n";
    std::cout << "Do you want to add additional notes about the transaction? Y/n: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
    std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
    user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character

    // Add a note only with a 'yes' input
    if (user_choice_c == 'Y' || user_choice_c == 'y') {
        std::cout << "Please write your note (max length is 21 chars): ";
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, new_note); // Use getline instead of cin to be able to read string with whitespace
        if (new_note.size() > 21) { // Limit the maximum note size to 21 chars
            new_note.resize(21);
        }
        note = new_note;
    } else {
        note = "";
        std::cout << "No additional notes." << std::endl;
    }

    new_transaction_data += note + ",";
}


void new_transaction::save_data() {
    // Ask confirmation for input data before saving it
    char user_choice_c;
    std::string user_choice_s;

    std::cout << "\n";
    std::cout << "Inputted data: " << new_transaction_data << std::endl;
    std::cout << "Do you want to save this data? Y/n: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
    std::getline(std::cin, user_choice_s); // Take input as a getline to eliminate failures from numbers
    user_choice_c = user_choice_s[0]; // Limit the accepted command to the first character

    // Exit the 'save_data' function if anything else is inputted than 'yes'
    if (user_choice_c == 'Y' || user_choice_c == 'y') {
        ;
    } else {
        return;
    }

    // Clear possible previous data before reading from a file
    monthly_transactions.clear();
    // Read data from file
    monthly_transactions = file_operations::readfile("./data/transactions/" + std::to_string(year)
                                                     + "/" + std::to_string(month) + ".txt");

    // Check if there is no read data for the selected month and append the CSV header line
    // to 'transactions' vector before new data for the month is written
    if (monthly_transactions.empty()) {
        monthly_transactions.push_back("Date/Month/Year, Category, Additional Notes, Sum");
    }    

    // Append the new transaction to monthly data
    monthly_transactions.push_back(new_transaction_data);
    std::sort(monthly_transactions.begin() + 1, monthly_transactions.end()); // Index 0 is the CSV header line

    // Create the needed year folder if it doesn't already exist
    std::string pathname = "./data/transactions/" + std::to_string(year);
    struct stat buffer;
    if (stat(pathname.c_str(), &buffer) != 0) { // Stat() returns 0 if the folder already exists
        mkdir(pathname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // Linux specific!
    }

    // Write the updated contents of the 'monthly transactions' vector to file
    file_operations::writefile("./data/transactions/" + std::to_string(year) + "/"
                               + std::to_string(month) + ".txt", monthly_transactions);
}

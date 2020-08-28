#include "displayed_month.h"
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>


// Set constructors
displayed_month::displayed_month() {
    // Set current month and year from system time
    time_t now = time(NULL);
    tm *time_p = localtime(&now);
    month = time_p->tm_mon + 1;
    year = time_p->tm_year + 1900;
}


displayed_month::displayed_month(int m, int y) {
    month = m;
    year = y;
}


void displayed_month::previous() {
    if (month == 1) {
        month = 12;
        year -= 1;
    } else {
        month -= 1;
    }
}


void displayed_month::next() {
    if (month == 12) {
        month = 1;
        year += 1;
    } else {
        month += 1;
    }
}


void displayed_month::change() {
    int m, y;

    std::cout << "Input month as number: ";
    std::cin >> m;
    while ((!std::cin.eof() && std::cin.fail()) || (m < 1 || m > 12)) {
            std::cout << "That is not a proper integer value for a month.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> m;
    }
    std::cout << "Input year: ";
    std::cin >> y;
    while (!std::cin.eof() && std::cin.fail()) {
            std::cout << "That is not a proper integer value for a year.\n";
            std::cin.clear(); // Clear cin failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard characters still in the input buffer until newline
            std::cout << "Please try again: ";
            std::cin >> y;
    }

    month = m;
    year = y;
}


void displayed_month::printout() {
    // Map integers to strings
    std::unordered_map<int, std::string> months;
    months[1] = "January";
    months[2] = "February";
    months[3] = "March";
    months[4] = "April";
    months[5] = "May";
    months[6] = "June";
    months[7] = "July";
    months[8] = "August";
    months[9] = "September";
    months[10] = "October";
    months[11] = "November";
    months[12] = "December";

    // Print out current month and year with appropriate borders calculated from string length
    std::string month_output = "Current View - " + months[month] + " " + std::to_string(year);
    char border = '*';
    char buffer = ' ';
    int border_length = 80; // Border length needs to be an even number for the calculations
    int output = month_output.size();

    // Center the output string in case it's size happens to be an odd number
    if (output % 2 != 0) {
        output += 1;
        month_output += " ";
    }

    std::cout << std::string(border_length, border) << "\n";
    std::cout << border << std::string(border_length - 2, buffer) << border << "\n";
    std::cout << border << std::string((border_length - 2 - output) / 2, buffer)
              << month_output << std::string((border_length - 2 - output) / 2, buffer)
              << border << "\n";
    std::cout << border << std::string(border_length - 2, buffer) << border << "\n";
    std::cout << std::string(border_length, border) << std::endl;
}

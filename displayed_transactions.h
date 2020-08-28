#ifndef DISPLAYED_TRANSACTIONS_H
#define DISPLAYED_TRANSACTIONS_H

#include <string>
#include <vector>

class displayed_transactions {

public:
    int month, year;
    double total_income = 0, total_expense = 0;
    std::vector<std::string> transactions;
    std::vector<std::string> transactions_line;

    // Set constructor
    displayed_transactions(int m, int y);

    // Load transaction data from file
    void load_data();

    // Display selected transactions
    void printout();

};

#endif // DISPLAYED_TRANSACTIONS_H

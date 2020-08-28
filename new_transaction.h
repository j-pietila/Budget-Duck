#ifndef NEW_TRANSACTION_H
#define NEW_TRANSACTION_H

#include <string>
#include <vector>

class new_transaction {

public:
    int day, month, year;
    double sum;
    std::string category = "";
    std::string note = "";
    std::string new_transaction_data = "";
    std::vector<std::string> category_data;
    std::vector<std::string> monthly_transactions;

    // Set constructor
    new_transaction();

    // Set transaction date
    void set_date();

    // Set additional transaction notes
    void set_notes();

    // Check given input and write all the transaction data to a file as a string
    void save_data();

};

#endif // NEW_TRANSACTION_H

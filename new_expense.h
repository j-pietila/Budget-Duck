#ifndef NEW_EXPENSE_H
#define NEW_EXPENSE_H

#include "new_transaction.h"

class new_expense: public new_transaction {

public:
    // Set constructor
    new_expense();

    // Set the expense category
    void set_category();

    // Set the expense sum
    void set_sum();

};

#endif // NEW_EXPENSE_H

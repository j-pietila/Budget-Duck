#ifndef NEW_INCOME_H
#define NEW_INCOME_H

#include "new_transaction.h"

class new_income: public new_transaction {

public:
    // Set constructor
    new_income();

    // Set the income category
    void set_category();

    // Set the income sum
    void set_sum();

};

#endif // NEW_INCOME_H

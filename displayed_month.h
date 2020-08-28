#ifndef DISPLAYED_MONTH_H
#define DISPLAYED_MONTH_H

class displayed_month {

public:
    int month;
    int year;

    // Set constructors
    displayed_month();
    displayed_month(int m, int y);

    // Change the month
    void previous();

    void next();

    void change();

    // Display current month
    void printout();

};

#endif // DISPLAYED_MONTH_H

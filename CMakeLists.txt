cmake_minimum_required(VERSION 3.5)

project(BudgetDuck LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    "main.cpp"
    "displayed_month.cpp"
    "displayed_transactions.cpp"
    "file_operations.cpp"
    "new_transaction.cpp"
    "new_income.cpp"
    "new_expense.cpp")

set(HEADERS
    "displayed_month.h"
    "displayed_transactions.h"
    "file_operations.h"
    "new_transaction.h"
    "new_income.h"
    "new_expense.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# C++ Personal Finance Tracker

A command-line personal finance management system built in C++. This project allows users to track income, expenses, budgets, category spending, and financial summaries through a menu-based interface.

## Features

- Add income transactions
- Add expense transactions
- View all transactions
- View monthly income, expenses, and savings
- View spending totals by category
- Set a monthly budget
- Check budget status and receive warnings
- Search transactions by type, category, date, or description
- Sort transactions by amount, date, or category
- Save and load data using file input/output

## Concepts Used

- Object-oriented programming
- Classes and objects
- Header and implementation files
- Vectors
- Maps
- File input/output
- Searching
- Sorting
- Loops and conditionals
- Input validation
- Modular program design

## Project Structure

```text
Personal-Finance-Tracker/
├── main.cpp
├── Transaction.h
├── Transaction.cpp
├── FinanceManager.h
├── FinanceManager.cpp
├── transactions.txt
└── README.md
```

## How to Run

### Compile

```bash
g++ main.cpp Transaction.cpp FinanceManager.cpp -o finance_tracker
```

### Run

```bash
./finance_tracker
```

On Windows, use:

```bash
finance_tracker.exe
```

## Example Menu

```text
========== PERSONAL FINANCE TRACKER ==========
1. Add Income
2. Add Expense
3. View All Transactions
4. View Monthly Summary
5. View Spending by Category
6. Set Monthly Budget
7. Check Budget Status
8. Search Transactions
9. Sort Transactions
10. Save Data
11. Load Data
0. Exit
```

## Sample Resume Bullets

**Personal Finance Tracker | C++**

- Developed a command-line personal finance application in C++ using object-oriented programming and modular file organization.
- Implemented transaction tracking for income, expenses, budgets, savings summaries, category reports, searching, and sorting.
- Used file input/output to save and load user financial data across program sessions.
- Applied vectors, maps, input validation, and custom classes to create a structured real-world application.

## Future Improvements

- Add login support for multiple users
- Export reports to CSV
- Add monthly filtering
- Add recurring transactions
- Add a graphical user interface

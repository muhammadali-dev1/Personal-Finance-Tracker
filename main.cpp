#include "FinanceManager.h"
#include <iostream>
#include <limits>

void displayMenu() {
    std::cout << "\n========== PERSONAL FINANCE TRACKER ==========" << std::endl;
    std::cout << "1. Add Income" << std::endl;
    std::cout << "2. Add Expense" << std::endl;
    std::cout << "3. View All Transactions" << std::endl;
    std::cout << "4. View Monthly Summary" << std::endl;
    std::cout << "5. View Spending by Category" << std::endl;
    std::cout << "6. Set Monthly Budget" << std::endl;
    std::cout << "7. Check Budget Status" << std::endl;
    std::cout << "8. Search Transactions" << std::endl;
    std::cout << "9. Sort Transactions" << std::endl;
    std::cout << "10. Save Data" << std::endl;
    std::cout << "11. Load Data" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    FinanceManager manager;
    const std::string filename = "transactions.txt";
    int choice;

    manager.loadFromFile(filename);

    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.addIncome();
                break;
            case 2:
                manager.addExpense();
                break;
            case 3:
                manager.viewTransactions();
                break;
            case 4:
                manager.viewMonthlySummary();
                break;
            case 5:
                manager.viewCategorySummary();
                break;
            case 6:
                manager.setBudget();
                break;
            case 7:
                manager.checkBudgetStatus();
                break;
            case 8:
                manager.searchTransactions();
                break;
            case 9:
                manager.sortTransactions();
                break;
            case 10:
                manager.saveToFile(filename);
                break;
            case 11:
                manager.loadFromFile(filename);
                break;
            case 0:
                manager.saveToFile(filename);
                std::cout << "Goodbye. Your data has been saved.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

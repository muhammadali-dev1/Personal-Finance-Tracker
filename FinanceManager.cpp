#include "FinanceManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <limits>
#include <cctype>

FinanceManager::FinanceManager() {
    monthlyBudget = 0.0;
}

std::string FinanceManager::getInputLine(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

double FinanceManager::getPositiveAmount(const std::string& prompt) const {
    double amount;

    while (true) {
        std::cout << prompt;
        std::cin >> amount;

        if (!std::cin.fail() && amount > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return amount;
        }

        std::cout << "Invalid amount. Please enter a positive number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool FinanceManager::isValidDate(const std::string& date) const {
    if (date.length() != 10) {
        return false;
    }

    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return false;
        }
    }

    return true;
}

std::string FinanceManager::toLowerCase(std::string text) const {
    for (int i = 0; i < static_cast<int>(text.length()); i++) {
        text[i] = static_cast<char>(tolower(text[i]));
    }
    return text;
}

double FinanceManager::getTotalIncome() const {
    double total = 0.0;

    for (const Transaction& transaction : transactions) {
        if (transaction.getType() == "Income") {
            total += transaction.getAmount();
        }
    }

    return total;
}

double FinanceManager::getTotalExpenses() const {
    double total = 0.0;

    for (const Transaction& transaction : transactions) {
        if (transaction.getType() == "Expense") {
            total += transaction.getAmount();
        }
    }

    return total;
}

void FinanceManager::addIncome() {
    std::string category;
    std::string date;
    std::string description;
    double amount;

    category = getInputLine("Enter income category: ");
    amount = getPositiveAmount("Enter income amount: $");

    do {
        date = getInputLine("Enter date (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        }
    } while (!isValidDate(date));

    description = getInputLine("Enter description: ");

    transactions.push_back(Transaction("Income", category, amount, date, description));
    std::cout << "Income added successfully.\n";
}

void FinanceManager::addExpense() {
    std::string category;
    std::string date;
    std::string description;
    double amount;

    category = getInputLine("Enter expense category: ");
    amount = getPositiveAmount("Enter expense amount: $");

    do {
        date = getInputLine("Enter date (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        }
    } while (!isValidDate(date));

    description = getInputLine("Enter description: ");

    transactions.push_back(Transaction("Expense", category, amount, date, description));
    std::cout << "Expense added successfully.\n";
}

void FinanceManager::viewTransactions() const {
    if (transactions.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }

    std::cout << "\n==================== ALL TRANSACTIONS ====================\n";
    std::cout << std::left << std::setw(12) << "Type"
              << std::setw(15) << "Category"
              << std::setw(11) << "Amount"
              << std::setw(15) << "Date"
              << "Description" << std::endl;
    std::cout << "----------------------------------------------------------\n";

    for (const Transaction& transaction : transactions) {
        transaction.displayTransaction();
    }
}

void FinanceManager::viewMonthlySummary() const {
    double income = getTotalIncome();
    double expenses = getTotalExpenses();
    double savings = income - expenses;

    std::cout << "\n==================== MONTHLY SUMMARY ====================\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Income:   $" << income << std::endl;
    std::cout << "Total Expenses: $" << expenses << std::endl;
    std::cout << "Net Savings:    $" << savings << std::endl;

    if (savings > 0) {
        std::cout << "Status: You saved money this period.\n";
    } else if (savings < 0) {
        std::cout << "Status: You spent more than you earned.\n";
    } else {
        std::cout << "Status: Your income and expenses are equal.\n";
    }
}

void FinanceManager::viewCategorySummary() const {
    std::map<std::string, double> categoryTotals;

    for (const Transaction& transaction : transactions) {
        if (transaction.getType() == "Expense") {
            categoryTotals[transaction.getCategory()] += transaction.getAmount();
        }
    }

    if (categoryTotals.empty()) {
        std::cout << "No expense categories found.\n";
        return;
    }

    std::cout << "\n==================== CATEGORY SUMMARY ====================\n";
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& category : categoryTotals) {
        std::cout << std::left << std::setw(20) << category.first
                  << "$" << category.second << std::endl;
    }
}

void FinanceManager::setBudget() {
    monthlyBudget = getPositiveAmount("Enter monthly budget: $");
    std::cout << "Monthly budget set to $" << std::fixed << std::setprecision(2)
              << monthlyBudget << std::endl;
}

void FinanceManager::checkBudgetStatus() const {
    double expenses = getTotalExpenses();
    double remaining = monthlyBudget - expenses;

    if (monthlyBudget <= 0) {
        std::cout << "No monthly budget has been set yet.\n";
        return;
    }

    std::cout << "\n==================== BUDGET STATUS ====================\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Monthly Budget: $" << monthlyBudget << std::endl;
    std::cout << "Total Expenses: $" << expenses << std::endl;
    std::cout << "Remaining:      $" << remaining << std::endl;

    double percentUsed = (expenses / monthlyBudget) * 100;
    std::cout << "Budget Used:    " << percentUsed << "%\n";

    if (percentUsed >= 100) {
        std::cout << "Warning: You have reached or exceeded your budget.\n";
    } else if (percentUsed >= 80) {
        std::cout << "Warning: You have used at least 80% of your budget.\n";
    } else {
        std::cout << "Status: You are within your budget.\n";
    }
}

void FinanceManager::searchTransactions() const {
    if (transactions.empty()) {
        std::cout << "No transactions available to search.\n";
        return;
    }

    std::string keyword = getInputLine("Enter keyword to search by type, category, date, or description: ");
    keyword = toLowerCase(keyword);

    bool found = false;

    std::cout << "\n==================== SEARCH RESULTS ====================\n";

    for (const Transaction& transaction : transactions) {
        std::string type = toLowerCase(transaction.getType());
        std::string category = toLowerCase(transaction.getCategory());
        std::string date = toLowerCase(transaction.getDate());
        std::string description = toLowerCase(transaction.getDescription());

        if (type.find(keyword) != std::string::npos ||
            category.find(keyword) != std::string::npos ||
            date.find(keyword) != std::string::npos ||
            description.find(keyword) != std::string::npos) {
            transaction.displayTransaction();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching transactions found.\n";
    }
}

void FinanceManager::sortTransactions() {
    if (transactions.empty()) {
        std::cout << "No transactions available to sort.\n";
        return;
    }

    int choice;

    std::cout << "\nSort by:\n";
    std::cout << "1. Amount: Low to High\n";
    std::cout << "2. Amount: High to Low\n";
    std::cout << "3. Date\n";
    std::cout << "4. Category\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() < b.getAmount();
        });
    } else if (choice == 2) {
        std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() > b.getAmount();
        });
    } else if (choice == 3) {
        std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
            return a.getDate() < b.getDate();
        });
    } else if (choice == 4) {
        std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
            return a.getCategory() < b.getCategory();
        });
    } else {
        std::cout << "Invalid choice. Transactions were not sorted.\n";
        return;
    }

    std::cout << "Transactions sorted successfully.\n";
}

void FinanceManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cout << "Error: Could not open file for saving.\n";
        return;
    }

    outFile << monthlyBudget << std::endl;

    for (const Transaction& transaction : transactions) {
        outFile << transaction.toFileString() << std::endl;
    }

    outFile.close();
    std::cout << "Data saved to " << filename << " successfully.\n";
}

void FinanceManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cout << "No saved data file found. Starting with empty data.\n";
        return;
    }

    transactions.clear();

    std::string line;
    std::getline(inFile, line);

    try {
        monthlyBudget = std::stod(line);
    } catch (...) {
        monthlyBudget = 0.0;
    }

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string type;
        std::string category;
        std::string amountText;
        std::string date;
        std::string description;

        std::getline(ss, type, ',');
        std::getline(ss, category, ',');
        std::getline(ss, amountText, ',');
        std::getline(ss, date, ',');
        std::getline(ss, description);

        if (!type.empty() && !category.empty() && !amountText.empty() && !date.empty()) {
            try {
                double amount = std::stod(amountText);
                transactions.push_back(Transaction(type, category, amount, date, description));
            } catch (...) {
                // Skip invalid transaction lines.
            }
        }
    }

    inFile.close();
    std::cout << "Data loaded from " << filename << " successfully.\n";
}

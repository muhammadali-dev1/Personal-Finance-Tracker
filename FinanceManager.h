#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include "Transaction.h"
#include <vector>
#include <string>

class FinanceManager {
private:
    std::vector<Transaction> transactions;
    double monthlyBudget;

    double getTotalIncome() const;
    double getTotalExpenses() const;
    std::string getInputLine(const std::string& prompt) const;
    double getPositiveAmount(const std::string& prompt) const;
    bool isValidDate(const std::string& date) const;
    std::string toLowerCase(std::string text) const;

public:
    FinanceManager();

    void addIncome();
    void addExpense();
    void viewTransactions() const;
    void viewMonthlySummary() const;
    void viewCategorySummary() const;
    void setBudget();
    void checkBudgetStatus() const;
    void searchTransactions() const;
    void sortTransactions();
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif

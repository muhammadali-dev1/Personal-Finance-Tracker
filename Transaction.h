#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string type;
    std::string category;
    double amount;
    std::string date;
    std::string description;

public:
    Transaction();
    Transaction(std::string type, std::string category, double amount,
                std::string date, std::string description);

    std::string getType() const;
    std::string getCategory() const;
    double getAmount() const;
    std::string getDate() const;
    std::string getDescription() const;

    void displayTransaction() const;
    std::string toFileString() const;
};

#endif

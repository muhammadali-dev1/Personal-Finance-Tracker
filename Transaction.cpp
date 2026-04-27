#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Transaction::Transaction() {
    type = "";
    category = "";
    amount = 0.0;
    date = "";
    description = "";
}

Transaction::Transaction(std::string type, std::string category, double amount,
                         std::string date, std::string description) {
    this->type = type;
    this->category = category;
    this->amount = amount;
    this->date = date;
    this->description = description;
}

std::string Transaction::getType() const {
    return type;
}

std::string Transaction::getCategory() const {
    return category;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getDate() const {
    return date;
}

std::string Transaction::getDescription() const {
    return description;
}

void Transaction::displayTransaction() const {
    std::cout << std::left << std::setw(12) << type
              << std::setw(15) << category
              << "$" << std::setw(10) << std::fixed << std::setprecision(2) << amount
              << std::setw(15) << date
              << description << std::endl;
}

std::string Transaction::toFileString() const {
    std::ostringstream output;
    output << type << "," << category << "," << amount << "," << date << "," << description;
    return output.str();
}

#include <iostream>
#include <cmath>
#include <exception>

class Account {
public:
    Account()
        : balance(0) {}

    int get_balance() const {
        return balance;
    }

    void deposit(int money) {
        balance += money;
    }

    void withdraw(int money) {
        if (balance < money) {
            throw std::logic_error("Insufficient funds");
        }
        balance -= money;
    }

private:
    int balance;
};

int main() {
    Account account;
    int operation = 0;

    do {
        std::cout << "your balance is " << account.get_balance() << ": ";
        std::cin >> operation;
        if (operation < 0) {
            account.withdraw(std::abs(operation));
        } else if (operation > 0) {
            account.deposit(operation);
        }
    } while (operation != 0);
    return 0;
}

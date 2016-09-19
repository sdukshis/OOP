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

protected:
    int balance;
};

class AccountWithOverdraft : public Account {
public:
    explicit AccountWithOverdraft(int maximum_overdraft)
        : max_overdraft(maximum_overdraft) {}

    int get_max_overdraft() const {
        return max_overdraft;
    }

    void withdraw(int money) {
        if (balance + max_overdraft < money) {
            throw std::logic_error("Overdraft limit exceeded");
        }
        balance -= money;
    }

private:
    int max_overdraft;
};

int main() {
    AccountWithOverdraft account(100);
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

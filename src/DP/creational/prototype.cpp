#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Document {
public:
  virtual ~Document(){};

  friend std::ostream &operator<<(std::ostream &stream, const Document &doc) {
    doc.print(stream);
    return stream;
  }

  virtual std::unique_ptr<Document> clone() const = 0;

private:
  virtual void print(std::ostream &) const = 0;
};

class Product {
public:
  Product(const std::string &name) : name_{name} {}

  std::string name() const { return name_; }

  friend bool operator==(const Product &lhs, const Product &rhs) {
    return lhs.name_ == rhs.name_;
  }

private:
  std::string name_;
};

class Order : public Document {
public:
  Order() = default;

  Order(const Order &) = default;

  Order &operator=(const Order &) = default;

  void add_product(const Product &product) {
    auto it =
        std::find_if(items.begin(), items.end(), [&product](const auto &item) {
          return item.first == product;
        });
    if (it == items.end()) {
      items.emplace_back(product, 1);
    } else {
      ++it->second;
    }
  }

private:
  void print(std::ostream &stream) const override {
    stream << "| Product | Quantity |\n";
    stream << "|---------|----------|\n";
    for (auto &item : items) {
      auto &product = item.first;
      auto &quantity = item.second;
      stream << '|' << std::setw(9) << product.name() << '|' << std::setw(10)<< quantity << "|\n";
    }
  }

  std::unique_ptr<Document> clone() const override {
    return std::make_unique<Order>(*this);
  }

private:
  using Quantity = size_t;
  using Item = std::pair<Product, Quantity>;
  std::vector<Item> items;
};

int main() {
  Order order;
  order.add_product(Product{"apple"});
  order.add_product(Product{"beef"});
  order.add_product(Product{"milk"});

  std::cout << order;
}
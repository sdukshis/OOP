#include <iostream>
#include <memory>

class Logger {
public:
  virtual void trace(const std::string &msg) {
    std::clog << "TRACE: " << msg << std::endl;
  }
};

class ServiceLocator {
public:
  ServiceLocator() = default;

  ServiceLocator(const ServiceLocator &) = delete;

  ServiceLocator(ServiceLocator &&) = delete;

  ServiceLocator &operator=(const ServiceLocator &) = delete;

  ServiceLocator &operator=(ServiceLocator &&) = delete;

  static ServiceLocator &instance() {
    static std::unique_ptr<ServiceLocator> self(new ServiceLocator());
    return *self;
  }

  void logger(Logger *new_logger) { logger_ = new_logger; }

  Logger *logger() const { return logger_; }

private:
  Logger *logger_ = nullptr;
};

void process() {
  auto &&logger = ServiceLocator::instance().logger();
  if (logger) {
    logger->trace("process called");
  }
}

int main() {
  Logger default_logger;
  ServiceLocator::instance().logger(&default_logger);

  process();
}

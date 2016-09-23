//    SRP: The Single Responsibility Principle
//
// A CLASS SHOULD HAVE ONLY ONE REASON TO CHANGE.

// SRP violation
class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    const std::string & firstname() const;

    const std::string & lastname() const;

    void store(std::string &) const;
};

// Decoupling responsibilities

class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    const std::string & firstname() const;

    const std::string & lastname() const;
};

class PersonSerializer {
 public:
    void store(const Person &, std::string &) const;
};

// OCP: Open-Closed Principle
//
// SOFTWARE ENTITIES (CLASSES, MODULES, FUNCTIONS, ETC.)
// SHOULD BE OPEN FOR EXTENSION, BUT CLOSED FOR MODIFICATION.

#include <string>
#include <typeinfo>
#include <stdexcept>

class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    virtual ~Person();

    const std::string & firstname() const;

    const std::string & lastname() const;
};

class AristocraticPerson: public Person {
 public:
    AristocraticPerson(const std::string &title,
                       const std::string &firstname,
                       const std::string &lastname);

    const std::string & title() const;
};

std::string to_string(const Person &p) {
    if (typeid(Person) == typeid(p)) {
        return p.firstname() + " " + p.lastname();
    }
    if (typeid(AristocraticPerson) == typeid(p)) {
        const AristocraticPerson &ap = static_cast<const AristocraticPerson&>(p);
        return ap.title() + " " + ap.firstname() + " " + ap.lastname();
    }
    throw std::logic_error("Unknown class");
}



class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    virtual ~Person();

    const std::string & firstname() const;

    const std::string & lastname() const;

    virtual std::string to_string() const;
};

class AristocraticPerson: public Person {
 public:
    AristocraticPerson(const std::string &title,
                       const std::string &firstname,
                       const std::string &lastname);

    const std::string & title() const;

    std::string to_string() const override;
};

std::string to_string(const Person &p) {
    return p.to_string();
}
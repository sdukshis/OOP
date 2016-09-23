//      ISP: The Interface Segregation Principle
//
//  CLIENTS SHOULD NOT BE FORCED TO DEPEND UPON INTERFACES
//  THAT THEY DO NOT USE.

#include <string>

class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    virtual ~Person();

    const std::string & firstname() const;

    const std::string & lastname() const;

    virtual std::string to_string() const;
};

class Report {
 public:
    Report(const std::string &title,
           const Person *author);

    const std::string & title() const;

    const Person * person() const;

    virtual std::string to_string() const;
};


class Debugger {
 public:
    void debug(const Person &);

    void debug(const Report &);
};


// Extract Printable interface

class Printable {
 public:
    virtual ~Printable();

    virtual std::string to_string() const = 0;
};

class Person: public Printable {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    virtual ~Person();

    const std::string & firstname() const;

    const std::string & lastname() const;

    std::string to_string() const override;    
};

class Report: public Printable {
 public:
    Report(const std::string &title,
           const Person *author);

    const std::string & title() const;

    const Person * person() const;

    std::string to_string() const override;
};


class Debugger {
 public:
    void debug(const Printable &);
};

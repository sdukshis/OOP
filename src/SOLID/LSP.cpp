//        LSP: The Liskov Substitution Principle
//
// FUNCTIONS THAT USE POINTERS OR REFERENCES TO BASE
// CLASSES MUST BE ABLE TO USE OBJECTS OF DERIVED CLASSES
// WITHOUT KNOWING IT.


class Person {
 public:
    Person(const std::string &firstname,
           const std::string &lastname);

    virtual ~Person();

    const std::string & firstname() const;

    const std::string & lastname() const;

    virtual void set_firstname(const std::string &firstname) {
        firstname_ = firstname;
    }
};

class AristocraticPerson: public Person {
 public:
    AristocraticPerson(const std::string &title,
                       const std::string &firstname,
                       const std::string &lastname);

    const std::string & title() const;

    virtual void set_firstname(const std::string &firstname) {
        assert(!firstname.empty());
        firstname_ = firstname;
    }
};

void change_firstname(Person &p, const std::string &newname) {
    p.set_firstname(newname);
}

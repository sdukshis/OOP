// DIP: The Dependency Inversion Principle
//
// A. HIGH LEVEL MODULES SHOULD NOT DEPEND UPON LOW
// LEVEL MODULES. BOTH SHOULD DEPEND UPON ABSTRACTIONS.

// B. ABSTRACTIONS SHOULD NOT DEPEND UPON DETAILS. DETAILS
// SHOULD DEPEND UPON ABSTRACTIONS.


// DIP violation
class JsonSerializer {
 public:
    void set_buffer(std::string &buffer);

    void put_key(const std::string &);

    void put_string(const std::string &);
};


class JsonPersonSerializer {
 public:
    void store(const Person &p, std::string &buffer) {
        JsonSerializer serializer;
        serializer.set_buffer(buffer);
        
        serializer.put_key("firstname");
        serializer.put_string(p.firstname());

        serializer.put_key("lastname");
        serializer.put_string(p.lastname());
    }
};


// Extract Serializer interface

class Serializer {
 public:
    virtual void set_buffer(std::string &buffer) = 0;

    void put_key(const std::string &) = 0;

    void put_string(const std::string &) = 0;
};


class PersonSerializer {
 public:
    PersonSerializer(Serializer &);

    void store(const Person &p, std::string &buffer) {
        serializer_.set_buffer(buffer);

        serializer_.put_key("firstname");
        serializer_.put_string(p.firstname());

        serializer_.put_key("lastname");
        serializer_.put_string(p.lastname());        
    }
 private:
    Serializer &serializer_;   
};

class JsonPersonSerializer: public Serializer {
 private:
    void set_buffer(std::string &) override;

    void put_key(const std::string &) override;

    void put_string(const std::string &) override;
};

class XmlPersonSerializer: public Serializer {
 private:
    void set_buffer(std::string &) override;

    void put_key(const std::string &) override;

    void put_string(const std::string &) override;
};

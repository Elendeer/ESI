#include <iostream>
#include <exception>
#include <string>

using namespace std;

class E {
protected :
    string _str;

public :
    E(const string & str);
    virtual ~E();

    virtual string what() const = 0;
};

E::E(const string & str) :
    _str(str) {}

E::~E() {}

class Error : public E {
private :

public :
    Error(const string & str);
    virtual ~Error();

    virtual string what() const;
};

Error::Error(const string & str) :
    E(str) {}

Error::~Error() {}

string Error::what() const {
    return _str;
}

int main () {
    try {
        throw Error("error test.");
    }
    catch (const E & e) {
        cout << e.what() << endl;
    }

    return 0;
}

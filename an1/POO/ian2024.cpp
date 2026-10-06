#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <exception>

class MarathonException : public std::exception {
    std::string msg;
public:
    MarathonException(std::string motiv) {
        msg = "eroare: " + motiv;
    }
    const char* what() const noexcept override { return msg.c_str(); }
};

class Proba {
public:
    Proba() = default;

    virtual ~Proba() = default;

    virtual double val() const = 0;

    virtual Proba* clone() const = 0;
};

class Sprint : public Proba {
    int tsec;
public:
    Sprint(int t) : Proba(), tsec(t) {}

    double val() const override {
        if (tsec<10) {
            return 10;
        }
        return 90.0 / tsec;
    }

    Sprint* clone() const override {
        return new Sprint(*this);
    }
};

class Cros : public Proba {
    int tmin;
public:
    Cros(int t) : Proba(), tmin(t) {}

    double val() const override {
        if (tmin<30) {
            return 10;
        }
        return 120.0 / tmin;
    }

    Cros* clone() const override {
        return new Cros(*this);
    }
};

class Maraton : virtual public Proba {
protected:
    int dkm;
public:
    Maraton(int d) : Proba(), dkm(d) {}

    double val() const override {
        if (dkm>50) {
            return 10;
        }
        return dkm/5.0;
    }

    Maraton* clone() const override {
        return new Maraton(*this);
    }
};

class Semi : public Maraton {
public:
    Semi(int d) : Proba(), Maraton(d) {}

    Semi* clone() const override {
        return new Semi(*this);
    }
};

class ProbaFactory {
public:
    static Proba* create(const std::string& tip, int extrainfo) {
        if (tip == "sprint") {
            return new Sprint(extrainfo);
        } else if (tip == "cros") {
            return new Cros(extrainfo);
        } else if (tip == "maraton") {
            return new Maraton(extrainfo);
        } else if (tip == "semi-maraton") {
            return new Semi(extrainfo);
        } else {
            throw MarathonException("nu exista acest tip de proba");
        }
    }
};

//----

struct fullname {
    std::string nume;
    std::string prenume;
};

struct Data {
    int zi;
    int luna;
    int an;
};

class Candidat {
    fullname name;
    Data bday;
    Proba* proba;
public:
    Candidat(fullname n, Data bday, const std::string& tip, int extrainfo) :
    name(n), bday(bday) {
        proba = ProbaFactory::create(tip, extrainfo);
    }
    ~Candidat() {
        delete proba;
    }

    Candidat(const Candidat& other) : name(other.name), bday(other.bday) {
        proba = other.proba->clone();
    }

    Candidat& operator=(const Candidat& other) {
        if (this == &other) {
            return *this;
        }

        this->name = other.name;
        this->bday = other.bday;

        delete proba;
        proba = other.proba->clone();

        return *this;
    }

    void afisare(std::ostream& os) const {
        os << name.nume << ' ' << name.prenume << ' ' << bday.zi << ' ' << bday.luna << ' ' << bday.an;
    }

    friend std::ostream& operator<<(std::ostream& os, const Candidat& c) {
        c.afisare(os);
        return os;
    }
     double getvalcand() const {
        return proba->val();
    }
};

template <typename T>
class Singleton {
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getinstance() {
        static T instance;
        return instance;
    }
};
class Event : public Singleton<Event> {
    friend class Singleton<Event>;
private:
    Event() = default;
    std::vector<Candidat> cand;
    static std::vector<std::string> acceptat;

public:
    void readcand() {
        std::string nume, prenume, tip;
        int zi, luna, an;
        int extrainfo;

        std::cout << "nume:";
        std::cin >> nume >> prenume;
        std::cout << "data nastere:";
        std::cin >> zi >> luna >> an;

        std::cout << "tip proba + info proba: ";
        std::cin >> tip >> extrainfo;

        cand.push_back(Candidat({nume, prenume}, {zi, luna, an}, tip, extrainfo));
    }

    void choose() {
        int limit = std::min(500, (int)cand.size());

        std::partial_sort(cand.begin(), cand.begin() + limit, cand.end(), [](const Candidat& c1, const Candidat& c2) {
            return c1.getvalcand() > c2.getvalcand();
        });

        cand.erase(cand.begin() + limit, cand.end());
    }

    void incheiere(const std::string& cod) {
        int found = 0;

        choose();

        for (auto a : acceptat) {
            if (a==cod) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            throw MarathonException("access denied");
        }
        for (auto c : cand) {
            std::cout << c << '\n';
        }
    }
};
std::vector<std::string> Event::acceptat = {"ID1", "ID2", "ID3"};

int main() {
    auto& event = Event::getinstance();

    std::cout << "== meniu event ==" << '\n';
    std::cout << "1 - adauga candidat" << '\n' << "2 - incheie inscrieri" << '\n' << "0 - exit" << '\n';

    try {
        int op;
        std::string cod;

        std::cin >> op;
        do {
            if (op == 1) {
                event.readcand();
            } else if (op == 2) {
                std::cin >> cod;
                event.incheiere(cod);
            }
            std::cin >> op;
        } while (op != 0);
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}

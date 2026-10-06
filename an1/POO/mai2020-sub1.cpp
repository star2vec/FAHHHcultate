#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
#include <chrono>
#include <unordered_map>

class PandemieException : public std::exception {
    std::string msg;
public:
    PandemieException(std::string motiv) {
        msg = "eroare: " + motiv;
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

enum Protectie {
    ffp0,
    ffp1,
    ffp2,
    ffp3
};

class Masca {
protected:
    Protectie protectie;
public:
    Masca(Protectie p) : protectie(p) {}
    virtual ~Masca() = default;

    virtual Masca* clone() const = 0;

    Protectie getproc() const { return protectie; }
};


class Chirurg : public Masca {
    std::string culoare;
    int nrpl;
public:
    Chirurg(Protectie p, const std::string& culoare, int nrpl) :
    Masca(p), culoare(culoare), nrpl(nrpl) {
        if (p == ffp0) {
            throw PandemieException("nu putem aveaacest tip de protectie");
        }
    }

    Chirurg* clone() const override {
        return new Chirurg(*this);
    }
};

class Policarb : public Masca {
    std::string prindere;

public:
    Policarb(const std::string& prindere) :
    Masca(ffp0), prindere(prindere) {}

    Policarb* clone() const override {
        return new Policarb(*this);
    }
};

//-----///

class Dezinfectant {
protected:
    int nrorg;
    std::vector<std::string> ingrediente;
    std::vector<std::string> suprafete;
    static int nrbact;
    static int nrfung;
    static int nrvir;

    int nrkilled;

    int id;
    static int cnt;
public:
    Dezinfectant(int n, const std::vector<std::string>& i, const std::vector<std::string>& s) :
    nrorg(n), ingrediente(i), suprafete(s), id(cnt++) {};

    virtual double eficienta() const = 0;

    std::ostream& afiseaza(std::ostream& os) const {
        os << id << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const Dezinfectant& d) {
        d.afiseaza(os);
        return os;
    }

    virtual Dezinfectant* clone() const = 0;

    int getid() const { return id; }
};
int Dezinfectant::nrbact = 1e9;
int Dezinfectant::nrfung = 1.5e6;
int Dezinfectant::nrvir = 1e8;
int Dezinfectant::cnt = 0;

class Bacterie : virtual public Dezinfectant {

public:
    Bacterie(int n, const std::vector<std::string>& i, const std::vector<std::string>& s) :
    Dezinfectant(n, i, s) {};

    double eficienta() const override {
        return nrkilled / nrbact;
    };

    Bacterie* clone() const override {
        return new Bacterie(*this);
    }
};

class Fungi : virtual public Dezinfectant {
public:
    Fungi(int n, const std::vector<std::string>& i, const std::vector<std::string>& s) :
    Dezinfectant(n, i, s) {};

    double eficienta() const override {
        return nrkilled / nrfung;
    };

    Fungi* clone() const override {
        return new Fungi(*this);
    }
};

class Virus : virtual public Dezinfectant {
public:
    Virus(int n, const std::vector<std::string>& i, const std::vector<std::string>& s) :
    Dezinfectant(n, i, s) {};
    double eficienta() const override {
        return nrkilled / nrvir;
    };

    Virus* clone() const override {
        return new Virus(*this);
    }
};

class Toate : public Bacterie, public Fungi, public Virus {
public:
    Toate(int n, const std::vector<std::string>& i, const std::vector<std::string>& s) :
    Dezinfectant(n, i, s), Bacterie(n, i, s), Fungi(n, i, s), Virus(n, i, s) {};
    double eficienta() const override {
        return Bacterie::eficienta() + Virus::eficienta() + Fungi::eficienta();
    }

    Toate* clone() const override {
        return new Toate(*this);
    }
};


///---------------///

class Achizitie {
    std::string data; /// aici putem sa bagam cu chrono cred???
    std::string client;
    std::vector<Masca*> masti;
    std::vector<Dezinfectant*> dezinf;

    static std::unordered_map<std::string, int> f;
public:
    Achizitie(const std::string& d, const std::string& c, const std::vector<Masca*>& mas, const std::vector<Dezinfectant*>& dez) :
    data(d), client(c), masti(mas), dezinf(dez) {
        f[client]++;
    }

    Achizitie& operator+=(Masca* m) {
        masti.push_back(m->clone());
        return *this;
    }
    Achizitie& operator+=(Dezinfectant* d) {
        dezinf.push_back(d->clone());
        return *this;
    }


    static std::string maxf() {
        int max = 0;
        std::string numemax;
        for (auto pereche : f) {
            if (pereche.second > max) {
                max = pereche.second;
                numemax = pereche.first;
            }
        }
        return numemax;
    }

    ~Achizitie() {
        for (auto m : masti) {
            delete m;
        }
        for (auto d : dezinf) {
            delete d;
        }
    }

    Achizitie(const Achizitie& other) : data(other.data), client(other.client) {
        for (auto m : other.masti) {
            masti.push_back(m->clone());
        }
        for (auto d : other.dezinf) {
            dezinf.push_back(d->clone());
        }
    }

    Achizitie& operator=(const Achizitie& other) {
        if (this == &other) {
            return *this;
        }

        this->data = other.data;
        this->client = other.client;

        for (auto m : masti) {
            delete m;
        }
        masti.clear();
        for (auto d : dezinf) {
            delete d;
        }
        dezinf.clear();

        for (auto m : other.masti) {
            masti.push_back(m->clone());
        }
        for (auto d : other.dezinf) {
            dezinf.push_back(d->clone());
        }

        return *this;
    }

    int totalcomanda() {
        int cost = 0;
        Protectie pr;

        for (auto m : masti) {
            if (dynamic_cast<Policarb*>(m) != nullptr) {
                cost+=20;
            } else {
                pr = m->getproc();
                if (pr == ffp1) {
                    cost += 5;
                } else if (pr == ffp2) {
                    cost += 10;
                } else {
                    cost += 15;
                }
            }
        }

        for (auto d : dezinf) {
            double ef = d->eficienta();

             if (ef >= 99) {
                cost += 50;
            } else if (ef >= 97.5) {
                cost += 40;
            } else if (ef >= 95) {
                cost += 30;
            } else if (ef >= 90) {
                cost += 20;
            } else {
                cost += 10;
            }
        }

        return cost;
    }
};
std::unordered_map<std::string, int> Achizitie::f;

//---------///

template <typename T>
class Singleton {
private:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getinstance() {
        static T instance;
        return instance;
    }
};

class Meniu : public Singleton<Meniu> {
    friend class Singleton<Meniu>;
private:
    Meniu() = default;
    std::vector<Masca*> masti;
    std::vector<Dezinfectant*> dezinf;
    std::vector<Achizitie*> achiz;

public:
    ~Meniu() {
        for (auto m : masti) {
            delete m;
        }
        for (auto d : dezinf) {
            delete d;
        }
        for (auto a : achiz) {
            delete a;
        }
    }

    Masca* readmasca() {
        std::string tip;

        std::cin >> tip;

        if (tip == "chirurgicala") {
            std::string pstr, culoare;
            int nrpl;
            Protectie p;

            std::cin >> pstr;

            if (pstr=="ffp1") {
                p = ffp1;
            } else if (pstr=="ffp2") {
                p = ffp2;
            } else if (pstr=="ffp3") {
                p = ffp3;
            }

            std::cin >> std::ws;
            std::getline(std::cin, culoare);
            std::cin >> nrpl;

            return new Chirurg(p, culoare, nrpl);
        } else if (tip == "policarbonat") {
            std::string pr;
            std::cin >> pr;

            return new Policarb(pr);
        } else {
            throw PandemieException("nu exista acest tip de masca");
        }
    }
    void addmasca() {
        Masca* m = readmasca();
        masti.push_back(m);
    }

    Dezinfectant* readdezinf() {
        std::string tip;
        int nrorg;
        std::vector<std::string> ingr;
        std::vector<std::string> supr;
        std::string x;
        int m, i;

        std::cin >> tip >> nrorg;

        std::cout << "cate ingrediente? ";
        std::cin >> m;
        for (i=0; i<m; i++) {
            std::cin >> x;
            ingr.push_back(x);
        }

        std::cout << "cate suprafete? ";
        std::cin >> m;
        for (i=0; i<m; i++) {
            std::cin >> x;
            supr.push_back(x);
        }

        if (tip == "bacterie") {
            return new Bacterie(nrorg, ingr, supr);
        } else if (tip == "fungi") {
            return new Fungi(nrorg, ingr, supr);
        } else if (tip == "virus") {
            return new Virus(nrorg, ingr, supr);
        }
    }
    void adddezinf() {
        Dezinfectant* d = readdezinf();
        dezinf.push_back(d);
    }

    void addachizitie() {
        std::string data; /// aici putem sa bagam cu chrono cred???
        std::string client;
        std::vector<Masca*> achmasti;
        std::vector<Dezinfectant*> achdezinf;
        int i, m;

        std::cin >> data >> client;

        std::cout << "cate masti? ";
        std::cin >> m;
        for (i=0; i<m; i++) {
            Masca* x = readmasca();
            achmasti.push_back(x);
        }
        std::cout << "cate dezinf? ";
        std::cin >> m;
        for (i=0; i<m; i++) {
            Dezinfectant* x = readdezinf();
            achdezinf.push_back(x);
        }

        achiz.push_back(new Achizitie(data, client, achmasti, achdezinf));
    }

    int bestdezinf() {
        int max, idmax;

        max = 0;
        for (auto d : dezinf) {
            if (d->eficienta() > max) {
                max = d->eficienta();
                idmax = d->getid();
            }
        }

        return idmax;
    }

    std::string fidel() {
        return Achizitie::maxf();
    }
};

int main() {
    return 0;
}
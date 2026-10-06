#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <exception>
#include <cmath>
#include <map>

/*
    to do:
    - constructorii
    - data sa fie cititia cu spatii
*/

class Masina {
    int an;
    std::string nume;
    int viteza;
    int greutate;

public:
    Masina(int an, const std::string& nume, int v, int g) :
    an(an), nume(nume), viteza(v), greutate(g) {}

    virtual ~Masina() = default;

    virtual Masina* clone() const = 0;

    virtual double autonomie() const = 0;
    virtual std::string getmodel() const = 0;

    int getgreutate() const { return greutate; }
    std::string getname() const { return nume; }

    void crestevit(int p) {
        viteza = viteza*(100+p)/100;
    }

};

enum Tip {
    BENZINA,
    MOTORINA
};

class Combustibila : virtual public Masina {
    Tip tip;
    int caprez;

public:
    Combustibila(int an, const std::string& nume, int v, int g,
        Tip tip, int cap) :
    Masina(an, nume, v, g), tip(tip), caprez(cap) {}

    Combustibila* clone() const override {
        return new Combustibila(*this);
    }

    double autonomie() const override {
        return (double) caprez / std::sqrt(this->getgreutate());
    }
    std::string getmodel() const override {
        return "combustibila";
    }
};

class Electrica : virtual public Masina {
    int capbat;

public:
    Electrica(int an, const std::string& nume, int v, int g, int cap) :
    Masina(an, nume, v, g), capbat(cap) {}

    Electrica* clone() const override {
        return new Electrica(*this);
    }

    double autonomie() const override {
        return (double) capbat / std::pow(this->getgreutate(), 2);
    }
    std::string getmodel() const override {
        return "electrica";
    }
};


class Hibrida : public Combustibila, public Electrica {
public:
    Hibrida(int an, const std::string& nume, int v, int g,
    Tip tip, int cr, int cb) :
    Masina(an, nume, v, g), Combustibila(an, nume, v, g, tip, cr),
    Electrica(an, nume, v, g, cb) {
    }

    Hibrida* clone() const override {
        return new Hibrida(*this);
    }

    double autonomie() const override {
        return Electrica::autonomie() + Combustibila::autonomie();
    }
    std::string getmodel() const override {
        return "hibrida";
    }
};

class CarFactory {
public:
    static Masina* create(const std::string& tipcar, int an,
        const std::string& nume, int vit, int greutate) {
        std::cout << "extra detalii: ";
        if (tipcar == "combustibila") {
            std::string tipstr;
            Tip tip;
            int cap;

            std::cin >> tipstr >> cap;
            if (tipstr=="benzina") {
                tip = BENZINA;
            } else if (tipstr=="motorina") {
                tip = MOTORINA;
            }

            return new Combustibila(an, nume, vit, greutate, tip, cap);
        } else if (tipcar == "electrica") {
            int cb;
            std::cin >> cb;
            return new Electrica(an, nume, vit, greutate, cb);
        } else if (tipcar == "hibrida") {
            std::string tipstr;
            Tip tip;
            int cr, cb;

            std::cin >> tipstr >> cr >> cb;
            if (tipstr=="benzina") {
                tip = BENZINA;
            } else if (tipstr=="motorina") {
                tip = MOTORINA;
            }

            return new Hibrida(an, nume, vit, greutate, tip, cr, cb);
        } else {
            throw std::invalid_argument("unknown tipcar");
        }

    }
};





//------------------

class Tranzactie {
    std::string client;
    std::string data;
    std::vector<Masina*> modele;
public:
    Tranzactie(const std::string& client, const std::string& data,
        const std::vector<Masina*>& modele) :
    client(client), data(data), modele(modele) {}

    const std::vector<Masina*>& getmodele() const {
        return modele;
    }
};

class Meniu {
    std::vector<Masina*> catalog;
    std::vector<Tranzactie> tranz;

    Meniu() = default;
public:
    Meniu(const Meniu&) = delete;
    Meniu& operator=(const Meniu&) = delete;

    ~Meniu() {
        for (auto m : catalog) {
            delete m;
        }
    }

    static Meniu& getmeniu() {
        static Meniu meniu;
        return meniu;
    }

    Masina* readcar() {
        std::string tipcar;
        int an, vit, greutate;
        std::string nume;

        std::cout << "tip masina: ";
        std::cin >> tipcar;

        std::cout << "detalii de baza: ";
        std::cin >> an >> nume >> vit >> greutate;

        return CarFactory::create(tipcar, an, nume, vit, greutate);
    }

    void addcatalog() {
        Masina* m;
        try {
            m = readcar();
        } catch (std::invalid_argument& e) {
            std::cout << "eroare citire" << std::endl;
            return;
        }
        catalog.push_back(m);
    }

    void addtranz() {
        int nrm, i, found;
        std::string client, data, nume;
        std::vector<Masina*> modele;

        std::cout << "detalii tranzactie: ";

        std::cin>>client;

        std::cin>>std::ws;
        std::getline(std::cin, data);

        std::cin >> nrm;
        for (i=0; i<nrm; i++) {
            std::cin >> nume;
            found = -1;
            for (auto m : catalog) {
                if (m->getname() == nume) {
                    modele.push_back(m);
                    found = 1;
                    break;
                }
            }

            if (found == -1) {
                std::cout << "masina nu exista" << std::endl;
            }
        }

        tranz.push_back(Tranzactie(client, data, modele));
    }

    double maxautonomie() {
        double max = 0;
        for (auto m : catalog) {
            if (m->autonomie() > max) {
                max = m->autonomie();
            }
        }
        return max;
    }

    std::string vandut() const {
        std::map<std::string, int> frecv;

        for (const auto& t : tranz) {
            for (auto m : t.getmodele()) {
                frecv[m->getname()]++;
            }
        }

        int max;
        std::string maxmodel;

        for (const auto& x : frecv) {
            if (x.second > max) {
                max = x.second;
                maxmodel = x.first;
            }
        }
        return maxmodel;
    }

    void optimizare(int p, const std::string& nume) {
        int idx = -1, i;
        for (i=0; i<catalog.size(); i++) {
            if (catalog[i]->getname() == nume) {
                idx = i;
            }
        }
        if (idx==-1) {
            std::cout << "masina nu exista";
            return;
        }
        catalog[idx]->crestevit(p);
    }
};





int main() {
    auto& meniu = Meniu::getmeniu();

    return 0;
}
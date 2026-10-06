#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>

enum Culoare {
    ROSU,
    GALBEN,
    ALBASTRU
};

class Unealta {
private:
    std::string serie;
    unsigned int nrserie;
    Culoare culoare;

    ///static std::vector<std::pair<std::string, unsigned int>> used;
public:
    Unealta(const std::string& serie, unsigned int nrserie, Culoare culoare) : serie(serie), nrserie (nrserie), culoare (culoare) {
        if (nrserie == 0 || serie.size() < 3) {
            throw std::invalid_argument("serie must be greater than 0");
        }

        /*
        for (auto u : used) {
            if (u.first == serie || u.second == nrserie) {
                throw std::invalid_argument("seria si numarul seriei trebuie sa fie unice");
            }
        }
        used.push_back({serie, nrserie});
        */
    }
    virtual ~Unealta() = default;

    virtual Unealta* clone() const = 0;

    virtual double timp(double area) const = 0;
    virtual double consum(double area) const = 0;
};
//std::vector<std::pair<std::string, unsigned int>> Unealta::used;

class Lopata : public Unealta {
private:
    double faras;
    double baterie;
public:
    Lopata (const std::string& serie, unsigned int nrserie, Culoare culoare, double faras, double baterie) : Unealta(serie, nrserie, culoare), faras(faras), baterie(baterie) {};

    Lopata* clone() const override {
        return new Lopata(*this);
    }

    double timp(double area) const override {
        return area / std::sqrt(faras);
    }
    double consum(double area) const override {
        return std::pow(area, 2) * baterie;
    }
};

class Drona : public Unealta {
private:
    double altmax;
    unsigned int nrmotor;

public:
    Drona (const std::string& serie, unsigned int nrserie, Culoare culoare, double altmax, unsigned int nrmotor) : Unealta(serie, nrserie, culoare), altmax(altmax), nrmotor(nrmotor) {};

    Drona* clone() const override {
        return new Drona(*this);
    }

    void turturi() {
        int sansa;

        sansa = std::rand() % 100;
        if (int(sansa) < 25) {
            throw std::runtime_error("turturi");
        }
        std::cout << "turturi: succes!!" << '\n';

    }

    double timp(double area) const override {
        return std::log(area) * std::tanh(altmax);
    }
    double consum(double area) const override {
        return area * std::pow(nrmotor, 3);
    }


};

template <typename T, typename U>
class Prototip : public Unealta {
    T pret;
    U viteza;
public:
    Prototip (std::string serie, unsigned int nrserie, Culoare culoare, T pret, U viteza) : Unealta(serie, nrserie, culoare), pret(pret), viteza(viteza) {}

    Prototip* clone() const override {
        return new Prototip(*this);
    }

    double timp(double area) const override {
        return area;
    }
    double consum(double area) const override {
        return area;
    }
};

class Echipa {
    std::string nume;
    std::string motto;
    std::vector<Unealta*> tools;
public:
    Echipa(const std::string& nume, const std::string& motto) : nume(nume), motto(motto) {};

    ~Echipa() {
        for (auto u : tools) {
            delete(u);
        }
    }

    Echipa (const Echipa& other) : nume(other.nume), motto(other.motto) {
        for (auto u : other.tools) {
            tools.push_back(u->clone());
        }
    }

    Echipa& operator= (Echipa other) {
        std::swap(nume, other.nume);
        std::swap(motto, other.motto);
        std::swap(tools, other.tools);

        return *this;
    }

    void addtool(Unealta* u) {
        tools.push_back(u);
    }

    std::string getnume() const {
        return nume;
    }

    double timpechipa(double area) const {
        if (tools.size() == 0) {
            return -1;
        }

        double t;
        t = 0;
        area = area / tools.size();
        for (auto u : tools) {
            t += u->timp(area);
        }
        return t;
    }
    double consumechipa(double area) const {
        if (tools.size() == 0) {
            return -1;
        }

        double c;
        c = 0;
        area = area / tools.size();
        for (auto u : tools) {
            c += u->consum(area);
        }
        return c;
    }
};

class Competitie {
private:
    std::vector<Echipa> echipe;
    Competitie() = default;
public:
    Competitie(const Competitie& comp) = delete;
    Competitie& operator= (const Competitie& comp) = delete;

    static Competitie& getcomp() {
        static Competitie comp;
        return comp;
    }

    void addechipa(const Echipa& e) {
        echipe.push_back(e);
    }

    void clasamenttimp(double area) {
        std::vector<Echipa> clasament = echipe;

        std::sort(clasament.begin(), clasament.end(),
            [area](const Echipa& x, const Echipa& y) {
                return x.timpechipa(area) < y.timpechipa(area);
            }
        );

        for (const auto& e : clasament) {
            std::cout << e.getnume() << ": " <<  e.timpechipa(area) << '\n';
        }

        std::cout << '\n';
    }

    void clasamentconsum(double area) {
        std::vector<Echipa> clasament = echipe;

        std::sort(clasament.begin(), clasament.end(),
            [area](const Echipa& x, const Echipa& y) {
                return x.consumechipa(area) < y.consumechipa(area);
            }
        );

        for (const auto& e : clasament) {
            std::cout << e.getnume() << ": " <<  e.consumechipa(area) << '\n';
        }
        std::cout << '\n';
    }
};

int main() {
    std::srand(time(nullptr));

    Echipa echipa1("lopatamaxxers", "daca nu esti gata te iau cu lopata");
    Echipa echipa2("vreau acasa", "cred ca vreau acasa");
    Echipa echipa3("francu", "trebuie sa apara francu in program");

    Unealta* lopata1 = new Lopata("LOP1", 201, ALBASTRU, 6.7, 100);
    Unealta* lopata2 = new Lopata("LOP2", 206, ROSU, 0.27, 145);
    Unealta* lopata3 = new Lopata("LOP3", 205, ALBASTRU, 6767, 123);
    Unealta* drona1 = new Drona("DRO1", 202, GALBEN, 6.9, 101);
    Unealta* drona2 = new Drona("DRO2", 202, ALBASTRU, 100.0, 8);

    Unealta* proto = new Prototip<double, int>("PRT1", 999, ROSU, 4500.50, 150);


    Drona* testdrona = dynamic_cast<Drona*>(drona1);
    if (testdrona != nullptr) {
        try {
            testdrona->turturi();
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << '\n';
        }
    }
    std::cout << '\n';

    echipa1.addtool(lopata1);
    echipa2.addtool(lopata2);
    echipa3.addtool(lopata3);
    echipa1.addtool(drona1);
    echipa2.addtool(drona2);
    echipa3.addtool(proto);

    auto& compa = Competitie::getcomp();

    compa.addechipa(echipa1);
    compa.addechipa(echipa2);
    compa.addechipa(echipa3);

    double area;
    area = 6767;

    compa.clasamenttimp(area);
    compa.clasamentconsum(area);

    return 0;
}

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <exception>
#include <random>

/* TO DO

exception: PENTRU CO2 SI PENTRU CEALLATA CHESTIE!!

SA FACEM STATIC CU ID????

*/

class EngineException : public std::exception {
private:
    std::string msg;
public:
    EngineException(const std::string& motiv) {
        msg = "eroare: " + motiv;
    }

    const char* what() const noexcept override { return msg.c_str(); }
};


class Echipament {
protected:
    std::string nume;
    int id;
    static int cnt;
    double pret;
public:
    Echipament(const std::string& nume, double pret): nume(nume), pret(pret), id(cnt++) {}
    virtual ~Echipament() = default;
    virtual double consum() const = 0;
};
int Echipament::cnt = 0;


class Incalzire : public Echipament {
double suprafata;
public:
    Incalzire(const std::string& nume, double pret, double s) :
    Echipament(nume, pret), suprafata(s) {}
    double consum() const override {
        return suprafata * pret;
    }
};

class Pompa : public Echipament {
    double intmet;
public:
    Pompa(const std::string& nume, double pret, double i) :
    Echipament(nume, pret), intmet(i) {}
    double consum() const override {
        return 1000/intmet;
    }
};

class Purificator : public Echipament {
public:
    Purificator(const std::string& nume, double pret) :
    Echipament(nume, pret) {}
    double consum() const override {
        int r = rand() % 7;

        if (r!=0) {
            return 100;
        } else {
           throw EngineException("1/7 eroare la purificator");
        }
    }
};


class Problema {
protected:
    std::string nume;
    int tstart;
    int prag;
    double indicator;

    int timplucrat;
    bool solved;
public:
    Problema(const std::string& nume, int t, double p) :
    nume(nume), tstart(t), prag(p), indicator(0), timplucrat(0), solved(false) {}

    virtual ~Problema() = default;
    virtual Problema* clone() const = 0;

    void raiseindicator() {
        if (!solved) {
            indicator = (100+rand()%10)*indicator/100 + 3.27/100;
        }
    }
    bool active() const { return indicator>prag && !solved;  }

    void work() {
        timplucrat+=15;
        if (timplucrat == 30) {
            solved = true;
            indicator = 0;
        }
    }
    virtual int priority() const = 0;
};

class Centrala : public Problema {
    int nretaje; ///aia cu 1 prioritate  medie???
public:
    Centrala(const std::string& nume, int t, double prag, int nre) :
        Problema(nume, t, prag), nretaje(nre) {}

    Centrala* clone() const override {
        return new Centrala(*this);
    }

    int priority() const override {
        if (nretaje == 1) {
            return 2;
        }
        return 3;
    }

};

class Apa : public Problema {
    int m3;
public:
    Apa(const std::string& nume, int t, double prag, int m3) :
        Problema(nume, t, prag), m3(m3) {}
    Apa* clone() const override {
        return new Apa(*this);
    }
    int priority() const override { return 1;  }
};

class Aer : public Problema {
    double nrpart;
    double co2;
public:
    Aer(const std::string& nume, int t, double p, double nr, double co2) :
    Problema(nume, t, p), nrpart(nr), co2(co2) {
        if (co2<400) {
            throw EngineException("nivelul de co2 trebuie sa fie peste 400");
        }
    }

    Aer* clone() const override {
        return new Aer(*this);
    }
    int priority() const override { return 3; }
};

class Factory {
public:
    static std::pair<Problema*, Echipament*> create(const std::string& tippb, const std::string& np, int tstart, double prag,
        const std::string& ne, double pret) {

        if (tippb == "centrala") {
            int nretaje;
            double suprafata;
            std::cout << "Etaje afectate si suprafata incalzire: ";
            std::cin >> nretaje >> suprafata;
            return {new Centrala(np, tstart, prag, nretaje), new Incalzire(ne, pret, suprafata)};

        } else if (tippb == "apa") {
            int m3; double intm;
            std::cout << "Metri cubi consumati si interval metrou: ";
            std::cin >> m3 >> intm;
            return {new Apa(np, tstart, prag, m3), new Pompa(ne, pret, intm)};

        } else if (tippb == "aer") {
            double nrpart, co2;
            std::cout << "Nr particule si CO2: ";
            std::cin >> nrpart >> co2;
            return {new Aer(np, tstart, prag, nrpart, co2), new Purificator(ne, pret)};

        } else {
            throw EngineException("tip de problema necunoscut");
        }
    }
};

template <typename T>
class Singleton {
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        static T instance;
        return instance;
    }
};

class Engine : public Singleton<Engine> {
    friend class Singleton<Engine>;
private:
    Engine() = default;
    std::vector<std::pair<Problema*, Echipament*>> sistem;
    std::vector<std::pair<Problema*, Echipament*>> backup;
    int timp = 0;
public:
    ~Engine() {
        for (auto& s : sistem) {
            delete s.first;
            delete s.second;
        }
    }

    void addSistem(Problema* p, Echipament* e) {
        sistem.push_back({p, e});
    }

    void tick() {
        timp+=15;
        std::cout << "timp rn: " << timp << std::endl;

        for (auto& s : sistem) {
            s.first->raiseindicator();
        }

        std::vector<std::pair<Problema*, Echipament*>> active;
        for (auto& s : sistem) {
            if (s.first->active()) {
                active.push_back(s);
            }
        }

        int k = std::min(2, (int)active.size());

        std::partial_sort(active.begin(), active.begin() + k, active.end(),
            [](const std::pair<Problema*, Echipament*>& a, const std::pair<Problema*, Echipament*>& b) {
                return a.first->priority() > b.first->priority();
            });

        for (int i = 0; i < k; i++) {
            auto& p = active[i].first;
            auto& e = active[i].second;

            try {
                double c = e->consum();
                std::cout << "consum: " << c << '\n';
                p->work();
            } catch(const EngineException& ex) {
                std::cout << ex.what() << '\n';
            }
        }
    }

    void faBackup() {
        for(auto& b : backup) {
            delete b.first;
            delete b.second;
        }
        backup.clear();
        for(auto& s : sistem) {
            backup.push_back({s.first->clone(), s.second});
        }
    }
};

int main() {
    auto& engine = Engine::getInstance();

    try {
        std::cout << "Baga o Centrala (ex: 2 150):\n";
        auto sistem1 = Factory::create("centrala", "Frig etaj", 0, 0.5, "Incalzitor1", 10);
        engine.addSistem(sistem1.first, sistem1.second);

        std::cout << "Baga un Purificator (ex: 50 450):\n";
        engine.addSistem(Factory::create("aer", "Aer inchis", 0, 0.2, "Purif1", 50).first,
                         Factory::create("aer", "Aer inchis", 0, 0.2, "Purif1", 50).second);
    } catch(const EngineException& e) {
        std::cout << e.what() << '\n';
    }

    for (int i = 0; i < 4; i++) {
        engine.tick();
    }

    return 0;
}

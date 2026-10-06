#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <exception>
#include <unordered_map>

/*TO DO:
de facut strategy pattern pentru lungime totala

poate deepcopy VS shallowcopy la chestia cu newcontracte???


*///

class InfrastructuraException : public std::exception {
private:
    std::string msg;
public:
    InfrastructuraException(const std::string& motiv) {
        msg = "eroare: " + motiv;
    }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class Drum {
protected:
    std::string denumire;
    double lung;
    int nrtrons;

public:
    Drum(int nrden, double l, int nt) : lung(l), nrtrons(nt) {
        if (nt == 0) {
            throw InfrastructuraException("nr tronsoane trebuie sa fie nenul");
        }
    }
    virtual std::string prefix() const = 0;

    virtual ~Drum() = default;

    double lungtrons() const { return lung / nrtrons; }

    virtual double cost() const {
        return 3000 * lungtrons();
    }

    virtual Drum* clone() const = 0;

    double getlung() const { return lung; }
    std::string getname() const { return denumire; }

    virtual void afisare(std::ostream& os) const {
        os << "[" << denumire << "] Lungime: " << lung << "km, Tronsoane: " << nrtrons;
    }

    friend std::ostream& operator<<(std::ostream& os, const Drum& d) {
        d.afisare(os);
        return os;
    }
};

class National : public Drum {
    int nrjud;
public:
    National(int nrden, double l, int nt, int nj) :
    Drum(nrden, l, nt), nrjud(nj) {
        denumire = prefix() + std::to_string(nrden);
    }

    std::string prefix() const override {
        return "DN";
    }

    double cost() const override {
        return Drum::cost();
    }

    National* clone() const override {
        return new National(*this);
    }

    void afisare(std::ostream& os) const override {
        Drum::afisare(os);
        os << ", Judete: " << nrjud;
    }
};

class European : virtual public Drum {
protected:
    int nrtari;
public:
    European(int nrden, double l, int nt, int ntari) :
    Drum(nrden, l, nt), nrtari(ntari) {
        denumire = prefix() + std::to_string(nrden);
    }

    std::string prefix() const override {
        return "E";
    }

    double cost() const override {
        return Drum::cost() + 500*nrtari;
    }

    European* clone() const override {
        return new European(*this);
    }

    void afisare(std::ostream& os) const override {
        Drum::afisare(os);
        os << ", Nr tari: " << nrtari;
    }
};

class Autostrada : virtual public Drum {
protected:
    int nrben;
public:
    Autostrada(int nrden, double l, int nt, int nb) :
    Drum(nrden, l, nt), nrben(nb) {
        denumire = prefix() + std::to_string(nrden);
    }

    std::string prefix() const override {
        return "A";
    }

    double cost() const override {
        return 2500 * nrben * lungtrons();
    }

    Autostrada* clone() const override {
        return new Autostrada(*this);
    }

    void afisare(std::ostream& os) const override {
        Drum::afisare(os);
        os << ", nrbenzi: " << nrben;
    }
};

class AutoEuro : public European, public Autostrada {
public:
    AutoEuro(int nrden, double l, int nt, int ntari, int nb) :
    Drum(nrden, l, nt), European(nrden, l, nt, ntari), Autostrada(nrden, l, nt, nb) {
        denumire = prefix() + std::to_string(nrden);
    }

    std::string prefix() const override {
        return "A";
    }

    double cost() const override {
        return Autostrada::cost() + 500*nrtari;
    }

    AutoEuro* clone() const override {
        return new AutoEuro(*this);
    }

    void afisare(std::ostream& os) const override {
        Drum::afisare(os);
        os << ", nrbenzi: " << nrben << ", Nr tari: " << nrtari;
    }
};

class DrumFactory {
public:
    static Drum* create(const std::string& tipdrum, int nrden, double lung, int nrtron) {
        int nr, nrtari, nrben;
        if (tipdrum == "national") {
            std::cin >> nr;
            return new National(nrden, lung, nrtron, nr);
        } else if (tipdrum == "european") {
            std::cin >> nr;
            return new European(nrden, lung, nrtron, nr);
        } else if (tipdrum == "autostrada") {
            std::cin >> nr;
            return new Autostrada(nrden, lung, nrtron, nr);
        } else if (tipdrum == "autostrada-europeana") {
            std::cin >> nrtari >> nrben;
            return new AutoEuro(nrden, lung, nrtron, nrtari, nrben);
        } else {
            throw InfrastructuraException("nu exista acest tip de drum");
        }
    }
};

//-------------///

class Contract {
    static int cnt;
    int id;
    std::string nume;
    std::string cif;

    std::string numedrum;
    int idxtr;

    static std::unordered_map<std::string, std::unordered_map<int, int>> f;
public:
    Contract(const std::string& nume, const std::string& cif, const std::string& nd, int idx) :
    nume(nume), cif(cif), id(cnt++), numedrum(nd), idxtr(idx) {
        f[numedrum][idxtr]++;
        if (f[numedrum][idxtr] > 1) {
            throw InfrastructuraException("indicele deja e considerat pentru acest drum");
        }
    }

    static void elibereazadrum(const std::string& numedrum, int idxtr) {
        f[numedrum][idxtr]--;
    }

    std::string getdrum() const { return numedrum; }
    int getidxtr() const { return idxtr; }
    std::string getcif() const { return cif; }

    friend std::ostream& operator<<(std::ostream& os, const Contract& c) {
        os << "Contract #" << c.id << " - Firma: " << c.nume
           << " (CIF: " << c.cif << "), Drum: " << c.numedrum << ", Tronson: " << c.idxtr;
        return os;
    }
};
int Contract::cnt = 0;
std::unordered_map<std::string, std::unordered_map<int, int>> Contract::f;

template <typename T>
class Singleton {
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getinstance() {
        static T miau;
        return miau;
    }
};
class Aplicatie : public Singleton<Aplicatie> {
    friend class Singleton<Aplicatie>;
private:
    Aplicatie() = default;
    std::vector<Drum*> drumuri;
    std::vector<Contract> contracte;

public:
    ~Aplicatie() {
        for (auto d : drumuri) {
            delete d;
        }
    }

    void readdrum() {
        std::string tipdrum;
        int nrden;
        double lung;
        int nrtrons;

        std::cin >> tipdrum >> nrden >> lung >> nrtrons;

        drumuri.push_back(DrumFactory::create(tipdrum, nrden, lung, nrtrons));
    }

    void readContract() {
        std::string nume;
        std::string cif;
        std::string numedrum;
        int idxtr;

        std::cin >> nume >> cif >> numedrum >> idxtr;

        contracte.push_back(Contract(nume, cif, numedrum, idxtr));
    }

    double lungtotala() const {
        double ltot = 0;

        for (auto d : drumuri) {
            ltot += d->getlung();
        }

        return ltot;
    }

    double lungtotauto() const {
        double ltot = 0;

        for (auto d : drumuri) {
            if (dynamic_cast<Autostrada*>(d) != nullptr ||
                dynamic_cast<AutoEuro*>(d) != nullptr) {
                ltot += d->getlung();
            }
        }

        return ltot;
    }

    double totalcost(const std::string& numedrum) const {
        double cost = 0;
        for (auto c : contracte) {
            if (c.getdrum() == numedrum) {
                int idx = -1;
                for (int i=0; i<drumuri.size(); i++) {
                    if (drumuri[i]->getname() == numedrum) {
                        idx = i;
                        break;
                    }
                }
                if (idx != -1) {
                    cost += drumuri[idx]->cost();
                }
            }
        }
        return cost;
    }

    void delcif(const std::string& cif) {
        std::vector<Contract> newcontracte;

        for (auto c : contracte) {
            if (c.getcif() != cif) {
                newcontracte.push_back(c);
            } else {
                Contract::elibereazadrum(c.getdrum(), c.getidxtr());
            }
        }

        contracte = newcontracte;
    }

    void afisaredrumuri() const {
        for (auto d : drumuri) {
            std::cout << *d << '\n';
        }
    }

    void afisarecntracte() const {
        for (const auto& c : contracte) {
            std::cout << c << '\n';
        }
    }
};


int main() {
    auto& app = Aplicatie::getinstance();

    int op;
    std::cin >> op;
    do {
        ///restul de optiuni aici
        std::cin >> op;
    } while (op!=0);

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <exception>


///// to do - citire cu ws get la tip campanie

class MarketingException : public std::exception {
private:
    std::string msg;
public:
    MarketingException(const std::string& motiv) {
        msg = "eroare: " + motiv;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};


//// de facut constructori

class Actiune {
protected:
    std::string denumire;
    int id;
    static int cnt;
    std::string data; //// AICI VOIAM AIA CU DATA
    int buget;
public:
    Actiune(const std::string& den, const std::string& data) :
   denumire(den), id(cnt++), data(data), buget(0) {}

    Actiune(const std::string& den, const std::string& data, double buget) :
    denumire(den), id(cnt++), data(data), buget(buget) {
        if (buget <= 0) {
            throw MarketingException("bugetul trebuie sa fie pozitiv");
        }
    }

    virtual ~Actiune() = default;

    virtual Actiune* clone() const = 0;

    virtual double cost() const = 0;
    double getbuget() const { return buget; }


    virtual void afisare(std::ostream& os, int nivel = 0) const {
        os << std::string(nivel * 4, ' ') << "- " << denumire << " (ID: " << id << ")\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Actiune& act) {
        act.afisare(os);
        return os;
    }

    virtual void extract(std::vector<Actiune*>& collect) const = 0;

};
int Actiune::cnt = 0;

class Simpla : public Actiune {
public:
    Simpla(const std::string& den, const std::string& data, double buget) :
        Actiune(den, data, buget) {}
    virtual ~Simpla() = default;
    void extract(std::vector<Actiune*>& collect) const override {
        collect.push_back(this->clone());
    }
    virtual Simpla* clone() const override = 0;
};

class Postare : public Simpla {
    int nrcan;
    bool video;
public:
    Postare(const std::string& den, const std::string& data, double buget, int nrcan, bool video) :
        Simpla(den, data, buget), nrcan(nrcan), video(video) {}

    Postare* clone() const override {
        return new Postare(*this);
    }

    double cost() const override {
        return buget * nrcan;
    }
};

class Reclama : public Simpla {
    std::string platforma;
    double cpc;
    int nrclick;

public:
    Reclama(const std::string& den, const std::string& data, double buget, const std::string& plat, double cpc, int nrclick) :
        Simpla(den, data, buget), platforma(plat), cpc(cpc), nrclick(nrclick) {}

    Reclama* clone() const override {
        return new Reclama(*this);
    }

    double cost() const override {
        double rez;
        rez = cpc * nrclick;
        if (buget > 5000) {
            rez = rez*110.0/100.0;
        }
        return rez;
    }
};

class Compusa : public Actiune {
    std::vector<Actiune*> act;
public:
    Compusa(const std::string& den, const std::string& data, std::vector<Actiune*> act) :
    Actiune(den, data), act(act) {
        if (act.size() == 0) {
            throw MarketingException("nu poate fi frunza");
        }
        if (act.size() < 2) {
            throw MarketingException("minim 2 copii");
        }
        for (auto a : act) {
            buget += a->getbuget();
        }
    }

    ~Compusa() {
        for (auto a : act) {
            delete a;
        }
    }

    Compusa(const Compusa& other) : Actiune(other.denumire, other.data) {
        for (auto a : other.act) {
            act.push_back(a->clone());
        }
    }

    Compusa& operator=(const Compusa& other) {
        if (this == &other) {
            return *this;
        }
        for (auto a : act) {
            delete a;
        }
        act.clear();

        for (auto a : other.act) {
            act.push_back(a->clone());
        }
        return *this;
    }

    Compusa* clone() const override {
        return new Compusa(*this);
    }

    void extract(std::vector<Actiune*>& collect) const override {
        for (auto a : act) {
            a->extract(collect);
        }
    }

    void afisare(std::ostream& os, int nivel = 0) const override {
        os << std::string(nivel * 4, ' ') << "=> [Compusa] " << denumire << " (ID: " << id << ")\n";

        for (const auto& a : act) {
            a->afisare(os, nivel + 1);
        }
    }

    double cost() const override {
        double c = 0.0;
        for (auto a : act) {
            c += a->cost();
        }
        if (act.size() <= 3) {
            c = c*105.0/100.0;
        } else {
            c = c*110.0/100.0;
        }
        return c;
    }
};


///---------

class Campanie {
    static int cnt;
    int id;
    std::string tip;
    std::string nume;
    std::string companie;

    std::vector<Actiune*> act;

public:
    Campanie(const std::string& tip, const std::string& nume) : tip(tip), nume(nume) {
        if (tip == "persoana juridica") {
            throw MarketingException("trebuie specificat numele companiei");
        }
    }
    Campanie(const std::string& tip, const std::string& nume, const std::string& companie) :
    tip(tip), nume(nume), companie(companie) {}

    void afis() {
        std::cout << tip << " " << nume << std::endl;
        for (auto a : act) {
            std::cout << *a << std::endl;
        }
    }

    ~Campanie() {
        for (auto a : act) {
            delete a;
        }
    }

    Campanie(const Campanie& other) : id(other.id), tip(other.tip), nume(other.nume), companie(other.companie) {
        for (auto a : other.act) {
            act.push_back(a->clone());
        }
    }

    Campanie& operator=(const Campanie& other) {
        if (this == &other) {
            return *this;
        }

        for (auto a : act) {
            delete a;
        }
        act.clear();

        this->id = other.id;
        this->tip = other.tip;
        this->nume = other.nume;
        this->companie = other.companie;

        for (auto a : other.act) {
            act.push_back(a->clone());
        }

        return *this;
    }

    int getid() const { return id; }

    double costcampanie() const {
        double c = 0.0;

        for (auto a : act) {
            c += a->cost();
        }
        return c;
    }


    void aplatizare() {
        std::vector<Actiune*> newact;
        double cvechi = costcampanie();

        for (auto a : act) {
            a->extract(newact);
        }

        double newc = 0;
        for (auto a : newact) {
            newc += a->cost();
        }

        std::cout << "dif " << cvechi - newc;

        std::cout << "Confirmati? (1 pt DA): ";
        int op;
        std::cin >> op;

        if (op == 1) {
            for (auto a : act) {
                delete a;
            }
            act = newact;
        } else {
            for (auto a : newact) {
                delete a;
            }
        }
    }
};
int Campanie::cnt = 0;


template <typename T>
class Singleton {
protected:
    Singleton() = default;
public:
    // Stergem constructorul de copiere si operatorul de atribuire
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Returnam instanta prin REFERINTA (&)
    static T& getinstance() {
        static T instance;
        return instance;
    }
};
class Market : public Singleton<Market> {
    friend class Singleton<Market>;
private:
    Market() = default;
    std::vector<Actiune*> act;
    std::vector<Campanie> camp;

public:
    Market(const Market& other) = delete;
    Market& operator=(const Market& other) = delete;
    ///getinstance

    ~Market() {
        for (auto a : act) {
            delete a;
        }
    }

    void addsimpla() {
        ///// citire tip, date necesare, push_back vectori actiuni
    }

    void addactcamp() {}

    void addcampanie() {
        //citim date generale,
        // avem un vector cu indici ale actiunilor existante
        //cautam actiunile existente si facem un vector nou si cream campania asa (o sa cautam duoa id)
    }

    void addcompusa(std::vector<int>idx) {
        std::vector<Actiune*> children;
        int i;

        for (i=0; i<act.size(); i++) {
            auto it = std::find(idx.begin(), idx.end(), i);
            if (it != idx.end()) {
                children.push_back(act[i]->clone());
            }
        }

        act.push_back(new Compusa("compusa", "lkdlsj", children));
    }


    void costcamp(int id) {
        int idx, i;
        for (i=0; i<camp.size(); i++) {
            if (id == camp[i].getid()) {
                idx = i;
                break;
            }
        }

        std::cout << camp[idx].costcampanie() << std::endl;
    }

    ////asta face memory leaks!! tb sa afisam normal
    void filtrare() {
        std::vector<Actiune*> newact;

        for (auto a : act) {
            if (dynamic_cast<Compusa*>(a) != nullptr) {
                newact.push_back(a->clone());
            }
        }
    }

    void costtotal() {
        double c = 0.0;

        for (auto ca : camp) {
            c += ca.costcampanie();
        }

        std::cout << c << std::endl;
    }

    void afisact() {
        for (auto a : act) {
            std::cout << *a <<  std::endl;
        }
    }

    void afiscamp() {
        for (auto c : camp) {
            c.afis();
        }
    }

    void aplatizare(int id) {
        int idx = 0; /// aici e hardcoded
        camp[idx].aplatizare();
    }
};



int main() {
    auto& market = Market::getinstance();

    std::cout << "\n=== MENIU AGENTIE DE MARKETING ===\n";
    std::cout << "1. Adauga o actiune simpla (Postare/Reclama)\n"; // [cite: 210]
    std::cout << "2. Construieste o actiune compusa\n"; // [cite: 211]
    std::cout << "3. Afiseaza toate actiunile disponibile (ierarhic)\n"; // [cite: 212]
    std::cout << "4. Filtreaza actiunile dupa tip\n"; // [cite: 213]
    std::cout << "5. Creeaza o campanie noua\n"; // [cite: 214]
    std::cout << "6. Afiseaza toate campaniile (arborescent)\n"; // [cite: 215]
    std::cout << "7. Calculeaza costul total al unei campanii\n"; // [cite: 216]
    std::cout << "8. Calculeaza valoarea totala a tuturor campaniilor\n"; // [cite: 217]
    std::cout << "9. Aplatizeaza o campanie\n"; // [cite: 218]
    std::cout << "0. Iesire\n";
    std::cout << "Alege o optiune: ";

    int op;
    std::cin >> op;
    do {
        try {
            switch (op) {
                case 1:
                    market.addsimpla();
                    break;
                case 2:
                    // market.newcompusa(...); // aici poti citi un numar de id-uri inainte
                    std::cout << "Functionalitate in constructie.\n";
                    break;
                case 3:
                    market.afisact();
                    break;
                case 4:
                    market.filtrare();
                    break;
                case 5:
                    market.addcampanie();
                    break;
                case 6:
                    market.afiscamp();
                    break;
                case 7:
                    int id_campanie;
                    std::cout << "Introdu ID-ul campaniei: ";
                    std::cin >> id_campanie;
                    market.costcamp(id_campanie);
                    break;
                case 8:
                    market.costtotal();
                    break;
                case 9:
                    // int id_campanie;
                    // std::cin >> id_campanie;
                    // market.aplatizareCampanie(id_campanie);
                    std::cout << "Functionalitate in constructie.\n";
                    break;
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        std::cin >> op;
    } while (op != 0);

    return 0;
}

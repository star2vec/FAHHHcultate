#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <string>

/*
TO DO
nu prea merge citirea / meniul idk
*/

class Jucarie {
protected:
    std::string denumire;
    int dimensiune;
    std::string tip;

public:
    Jucarie(const std::string& den, int dim, const std::string& tip) :
    denumire(den), dimensiune(dim), tip(tip) {}

    virtual ~Jucarie() = default;

    virtual Jucarie* clone() const = 0;
};

class Clasica : public Jucarie {
    std::string material;
    std::string culoare;
    static int nrclas;

public:
    Clasica(const std::string& den, int dim, const std::string& tip,
        const std::string& cul, const std::string& mat) :
    Jucarie(den,dim,tip), culoare(cul), material(mat) {
        nrclas++;
    }

    Clasica* clone() const override {
        return new Clasica(*this);
    }

    static int getnr() {
        return nrclas;
    }
};
int Clasica::nrclas = 0;

class Educativa : virtual public Jucarie {
    std::string abilitate;
    static int nred;

public:
    Educativa(const std::string& den, int dim, const std::string& tip,
        const std::string& a) :
    Jucarie(den,dim,tip), abilitate(a) {
        nred++;
    }

    static void scadenr() { nred--; }

    Educativa* clone() const override {
        return new Educativa(*this);
    }

    static int getnr() {
        return nred;
    }
};
int Educativa::nred = 0;

class Electronica : virtual public Jucarie {
    int nrbat;
    static int nrel;

public:
    Electronica(const std::string& den, int dim, const std::string& tip,
        int n) :
    Jucarie(den,dim,tip), nrbat(n) {
        nrel++;
    }

    static void scadenr() { nrel--; }

    Electronica* clone() const override {
        return new Electronica(*this);
    }

    static int getnr() {
        return nrel;
    }
};
int Electronica::nrel = 0;

class Moderna : public Electronica, public Educativa {
    std::string brand;
    std::string model;
    static int nrmod;

public:
    Moderna(const std::string& den, int dim, const std::string& tip,
        const std::string b, const std::string& m) :
    Jucarie(den,dim,tip), Educativa(den, dim, tip, "generala"), Electronica(den, dim, tip, 1),
    brand(b), model(m) {
        nrmod++;
        Electronica::scadenr();
        Educativa::scadenr();
    }

    Moderna* clone() const override {
        return new Moderna(*this);
    }

    static int getnr() {
        return nrmod;
    }
};
int Moderna::nrmod = 0;

//------------//

class ToyFactory {
public:
    static Jucarie* create(const std::string& toy, const std::string& den, int dim, const std::string& tip) {
        if (toy == "clasica") {
            std::string mat, cul;
            std::cout << "detalii: ";
            std::cin >> mat >> cul;
            return new Clasica(den, dim, tip, mat, cul);
        } else if (toy == "educativa") {
            std::string ab;
            std::cout << "detalii: ";
            std::cin >> ab;
            return new Educativa(den, dim, tip, ab);
        } else if (toy == "electronica") {
            int nb;
            std::cout << "detalii: ";
            std::cin >> nb;
            return new Electronica(den, dim, tip, nb);
        } else if (toy == "moderna") {
            std::string b, m;
            std::cout << "detalii: ";
            std::cin >> b >> m;
            return new Moderna(den, dim, tip, b, m);
        } else {
            throw std::invalid_argument("nu exista acest tip de jucarie");
        }
    }
};

//------------------//

struct fullname {
    std::string nume;
    std::string prenume;
};

enum statuscopil {
    CUMINTE,
    NEASTAMPARAT
};

class Copil {
    int id;
    static int cnt;
    fullname nume;
    int varsta;
    int nrfapte;
    std::vector<Jucarie*> toys;
    statuscopil status;
    int nrdul;
    int nrcarb;

public:
    Copil(fullname n, int v, int nf, statuscopil sc, int nr) :
    id(cnt++), nume(n), varsta(v), nrfapte(nf), status(sc) {
        if (status == CUMINTE) {
            nrdul = nr;
            nrcarb = 0;
        } else {
            nrcarb = nr;
            nrdul = 0;
        }

        if (status == CUMINTE && nrfapte < 10) {
            throw std::runtime_error("copilul nu e suficient de cuminte");
        }
    }

    ~Copil() {
        for (auto t : toys) {
            delete t;
        }
    }

    Copil(const Copil& other) :
    id(other.id), nume(other.nume), varsta(other.varsta),
    nrfapte(other.nrfapte), status(other.status), nrdul(other.nrdul), nrcarb(other.nrcarb){
        for (auto x : other.toys) {
            this->toys.push_back(x->clone());
        }
    }

    Copil& operator=(const Copil& other) {
        if (this==&other) {
            return *this;
        }
        for (auto x : toys) {
            delete x;
        }
        toys.clear();

        this->id = other.id;
        this->varsta = other.varsta;
        this->nume = other.nume;
        this->nrdul = other.nrdul;
        this->nrcarb = other.nrcarb;
        this->status = other.status;
        this->nrfapte = other.nrfapte;

        for (auto x : other.toys) {
            this->toys.push_back(x->clone());
        }

        return *this;
    }

    void addtoy() {
        std::string tiptoy;
        Jucarie* toy;
        std::string den, tip;
        int dim;

        std::cout << "tip: ";
        std::cin >> tiptoy;
        std::cout << "detalii de baza: ";
        std::cin >> den >> dim >> tip;

        toy = ToyFactory::create(tiptoy, den, dim, tip);
        toys.push_back(toy);
    }

    void citire(int m) {
        int i;
        for (i=0; i<m; i++) {
            addtoy();
        }
    }

    int getvarsta() const { return varsta; }
    int getfapte() const { return nrfapte; }
    int getid() const { return id; }

    std::string getnume() const { return nume.nume; }
    std::string getprenume() const { return nume.prenume; }

    void raisefapte(int x) {
        nrfapte += x;
    }


};
int Copil::cnt = 0;


class MosCraciun {
private:
    std::vector<Copil> children;
    MosCraciun() = default;
public:
    MosCraciun(const MosCraciun&) = delete;
    MosCraciun& operator=(const MosCraciun&) = delete;

    static MosCraciun& mos() {
        static MosCraciun m;
        return m;
    }

    void addcopil(Copil c) {
        children.push_back(c);
    }

    void citire(int n) {
        int i, v, nrfap, nr, valid;
        std::string nume, prenume, st;
        statuscopil status;
        for (i=0; i<n; i++) {
            valid = 0;
            do {
                try {
                    std::cout << "date copil: ";
                    std::cin >> nume >> prenume >> v >> nrfap >> st >> nr;
                    if (st == "neastamparat") {
                        status = NEASTAMPARAT;
                    } else {
                        status = CUMINTE;
                    }
                    addcopil(Copil({nume, prenume}, v, nrfap, status, nr));
                    valid = 1;
                } catch (std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
            } while (valid==0);
        }
    }

    void afisare() const {
        for (auto c : children) {
            //.. afsaee aici
        }
    }

    void numecopil(const std::string& search) const {
        int found = 0;
        for (auto c : children) {
            if (c.getnume().find(search) != std::string::npos ||
                c.getprenume().find(search) != std::string::npos) {
                std::cout << "gasit: " << c.getid() << " " << c.getnume() << std::endl;
                found = 1;
            }
        }
        if (found == 0) {
            std::cout << "nu exista" << std::endl;
        }
    }

    void sortvarsta() {
        std::sort(children.begin(), children.end(), [](const Copil& c1, const Copil& c2) {
            return c1.getvarsta() < c2.getvarsta();
        });
    }

    void sortfapte() {
        std::sort(children.begin(), children.end(), [](const Copil& c1, const Copil& c2) {
            return c1.getfapte() < c2.getfapte();
        });
    }

    void raise(int x, int id) {
        int i, idx = -1;
        for (i=0; i<children.size(); i++) {
            if (children[i].getid() == id) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            std::cout << "copilul nu exista";
            return;
        }
        children[idx].raisefapte(x);
        children[idx].citire(x);
    }

    void raport() const {
        int nr, nrclas, nred, nrel, nrmod;

        nrclas = Clasica::getnr();
        nred = Educativa::getnr();
        nrel = Electronica::getnr();
        nrmod = Moderna::getnr();

        nr = nrclas + nred + nrel + nrmod;

        std::cout << nr << ' ' << nrclas << ' ' << nred << ' ' << nrel << ' ' << nrmod << std::endl;
    }
};


int main() {
    auto& mos = MosCraciun::mos();
    int n, op, x, id;

    std::cout << "meniu: 1) citire, 2) afisare, 3) gaseste nume, 4)sortare varsta,"
                 " 5) sortare fapte, 6) raise, 7) raport, 8) exit" << '\n';

    std::string nume;
    std::cin >> op;
    while (op!=8) {
        switch (op) {
            case 1:
                std::cin >> n;
                mos.citire(n);
                break;
            case 2:
                mos.afisare();
                break;
            case 3:
                std::cin >> nume;
                mos.numecopil(nume);
                break;
            case 4:
                mos.sortvarsta();
                break;
            case 5:
                mos.sortfapte();
                break;
            case 6:
                std::cin >> id >> x;
                mos.raise(id, x);
                break;
            case 7:
                mos.raport();
                break;
        }

        std::cin>>op;
    }


    return 0;
}
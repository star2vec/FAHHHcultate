#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>

enum CategorieArtefact {
    ISTORIC,
    ARTISTIC,
    PRETIOS
};

class Artefact {
protected:
    int id;
    std::string nume;
    std::string data;
    double pret;
    double final;

public:
    Artefact(int id, const std::string& nume, const std::string& data, double pret) : id(id), nume(nume), data(data), pret(pret) {}
    virtual ~Artefact() = default;

    virtual Artefact* clone() const = 0;

    virtual CategorieArtefact getcateg() const = 0;

    double getpret() const {
        return pret;
    }
    double getid() const {
        return id;
    }
    void setfinal(double pretfinal) {
        final = pretfinal;
    }
    double getfinal() const {
        return final;
    }
};

class Istoric : public Artefact {
private:
    std::string personalitate;
public:
    Istoric(int id, const std::string& nume, const std::string& data, double pret, const std::string& personalitate) :
    Artefact(id, nume, data, pret), personalitate(personalitate) {}

    Istoric* clone() const override {
        return new Istoric(*this);
    }

    CategorieArtefact getcateg() const override {
        return ISTORIC;
    }
};

enum Tip {
    PICTURA,
    SCULPTURA
};
enum Material {
    ACRILIC,
    ULEI,
    LEMN,
    PIATRA,
    MARMURA
};
class Artistic : public Artefact {
private:
    Tip tip;
    Material material;
public:
    Artistic(int id, const std::string& nume, const std::string& data, double pret, Tip tip, Material material) :
    Artefact(id, nume, data, pret), material(material), tip(tip) {}

    Artistic* clone() const override {
        return new Artistic(*this);
    }

    CategorieArtefact getcateg() const override {
        return ARTISTIC;
    }
};


class Pretios : public Artefact {
private:
    std::string designer;
    double greutate;

public:
    Pretios(int id, const std::string& nume, const std::string& data, double pret,  double greutate, const std::string& designer = "necunoscut") :
    Artefact(id, nume, data, pret), designer(designer), greutate(greutate) {}

    Pretios* clone() const override {
        return new Pretios(*this);
    }

    CategorieArtefact getcateg() const override {
        return PRETIOS;
    }
};


class Entitate {
protected:
    int nrunic;
    int buget;
    int pas;
    int confort;
    CategorieArtefact preferat;
    CategorieArtefact ignorat;

    std::vector<Artefact*> cump;
public:
    Entitate(int nrunic, int buget, int pas, int confort, CategorieArtefact preferat, CategorieArtefact ignorat) :
    nrunic(nrunic), buget(buget), pas(pas), confort(confort), preferat(preferat), ignorat(ignorat) {}

    virtual Entitate* clone() const = 0;
    virtual ~Entitate() = default;

    virtual bool continua(CategorieArtefact categorie, double pret) const = 0;

    int getpas() const {
        return pas;
    }

    virtual void win(Artefact* a, double pret) {
        buget -= pret;
        cump.push_back(a);
        std::cout << "entitatea " << nrunic << "a castigat pentru " << pret << " lei!!\n";
    }

    int nrcump() const {
        return cump.size();
    }

    int getnrunic() const {
        return nrunic;
    }
};

class PersFizica : public Entitate {
    std::string nume;
public:
    PersFizica(int nrunic, int buget, int pas, int confort, CategorieArtefact preferat, CategorieArtefact ignorat, const std::string& nume) :
    Entitate(nrunic, buget, pas, confort, preferat, ignorat), nume(nume) {}

    PersFizica* clone() const override {
        return new PersFizica(*this);
    }

    bool continua(CategorieArtefact categ, double pret) const override {
        if (categ == ignorat) {
            return false;
        }
        if (pret+pas > buget) {
            return false;
        }
        if (categ==preferat) {
            return true;
        }
        if (pret+pas <= confort) {
            return true;
        }
        return false;
    }
};

class PersJuridica : public Entitate {
    std::string nume;
    std::vector<PersFizica*> persoane;
public:
    PersJuridica(int nrunic, int buget, int pas, int confort, CategorieArtefact preferat, CategorieArtefact ignorat, const std::string& nume, std::vector<PersFizica*> persoane) :
    Entitate(nrunic, buget, pas, confort, preferat, ignorat), nume(nume), persoane(persoane) {}

    PersJuridica* clone() const override {
        return new PersJuridica(*this);
    }

    bool continua(CategorieArtefact categ, double pret) const override {
        if (categ == ignorat) {
            return false;
        }
        if (pret+pas > buget) {
            return false;
        }

        int nrp;
        nrp = 0;
        for (auto p : persoane) {
            if (p->continua(categ, pret) == true) {
                nrp++;
            }
        }
        if (nrp >= persoane.size()/2) {
            return true;
        }
        if (nrp>=1 && categ == preferat) {
            return true;
        }
        return false;
    }
};

class Licitatie {
private:
    std::vector<Entitate*> participanti;
    std::vector<Artefact*> inventory;
    std::vector<Artefact*> istoric;
    Licitatie() = default;
    ~Licitatie() {
        for (auto p : participanti) delete p;
        for (auto a : inventory) delete a;
        for (auto a : istoric) delete a;
    }
public:
    Licitatie(const Licitatie&) = delete;
    Licitatie& operator=(const Licitatie&) = delete;

    static Licitatie& getlicitatie() {
        static Licitatie licitatie;
        return licitatie;
    }

    void addpart(Entitate* p) {
        participanti.push_back(p);
    }
    void addart(Artefact* a) {
        inventory.push_back(a);
    }

    void simulare(int id) {
        int i, sterge;
        Artefact* art;
        art = nullptr;

        sterge = -1;
        for (i=0; i<inventory.size(); i++) {
            if (inventory[i]->getid() == id) {
                art = inventory[i];
                sterge = i;
                break;
            }
        }
        if (art == nullptr) {
            std::cout << "nu am gasit" << '\n';
            return;
        }

        double pret;
        pret = art->getpret();

        bool ongoing;
        Entitate* lider;
        ongoing = true;
        lider = nullptr;
        while (ongoing==true) {
            ongoing = false;
            for (auto p : participanti) {
                if (p != lider) {
                    if (p->continua(art->getcateg(), pret)) {
                        pret += p->getpas();
                        lider = p;
                        ongoing = true;
                        std::cout << "oferta: " << pret << " lei!!\n";
                    }
                }
            }
        }

        if (lider!=nullptr) {
            lider->win(art, pret);
            art->setfinal(pret);
            istoric.push_back(art);
            inventory.erase(inventory.begin()+sterge);
        }
    }

    void afispart() {
        std::vector<Entitate*> pord = participanti;

        std::sort(pord.begin(), pord.end(), [](Entitate* x, Entitate* y) {
            return x->nrcump() > y->nrcump();
        });

        for (auto p : pord) {
            std::cout << p->getnrunic() << ' ' << p->nrcump() << '\n';
        }
        std::cout << '\n';
    }

    void afisart() {
        std::vector<Artefact*> aord = istoric;

        std::sort(aord.begin(), aord.end(), [](Artefact* x, Artefact* y) {
            return x->getfinal() > y->getfinal();
        });

        for (auto a : aord) {
            std::cout << a->getid() << '\n';
        }
        std::cout << '\n';
    }

};

int main() {
    Artefact* a1 = new Istoric(101, "Sabie veche", "Evul Mediu", 500.0, "Stefan cel Mare");
    Artefact* a2 = new Artistic(102, "Mona Lisa 2", "Renastere", 1000.0, PICTURA, ULEI);
    Artefact* a3 = new Pretios(103, "Inel aur", "Antichitate", 200.0, 15.5);

    PersFizica* p1 = new PersFizica(1, 2000, 100, 800, ISTORIC, PRETIOS, "Andrei");
    PersFizica* p2 = new PersFizica(2, 5000, 200, 1500, ARTISTIC, ISTORIC, "Maria");
    PersFizica* p3 = new PersFizica(3, 1000, 50, 400, PRETIOS, ARTISTIC, "Gelu");

    std::vector<PersFizica*> reprezentanti;
    reprezentanti.push_back(p1);
    reprezentanti.push_back(p2);

    PersJuridica* firma = new PersJuridica(4, 15000, 500, 5000, ARTISTIC, PRETIOS, "Q&V Corp", reprezentanti);

    auto& licitatia = Licitatie::getlicitatie();

    licitatia.addart(a1);
    licitatia.addart(a2);
    licitatia.addart(a3);

    licitatia.addpart(p1);
    licitatia.addpart(p2);
    licitatia.addpart(p3);
    licitatia.addpart(firma);

    std::cout << "--- LICITATIA 1 (ISTORIC) ---\n";
    licitatia.simulare(101);

    std::cout << "\n--- LICITATIA 2 (ARTISTIC) ---\n";
    licitatia.simulare(102);

    std::cout << "\n--- LICITATIA 3 (PRETIOS) ---\n";
    licitatia.simulare(103);

    licitatia.afispart();
    licitatia.afisart();

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Produs {
protected:
    double pret;
    int cantitate;
    int ID;
    static int cnt;
public:
    Produs(double p, int c) : pret(p), cantitate(c), ID(cnt++) {}

    virtual ~Produs() {}

    virtual Produs* clone() const = 0;

    int getid() const { return ID; }
    int getcant() const { return cantitate; }
    double getpret() const { return pret; }

    void setpret(double p) { pret = p; }
    void setcant(int c) { cantitate = c; }

    virtual void afisare() const = 0;
};
int Produs::cnt = 1;

class Carte : public Produs {
    std::string titlu;
    std::vector<std::string> autori;
    std::string editura;
public:
    Carte(double p, int c, std::string t, std::vector<std::string> aut, std::string ed) :
    Produs(p, c), titlu(t), autori(aut), editura(ed) {}

    Carte* clone() const override {
        return new Carte(*this);
    }

    std::string gettitlu() const { return titlu; }

    void afisare() const override {
        std::cout << "Tip: Carte | ID: " << getid() << " | Pret: " << getpret() << " | Cantitate: " << getcant()
                  << " | Titlu: " << titlu << " | Editura: " << editura << " | Autori: ";
        for (const auto& aut : autori) {
            std::cout << aut << " ";
        }
        std::cout << '\n';
    }


};

class DVD : public Produs {
protected:
    int nrmin;
public:
    DVD(double p, int c, int nrmin) : Produs(p, c), nrmin(nrmin) {}
};

class DVDMuz : public DVD {
    std::string album;
    std::vector<std::string> interpreti;
public:
    DVDMuz(double p, int c, int nrmin, std::string a, std::vector<std::string> intp) :
    DVD(p, c, nrmin), album(a),  interpreti(intp) {}

    DVDMuz* clone() const override {
        return new DVDMuz(*this);
    }

    void afisare() const override {
        std::cout << "Tip: DVDMuz | ID: " << getid() << " | Pret: " << getpret() << " | Cantitate: " << getcant()
                  << " | Minute: " << nrmin << " | Album: " << album << " | Interpreti: ";
        for (const auto& interp : interpreti) {
            std::cout << interp << " ";
        }
        std::cout << '\n';
    }
};

class DVDMov : public DVD {
    std::string nume;
    std::string gen;
public:
    DVDMov(double p, int c, int nrmin, std::string n, std::string gen) :
    DVD(p, c, nrmin), nume(n),  gen(gen) {}

    DVDMov* clone() const override {
        return new DVDMov(*this);
    }

    void afisare() const override {
        std::cout << "Tip: DVDMov | ID: " << getid() << " | Pret: " << getpret() << " | Cantitate: " << getcant()
                  << " | Minute: " << nrmin << " | Nume film: " << nume << " | Gen: " << gen << '\n';
    }
};

class ObCol : public Produs {
protected:
    std::string denumire;
public:
    ObCol(double p, int c, std::string d) : Produs(p, c), denumire(d) {}
};

class Figurina : public ObCol {
    std::string categorie;
    std::string brand;
    std::string material;
public:
    Figurina(double p, int c, std::string d, std::string cat, std::string b, std::string m) :
    ObCol(p, c, d), categorie(cat), brand(b), material(m) {}

    Figurina* clone() const override {
        return new Figurina(*this);
    }

    void afisare() const override {
        std::cout << "Tip: Figurina | ID: " << getid() << " | Pret: " << getpret() << " | Cantitate: " << getcant()
                  << " | Denumire: " << denumire << " | Categorie: " << categorie << " | Brand: " << brand
                  << " | Material: " << material << '\n';
    }

};

class Poster : public ObCol {
    std::string format;
public:
    Poster(double p, int c, std::string d, std::string f) :
    ObCol(p, c, d), format(f) {}

    Poster* clone() const override {
        return new Poster(*this);
    }

    void afisare() const override {
        std::cout << "Tip: Poster | ID: " << getid() << " | Pret: " << getpret() << " | Cantitate: " << getcant()
                  << " | Denumire: " << denumire << " | Format: " << format << '\n';
    }
};

class Librarie {
    std::vector<Produs*> produse;

    Librarie() = default;
    ~Librarie() {
        for (auto p : produse) {
            delete p;
        }
    }
public:
    Librarie(const Librarie&) = delete;
    Librarie& operator=(const Librarie&) = delete;

    static Librarie& getlib() {
        static Librarie lib;
        return lib;
    }


    void citire() {
        int n, i, j;
        std::string tip;
        double pret;
        int cantitate, id, nraut;

        std::cout << "Cate produse vor fi citite? ";
        std::cin >> n;

        for (i=0; i<n; i++) {
            std::cout << "Tip: ";
            std::cin >> tip;
            std::cout << "Atribute: ";

            std::cin >> pret >> cantitate;
            if (tip == "Carte") {
                std::cout << "Numar autori: ";
                std::cin >> nraut;
                std::string titlu;
                std::vector<std::string> autori;
                std::string autor;
                std::string editura;

                std::cin >> titlu;
                for (j=0; j<nraut; j++) {
                    std::cin >> autor;
                    autori.push_back(autor);
                }
                std::cin >> editura;

                produse.push_back(new Carte(pret, cantitate, titlu, autori, editura));
            } else if (tip == "DVDMuz") {
                int nrmin, nrint;
                std::string album, interpret;
                std::vector<std::string> interpreti;

                std::cout << "Nr minute, Album, Nr interpreti, Interpreti:\n";
                std::cin >> nrmin >> album >> nrint;
                for (j=0; j<nrint; j++) {
                    std::cin >> interpret;
                    interpreti.push_back(interpret);
                }
                produse.push_back(new DVDMuz(pret, cantitate, nrmin, album, interpreti));
            } else  if (tip == "DVDMov") {
                int nrmin;
                std::string nume, gen;

                std::cout << "Nr minute, Nume film, Gen:\n";
                std::cin >> nrmin >> nume >> gen;

                produse.push_back(new DVDMov(pret, cantitate, nrmin, nume, gen));
            } else if (tip == "Figurina") {
                std::string denumire, categorie, brand, material;

                std::cout << "Denumire, Categorie, Brand, Material:\n";
                std::cin >> denumire >> categorie >> brand >> material;

                produse.push_back(new Figurina(pret, cantitate, denumire, categorie, brand, material));
            } else  if (tip == "Poster") {
                std::string denumire, format;

                std::cout << "Denumire, Format:\n";
                std::cin >> denumire >> format;

                produse.push_back(new Poster(pret, cantitate, denumire, format));
            }
        }
    }

    void cantmax() {
        int max, maxid, i;
        Produs* p;
        max = 0;
        for (i=0; i<produse.size(); i++) {
            p = produse[i];
            if (p->getcant() > max) {
                max = p->getcant();
                maxid = i;
            }
        }
        p = produse[maxid];
        p->afisare();
    }

    void addprodus(Produs* p) {
        produse.push_back(p);
    }

    int cautcarte(std::string titlu) {
        int i, idx;
        Produs* p;
        Carte* carte;
        idx = -1;
        for (i=0; i<produse.size(); i++) {
            carte = dynamic_cast<Carte*> (produse[i]);
            if (carte != nullptr) {
                if (titlu == carte->gettitlu()) {
                    idx = i;
                    break;
                }
            }
        }
        return idx;
    }

    void edit(int id, double newpr, int newcant) {
        for (auto p : produse) {
            if (p->getid() == id) {
                p->setpret(newpr);
                p->setcant(newcant);
                return;
            }
        }
    }

    void sortare() {
        std::sort(produse.begin(), produse.end(), [](Produs* x, Produs* y) {
            return x->getpret() < y->getpret();
        });
    }

    void afis() {
        for (auto p : produse) {
            p->afisare();
        }
        std::cout << std::endl;
    }
};

int main() {

    auto& lib = Librarie::getlib();

    // 1. Adaugam produsele
    lib.addprodus(new Carte(45.5, 10, "Dune", {"Frank Herbert"}, "Nemira"));
    lib.addprodus(new DVDMuz(29.9, 5, 45, "Dark Side of the Moon", {"Pink Floyd"}));
    lib.addprodus(new DVDMov(39.9, 20, 120, "Interstellar", "Sci-Fi"));
    lib.addprodus(new Figurina(150.0, 2, "Batman", "Filme", "DC", "Plastic"));
    lib.addprodus(new Poster(15.0, 50, "Poster Avengers", "A3"));

    // 2. Afisare initiala
    std::cout << "--- PRODUSE INITIALE ---\n";
    lib.afis();

    // 3. Editarea unui produs (Sa zicem ca modificam figurina cu ID-ul 4)
    std::cout << "\n--- EDITARE PRODUS ID 4 ---\n";
    lib.edit(4, 120.0, 5); // Reducem pretul, crestem cantitatea
    lib.afis();

    // 4. Sortare
    std::cout << "\n--- PRODUSE SORTATE DUPA PRET (CRESCATOR) ---\n";
    lib.sortare();
    lib.afis();

    // 5. Cautare
    std::cout << "\n--- CAUTARE CARTE 'Dune' ---\n";
    int index = lib.cautcarte("Dune");
    if (index != -1) {
        std::cout << "Cartea a fost gasita la indexul " << index << " din vector!\n";
    } else {
        std::cout << "Cartea nu exista.\n";
    }

    // 6. Produsul cu cea mai mare cantitate
    std::cout << "\n--- PRODUSUL CU CANTITATE MAXIMA ---\n";
    lib.cantmax();

    return 0;
}
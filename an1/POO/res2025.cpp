#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

/*
TO DO:

- readanswer pentru toate functiile
AF - done
grila - done
liber - done
pereche

- vezi onstructorii pentru toate functiile

- vezi ca avem clonare / constructor de copiere (ala nu cred ca a fost facut inca)

*/

enum Capitol {
    GENERAL,
    STATIC,
    MOSTENIRE,
    VIRTUAL,
    TEMPLATE,
    PATTERNS
};

class Intrebare {
protected:
    int id;
    std::string enunt;
    std::vector<Capitol> tags;
    bool complex;

public:
    Intrebare(int id, std::string e, std::vector<Capitol> tags) : id(id), enunt(e), tags(tags), complex(false) {
    }
    virtual ~Intrebare() = default;

    virtual Intrebare* clone() const = 0;

    virtual double dificultate() const {
        double baseline;

        baseline = 1;
        for (auto t : tags) {
            if (t==TEMPLATE || t==PATTERNS) {
                baseline++;
            }
        }
        return baseline;
    }

    virtual bool readanswer() = 0;

    std::string getenunt() const {
        return enunt;
    }
};

class Grila : public Intrebare {
    std::vector<std::string> optiuni;
    int corect;
public:
    Grila(int id, std::string e, std::vector<Capitol>tags, std::vector<std::string> optiuni, int corect)
    : Intrebare(id, e, tags), optiuni(optiuni), corect(corect) {
        if (optiuni.size() > 6 || optiuni.size() < 4) {
            throw std::runtime_error("numar de optiuni necorespunzator");
        }
    }

    Grila* clone() const override {
        return new Grila(*this);
    }

    double dificultate() const override {
        return Intrebare::dificultate() + 0.5 * optiuni.size();
    }

    bool readanswer() override {
        int i, rasp;
        std::cout << enunt << '\n';
        for (i=0; i<optiuni.size(); i++) {
            std::cout << i << ") " << optiuni[i] << '\n';
        }
        std::cout << "[numarul optiunii alese]:" << '\n';
        std::cin >> rasp;
        if (rasp == corect) {
            return true;
        }
        return false;
    }
};

class AF : public Intrebare {
    std::vector<std::string> optiuni;
    char corect;
public:
    AF(int id, std::string e, std::vector<Capitol> tags,  char c) :
    Intrebare(id, e, tags), corect(c) {
        if (corect != 'A' && corect != 'F') {
            throw std::runtime_error("nu respecta formatul");
        }
    }

    AF* clone() const override {
        return new AF(*this);
    }

    double dificultate() const override {
        return Intrebare::dificultate();
    }

    bool readanswer() override{
        char rasp;
        std::cout << enunt << " [A/F]: ";
        std::cin >> rasp;
        if (rasp == corect) {
            return true;
        }
        return false;
    }
};

class Pereche : public Intrebare {
    std::vector<std::string> col1;
    std::vector<std::string> col2;
public:
    Pereche(int id, std::string e, std::vector<Capitol> tags,  std::vector<std::string> col1, std::vector<std::string> col2) :
    Intrebare(id, e, tags), col1(col1), col2(col2) {}

    double dificultate() const override {
        return Intrebare::dificultate() + 0.25*col1.size();
    }

    Pereche* clone() const override {
        return new Pereche(*this);
    }

    bool readanswer() override {
        //// nu am mai avut timp sa implementez dar planul era sa am un vector corect care ...
        return true;
    }
};

class Liber : public Intrebare {
    std::vector<std::string> raspunsuri;
    std::vector<bool> punctaje;
public:
    Liber(int id, std::string e, std::vector<Capitol> tags) : Intrebare(id, e, tags) {}

    double dificultate() const override {
        return Intrebare::dificultate() + 3;
    }
    Liber* clone() const override {
        return new Liber(*this);
    }

    bool readanswer() override {
        int i, idx, miau;
        std::string rasp;
        std::cout << enunt;

        std::cin >> rasp;
        idx = -1;
        for (i=0; i<raspunsuri.size(); i++) {
            if (raspunsuri[i]==rasp) {
                idx = i;
                break;
            }
        }
        if (idx==-1) {
            raspunsuri.push_back(rasp);
            std::cout << "corectitudine: ";
            std::cin >> miau;
            if (miau==1) {
                punctaje.push_back(true);
            } else {
                punctaje.push_back(false);
            }
            idx = punctaje.size()-1;
        }

        return punctaje[idx];
    }

};

///-------------------------------------///

class Sistem {
private:
    std::vector<Intrebare*> intrebari;
    Sistem() = default;

    ~Sistem() {
        for (auto i : intrebari) {
            delete i;
        }
    }
public:
    Sistem(const Sistem&) = delete;
    Sistem& operator=(const Sistem&) = delete;

    static Sistem& getsistem() {
        static Sistem sistem;
        return sistem;
    }

    void addintr(Intrebare* q) {
        intrebari.push_back(q);
    }

    void simulare() {
        int optiune;
        std::cout << "alege mod de invatare (0 pentru liber, 1 pentru practice): ";
        std::cin >> optiune;
        if (optiune==0) {
            modliber();
        } else {
            modpractice();
        }
    }

    void modliber() {
        bool corect;

        for (Intrebare* q : intrebari) {
            corect = q->readanswer();
            if (corect == true) {
                std::cout << "raspuns corect yayayyayyay :3 !!!!";
            } else {
                std::cout << "TRY AGAIN KILL YOURSELF";
            }
            std::cout << '\n';
        }
    }

    void modpractice() {
        int nrintr, nrq, scor;
        int dificultate, nobreak;
        bool rasp;

        std::vector<Intrebare*> test = intrebari;
        std::vector<std::string> greseli;

        std::shuffle(test.begin(), test.end(), std::default_random_engine(time(0)));

        std::cout << "numar intrebari? ";
        std::cin >> nrintr;
        std::cout << "dificultate? (0 - usor, 1 - mediu, 2 - dificil) ";
        std::cin >> dificultate;

        nrq = 0;
        nobreak = 0;
        scor = 0;
        for (Intrebare* q : test) {
            nobreak = 0;
            if (dificultate == 0) {
                if (q->dificultate() <= 2) {
                    nobreak = 1;
                }
            } else if (dificultate == 1) {
                if (q->dificultate() >= 2 && q->dificultate() <= 4) {
                    nobreak = 1;
                }
            } else if (dificultate == 2) {
                if (q->dificultate() >= 5) {
                    nobreak = 1;
                }
            }

            if (nobreak==1) {
                rasp = q->readanswer();
                if (rasp==true) {
                    scor++;
                } else {
                    greseli.push_back(q->getenunt());
                }
                nrq++;
                if (nrq == nrintr) {
                    break;
                }
            }
        }

        std::cout << "ai obtinut " << scor << " puncte\n";
        if (greseli.size() > 0) {
            std::cout << "greseli:\n";
            for (auto g : greseli) {
                std::cout << g << '\n';
            }
        }
    }
};

int main() {
    ///// YES IAR MI-A FOST LENE SA BAG CHESTIILE IN MAIN OK???? OK??? KYS


    auto& platforma = Sistem::getsistem();

    // Optiuni predefinite pentru grile (minim 4 ca sa treaca de acel IF)
    std::vector<std::string> opt_oop = {"Compilarea", "Polimorfismul", "Pointerii", "Recursivitatea"};
    std::vector<std::string> opt_mem = {"4 bytes", "8 bytes", "16 bytes", "Depinde de OS"};
    std::vector<std::string> opt_static = {"Face functia globala", "Apartine clasei, nu obiectului", "Nu poate fi modificata", "Devine virtuala"};

    // Intrebari Grila
    Intrebare* q1 = new Grila(1, "Care dintre urmatoarele este un principiu fundamental OOP?", {GENERAL}, opt_oop, 1);
    Intrebare* q2 = new Grila(2, "Care este dimensiunea unui pointer pe o arhitectura de 64 biti?", {GENERAL}, opt_mem, 1);
    Intrebare* q3 = new Grila(3, "Ce face keyword-ul 'static' aplicat unei variabile din clasa?", {STATIC}, opt_static, 1);

    // Intrebari Adevarat/Fals
    Intrebare* q4 = new AF(4, "Limbajul C++ suporta mostenirea multipla?", {MOSTENIRE}, 'A');
    Intrebare* q5 = new AF(5, "O clasa cu cel putin o metoda pur virtuala poate fi instantiata?", {VIRTUAL}, 'F');
    Intrebare* q6 = new AF(6, "Constructorul de copiere este apelat automat la transmiterea unui obiect prin valoare?", {GENERAL}, 'A');

    // Intrebari Libere (Tag-uri Complexe - adauga +1 la dificultate din oficiu!)
    Intrebare* q7 = new Liber(7, "Ce este un template in C++ si la ce ajuta?", {TEMPLATE});
    Intrebare* q8 = new Liber(8, "Explica pe scurt utilitatea design pattern-ului Singleton.", {PATTERNS});
    Intrebare* q9 = new Liber(9, "Cum previi problema de 'Object Slicing'?", {VIRTUAL, MOSTENIRE});

    // Intrebare Pereche
    std::vector<std::string> c1 = {"class", "virtual"};
    std::vector<std::string> c2 = {"obiect", "polimorfism"};
    Intrebare* q10 = new Pereche(10, "Asociaza cuvintele cheie cu conceptele (se va implementa mai tarziu):", {GENERAL}, c1, c2);

    // Adaugam totul in baza de date a Singleton-ului
    platforma.addintr(q1);
    platforma.addintr(q2);
    platforma.addintr(q3);
    platforma.addintr(q4);
    platforma.addintr(q5);
    platforma.addintr(q6);
    platforma.addintr(q7);
    platforma.addintr(q8);
    platforma.addintr(q9);
    platforma.addintr(q10);

    platforma.simulare();

    return 0;
}
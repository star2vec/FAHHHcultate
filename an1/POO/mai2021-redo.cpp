#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

/*
    TO DO;
    citere nume cu mai multe spatii
    EXCEPTIE IN RANSOMWARE
 */


struct Data {
    int zi;
    int luna;
    int an;
};

class Malware {
    double impact;
    Data data;
    std::string nume;
    std::string metoda; ////VALOARE IMPLICTA AICI!!!
    std::vector<std::string> registrii;

public:
    Malware(double i, Data d, const std::string& n, const std::vector<std::string>& reg, const std::string& met = "unknown") :
    impact(i), data(d), nume(n), metoda(met) {}

    virtual ~Malware() = default;

    virtual Malware* clone() const = 0;

    virtual double ratimp() const {
        double rat = 0;
        for (auto r : registrii) {
            if (r == "HKLM-run" || r == "HKCU-run") {
                rat+=20;
            }
        }
        return rat;
    }

    std::string getnume() const { return nume; }
};

class Rootkit : virtual public Malware {
    std::vector<std::string> importuri;
    std::vector<std::string> stringuri;

public:
    Rootkit(double i, Data d, const std::string& n, const std::vector<std::string>& reg,
        const std::vector<std::string>& imp, const std::vector<std::string>& str, const std::string& met = "unknown") :
    Malware(i, d, n, reg, met), importuri(imp), stringuri(str) {}

    Rootkit* clone() const override {
        return new Rootkit(*this);
    }

    double ratimp() const override {
        double rat = 0;
        int found = -1;;
        for (auto s : stringuri) {
            if (s=="SSDT" || s=="Ntcreatefile") { //+ restul
                rat+=20;
            }
        }
        for (auto i : importuri) {
            if (i=="nkt.exe") {
                found = 1;
                break;
            }
        }
        if (found==1) {
            rat*=2;
        }
        return Malware::ratimp() + rat;
    }
};

class Keylogger : virtual public Malware {
    std::vector<std::string> taste;
    std::vector<std::string> functii;
public:
    Keylogger(double i, Data d, const std::string& n, const std::vector<std::string>& reg,
        const std::vector<std::string>& t, const std::vector<std::string>& f, const std::string& met = "unknown") :
    Malware(i, d, n, reg, met), taste(t), functii(f) {}

    Keylogger* clone() const override {
        return new Keylogger(*this);
    }

    double ratimp() const override {
        double rat = 100; ///hardcodat
        //// de pus aici
        return Malware::ratimp() + rat;
    }
};

class Kernelkey : public Rootkit, public Keylogger {
    bool hidingfiles;
    bool hidingreg;
public:
    Kernelkey(double i, Data d, const std::string& n, const std::vector<std::string>& reg,
        const std::vector<std::string>& imp, const std::vector<std::string>& str,
        const std::vector<std::string>& t, const std::vector<std::string>& f, bool hf, bool hr,
        const std::string& met = "unknown") :
    Malware(i, d, n, reg, met), Rootkit(i, d, n, reg, imp, str, met), Keylogger(i, d, n, reg, t, f, met),
    hidingfiles(hf), hidingreg(hr) {}

    Kernelkey* clone() const override {
        return new Kernelkey(*this);
    }

    double ratimp() const override {
        double rat = 0;
        if (hidingfiles) {
            rat+=20;
        }
        if (hidingreg) {
            rat+=30;
        }
        return Keylogger::ratimp() + Rootkit::ratimp() - Malware::ratimp() + rat;
    }
};

class Ransom : public Malware {
    int rating;
    double obfuscare;
public:
    Ransom(double i, Data d, const std::string& n, const std::vector<std::string>& reg,
        int rating, double obf, const std::string& met = "unknown") :
    Malware(i, d, n, reg, met), rating(rating), obfuscare(obf) {
        if (rating > 10) {
            throw std::runtime_error("rat criptare invalid");
        }
    }

    Ransom* clone() const override {
        return new Ransom(*this);
    }

    double ratimp() const override {
        return Malware::ratimp() + rating + obfuscare;
    }
};

class MalwareFactory {
public:
    static Malware* create(const std::string& tipmal, double i, Data d, const std::string& nume,
         const std::vector<std::string>& reg, std::string& metoda) {
        if (tipmal == "rootkit") {
            ///citire aici
            std::vector<std::string> stringuri = {};
            std::vector<std::string> importuri = {};

            return new Rootkit(i, d, nume, reg, stringuri, importuri, metoda);
        } else if (tipmal == "keylogger") {
            std::vector<std::string> taste = {};
            std::vector<std::string> functii = {};

            return new Keylogger(i, d, nume, reg, taste, functii, metoda);
        } else if (tipmal == "kernelkey") {
            std::vector<std::string> taste = {};
            std::vector<std::string> functii = {};
            std::vector<std::string> stringuri = {};
            std::vector<std::string> importuri = {};
            bool hf, hr;

            std::cin >> hf >> hr;

            return new Kernelkey(i, d, nume, reg, stringuri, importuri, taste, functii, hf, hr, metoda);
        } else if (tipmal == "ransomware") {
            int cr;
            double obf;
            std::cin >> cr >> obf;

            return new Ransom(i, d, nume, reg, cr, obf, metoda);
        } else {
            throw std::runtime_error("nu exista acest tip de malware");
        }
    }
};

///---------


class Computer {
    static int cnt;
    int id;
    double rating;
    std::vector<Malware*> mal;

public:
    Computer(std::vector<Malware*> ma) :id(cnt++) {
        rating = 0;
        for (auto m : ma) {
            mal.push_back(m->clone());
        }
        for (auto m : mal) {
            rating += m->ratimp();
        }
    }

    ~Computer() {
        for (auto m : mal) {
            delete m;
        }
    }

    Computer(const Computer& other) : id(other.id), rating(other.rating) {
        for (auto m : other.mal) {
            mal.push_back(m->clone());
        }
    }

    Computer& operator=(const Computer& other) {
        if (this == &other) {
            return *this;
        }

        this->id = other.id;
        this->rating = other.rating;

        for (auto m : mal) {
            delete m;
        }
        mal.clear();

        for (auto m : other.mal) {
            mal.push_back(m->clone());
        }

        return *this;
    }

    void afiscalc() const {
        std::cout << id << ' ' << rating;
        for (auto m : mal) {
            std::cout << m->getnume() << ' ';
        }
        std::cout << std::endl;
    }

    double getrat() const { return rating; }

    bool infectat() const {
        if (mal.size() == 0) {
            return false;
        }
        return true;
    }
};
int Computer::cnt = 0;

////-------

class Meniu {
    std::vector<Computer> calc;

    Meniu() = default;
public:
    Meniu(const Meniu&) = delete;
    Meniu& operator=(const Meniu&) = delete;

    static Meniu& getmeniu() {
        static Meniu m;
        return m;
    }

    void afis() const {
        for (auto c : calc) {
            c.afiscalc();
        }
        std::cout << std::endl;
    }

    void afissort() const {
        std::vector<Computer> newcalc = calc;

        std::sort(newcalc.begin(), newcalc.end(), [](const Computer& c1, const Computer& c2) {
            return c1.getrat() < c2.getrat();
        });

        for (auto c : newcalc) {
            c.afiscalc();
        }
    }

    void afistopk(int k) const {
        std::vector<Computer> newcalc = calc;

        std::sort(newcalc.begin(), newcalc.end(), [](const Computer& c1, const Computer& c2) {
            return c1.getrat() < c2.getrat();
        });

        int i;
        for (i=0; i<std::min(k, (int)newcalc.size()); i++) {
            newcalc[i].afiscalc();
        }
    }

    double procinf() const {
        double nrtot = calc.size();
        if (nrtot == 0) {
            return 0;
        }
        double nrinf = 0;
        for (auto c : calc) {
            if (c.infectat()) {
                nrinf++;
            }
        }
        return nrinf/nrtot*100;
    }

    void addcalc() {
        std::cout << "detalii calc: ";
        int nrm, i;
        std::string tipmal;
        std::vector<Malware*> mal;

        std::cout << "cate malwareuri? ";
        std::cin >> nrm;

        for (i=0; i<nrm; i++) {
            double impact;
            int zi, luna, an, nr, j;
            std::string nume;
            std::string metoda;
            std::vector<std::string> reg;
            std::string regi;
            Malware* newmal;

            std::cout << "detalii de baza: ";
            std::cin >> tipmal >> impact >> zi >> luna >> an;
            std::cin >> nume >> metoda;
            std::cout << "cati reg?";
            std::cin >> nr;
            for (j=0; j<nr; j++) {
                std::cin >> std::ws;
                std::getline(std::cin, regi);
                reg.push_back(regi);
            }

            try {
                newmal = MalwareFactory::create(tipmal, impact, {zi, luna, an}, nume, reg, metoda);
                mal.push_back(newmal);
            } catch (std::exception& e) {
                std::cout << "date invalide " << e.what() << std::endl;
            }
        }

        try {
            Computer newcalc = Computer(mal);
            calc.push_back(newcalc);
        } catch (std::exception& e) {
            std::cout << "date invalide " << e.what() << std::endl;
        }

        for (auto m : mal) {
            delete m;
        }
    }
};

int main() {
    auto& meniu = Meniu::getmeniu();

    int op;

    std::cin >> op;
    do {
        switch (op) {
            case 0:
                meniu.addcalc();
                break;
            case 1:
                meniu.afis();
                break;
            case 2:
                meniu.afissort();
                break;
        }
        std::cin >> op;
    } while (op!=3);

    return 0;
}
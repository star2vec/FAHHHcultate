#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <stdexcept>

/*
PLAN

ierarhie: malware - ro, k, kk, ra

exceptii - in aia cu numar de la 1 la 10 din ransom

*/

struct Data {
    int zi;
    int luna;
    int an;
};

class Malware {
protected:
    double rating;
    Data infectare;
    std::string nume;
    std::string metoda;
    std::vector<std::string> registrii;

public:
    Malware(double r, Data i, const std::string& nume, std::vector<std::string> reg, std::string m = "unknown") :
    rating(r), infectare(i), nume(nume),  registrii(reg), metoda(m) {}

    virtual ~Malware() = default;

    virtual Malware* clone() const = 0;

    std::string getnume() const { return nume; }

    virtual double impact() {
        double r = 0;
        for (auto reg : registrii) {
            if (reg == "HKLM-run" || reg == "HKCU-run") {
                r += 20;
            }
        }
        return rating + r;
    };
};

class Rootkit : virtual public Malware {
protected:
    std::vector<std::string> importuri;
    std::vector<std::string> stringuri;
public:
    Rootkit(double r, Data i, const std::string& nume, std::vector<std::string> reg,
        std::vector<std::string> imp, std::vector<std::string> stri, std::string m = "unknown") :
    Malware(r, i, nume, reg, m), stringuri(stri), importuri(imp) {}

    Rootkit* clone() const override { return new Rootkit(*this); }

    double impact() override {
        int r = 0;
        for (auto i : stringuri) {
            if (i=="System Service Descriptor Table" ||
                i=="SSDT" || i=="NtCreateFile") {
                r+=100;
            }
        }

        int found = 0;
        for (auto s : importuri) {
            if (s == "ntoskrnl.exe") {
                found = 1;
                break;
            }
        }
        if (found==1) {
            r*=2;
        }

        return Malware::impact() + r;
    }
};

class Keylogger : virtual public Malware {
protected:
    std::vector<char> taste;
    std::vector<std::string> functii;
public:
    Keylogger(double r, Data i, const std::string& nume, std::vector<std::string> reg,
        std::vector<char> taste, std::vector<std::string> fct, std::string m = "unknown") :
    Malware(r, i, nume, reg, m), taste(taste), functii(fct) {}

    Keylogger* clone() const override { return new Keylogger(*this); }

    double impact() override {
        /// de implementat la fel ca si rootkit
        return Malware::impact();
    }
};

class KernelKey : public Rootkit,  public Keylogger {
private:
    bool hfiles;
    bool hreg;
public:
    KernelKey(double r, Data i, const std::string& nume, std::vector<std::string> reg,
        std::vector<std::string> imp, std::vector<std::string> stri,
        std::vector<char> taste, std::vector<std::string> fct,
        bool hf, bool hr, std::string m = "unknown") :
    Malware(r, i, nume, reg, m), Keylogger(r, i, nume, reg, taste, fct, m),
    Rootkit(r, i, nume, reg, stri, imp, m), hfiles(hf), hreg(hr) {}

    KernelKey* clone() const override { return new KernelKey(*this); }

    double impact() override {
        int r = Keylogger::impact() + Rootkit::impact() - Malware::impact();

        if (hfiles) { r+=20; }
        if (hreg) { r += 30; }

        return r;
    }
};

class Ransom : public Malware {
private:
    int criptare;
    double obfuscare;
public:
    Ransom(double r, Data i, const std::string& nume, std::vector<std::string> reg,
        int c, double o, std::string m = "unknown") :
    Malware(r, i, nume, reg, m), criptare(c), obfuscare(o) {
        if (criptare > 10) {
            throw std::invalid_argument("criptarea e numar de la 1 la 10");
        }
    }

    Ransom* clone() const override { return new Ransom(*this); }

    double impact() override {
        return Malware::impact() + criptare + obfuscare;
    }

};

//------------------------------------//

class Computer {
private:
    static int cnt;
    int id;
    std::vector<Malware*> lm; // lista malware
    double rating;
public:
    Computer(std::vector<Malware*> lm) : lm(lm), id(cnt++) {
        for (auto x : lm) {
            rating += x->impact();
        }
    }

    Computer(const Computer& other) : id(other.id), rating(other.rating) {
        for (auto x : other.lm)  {
            this->lm.push_back(x->clone());
        }
    }

    Computer& operator=(const Computer& other) {
        if (this == &other) {
            return *this;
        }
        for (auto x : lm) {
            delete x;
        }
        lm.clear();

        this->id = other.id;
        this->rating = other.rating;

        for (auto x : other.lm) {
            this->lm.push_back(x->clone());
        }

        return *this;
    }

    ~Computer() {
        for (auto x : lm) {
            delete x;
        }
    }

    double getrating() const { return rating; }

    void afiscalc() const {
        std::cout << id << ' ' << rating << ' ' << "lista malware: ";
        for (Malware* x : lm) {
            std::cout << x->getnume() << ' ';
        }
        std::cout << '\n';
    }

    bool verifinf() const {
        if (lm.size() == 0) {
            return false;
        }
        return true;
    }
};
int Computer::cnt = 0;



/// SINGLETON
class Firma {
private:
    std::vector<Computer> calc;

    Firma() = default;
public:
    Firma(const Firma&) = delete;
    Firma& operator=(const Firma&) = delete;

    static Firma& getfirma() {
        static Firma firma;
        return firma;
    }

    void addcomputer(const Computer& c) {
        calc.push_back(c);
    }

    void afis() const {
        for (auto c : calc) {
            c.afiscalc();
        }
        std::cout << '\n';
    }

    void sortafis() const {
        std::vector<Computer> nc = calc; ///newcalc

        std::sort(nc.begin(), nc.end(), [](const Computer& c1, const Computer& c2) {
            return c1.getrating() <= c2.getrating();
        });

        for (auto c : nc) {
            c.afiscalc();
        }
        std::cout << '\n';
    }

    void procinfect() const {
        int nr = calc.size();
        int nrinf = 0;

        for (auto c : calc) {
            if (c.verifinf()) {
                nrinf++;
            }
        }
        std::cout << (double) nrinf / nr * 100 << '\n';
    }
};




//-----------------------//


class MalwareFactory {
public:
    static Malware* createmalware(const std::string& tip, double r,
        Data i, const std::string& nume, std::vector<std::string> reg, std::string m) {
        std::cout << "extra date? ";
        if (tip == "ransom") {
            int criptare;
            double obfuscare;
            std::cin >> criptare >> obfuscare;
            return new Ransom(r, i, nume, reg, criptare, obfuscare, m);
        } else if (tip == "rootkit") {
            std::vector<std::string> imp = {"ntoskrnl.exe"}; // Hardcodat doar pentru exemplu scurt
            std::vector<std::string> stri = {"SSDT"};
            return new Rootkit(r, i, nume, reg, imp, stri, m);
        } else if (tip == "keylogger") {
            std::vector<char> taste = {'A'};
            std::vector<std::string> functii = {"OpenProcess"};
            return new Keylogger(r, i, nume, reg, taste, functii, m);
        } else if (tip == "kernelkey") {
            std::vector<std::string> imp = {"ntoskrnl.exe"};
            std::vector<std::string> stri = {"SSDT"};
            std::vector<char> taste = {'A'};
            std::vector<std::string> functii = {"CreateFileW"};

            bool hfiles, hreg;
            std::cout << "KernelKey " << nume << " ascunde fisiere? (1/0): ";
            std::cin >> hfiles;
            std::cout << "Ascunde registrii? (1/0): ";
            std::cin >> hreg;

            // Uite cat de curat arata acum crearea obiectului final, fara sa murdaresti main-ul!
            return new KernelKey(r, i, nume, reg, imp, stri, taste, functii, hfiles, hreg, m);
        } else {
            throw std::invalid_argument("tip de malware unknown");
        }
    }
};

int main() {
    auto& firma = Firma::getfirma();

    std::vector<std::string> reg = {"HKLM-run", "alte-chei"};
    Data d = {10, 5, 2021};

    try {
        // Testam Fabrica.
        // Aici va intra pe ramura if (tip == "Ransom") si iti va cere de la tastatura criptarea.
        // BAGA 15 CA SA VEZI CUM SE ACTIVEAZA CATCH-UL!
        Malware* m1 = MalwareFactory::createmalware("ransom", 5.0, d, "WannaCry", reg, "Criptare totala");

        // Creaza corect si Diamantul
        Malware* m2 = MalwareFactory::createmalware("kernelkey", 8.0, d, "Stuxnet", reg, "Spionaj avansat");

        // Cream un calculator cu acesti virusi si il bagam in firma
        std::vector<Malware*> virusi_calc1 = {m1, m2};
        Computer c1(virusi_calc1);
        firma.addcomputer(c1);

        std::cout << "\n--- SITUATIA FIRMEI ---\n";
        firma.afis();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "eroare: " << e.what() << '\n';
    }

    return 0;
}
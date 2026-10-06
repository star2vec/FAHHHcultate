#include <iostream>
#include <vector>

class Imobil {
private:
    const int id;
    static int idGenerator;
protected:
    std::string pozitie;
    float suprafata;
    const float pretmetru = 2000;
    const float pret = 0;

    float getMultiplicatorPozitie() const {
        if (pozitie == "central") return 2.0f;
        if (pozitie == "periferic") return 1.25f;
        if (pozitie == "mixt") return 1.50f;
        return 1.0f;
    }
public:
    Imobil(const std::string& pozitie, float suprafata)
        : id(idGenerator++), pozitie(pozitie), suprafata(suprafata) {}

    virtual ~Imobil() {};

    virtual std::string getTip() const = 0;

    virtual float getPret() const = 0;

    virtual void afisare(std::ostream& out) const {
        out << "ID=" << id << ", Tip=" << getTip()
            << ", Pozitie=" << pozitie << ", Suprafata=" << suprafata
            << "m^2, Pret=" << getPret() << "$";
    }

    friend std::ostream& operator<<(std::ostream& out, const Imobil& imobil) {
        imobil.afisare(out);
        return out;
    }
};

int Imobil::idGenerator = 1;

class Garsoniera: public Imobil {
private:
    bool bucatarie;
public:
    Garsoniera(const std::string& pozitie, float suprafata, bool bucatarie)
        : Imobil(pozitie, suprafata), bucatarie(bucatarie) {}

    std::string getTip() const override { return "Garsoniera"; }

    float getPret() const override {
        return 0;
    }

    void afisare(std::ostream& out) const override {
        out << "Garsoniera(";
        Imobil::afisare(out);
        out << ", bucatarie=" << (bucatarie ? "Da" : "Nu") << ")";
    }
};

class Apartament : public Imobil {
private:
    int nrCamere;
    int etaj;
    int etajeBloc;
    int anConstructie;

public:
    Apartament(const std::string& pozitie, float suprafata, int nrCamere, int etaj, int etajeBloc, int anConstructie)
        : Imobil(pozitie, suprafata), nrCamere(nrCamere), etaj(etaj), etajeBloc(etajeBloc), anConstructie(anConstructie) {}

    std::string getTip() const override { return "Apartament"; }

    float getPret() const override {
        return 0;
    }

    void afisare(std::ostream& out) const override {
        out << "Apartament(";
        Imobil::afisare(out);
        out << ", Camere=" << nrCamere << ", Etaj=" << etaj << "/" << etajeBloc << ", An=" << anConstructie << ")";
    }
};

class Casa : public Imobil {
private:
    float terenDisponibil;
    int nrEtajeConstruite;
    int nrCamere;
    bool arePiscina;

public:
    Casa(const std::string& pozitie, float suprafataConstruita, float terenDisponibil, int nrEtajeConstruite, int nrCamere, bool arePiscina)
        : Imobil(pozitie, suprafataConstruita), terenDisponibil(terenDisponibil), nrEtajeConstruite(nrEtajeConstruite), nrCamere(nrCamere), arePiscina(arePiscina) {}

    std::string getTip() const override { return "Casa"; }

    float getPret() const override {
        return 0;
    }

    void afisare(std::ostream& out) const override {
        out << "Casa(";
        Imobil::afisare(out);
        out << ", Teren=" << terenDisponibil << "m^2, Etaje=" << nrEtajeConstruite << ", Camere=" << nrCamere << ", Piscina=" << (arePiscina ? "Da" : "Nu") << ")";
    }
};


int main() {
    std::vector<Imobil*> imobiliare;

    imobiliare.push_back(new Garsoniera("central", 35.0f, true));
    imobiliare.push_back(new Apartament("mixt", 70.0f, 3, 2, 4, 1985));
    imobiliare.push_back(new Casa("periferic", 120.0f, 300.0f, 2, 5, true));

    for (const auto& imobil : imobiliare) {
        std::cout << *imobil << "\n";
    }


    // std::vector<Produs*> produse;
    // auto aux1 = new FloareLaFir("Trandafir", 10);
    // auto aux2 = new FloareLaFir("Lalea", 20);
    // produse.push_back(aux1); produse.push_back(aux2); produse.push_back(new Aranjament("Aranjament1", 5, {aux1, aux2}, "cutie"));
    // std::cout << *produse[2];

    // int floriLaFir = 0;
    // for (auto &a: produse) {
    //     if (dynamic_cast<FloareLaFir*>(a)) {
    //         floriLaFir += 1;
    //     }
    // }
    // std::cout << floriLaFir;
}
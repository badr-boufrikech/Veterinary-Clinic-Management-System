
/*
===============================================================================
VitaVet - Veterinary Clinic Management System
File: VitaVet.cpp
Author: Badr Boufrikech

Implementation of animal classes, input validation,
consultation management, financial reporting and file export.
===============================================================================
*/

#include "VitaVet.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <chrono>
#include <ctime>
#include <cstdio>

using namespace std;

// ============================================================================
// 1. INPUT VALIDATION
// ============================================================================

static void nettoyerCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static int lireIntDansIntervalle(const string& message, int min, int max)
{
    int x;
    cout << message;
    cin >> x;

    if (cin.fail())
    {
        nettoyerCin();
        throw invalid_argument("Saisie non numerique.");
    }

    nettoyerCin();

    if (x < min || x > max)
        throw out_of_range("Valeur hors intervalle.");

    return x;
}

static int lireIntMin(const string& message, int min)
{
    int x;
    cout << message;
    cin >> x;

    if (cin.fail())
    {
        nettoyerCin();
        throw invalid_argument("Saisie non numerique.");
    }

    nettoyerCin();

    if (x < min)
        throw out_of_range("Valeur negative/invalide.");

    return x;
}

static double lireDoubleMin(const string& message, double min)
{
    double x;
    cout << message;
    cin >> x;

    if (cin.fail())
    {
        nettoyerCin();
        throw invalid_argument("Saisie non numerique.");
    }

    nettoyerCin();

    if (x < min)
        throw out_of_range("Valeur negative/invalide.");

    return x;
}

static string lireLigneNonVide(const string& message)
{
    string s;
    cout << message;
    getline(cin, s);

    if (s.empty())
        throw invalid_argument("Champ vide.");

    return s;
}

// Date used in generated reports
static string dateAujourdhuiYYYYMMDD()
{
    using namespace chrono;

    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);

    tm localTm{};

#ifdef _WIN32
    localtime_s(&localTm, &t);
#else
    localtime_r(&t, &localTm);
#endif

    char buf[11];

    snprintf(buf, sizeof(buf), "%04d-%02d-%02d",
             localTm.tm_year + 1900,
             localTm.tm_mon + 1,
             localTm.tm_mday);

    return string(buf);
}

// ============================================================================
// 2. ABSTRACT BASE CLASS
// ============================================================================

// Unique ID shared across all animal types
int AnimalBB::prochainId = 1;

AnimalBB::AnimalBB(const string& nom,
                   int age,
                   const string& nomProprietaire,
                   const string& numeroTelephone)
    : id(prochainId++),
      nom(nom),
      age(age),
      nomProprietaire(nomProprietaire),
      numeroTelephone(numeroTelephone)
{
}

// ============================================================================
// 3. DERIVED ANIMAL CLASSES
// ============================================================================

// -------------------- DOG --------------------

ChienBB::ChienBB(const string& nom,
                 int age,
                 const string& nomProprietaire,
                 const string& numeroTelephone,
                 const string& race)
    : AnimalBB(nom, age, nomProprietaire, numeroTelephone),
      race(race)
{
}

void ChienBB::afficherFiche() const
{
    cout << getInfo() << "\n";
}

double ChienBB::getTarifConsultation() const
{
    return 45.00;
}

string ChienBB::getEspece() const
{
    return "Chien";
}

string ChienBB::getInfo() const
{
    ostringstream oss;

    oss << "[CHIEN #" << id << "] " << nom
        << " | Age: " << age
        << " | Race: " << race
        << " | Proprio: " << nomProprietaire
        << " (" << numeroTelephone << ")";

    return oss.str();
}

// -------------------- CAT --------------------

ChatBB::ChatBB(const string& nom,
               int age,
               const string& nomProprietaire,
               const string& numeroTelephone,
               bool estSterilise)
    : AnimalBB(nom, age, nomProprietaire, numeroTelephone),
      estSterilise(estSterilise)
{
}

void ChatBB::afficherFiche() const
{
    cout << getInfo() << "\n";
}

double ChatBB::getTarifConsultation() const
{
    return estSterilise ? 40.00 : 55.00;
}

string ChatBB::getEspece() const
{
    return "Chat";
}

string ChatBB::getInfo() const
{
    ostringstream oss;

    oss << "[CHAT #" << id << "] " << nom
        << " | Age: " << age
        << " | Sterilise: " << (estSterilise ? "Oui" : "Non")
        << " | Proprio: " << nomProprietaire
        << " (" << numeroTelephone << ")";

    return oss.str();
}

// -------------------- BIRD --------------------

OiseauBB::OiseauBB(const string& nom,
                   int age,
                   const string& nomProprietaire,
                   const string& numeroTelephone,
                   double envergure)
    : AnimalBB(nom, age, nomProprietaire, numeroTelephone),
      envergure(envergure)
{
}

void OiseauBB::afficherFiche() const
{
    cout << getInfo() << "\n";
}

double OiseauBB::getTarifConsultation() const
{
    return 30.00;
}

string OiseauBB::getEspece() const
{
    return "Oiseau";
}

string OiseauBB::getInfo() const
{
    ostringstream oss;

    oss << "[OISEAU #" << id << "] " << nom
        << " | Age: " << age
        << " | Envergure: " << envergure << "cm"
        << " | Proprio: " << nomProprietaire
        << " (" << numeroTelephone << ")";

    return oss.str();
}

// -------------------- REPTILE --------------------

ReptileBB::ReptileBB(const string& nom,
                     int age,
                     const string& nomProprietaire,
                     const string& numeroTelephone,
                     bool estVenimeux)
    : AnimalBB(nom, age, nomProprietaire, numeroTelephone),
      estVenimeux(estVenimeux)
{
}

void ReptileBB::afficherFiche() const
{
    cout << getInfo() << "\n";
}

double ReptileBB::getTarifConsultation() const
{
    return estVenimeux ? 70.00 : 55.00;
}

string ReptileBB::getEspece() const
{
    return "Reptile";
}

string ReptileBB::getInfo() const
{
    ostringstream oss;

    oss << "[REPTILE #" << id << "] " << nom
        << " | Age: " << age
        << " | Venimeux: " << (estVenimeux ? "Oui" : "Non")
        << " | Proprio: " << nomProprietaire
        << " (" << numeroTelephone << ")";

    return oss.str();
}

// ============================================================================
// 4. CLINIC MANAGEMENT FUNCTIONS
// ============================================================================

// Search for an animal by its unique ID
AnimalBB* rechercherAnimalParId(
    const list<AnimalBB*>& animalList, int id)
{
    for (AnimalBB* a : animalList)
    {
        if (a && a->getId() == id)
            return a;
    }

    return nullptr;
}

// -------------------- MAIN MENU --------------------

int afficherMenu()
{
    cout << "\n+----------------------------------+\n";
    cout << "|  VITAVET - Systeme de Gestion    |\n";
    cout << "+----------------------------------+\n";

    cout << "1. Enregistrer un animal\n";
    cout << "2. Ajouter une consultation\n";
    cout << "3. Afficher tous les animaux\n";
    cout << "4. Afficher toutes les consultations\n";
    cout << "5. Calculer le bilan financier\n";
    cout << "6. Sauvegarder le rapport\n";
    cout << "7. Quitter\n";

    return lireIntDansIntervalle("Votre choix : ", 1, 7);
}

// -------------------- REGISTER ANIMAL --------------------

void enregistrerAnimal(list<AnimalBB*>& animalList)
{
    int type = lireIntDansIntervalle(
        "Type (1=Chien 2=Chat 3=Oiseau 4=Reptile) : ", 1, 4);

    string nom = lireLigneNonVide("Nom : ");
    int age = lireIntMin("Age : ", 0);
    string proprietaire = lireLigneNonVide("Proprietaire : ");
    string telephone = lireLigneNonVide("Telephone : ");

    AnimalBB* a = nullptr;

    switch (type)
    {
    case 1:
    {
        string race = lireLigneNonVide("Race : ");

        a = new ChienBB(nom, age, proprietaire, telephone, race);
        break;
    }

    case 2:
    {
        int s = lireIntDansIntervalle(
            "Sterilise (1=Oui 0=Non) : ", 0, 1);

        a = new ChatBB(nom, age, proprietaire, telephone, s == 1);
        break;
    }

    case 3:
    {
        double env = lireDoubleMin("Envergure (cm) : ", 0.0);

        a = new OiseauBB(nom, age, proprietaire, telephone, env);
        break;
    }

    case 4:
    {
        int v = lireIntDansIntervalle(
            "Venimeux (1=Oui 0=Non) : ", 0, 1);

        a = new ReptileBB(nom, age, proprietaire, telephone, v == 1);
        break;
    }

    default:
        throw logic_error("Type d'animal inattendu.");
    }

    animalList.push_back(a);

    cout << "[OK] Animal enregistre avec succes. ID attribue : "
         << a->getId() << "\n";
}

// -------------------- ADD CONSULTATION --------------------

void ajouterConsultation(
    const list<AnimalBB*>& animalList,
    list<Consultation>& consultationList)
{
    if (animalList.empty())
    {
        cout << "Aucun animal enregistre. "
             << "Enregistrez d'abord un animal.\n";
        return;
    }

    afficherTousLesAnimaux(animalList);

    int animalId = lireIntMin("ID de l'animal : ", 1);

    AnimalBB* a = rechercherAnimalParId(animalList, animalId);

    if (!a)
    {
        throw runtime_error(
            "Tentative d'ajouter une consultation "
            "pour un ID d'animal inexistant.");
    }

    string date = lireLigneNonVide("Date (ex: 2026-04-01) : ");
    string description = lireLigneNonVide("Description du soin : ");

    Consultation c;

    c.date = date;
    c.description = description;
    c.coutFinal = a->getTarifConsultation();
    c.animalId = animalId;

    consultationList.push_back(c);

    cout << "[OK] Consultation ajoutee. Tarif applique : "
         << c.coutFinal << "$ (" << a->getEspece() << ")\n";
}

// -------------------- DISPLAY ANIMALS --------------------

void afficherTousLesAnimaux(
    const list<AnimalBB*>& animalList)
{
    if (animalList.empty())
    {
        cout << "Aucun animal enregistre.\n";
        return;
    }

    cout << "--- Liste des animaux ("
         << animalList.size() << " enregistres) ---\n";

    for (AnimalBB* an : animalList)
    {
        if (an)
            an->afficherFiche();
    }
}

// -------------------- DISPLAY CONSULTATIONS --------------------

void afficherConsultations(
    const list<Consultation>& consultationList)
{
    if (consultationList.empty())
    {
        cout << "Aucune consultation enregistree.\n";
        return;
    }

    cout << "--- Consultations ("
         << consultationList.size() << " enregistrees) ---\n";

    for (const Consultation& c : consultationList)
    {
        cout << "[" << c.date << "] Animal #" << c.animalId
             << " | " << c.description
             << " | " << c.coutFinal << "$\n";
    }
}

// -------------------- FINANCIAL REPORT --------------------

double calculerBilan(
    const list<Consultation>& consultationList)
{
    double total = 0.0;

    for (const Consultation& c : consultationList)
        total += c.coutFinal;

    int nb = static_cast<int>(consultationList.size());

    cout << "========== BILAN FINANCIER ==========\n";
    cout << "Nombre de consultations : " << nb << "\n";
    cout << "Total des revenus       : " << total << "$\n";
    cout << "Revenu moyen            : "
         << (nb > 0 ? total / nb : 0.0) << "$\n";
    cout << "=====================================\n";

    return total;
}

// -------------------- EXPORT REPORT --------------------

void sauvegarderRapport(
    const list<AnimalBB*>& animalList,
    const list<Consultation>& consultationList)
{
    ofstream f("rapport_vitavet.txt", ios::out);

    if (!f.is_open())
    {
        throw runtime_error(
            "Erreur lors de l'ouverture de rapport_vitavet.txt");
    }

    string dateGen = dateAujourdhuiYYYYMMDD();

    // Report header
    f << "===== RAPPORT VITAVET =====\n";
    f << "Date de generation : " << dateGen << "\n\n";

    // Registered animals
    f << "--- Animaux enregistres ("
      << animalList.size() << ") ---\n";

    for (AnimalBB* an : animalList)
    {
        if (an)
            f << an->getInfo() << "\n";
    }

    // Consultations
    f << "\n--- Consultations ("
      << consultationList.size() << ") ---\n";

    for (const Consultation& c : consultationList)
    {
        f << "[" << c.date << "] Animal #" << c.animalId
          << " | " << c.description
          << " | " << c.coutFinal << "$\n";
    }

    // Financial summary
    double total = 0.0;

    for (const Consultation& c : consultationList)
        total += c.coutFinal;

    int nb = static_cast<int>(consultationList.size());

    f << "\n========== BILAN FINANCIER ==========\n";
    f << "Nombre de consultations : " << nb << "\n";
    f << "Total des revenus       : " << total << "$\n";
    f << "Revenu moyen            : "
      << (nb > 0 ? total / nb : 0.0) << "$\n";
    f << "=====================================\n";

    // Verify successful file writing
    if (!f.good())
        throw runtime_error("Erreur lors de l'ecriture du rapport.");

    cout << "[OK] Rapport sauvegarde dans rapport_vitavet.txt\n";
}

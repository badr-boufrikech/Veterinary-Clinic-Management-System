
#pragma once

/*
===============================================================================
VitaVet - Veterinary Clinic Management System
File: VitaVet.hpp
Author: Badr Boufrikech

Description:
- Consultation data structure
- Abstract base class AnimalBB
- Derived classes: ChienBB, ChatBB, OiseauBB, ReptileBB
- Function declarations for clinic management

Concepts:
Object-Oriented Programming, Inheritance, Polymorphism,
Abstraction, STL Containers
===============================================================================
*/

#include <string>
#include <list>

using namespace std;

// ============================================================================
// 1. STRUCTURE CONSULTATION
// ============================================================================

struct Consultation
{
    string date;        // Date de la consultation
    string description; // Description du soin effectue
    double coutFinal;   // Cout final de la consultation
    int animalId;       // Identifiant de l'animal concerne
};


// ============================================================================
// 2. CLASSE ABSTRAITE : ANIMAL
// ============================================================================

class AnimalBB
{
private:
    // Identifiant unique genere automatiquement
    static int prochainId;

protected:
    int id;
    string nom;
    int age;
    string nomProprietaire;
    string numeroTelephone;

public:
    // Constructeur
    AnimalBB(const string& nom,
             int age,
             const string& nomProprietaire,
             const string& numeroTelephone);

    // Getters
    int getId() const { return id; }

    const string& getNom() const { return nom; }

    int getAge() const { return age; }

    const string& getNomProprietaire() const
    {
        return nomProprietaire;
    }

    const string& getNumeroTelephone() const
    {
        return numeroTelephone;
    }

    // Methodes virtuelles pures : polymorphisme
    virtual void afficherFiche() const = 0;

    virtual double getTarifConsultation() const = 0;

    virtual string getEspece() const = 0;

    // Retourne les informations formatees de l'animal
    virtual string getInfo() const = 0;

    // Destructeur virtuel
    virtual ~AnimalBB() = default;
};


// ============================================================================
// 3. CLASSE DERIVEE : CHIEN
// ============================================================================

class ChienBB : public AnimalBB
{
private:
    string race;

public:
    ChienBB(const string& nom,
            int age,
            const string& nomProprietaire,
            const string& numeroTelephone,
            const string& race);

    void afficherFiche() const override;

    double getTarifConsultation() const override;

    string getEspece() const override;

    string getInfo() const override;
};


// ============================================================================
// 4. CLASSE DERIVEE : CHAT
// ============================================================================

class ChatBB : public AnimalBB
{
private:
    bool estSterilise;

public:
    ChatBB(const string& nom,
           int age,
           const string& nomProprietaire,
           const string& numeroTelephone,
           bool estSterilise);

    void afficherFiche() const override;

    double getTarifConsultation() const override;

    string getEspece() const override;

    string getInfo() const override;
};


// ============================================================================
// 5. CLASSE DERIVEE : OISEAU
// ============================================================================

class OiseauBB : public AnimalBB
{
private:
    double envergure;

public:
    OiseauBB(const string& nom,
             int age,
             const string& nomProprietaire,
             const string& numeroTelephone,
             double envergure);

    void afficherFiche() const override;

    double getTarifConsultation() const override;

    string getEspece() const override;

    string getInfo() const override;
};


// ============================================================================
// 6. CLASSE DERIVEE : REPTILE
// ============================================================================

class ReptileBB : public AnimalBB
{
private:
    bool estVenimeux;

public:
    ReptileBB(const string& nom,
              int age,
              const string& nomProprietaire,
              const string& numeroTelephone,
              bool estVenimeux);

    void afficherFiche() const override;

    double getTarifConsultation() const override;

    string getEspece() const override;

    string getInfo() const override;
};


// ============================================================================
// 7. FONCTIONS UTILITAIRES
// ============================================================================

// Afficher le menu principal
int afficherMenu();

// Enregistrer un nouvel animal
void enregistrerAnimal(list<AnimalBB*>& animalList);

// Ajouter une consultation medicale
void ajouterConsultation(
    const list<AnimalBB*>& animalList,
    list<Consultation>& consultationList
);

// Afficher tous les animaux
void afficherTousLesAnimaux(
    const list<AnimalBB*>& animalList
);

// Afficher toutes les consultations
void afficherConsultations(
    const list<Consultation>& consultationList
);

// Calculer le bilan financier
double calculerBilan(
    const list<Consultation>& consultationList
);

// Generer un rapport texte
void sauvegarderRapport(
    const list<AnimalBB*>& animalList,
    const list<Consultation>& consultationList
);

// Rechercher un animal par son identifiant
AnimalBB* rechercherAnimalParId(
    const list<AnimalBB*>& animalList,
    int id
);

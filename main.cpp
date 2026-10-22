
/*
===============================================================================
VitaVet - Veterinary Clinic Management System
File: main.cpp
Author: Badr Boufrikech

Description:
- Main entry point of the application
- Interactive menu and program execution
- Animal and consultation management
- Exception handling
- Dynamic memory cleanup
===============================================================================
*/

#include <iostream>
#include <list>
#include <stdexcept>

#include "VitaVet.hpp"

using namespace std;

int main()
{
    // Conteneurs STL :
    // - Liste de pointeurs vers la classe de base pour le polymorphisme
    // - Liste des consultations médicales
    list<AnimalBB*> animalList;
    list<Consultation> consultationList;

    bool running = true;

    // Boucle principale du programme
    while (running)
    {
        try
        {
            // Affiche le menu et récupère le choix de l'utilisateur
            int choix = afficherMenu();

            switch (choix)
            {
            case 1:
                // Enregistrer un nouvel animal
                enregistrerAnimal(animalList);
                break;

            case 2:
                // Ajouter une consultation médicale
                ajouterConsultation(animalList, consultationList);
                break;

            case 3:
                // Afficher tous les animaux enregistrés
                afficherTousLesAnimaux(animalList);
                break;

            case 4:
                // Afficher toutes les consultations
                afficherConsultations(consultationList);
                break;

            case 5:
                // Calculer et afficher le bilan financier
                calculerBilan(consultationList);
                break;

            case 6:
                // Générer un rapport texte
                sauvegarderRapport(animalList, consultationList);
                break;

            case 7:
                // Quitter le programme
                running = false;
                break;

            default:
                throw out_of_range("Choix invalide.");
            }
        }
        catch (const exception& e)
        {
            // Gestion des erreurs standard
            cout << "[ERREUR] " << e.what() << "\n";
        }
        catch (...)
        {
            // Gestion des erreurs inattendues
            cout << "[ERREUR] Une erreur inattendue s'est produite.\n";
        }
    }

    // Libération de la mémoire allouée dynamiquement
    cout << "Fermeture du systeme VitaVet.\n";
    cout << "Liberation de la memoire...\n";

    for (AnimalBB* a : animalList)
    {
        delete a;
    }

    animalList.clear();

    cout << "Au revoir !\n";

    return 0;
}

/*
Compilation :
g++ VitaVet.cpp main.cpp -o app
*/

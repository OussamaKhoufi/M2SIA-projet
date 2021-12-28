#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <experimental/filesystem>
// Json
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace rapidjson ;
using namespace std ;


class Bibliotheque{
    private :      
        Json::Value _bibliotheque ;                                         // Objet de type Json
        string _cheminJson;
    public :
        /*Constructeurs*/
        Bibliotheque() ;                                                    // Constructeur vide 
        Bibliotheque(string nom) ;                                          // Constructeur avec le nom de la bibliotheque donnee par l'utilisateur
        Bibliotheque(const Json::Value bibliotheque) ;                      // Constructeur avec un objet Json
        /*Getter*/
        Json::Value getBilbiotheque() const ;
        string getCheminJson() const;
        /*Setter*/
        void setBilbiotheque(const Json::Value bibliotheque) ;

        /*Methodes principales*/
        void AfficherDescripteurs() ;                                       // Afficher la liste des descripteurs
        void AfficherCout() ;                                               // Affichage le cout d'une image
        void ConstruireAfficherSousListe() ;                                // Construire et afficher une sous-liste
        void Trier() ;                                                      // Trier la bibliotheque suivant une critere
        void AjouterImage() ;                                               // Ajouter une image dans la bibliotheque
        void SupprimerImage() ;                                             // Supprimer une image de la bibliotheque
        void Sauvegarder() ;                                                // Sauvegarder une bibliotheque

        /*Methodes supplementaires*/
        string SaisirDate(string& jour, string& mois, string& annee) ;      // Saisir et valider la date
        bool Continuer() ;                                                  // Continuer [Y/N]
        void VerifierExtension(string& nom) ;                               // Verifier l'extension ".json"
        Json::Value TriElement(const string critere) ;                      // Tri elementaire
        bool VerifierNumero(int& numero, const Json::Value biblio) ;        // Verifier l'existance d'un numero de l'image
        bool VerifierBibliotheque() ;                                       // Veriffier bibliotheque vide ou invalide
};

#endif // BIBLIOTHEQUE_H

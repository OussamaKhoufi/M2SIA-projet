#ifndef IMAGE_H
#define IMAGE_H
#define json_char TCHAR

// Systeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
// Json
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <experimental/filesystem>
// Plot
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp ;

//#include <chplot.h>

using namespace std ;
using namespace rapidjson ;
using namespace cv ;


class Image{
    private :
        string _cheminAccesContenu ;
		string _source ;
		string _titre ;
		int _numero ;
		double _cout ;
		string _acces ;
		string _dateAjout ;
		string _dateCreation ;
		string _cheminJson ;
		int _numeroJson ;
    public :
        /*Constructeurs*/
        Image();														// Constructeur vide
		Image(string chemin) ;											// Constructeur avec un chemin d'acces a la bibliotheque donne
		Image(string chemin, int num) ;									// Constructeur avec un chemin d'acces a la bibliotheque et un numero de l'image donnes

        /*Getter*/
        string getCheminAccesContenu() const ;      										// Chemin d'acces
		string getSource() const ;                  										// Source
		string getTitre() const ;                   										// Titre
		int getNumero() const ;                     										// Numero
		double getCout() const ;                    										// Cout
		string getAcces() const ;                   										// Permission
		string getDateAjout() const ;               										// Date d'ajout
		string getDateCreation() const ;            										// Date de creation
		string getCheminJson() const ;														// Chemin Json
		int getNumeroJson() const ;															// Numero Json

        /*Setters*/
        void setCheminAccesContenu(const string cheminAccesContenu) ;   					// Chemin d'acces
		void setSource(const string source) ;                           					// Source
		void setTitre(const string titre) ;                             					// Titre
		void setNumero(const int numero) ;                              					// Numero
		void setCout(const double cout) ;                               					// Cout
		void setAcces(const string acces) ;                             					// Permission
		void setDateAjout(const string dateAjout) ;                     					// Date d'ajout
		void setDateCreation(const string dateCreation) ;               					// Date de creation
		void setCheminJson(const string cheminJson) ;										// Chemin Json
		void setNumeroJson(const int numeroJson) ;											// Numero Json

        /*Methodes principales*/
        void AfficherContenuImage() ;														// Afficher le contenu de l'image
        void AfficherDescripteurImage() ;													// Afficher les descripteurs de l'image
        void ModifierDescripteurImage() ;													// Modifier un descripteur de l'image
        void TraitementImage() ;															// Traitement de l'image

		/*Methodes supplementaires*/
		Mat ImageZero(const int nbLigne, const int nbColonne) ; 							// Generer une matrice zero
		Mat ImageMiroir(const Mat image, const Mat filtre) ;								// Effet miroir
		Mat ImageConvolution(const Mat image, const Mat filtre) ;							// Produit de convolution
		void VerifierExtension(string& nom) ;												// Verifier l'extension ".json"
		bool Continuer() ;																	// Continuer [Y/N]
		bool VerifierNumero(int& numero, const Json::Value images) ;						// Verifier l'existance du numero d'image 
		string SaisirDate(string& jour, string& mois, string& annee) ;						// Saisir une date
		void ExtraireDate(const string date, string& jour, string& mois, string& annee) ;	// Extraire jour, mois, annee a partir d'une date
		vector<int> ImageHistogramme(const Mat image) ;										// Histogramme

} ;

#endif // IMAGE_H

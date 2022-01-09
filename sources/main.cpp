#include "../headers/bibliotheque.h"
#include "../headers/image.h"
using namespace std;
void lancerApp();
void identification();
void menuPrincipal(bool droitAcces);
void menuImage(Bibliotheque objBiblio,int numImage,bool droitAcces);
void menuBibliotheque(Bibliotheque objBiblio, bool droitAcces);
void menuTraitementImage(Bibliotheque objBiblio,int numImage, bool droitAcces);
void entreePourContinuer();
void messagePasDroitAcces();

int main (void){
	lancerApp();
	/*
	Mat img = imread("./DATA/Images/dangerous_dance.png");
	if (!img.data)
    {
        cout << "Image not loaded";
        return -1;
    }
	cout << img.depth();
	cout << endl << img.channels() << endl;*/
	return 0 ;
}
void entreePourContinuer(){
    cout << endl << "Tapez sur entree pour retourner au menu...";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
}
void messagePasDroitAcces(){
	cout << endl <<"Vous n'avez pas le droit d'accéder à cette fonctionnalité." << endl;
}
void identification(){
	string userId;
	string wantedId;
	string wantedIdSubstr;
	bool validId= false;
	bool found = false;
	bool droitAcces = false;
	ifstream idUsersFile;
	// Ouvrir le fichier idUsers
	idUsersFile.open("./DATA/idUsers.txt");
	// Tester si l ouverture a bien ete realise
	if (!idUsersFile) {
		cerr << "Impossible d'ouvrir le fichier idUsers.txt";
		exit(1);   // arret de l application
	}
	// Saisie de l identifiant utilisateur
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear cin buffer
	do {
		cout << endl <<"Taper votre identifiant :";
		getline(cin,wantedId);
		if (wantedId.length()==6){
			wantedIdSubstr = wantedId.substr(0,3);
			if (none_of(wantedIdSubstr.begin(), wantedIdSubstr.end(), ::isdigit)){
				wantedIdSubstr = wantedId.substr(4,5);
				if (all_of(wantedIdSubstr.begin(), wantedIdSubstr.end(), ::isdigit)){
					validId = true;
				}
			}
		}	
	}while(!validId);
	//verification de l'identifiant
	while (idUsersFile >> userId && found == false){
		if (userId == wantedId){
			found = true;
		}
	}
	idUsersFile.close(); // fermeture du fichier idUsers
	// Tester si l utilisateur est enregistré
	if (!found) {
		cout << endl << "Utilisateur non enregistré" << endl;
	} else {
		if (wantedId.substr(4,5) == "11" ){
			droitAcces = true; // identifier les droits d'acces de l utilisateur
		}
		cout << "Identification réussite" << endl; 
		menuPrincipal(droitAcces);
	}
}
void menuTraitementImage(Bibliotheque objBiblio,int numImage,bool droitAcces){
	Image objImage(objBiblio,numImage);
	while(1){
		int choixTraitement;
		string stringSaisi;
		cout << endl << "---------------------------" << endl;
		cout << endl << "---Menu Traitement Image---" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "**Traitement sur les composantes couleurs**" << endl;
		cout << endl << "1. Convertir l'image en Niveau de Gris" << endl;
		cout << endl << "2. Convertir l'image en Négatif" << endl;
		cout << endl << "3. Afficher une des composantes de l'image" << endl;
		cout << endl << "**Réhaussement de contraste**" << endl;
		cout << endl << "4. Normalisation" << endl;
		cout << endl << "5. Egalisation" << endl;
		cout << endl << "**Filtrage**" << endl;
		cout << endl << "6. Filtre Moyenneur" << endl;
		cout << endl << "7. Filtre Gaussien" << endl;
		cout << endl << "8. Filtre Median" << endl;
		cout << endl << "**Detection des contours**" << endl;
		cout << endl << "9. Filtre Sobel" << endl;
		cout << endl << "10. Filtre Laplacien" << endl;
		cout << endl << "**Rehaussement des contours**" << endl;
		cout << endl << "11. Filtre Gradient" << endl;
		cout << endl << "12. Filtre Laplacien" << endl;
		cout << endl << "**Seuillage & Segmentation**" << endl;
		cout << endl << "13. Seuillage" << endl;
		cout << endl << "14. Segmentation" << endl;
		cout << endl << "**Detection de ligne**" << endl;
		cout << endl << "15. Transformee de Hough" << endl;
		cout << endl << "** Calcul d'Histogramme**" << endl;
		cout << endl << "16. Afficher l'histogramme" << endl;
		cout << endl << "0. Retour au menu Image" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> stringSaisi;
		if (VerifierNumero(stringSaisi,choixTraitement)){
			if (choixTraitement>0 && choixTraitement <=20){
			objImage.TraitementImage(choixTraitement);
			}else if (choixTraitement==0) {
				menuImage(objBiblio,numImage,droitAcces);
			}else {
				cout << endl << "Choix non valide : Votre choix doit figurer dans le menu !" << endl;
			}
		}else {
			cout << endl << "Choix non valide : Votre choix doit etre un entier !" << endl;
		}
		entreePourContinuer();
	}
}
void menuImage(Bibliotheque objBiblio,int numImage,bool droitAcces){
	Image objImage(objBiblio,numImage);
	while(1){
		int choix;
		string stringSaisi;
		cout << endl << "---------------------------" << endl;
		cout << endl << "---------Menu Image--------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Afficher le contenu de l'image" << endl;
		cout << endl << "2. Afficher le descripteur de l'image" << endl;
		cout << endl << "3. Réaliser un traitement sur le contenu de l'image" << endl;
		cout << endl << "4. Modifier le descripteur de l'image" << endl;
		cout << endl << "0. Retour au menu gestion de bibliothèque" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> stringSaisi;
		if (VerifierNumero(stringSaisi,choix)){
			switch (choix){
			case 1:
			objImage.AfficherContenuImage();
			break;
			case 2:
			objImage.AfficherDescripteurImage();
			break;
			case 3:
			if (droitAcces){
				menuTraitementImage(objBiblio,numImage,droitAcces);
				break;
			} else {
				messagePasDroitAcces();
				break;
			}
			case 4:
			if (droitAcces){
				objImage.ModifierDescripteurImage();
				break;
			} else {
				messagePasDroitAcces();
				break;
			}
			case 0:
			menuBibliotheque(objBiblio,droitAcces);
			break;
			default:
			cout << endl << "Choix non valide : Votre choix doit figurer dans le menu !" << endl;
			break;
		}
		}else {
			cout << endl << "Choix non valide : Votre choix doit etre un entier !" << endl; 
		}
		entreePourContinuer();
    }
}
void menuBibliotheque(Bibliotheque objBiblio,bool droitAcces){
	while(1){
		int choix;
		int numImage;
		string stringSaisi ;
		//objBiblio.majBiblioSuivantDroitAcces(droitAcces);
		cout << endl << "----------------------------------" << endl;
		cout << endl << "---Menu Gestion de Bibliotheque---" << endl;
		cout << endl << "----------------------------------" << endl;
		cout << endl << "1. Afficher les descripteurs" << endl;
		cout << endl << "2. Afficher le cout d'une image" << endl;
		cout << endl << "3. Construire et afficher une sous-liste de descripteurs" << endl;
		cout << endl << "4. Trier la bibliotheque" << endl;
		cout << endl << "5. Sélectionner une image" << endl;
		cout << endl << "6. Ajouter une image" << endl;
		cout << endl << "7. Supprimer une image" << endl;
		cout << endl << "8. Sauvegarder la bibliotheque" << endl;
		cout << endl << "0. Retour au menu principal" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";	
		cin >> stringSaisi;
		if (VerifierNumero(stringSaisi,choix)){
			switch (choix){
			case 1:
            objBiblio.AfficherDescripteurs();
			break;
			case 2:
            objBiblio.AfficherCout();
			break;
			case 3:
            objBiblio.ConstruireAfficherSousListe();
			break;
			case 4:
            objBiblio.Trier();
			break;
			case 5: 
            cout << "Veuillez donner le numéro de l'image : ";
			do{
				cin >> stringSaisi;
				if(VerifierNumero(stringSaisi, numImage)){
					if(VerifierNumero(numImage, objBiblio.getBilbiotheque())){
						menuImage(objBiblio,numImage,droitAcces);
					}else{
						cout << "Image n'existe pas dans la bibliotheque. Veuillez choisir un autre numero : " ;
					}
				}else{
					cout << "Format invalide. Veuillez donner le numero de l'image : " ;
				}
			}while((VerifierNumero(stringSaisi, numImage) == false) || (VerifierNumero(numImage, objBiblio.getBilbiotheque()) == false)) ;
			break;
			case 6:
            if (droitAcces){
				objBiblio.AjouterImage();break;
			} else {
				messagePasDroitAcces();
				break;
			}
			case 7:
            if (droitAcces){
				objBiblio.SupprimerImage();
				break;
			} else {
				messagePasDroitAcces();
				break;
			}			
			case 8:
            if (droitAcces){
				objBiblio.Sauvegarder();
				break;
			} else {
				messagePasDroitAcces();
				break;
			}
			break;
			case 0:
			menuPrincipal(droitAcces);
			break;
			default:
			cout << endl << "Choix non valide : Votre choix doit figurer dans le menu !" << endl;
			break;
		}
		}else {
			cout << endl << "Choix non valide : Votre choix doit etre un entier !" << endl;
		}	
        entreePourContinuer();
    }
}
void menuPrincipal(bool droitAcces){
	while(1){
		int choix;
		string stringSaisi;
		cout << endl << "---------------------------" << endl;
		cout << endl << "-------Menu Principal------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Charger une bibliothèque " << endl;
		cout << endl << "0. Retour au menu d'identification" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> stringSaisi;
		if (VerifierNumero(stringSaisi,choix)){
			if (choix==1){
				//Charger une bibliothèque à partir d'un fichier existant ou créer une nv si nécessaire
				//cout << endl << "---Liste des bibliothèques existantes---" << endl;
            	Bibliotheque objBiblio;
				//lancer le menu Gestion de bibliothèque  
				menuBibliotheque(objBiblio,droitAcces);
        	}else if (choix==0){
				lancerApp();
        	}else {
				cout << endl << "Choix non valide : Votre choix doit figurer dans le menu !" << endl;
			}
		}else {
			cout << endl << "Choix non valide : Votre choix doit etre un entier !" << endl;
		}
		entreePourContinuer();
	}
}
void lancerApp(){


	while(1){
		int choix;
		string stringSaisi;
		cout << endl << "---------------------------" << endl;
		cout << endl << "----Menu Identification----" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Identifaction " << endl;
		cout << endl << "0. Fermer l application" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> stringSaisi;
		if (VerifierNumero(stringSaisi,choix)){
			if (choix==1){
				identification();
			}else if (choix==0){
				cout << endl << "Bye Bye !" << endl;
				exit(1);
			}else {
				cout << endl << "Choix non valide : Votre choix doit figurer dans le menu !" << endl;
			}
		}else {
			cout << endl << "Choix non valide : Votre choix doit etre un entier !" << endl;
		}
		entreePourContinuer();		
    }
}




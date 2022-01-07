#include "../headers/bibliotheque.h"
#include "../headers/image.h"
<<<<<<< HEAD
using namespace std;
void lancerApp();
bool identification();
void menuPrincipal(bool droitAcces);
void menuImage(Bibliotheque objBiblio,int numImage,bool droitAcces);
void menuBibliotheque(Bibliotheque objBiblio, bool droitAcces);
void menuTraitementImage(Bibliotheque objBiblio,int numImage);
void entreePourContinuer();
void messagePasDroitAcces();

int main (void){
	lancerApp();
    return 0 ;
}
void entreePourContinuer(){
    cout << "Tapez sur une touche pour retourner au menu précedent...";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
}
void messagePasDroitAcces(){
	cout << endl <<"Vous n'avez pas le droit d'accéder à cette fonctionnalité." << endl;
}
bool identification(){
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
		cout << "Utilisateur non enregistré" << endl;
		//menuIdentification();
	} else {
		if (wantedId.substr(4,5) == "11" ){
			droitAcces = true; // identifier les droits d'acces de l utilisateur
		}
		cout << "Identification réussite" << endl; 
		menuPrincipal(droitAcces);
	}

	//cout << endl << droitAcces<< endl;
	return droitAcces;
}
void menuTraitementImage(Bibliotheque objBiblio,int numImage){
	Image objImage(objBiblio,numImage-1);
	while(1){
		int choixTraitement;
		cout << endl << "---------------------------" << endl;
		cout << endl << "---Menu Traitement Image---" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Convertir l'image en niveau de gris" << endl;
		cout << endl << "2. Filtrage avec Moyenneur" << endl;
		cout << endl << "3. Filtrage avec Laplacien" << endl;
		cout << endl << "4. Filtrage avec Gaussien" << endl;
		cout << endl << "5. Filtrage avec Gradient en x (Sobel)" << endl;
		cout << endl << "6. Filtrage avec Gradient en y (Sobel)" << endl;
		cout << endl << "0. Retour au menu Image" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> choixTraitement;
		if (choixTraitement){
			objImage.TraitementImage(choixTraitement);
			entreePourContinuer();
		}else {
			menuImage(objBiblio,numImage,false);
		}
		
	}
}
void menuImage(Bibliotheque objBiblio,int numImage,bool droitAcces){
	Image objImage(objBiblio,numImage-1);
	while(1){
		int choix;
		cout << endl << "---------------------------" << endl;
		cout << endl << "---------Menu Image--------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Afficher le contenu de l'image" << endl;
		cout << endl << "2. Afficher le descripteur de l'image" << endl;
		cout << endl << "3. Réaliser un traitement sur le contenu de l'image" << endl;
		cout << endl << "4. Modifier le descripteur de l'image" << endl;
		cout << endl << "0. Retour au menu gestion de bibliothèque" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> choix;
		switch (choix){
			case 1:
			objImage.AfficherContenuImage();
			break;
			case 2:
			objImage.AfficherDescripteurImage();
			break;
			case 3:
			if (droitAcces){
				menuTraitementImage(objBiblio,numImage);
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
			cout << endl << "Choix non valide" << endl;
			break;
		}
        entreePourContinuer();
    }
}
void menuBibliotheque(Bibliotheque objBiblio,bool droitAcces){
	while(1){
		int choix;
		int numImage;
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
		cout << endl << "8. Sauvegarder la bibliothque" << endl;
		cout << endl << "0. Retour au menu principal" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> choix;
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
            cin >> numImage;
			menuImage(objBiblio,numImage,droitAcces);
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
			cout << endl << "Choix non valide" << endl;
			break;
		}
        entreePourContinuer();
    }
}
void menuPrincipal(bool droitAcces){
	while(1){
		int choix;
		cout << endl << "---------------------------" << endl;
		cout << endl << "-------Menu Principal------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Charger une bibliothèque " << endl;
		cout << endl << "0. Retour au menu d'identification" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> choix;
		if (choix==1){
			//Charger une bibliothèque à partir d'un fichier existant ou créer une nv si nécessaire
			//cout << endl << "---Liste des bibliothèques existantes---" << endl;
            Bibliotheque objBiblio;
			//lancer le menu Gestion de bibliothèque  
			menuBibliotheque(objBiblio,droitAcces);
        }else if (choix==0){
			lancerApp();
        }else {
			cout << endl << "Choix non valide" << endl;
        }
    }
}
void lancerApp(){
	while(1){
		int choix;
		bool droitAcces;
		cout << endl << "---------------------------" << endl;
		cout << endl << "----Menu Identification----" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Identifaction " << endl;
		cout << endl << "0. Fermer l application" << endl;
		cout << endl << "Veuillez saisir votre choix puis tapez sur Entrée : ";
		cin >> choix;
		if (choix==1){
			droitAcces = identification();
			cout << endl << droitAcces << endl;
        }else if (choix==0){
			cout << endl << "Bye Bye !" << endl;
			exit(1);
        }else {
			cout << endl << "Choix non valide" << endl;
        }
    }
}
=======
/*Test*/
using namespace cv ;

int main (void){
	/*string chemin1 = "./DATA/Images/halloween_sun.png" ;
	string chemin2 = "./DATA/Images/dangerous_dance(copy)2.png" ;
	Mat image = imread(chemin1, CV_LOAD_IMAGE_COLOR) ;

	// Rehaussement de contours
	// Mat imageRehausContour = ImageRehaussementContour(image, 20) ;

	Mat imageResultat = ImageInversement(image) ;
	// Concatenation (en couleurs)
	Mat imageConcatenationCouleur = ConcatenerImage(image, imageResultat) ;

	// Affichage
    namedWindow("Test", WINDOW_AUTOSIZE) ; 
    imshow("Test", imageConcatenationCouleur); 
    waitKey(0) ; 
    destroyWindow("Test") ;*/

	string chemin = "bibliotheque.json" ;
	Bibliotheque A(chemin) ;
	Json::Value B ;
	B = A.Trier(5) ;

	cout << B << endl ;

/*
	Image B("./DATA/Bibliothèques/test.json", 1) ;
	B.AfficherDescripteurImage() ;
	B.ModifierDescripteurImage() ;*/


	return 0 ;
}


// jq ".images[].source" bibliotheque.json
// g++ -Wall  bibliotheque.h
// g++ -Wall -c  bibliotheque.cpp -o bibliotheque.o -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio
// g++ -Wall  main.cpp bibliotheque.o -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio
>>>>>>> features-complement

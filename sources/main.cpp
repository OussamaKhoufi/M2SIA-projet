#include "../headers/bibliotheque.h"
#include "../headers/image.h"

void menuPrincipal();
void menuImage(Bibliotheque objBiblio,int numImage);
void menuBibliotheque(Bibliotheque objBiblio);
void menuTraitementImage(Bibliotheque objBiblio,int numImage);
void EntreePourContinuer();
int main (void){
	menuPrincipal();
    return 0 ;
}
void EntreePourContinuer(){
    cout << "Taper Entrée pour retourner au menu précedent...";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();
}
void menuTraitementImage(Bibliotheque objBiblio,int numImage){
	Image objImage(objBiblio,numImage-1);
	while(1){
		int choixTraitement;
		cout << endl << "---------------------------" << endl;
		cout << endl << "---------Menu Traitement Image--------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Convertir l'image en niveau de gris" << endl;
		cout << endl << "2. Filtrage avec Moyenneur" << endl;
		cout << endl << "3. Filtrage avec Laplacien" << endl;
		cout << endl << "4. Filtrage avec Gaussien" << endl;
		cout << endl << "5. Filtrage avec Gradient en x (Sobel)" << endl;
		cout << endl << "6. Filtrage avec Gradient en y (Sobel)" << endl;
		cout << endl << "0. Retour au menu Image" << endl;
		cout << endl << "Tapez votre choix et appuiyez sur Entrée : " << endl;
		cin >> choixTraitement;
		if (choixTraitement){
			objImage.TraitementImage(choixTraitement);
			EntreePourContinuer();
		}else {
			menuImage(objBiblio,numImage);
		}
		
	}
}
void menuImage(Bibliotheque objBiblio,int numImage){
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
		cout << endl << "Tapez votre choix et appuiyez sur Entrée : " << endl; 
		cin >> choix;
		switch (choix){
			case 1:
			objImage.AfficherContenuImage();
			break;
			case 2:
			objImage.AfficherDescripteurImage();
			break;
			case 3:
			menuTraitementImage(objBiblio,numImage);
			break;
			case 4:
			objImage.ModifierDescripteurImage();
			break;
			case 0:
			menuBibliotheque(objBiblio);
			break;
			default:
			cout << endl << "Choix non valide" << endl;
			break;
		}
        EntreePourContinuer();
    }
}
void menuBibliotheque(Bibliotheque objBiblio){
	while(1){
		int choix;
		int numImage;
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
		cout << endl << "Tapez votre choix et appuiyez sur Entrée : " << endl; 
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
			menuImage(objBiblio,numImage);
			break;
			case 6:
            objBiblio.AjouterImage();
			break;
			case 7:
            objBiblio.SupprimerImage();
			break;
			case 8:
            objBiblio.Sauvegarder();
			break;
			case 0:
			menuPrincipal();
			break;
			default:
			cout << endl << "Choix non valide" << endl;
			break;
		}
        EntreePourContinuer();
    }
}
void menuPrincipal(){
	while(1){
		int choix;

        string nomBibliotheque;
		cout << endl << "---------------------------" << endl;
		cout << endl << "-------Menu Principal------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Charger une bibliothèque " << endl;
		cout << endl << "0. Retour au menu d'identification" << endl;
		cout << endl << "Tapez votre choix et appuiyez sur Entrée : " << endl; 
		cin >> choix;
		if (choix==1){
			//Charger une bibliothèque à partir d'un fichier existant ou créer une nv si nécessaire
			//cout << endl << "---Liste des bibliothèques existantes---" << endl;
            Bibliotheque objBiblio;
			//lancer le menu Gestion de bibliothèque  
			menuBibliotheque(objBiblio);
        }else if (choix==0){
			exit(1);
        }else {
			cout << endl << "Choix non valide" << endl;
        }
    }
}




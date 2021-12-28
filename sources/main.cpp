#include "./../headers/bibliotheque.h"
#include "./../headers/image.h"

void menuPrincipal();
void menuImage();
void menuBibliotheque();

int main (void){
	menuPrincipal();
    return 0 ;
}
void menuImage(){
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
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 0:
			menuBibliotheque();
			break;
			default:
			cout << endl << "Choix non valide" << endl;
			break;
		}
    }
}

void menuBibliotheque(){
	while(1){
		int choix;
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
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5: 
			menuImage();
			break;
			case 6:
			break;
			case 7:
			break;
			case 8:
			break;
			case 0:
			menuPrincipal();
			break;
			default:
			cout << endl << "Choix non valide" << endl;
			break;
		}
    }
}

void menuPrincipal(){
	while(1){
		int choix;
		cout << endl << "---------------------------" << endl;
		cout << endl << "-------Menu Principal------" << endl;
		cout << endl << "---------------------------" << endl;
		cout << endl << "1. Charger une bibliothèque " << endl;
		cout << endl << "0. Retour au menu d'identification" << endl;
		cout << endl << "Tapez votre choix et appuiyez sur Entrée : " << endl; 
		cin >> choix;
		switch (choix){
		    case 1:
			//Charger une bibliothèque à partir d'un fichier existant ou créer une nv si nécessaire
			
			//lancer le menu Gestion de bibliothèque  
			menuBibliotheque();
			break;
			case 0:
			exit(1);
			default:
			cout << endl << "Choix non valide" << endl;
			break;
		}
    }
}




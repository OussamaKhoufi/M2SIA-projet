#include "./../headers/bibliotheque.h"
#include "./../headers/image.h"

int main (void){

    string nom = "bibliotheque";
    Bibliotheque A(nom) ;

    /*cout << "Afficher tous les descripteurs" << endl << endl ;
    A.AfficherDescripteurs() ; */

    /*cout << "Afficher le cout suivant le numero choisi" << endl << endl ;
    A.AfficherCout() ;*/

    /*cout << "Construire et afficher une sous-liste" << endl ;
    A.ConstruireAfficherSousListe() ;   */

    /*cout << "Trier la bibliotheque suivant une critere choisie" << endl ;
    A.Trier() ;*/

    /*cout << "Sauvegarder la bibliotheque" << endl ;
    A.Sauvegarder() ;*/

    /*cout << "Ajouter une image" << endl ; 
    A.AjouterImage() ; */

    /*cout << "Supprimer une image" << endl ; 
    A.SupprimerImage() ;*/


    // Image test ;
    //cout << test.getCheminAccesContenu() << endl ;

    string chemin = "./DATA/bibliotheque.json" ;
    // Image test(chemin) ;
    Image test(chemin, 1) ;

    /* Tests Methodes */
    // test.AfficherContenuImage() ;
    // test.AfficherDescripteurImage() ;
    test.TraitementImage() ;
    // test.ModifierDescripteurImage() ;


    return 0 ;
}


// jq ".images[].source" bibliotheque.json
// g++ -Wall  bibliotheque.h
// g++ -Wall -c  bibliotheque.cpp -o bibliotheque.o -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio
// g++ -Wall  main.cpp bibliotheque.o -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio
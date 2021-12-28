#include "./../headers/image.h"

Image::Image()
{
    int nb ;                                                                    // Numero de l'image
    Json::Value images ;
    Json::Reader reader ;
    ifstream bibliotheque_file("../DATA/Bibliothèques/bibliotheque.json", ios::in) ;          // Charger le contenu du fichier json 
    reader.parse(bibliotheque_file, images) ;                                   // Importer le contenu a l'objet Json

    cout << "Veuillez saisir le numero de l'image souhaitee : " << endl ; 
    do{
        // Saisir le numero de l'image
        cin >> nb ;
        // Verifier le numero de l'image et saisir un autre numero en cas d'erreur
        if ((nb > images["nbImages"].asInt()-1) || (nb < 0)){
            cout << "Veuillez saisir un numero valide !" << endl ;
        }
    }while((nb > images["nbImages"].asInt()-1) || (nb < 0)) ;
    _cheminAccesContenu = images["images"][nb]["cheminAcces"].asString() ;
    _source = images["images"][nb]["source"].asString() ;
    _titre = images["images"][nb]["titre"].asString() ;
    _numero = images["images"][nb]["numero"].asInt() ;
    _cout = images["images"][nb]["cout"].asDouble() ;
    _acces = images["images"][nb]["acces"].asString() ;
    _dateAjout = images["images"][nb]["dateAjout"].asString() ;
    _dateCreation = images["images"][nb]["dateCreation"].asString() ;
    _cheminJson = "./DATA/bibliotheque.json" ;
    _numeroJson = nb ;
}

Image::Image(string chemin)
{
    int nb ;                                                                    // Numero de l'image
    bool exist ;                                                                // Variable pour verifier l'existance du fichier
    char decision ;                                                             // Condition d'arret de la boucle
    Json::Value images ;                                                        // Objet Json
    Json::Reader reader ;                                                       // Variable pour la lecture du fichier Json

    VerifierExtension(chemin) ;                                                 // Verifier l'existance de l'xension ".json"
    exist = experimental::filesystem::exists(chemin) ;                          // Verifier l'existace du fichier
    do{
        decision = 'N' ; 
        // Verifier l'existance du fichier
        if (exist){                                                             // Si le fichier existe
            ifstream bibliotheque_file(chemin, ios::in) ;                       // Charger le contenu du fichier json 
            reader.parse(bibliotheque_file, images) ;                           // Importer le contenu a l'objet Json

            // Saisie et verification du numero de l'image
            do{
                cout << "Veuillez saisir le numero de l'image souhaitee : " << endl ; 
                cin >> nb ;
            }while(VerifierNumero(nb, images) == false) ;
        
            // Prendre les descripteurs de l'image
            _cheminAccesContenu = images["images"][nb]["cheminAcces"].asString() ;
            _source = images["images"][nb]["source"].asString() ;
            _titre = images["images"][nb]["titre"].asString() ;
            _numero = images["images"][nb]["numero"].asInt() ;
            _cout = images["images"][nb]["cout"].asDouble() ;
            _acces = images["images"][nb]["acces"].asString() ;
            _dateAjout = images["images"][nb]["dateAjout"].asString() ;
            _dateCreation = images["images"][nb]["dateCreation"].asString() ;
            _cheminJson = chemin ;
            _numeroJson = nb ;
        } else{                                                                 // Sinon
            // Saisir un autre chemin
            cout << "Fichier non exist" << endl ;
            if (Continuer()){                                                   // Si l'utilisateur veut continuer
                cout << "Veuillez saisir un autre chemin : ./DATA/Bibliothèques/" << endl ;
                cin >> chemin ;                                                 // Saisie du nouveau chemin
                chemin = "./DATA/Bibliothèques/" + chemin ;                     // Completer le chemin
                decision = 'Y' ;                                 
            }
        }
    }while(decision == 'Y') ;    
}

Image::Image(string chemin, int num){
    // Declaration des variables 
    bool exist ;                                                                // Variable pour verifier l'existance du fichier
    char decision ;                                                             // Condition d'arret de la boucle
    Json::Value images ;                                                        // Objet Json
    Json::Reader reader ;                                                       // Variable pour la lecture du fichier Json
    VerifierExtension(chemin) ;                                                 // Verifier l'existance de l'xension ".json"
    exist = experimental::filesystem::exists(chemin) ;                          // Verifier l'existace du fichier
    do{
        decision = 'N' ;
        if (exist){                                                             // Si le fichier existe
            ifstream bibliotheque_file(chemin, ios::in) ;                       // Charger le contenu du fichier json 
            reader.parse(bibliotheque_file, images) ;                           // Importer le contenu a l'objet Json

            // Verifier le numero de l'image et saisir un autre numero en cas d'erreur
            while(VerifierNumero(num, images) == false){
                cout << "Veuillez saisir un numero valide !" << endl ;
                cin >> num ;
            }

            // Prendre les descripteurs de l'image
            _cheminAccesContenu = images["images"][num]["cheminAcces"].asString() ;
            _source = images["images"][num]["source"].asString() ;
            _titre = images["images"][num]["titre"].asString() ;
            _numero = images["images"][num]["numero"].asInt() ;
            _cout = images["images"][num]["cout"].asDouble() ;
            _acces = images["images"][num]["acces"].asString() ;
            _dateAjout = images["images"][num]["dateAjout"].asString() ;
            _dateCreation = images["images"][num]["dateCreation"].asString() ;
            _cheminJson = chemin ;
            _numeroJson = num ;
        } else{
            // Saisir un autre chemin
            cout << "Fichier non exist" << endl ;
            if (Continuer()){                                                   // Si l'utilisateur veut continuer
                cout << "Veuillez saisir un autre chemin : ./DATA/Bibliothèques/" ;
                cin >> chemin ;                                                 // Saisie du nouveau chemin
                chemin = "./DATA/Bibliothèques/" + chemin ;                     // Completer le chemin
                decision = 'Y' ;
            }
        }
    }while(decision == 'Y') ;    
}

Image::Image(Bibliotheque objBiblio,int numImage){
    Json::Value biblioJson = objBiblio.getBilbiotheque();
    _cheminAccesContenu = biblioJson["images"][numImage]["cheminAcces"].asString() ;
    _source = biblioJson["images"][numImage]["source"].asString() ;
    _titre = biblioJson["images"][numImage]["titre"].asString() ;
    _numero = biblioJson["images"][numImage]["numero"].asInt() ;
    _cout = biblioJson["images"][numImage]["cout"].asDouble() ;
    _acces = biblioJson["images"][numImage]["acces"].asString() ;
    _dateAjout = biblioJson["images"][numImage]["dateAjout"].asString() ;
    _dateCreation = biblioJson["images"][numImage]["dateCreation"].asString() ;
    _cheminJson = objBiblio.getCheminJson() ;
    _numeroJson = numImage ;
    Image::AfficherDescripteurImage();
}

/*Getter*/
// Chemin d'acces
string Image::getCheminAccesContenu() const {
    return _cheminAccesContenu ;
}    
// Source
string Image::getSource() const {
    return _source ;
}              
// Titre
string Image::getTitre() const {
    return _titre ;
}       
// Numero
int Image::getNumero() const {
    return _numero ;
}                
// Cout
double Image::getCout() const {
    return _cout ;
}                    
// Permission
string Image::getAcces() const {
    return _acces ;
}                  
// Date d'ajout
string Image::getDateAjout() const {
    return _dateAjout ;
}              
// Date de creation
string Image::getDateCreation() const {
    return _dateCreation ;
}       
// Chemin Json
string Image::getCheminJson() const {
    return _cheminJson ;
}
// Numero Json
int Image::getNumeroJson() const {
    return _numeroJson ;
}

/*Setters*/
// Chemin d'acces
void Image::setCheminAccesContenu(const string cheminAccesContenu){
    _cheminAccesContenu = cheminAccesContenu ;
}   
// Source
void Image::setSource(const string source){
    _source = source ;
}                     
// Titre
void Image::setTitre(const string titre){
    _titre = titre ;
}                    
// Numero
void Image::setNumero(const int numero){
    _numero = numero ;
}                     
// Cout
void Image::setCout(const double cout){
    _cout = cout ;
}                        
// Permission
void Image::setAcces(const string acces){
    _acces = acces ;
}                       
// Date d'ajout
void Image::setDateAjout(const string dateAjout){
    _dateAjout = dateAjout ;
}              
// Date de creation
void Image::setDateCreation(const string dateCreation){
    _dateCreation = dateCreation ;
}      
// Chemin Json
void Image::setCheminJson(const string cheminJson){
    _cheminJson = cheminJson ;
}  
// Numero Json
void Image::setNumeroJson(const int numeroJson){
    _numeroJson = numeroJson ;
}

/*Methodes principales*/
/*Afficher le contenu de l'image*/
void Image::AfficherContenuImage(){
    // Declaration des variables
    Mat image = imread(getCheminAccesContenu()) ;   // Charger l'image
    string windowName = getTitre() ;                // Nom de la fenetre d'affichage    

    // Affichage
    namedWindow(windowName, WINDOW_AUTOSIZE) ; 
    imshow(windowName, image);  
    waitKey(0) ; 
    destroyWindow(windowName) ; 
}

/*Afficher les descripteurs de l'image*/
void Image::AfficherDescripteurImage(){
    // Afficher les descripteurs de l'image
    cout << "Chemin :" << getCheminAccesContenu() << endl ;
    cout << "Source :" << getSource() << endl ;
    cout << "Titre :" << getTitre() << endl ;
    cout << "Numero :" << getNumero() << endl ;
    cout << "Cout :" << getCout() << endl ;
    cout << "Acces :" << getAcces() << endl ;
    cout << "Date d'ajout :" << getDateAjout() << endl ;
    cout << "Date de creation :" << getDateCreation() << endl ;
}

/*Modifier les descripteurs de l'image*/
void Image::ModifierDescripteurImage(){
    // Declaration des variables
    bool validation ;                                                               // Variable booleenne pour valider les conditions
    char decision ;                                                                 // Decision [Y/N]
    int choix ;                                                                     // Choix des actions  
    int c ;                                                                         // Indice
    int nouveauEntier ;                                                             // Variable pour la saisie des numeros entiers
    float nouveauReel ;                                                             // Variable pour la saisie des numeros reels      
    string nouveauTexte ;                                                           // Variable pour la saisie des chaines de caractere
    string jourAjout, moisAjout, anneeAjout ;                                       // Jour, Mois, Annee d'ajout
    string jourCreation, moisCreation, anneeCreation ;                              // Jour, Mois, Annee de creation
    string dateAjout, dateCreation ;                                                // Date d'ajout, date de creation
    ofstream biblio_new ;                                                           // Objet fichier
    Json::StyledWriter styledWriter;                                                // Writer Json
    Json::Value biblio ;                                                            // Objet Json
    Json::Reader reader ;                                                           // Variable pour la lecture du fichier Json

    ifstream bibliotheque_file(getCheminJson(), ios::in) ;                          // Charger le contenu du fichier json 
    reader.parse(bibliotheque_file, biblio) ;                                       // Importer le contenu a l'objet Json 

    do{
        // Afficher les choix
        cout << "Liste des descripteurs : " << endl ;
        cout << "1.Chemin" << endl << "2.Source" << endl << "3.Titre" << endl ;
        cout << "4.Numero" << endl << "5.Cout" << endl << "6.Acces" << endl ;
        cout << "7.Date d'ajout" << endl << "8.Date de Creation" << endl ;
        cout << "Veuillez saisir un choix : " << endl ;
        do{
            // Saisir le choix
            cin >> choix ;
            // Verifier le choix
            if(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8){
                cout << "Choix invalide ! Veuillez saisir un autre choix : " << endl ;
            }
        }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8) ;

        // Modification des descripteurs
        switch(choix){
            // Chemin
            case 1 :
                // Saisir le nouveau chemin
                cout << "Veuillez saisir le nouveau chemin : ./DATA/Images/" ;
                do{
                    cin >> nouveauTexte ;
                    nouveauTexte = "./DATA/Images/" + nouveauTexte ;                       // Completer le chemin
                    validation = experimental::filesystem::exists(nouveauTexte) ;   // Verifier l'existace du fichier
                    if(validation == false){
                        cout << "Ce fichier n'existe pas. Veuillez saisir un nouveau nom valide : ./DATA/Images/" ;
                    }
                }while(validation == false) ;

                // Modifier le chemin de l'image
                setCheminAccesContenu(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["cheminAcces"] = nouveauTexte ;
                break ;

            // Source
            case 2 :
                // Saisir la nouvelle source
                cout << "Veuillez saisir la nouvelle source : " << endl ;
                cin >> nouveauTexte ;
                // Modifier la source de l'image
                setSource(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["source"] = nouveauTexte ;
                break ;

            // Titre
            case 3 :
                // Saisir le nouveau titre
                cout << "Veuillez saisir le nouveau titre : " << endl ;
                cin >> nouveauTexte ;
                // Modifier le titre de l'image
                setTitre(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["titre"] = nouveauTexte ;
                break ;

            // Numero
            case 4 :
                // Saisir et verifier le nouveau numero
                cout << "Veuillez saisir le nouveau numero : " << endl ;
                do{
                    validation = false ;
                    // Saisie
                    cin >> nouveauEntier ;
                    // Verification
                    for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
                        // Si le numero existe deja
                        if(nouveauEntier == biblio["images"][c]["numero"].asInt()){
                            cout << "Ce numero existe deja. Veuillez choisir un autre numero : " << endl ;
                            validation = true ;
                            break ;
                        }
                    }
                }while(validation) ;
                
                // Modifier le numero de l'image
                setNumero(nouveauEntier) ;
                biblio["images"][getNumeroJson()]["numero"] = nouveauEntier ;
                break ;
            
            // Cout
            case 5 :
                // Saisir le nouveau cout
                cout << "Veuillez saisir le nouveau cout : " << endl ;
                do{
                    cin >> nouveauReel ;
                    if(nouveauReel < 0){
                        cout << "Saisie incorrecte. Veuillez saisir un cout positif : " << endl ;
                    }
                }while(nouveauReel < 0) ;
                
                // Modifier le cout de l'image
                setCout(nouveauReel) ;
                biblio["images"][getNumeroJson()]["cout"] = nouveauReel ;
                break ;

            // Acces
            case 6 :
                // Saisir le nouveau acces
                cout << "Veuillez saisir le nouveau acces (P : Publique, R : Restreint) : " << endl ;
                do{
                    cin >> nouveauTexte ;
                    if((nouveauTexte != "P") && (nouveauTexte != "R")){
                        cout << "Saisie incorrecte. Veuillez saisir 'P' (Publique) ou 'R' (Restreint) : " << endl ;
                    }
                }while((nouveauTexte != "P") && (nouveauTexte != "R")) ;
                
                // Modifier l'acces de l'image
                setAcces(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["acces"] = nouveauTexte ;
                break ;

            // Date d'ajout
            case 7 :
                // Saisir et valider la nouvelle date d'ajout
                do{
                    validation = false ;
                    // Saisie
                    cout << "Veuillez saisir la nouvelle date d'ajout (dd/mm/yyyy) : " << endl ;
                    nouveauTexte = SaisirDate(jourAjout, moisAjout, anneeAjout) ;

                    // Extraction de la date de creation pour comparer avec la date d'ajout (dd/mm/yyyy)
                    ExtraireDate(biblio["images"][getNumeroJson()]["dateCreation"].asString(), jourCreation, moisCreation, anneeCreation) ;

                    // Verification
                    if(stoi(anneeAjout + moisAjout + anneeAjout) - (stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                        cout << "La date d'ajout doit etre superieure ou egale a la date de creation. Veuillez reessayer." << endl ;
                        validation = true ;
                    }                    
                }while(validation) ;

                // Modifer la date d'ajout de l'image
                setDateAjout(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["dateAjout"] = nouveauTexte ;
                break ;

            // Date de creation
            case 8 :
                // Saisir et valider la nouvelle date de creation
                do{
                    validation = false ;
                    // Saisie
                    cout << "Veuillez saisir la nouvelle date de creation (dd/mm/yyyy) : " << endl ;
                    nouveauTexte = SaisirDate(jourCreation, moisCreation, anneeCreation) ;

                    // Extraction de la date de creation pour comparer avec la date d'ajout (dd/mm/yyyy)
                    ExtraireDate(biblio["images"][getNumeroJson()]["dateAjout"].asString(), jourAjout, moisAjout, anneeAjout) ;

                    // Verification
                    if((stoi(anneeAjout + moisAjout + jourAjout) - stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                        cout << "La date de creation doit etre inferieure ou egale a la date d'ajout. Veuillez reessayer." << endl ;
                        validation = true ;
                    }
                }while(validation) ;

                // Modifier la date de creation de l'image
                setDateCreation(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["dateCreation"] = nouveauTexte ;
                break ;

            // Defaut
            default : break ;
        }
    }while(Continuer()) ;

    // Sauvegarder
    cout << "Voulez-vous sauvegarder ce resultat ? [Y/N]" << endl ;
    do{
        // Saisir la decision
        cin >> decision ;
        // Verifier la decision
        if((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide ! Veuillez saisir 'Y' ou 'N' : " << endl ;
        }
    }while((decision != 'Y') && (decision != 'N')) ;
    if(decision == 'Y'){
        biblio_new.open(getCheminJson()) ;              // Ouvrir le fichier
        biblio_new << styledWriter.write(biblio) ;      // Ecrire    
        biblio_new.close() ;                            // Fermer le fichier
        cout << "Modifications sauvegardees." << endl ;
    }
}

/*Traitement de l'image*/
void Image::TraitementImage(){
    Mat image = imread(getCheminAccesContenu()) ;                                   // Charger l'image
    Mat image_channels[3] ;                                                         // Canaux de l'image
    Mat filtre = (Mat_<double>(3,3) << 1, 1, 1, 1, 1, 1, 1, 1, 1) ;
    filtre = filtre/9 ;

    Mat imageConv = ImageConvolution(image, filtre) ;
    Mat image_NoirBlanc = ImageNiveauGris(image) ;

    // Affichage
    namedWindow("Image Noir et Blanc") ; 
    imshow("Image Noir et Blanc", image_NoirBlanc);  
    waitKey(0) ; 
    destroyWindow("Image Noir et Blanc") ;
}

/*Methodes supplementaires*/
/*Verifier l'extension ".json"*/
void Image::VerifierExtension(string& nom){
    if (nom.length() < 6){                                          // Si la longueur du nom est < 6 (".json" = 5 caracteres)
        nom += ".json" ;                                            // Ajouter l'extension
    }else{                                                          // Sinon
        if(nom.find(".json", nom.length()-5) != nom.length()-5){    // Si ".json" n'existe pas dans le nom saisi
            nom += ".json" ;                                        // Ajouter l'extension
        }
    }    
}

/*Continuer [Y/N]*/
bool Image::Continuer(){
    // Declaration de variable
    char decision ;

    cout << "Voulez-vous continuer ? [Y/N]" << endl ;
    do{
        // Saisie
        cin >> decision ;

        // Verification
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N'." << endl ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;

    // Retour
    return (decision == 'Y') ;
}

/*Verifier l'existance du numero d'image*/
bool Image::VerifierNumero(int& numero, const Json::Value biblio){
    // Declaration des variables
    int c ;                                             // Indice
    bool exist ;                                        // Verificaiton de l'existance du numero saisi
    int nbImages = biblio["nbImages"].asInt() ;         // Nombre d'images existantes dans la bibliotheque
     
    // Verification de l'existance du numero saisi dans la bibliotheque
    for (c = 0 ; c < nbImages ; c++){
        // Si le numero existe
        if (numero == biblio["images"][c]["numero"].asInt()){
            exist = true ;
        }
    }

    // Si le numero n'existe pas
    if (exist == false){
        cout << "Le numero choisi n'existe pas." << endl ;
    }

    // Retour
    return exist ;    
}

/*Saisie et validation de la date*/
string Image::SaisirDate(string& jour, string& mois, string& annee){
    // Declaration des variables
    bool valideDate = true ;            // Validation de la date
    string date ;                       // Date

    // Initialisation
    jour.clear() ;
    mois.clear() ;
    annee.clear() ;

    // Saisie et verification
    do{
        // Saisie - Jour
        getline(cin, jour, '/') ;
        // Saisie - Mois
        getline(cin, mois, '/') ;
        // Saisie - Annee
        getline(cin, annee, '\n') ;

        // Verification - Annee
        // Si l'annee saisie est hors intervalle [1800, 2022]
        if((stoi(annee) > 2022) || (stoi(annee) < 1800)){                                                                       
            cout << "Annee invalide. Veuillez saisir une nouvelle valeur entre 1800 et 2022 : " ;
            valideDate = false ;
        }

        // Verification - Mois
        // Si le mois saisi est  hors intervalle [1, 12]
        if((stoi(mois) < 1) || (stoi(mois) > 12)){                                                                              
            cout << "Mois invalide. Veuillez saisir une nouvelle valeur entre 1 et 12 : " ;
            valideDate = false ;
        }

        // Verification - Jour
        // Si le jour saisi est hors intervalle [1, 31]
        if((stoi(jour) > 31) || (stoi(jour) < 1)){                                                                              
            cout << "Jour invalide. Veuillez saisir une nouvelle valeur entre 1 et 31 : " ;
            valideDate = false ;
        // Si Mois = 2, Jour > 28
        }else if((stoi(mois) == 2) && (stoi(jour) > 28)){                 
            // Mois = 2, Jour > 29 ou jour = 29 mais annee % 4 != 0                                                      
            if((stoi(jour) > 29) || ((stoi(jour) == 29) && ((stoi(annee) % 4) != 0))){                                          
                cout << "Jour invalide. Veuillez saisir une nouvelle valeur < 29 : " ;
                valideDate = false ;
            }
        // Jour = 31 mais Mois = 4, 6, 9, 11
        }else if((stoi(jour) == 31) && ((stoi(mois) == 4) || (stoi(mois) == 6) || (stoi(mois) == 9) || (stoi(mois) == 11))){    
            cout << "Jour invalide. Veuillez saisir une nouvelle valeur < 31 : " ;
            valideDate = false ;
        }
    }while(valideDate == false) ;

    // Generer la date
    date = jour + "/" + mois + "/" + annee ;

    return date ;
}

/*Extraire jour, mois, annee a partir d'une date*/
void Image::ExtraireDate(const string date, string& jour, string& mois, string& annee){
    // Initialisation
    jour.clear() ;
    mois.clear() ;
    annee.clear() ;

    // Jour de creation : caracteres aux indices 0 et 1
    jour.push_back(date.at(0)) ; 
    jour.push_back(date.at(1)) ;

    // Mois de creation : caracteres aux indices 3 et 4
    mois.push_back(date.at(3)) ;
    mois.push_back(date.at(4)) ;

    // Annee de creation : 4 dernieres caracteres
    annee.push_back(date.at(6)) ;
    annee.push_back(date.at(7)) ;
    annee.push_back(date.at(8)) ;
    annee.push_back(date.at(9)) ;    
}


/*Filtre median*/




/*
            do{
                // Saisir le numero de l'image
                cin >> nb ;
                // Verifier le numero de l'image et saisir un autre numero en cas d'erreur
                if ((nb > images["nbImages"].asInt()-1) || (nb < 0)){
                    cout << "Veuillez saisir un numero valide !" << endl ;
                }
            }while((nb > images["nbImages"].asInt()-1) || (nb < 0)) ;
*/

/*
            do{
                if ((num > images["nbImages"].asInt()-1) || (num < 0)){
                    cout << "Veuillez saisir un numero valide !" << endl ;
                    cin >> num ;
                }
            }while((num > images["nbImages"].asInt()-1) || (num < 0)) ;
*/







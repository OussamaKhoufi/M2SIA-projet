#include "../headers/bibliotheque.h"

/*Constructeur vide*/
Bibliotheque::Bibliotheque(){
    // Declaration des variables
    string nomNew ;                                             // Nom du nouveau fichier
    bool exist ;                                                // Variable pour verifier l'existance du fichier

    // Saisie du nom du nouveau fichier
    cout << "Veuillez donner le nom de la bibliotheque : " << endl ;
    cin >> nomNew ;

    // Verifier l'extension ".json"
    VerifierExtension(nomNew) ;

    nomNew = "./DATA/Bibliothèques/" + nomNew ;
    exist = experimental::filesystem::exists(nomNew) ;  

    // Vérifier l'existance ou non du fichier
    if(exist){                                                              // Si le nom saisi existe
        cout << "Fichier existant." << endl ;

        Json::Reader reader ;                                               // Variable pour lire un fichie Json
        ifstream bibliothequeFile(nomNew, ios::in) ;                        // Chargement du fichier Json

        // Verifier l'extension ".json"
        VerifierExtension(nomNew) ;
        cout << nomNew << endl ; 
        // Lecture du fichier et copie du contenu dans la bibliotheque
        reader.parse(bibliothequeFile, _bibliotheque) ;    

    }else{                                                                  // Sinon
        cout << "Fichier inexistant. Generer une nouvelle bibliotheque." << endl ;
        AjouterImage() ;
    }
    _cheminJson = nomNew;
}

/*Constructeur avec le nom de la bibliotheque donnee par l'utilisateur*/
Bibliotheque::Bibliotheque(string nom){
    // Declaration des variables
    Json::Reader reader ;                       // Variable pour lire un fichie Json

    // Verifier l'extension ".json"
    VerifierExtension(nom) ;
    nom = "./DATA/Bibliothèques/" + nom ;
    cout << nom << endl ;

    // Lecture du fichier et copie du contenu dans la bibliotheque
    ifstream bibliothequeFile(nom, ios::in) ;   // Chargement du fichier Json
    reader.parse(bibliothequeFile, _bibliotheque) ; 
    _cheminJson = nom;                
}

/*Constructeur avec un objet Json*/
Bibliotheque::Bibliotheque(const Json::Value bibliotheque){
    setBilbiotheque(bibliotheque) ;
}

/*Getter*/
Json::Value Bibliotheque::getBilbiotheque() const{
    return _bibliotheque ;
}
string Bibliotheque::getCheminJson() const { return _cheminJson; }
/*Setter*/
void Bibliotheque::setBilbiotheque(const Json::Value bibliotheque){
    _bibliotheque = bibliotheque ;
}

/*Afficher la liste des descripteurs*/
void Bibliotheque::AfficherDescripteurs(){
    // Declaration des variables
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
    int c ;                                         // Indice

    // Affichage
    for (c = 0 ; c < nbImages ; c++){
        cout << "Descipteur de l'image " << c+1 << " : " << endl ;
        cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
        cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
        cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
        cout << "Cout : " << biblio["images"][c]["cout"].asDouble() << "€" << endl ;
        cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
        cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
        cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ;  
    }
}

/*Affichage le cout d'une image*/
void Bibliotheque::AfficherCout(){
    // Declaration des variables
    int c ;                                         // Indice
    int numeroSaisie ;                              // Numero saisi par l'utilisateur
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
     
    // Choix du numero de l'image et verification 
    do{
        // Saisie du numero souhaite
        cout << "Veuillez donner le numero de l'image : " << endl ;
        cin >> numeroSaisie ; 

        // Verification de l'existance du numero saisi dans la bibliotheque
        if (VerifierNumero(numeroSaisie, getBilbiotheque())){
            for(c = 0 ; c < nbImages ; c++){
                // Chercher l'image ayant le numero correspondant
                if(biblio["images"][c]["numero"].asInt() == numeroSaisie){
                    // Affichage le cout correspondant
                    cout << "Cout de l'image " << numeroSaisie << " : " << biblio["images"][c]["cout"].asDouble() << "€" << endl ;
                    break ;
                }
            }
        }
    }while(Continuer()) ;
}

/*Construire et afficher une sous-liste*/
void Bibliotheque::ConstruireAfficherSousListe(){
    // Declaration des variables
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
    int choix ;                                     // Choix du critere
    int choixPlage ;                                // Choix de la plage de cout
    int c, k ;                                      // Indices
    int compteur = 0 ;                              // Compteur du nombre d'images choisies par critere
    string choixSource ;                            // Choix de la source
    bool valideSource = false ;                     // Verification du choix de la source saisie par l'utilisateur
    double plageMin, plageMax ;                     // Plage de cout personalisee
    vector <string> listeSource ;                   // Liste des sources

    cout << "Veuillez choisir un critere : " << endl ;
    cout << "1. Cout" << endl << "2. Source" << endl << endl ;

    // Saisie du critere et verification
    do{
        // Saisie le choix
        cin >> choix ;
        // Validation du choix
        if ((choix != 1) && (choix != 2)){
            cout << "Choix invalide. Veuillez saisir '1' ou '2' : " ;
        }
    }while((choix != 1) && (choix != 2)) ;
    switch (choix){
        // Critere choisi : Cout
        case 1 :
            do{
                // Choix de la plage de cout
                cout << "Veuillez choisir une plage de cout :" << endl ;
                cout << "1. Gratuit" << endl << "2. Cout ≤ 99,99 €" << endl << "3. 100 ≤ Cout ≤ 999,99 €" << endl << "4. Cout > 1000 €" << endl << "5. Plage personnalisee" << endl ;

                // Saisie de la plage et validation
                do{
                    cin >> choixPlage ;
                    if ((choixPlage != 1) && (choixPlage != 2) && (choixPlage != 3) && (choixPlage != 4) && (choixPlage != 5)){
                        cout << "Choix invalide. Veuillez saisir '1', '2', '3', '4' ou '5' : " ;
                    }
                }while((choixPlage != 1) && (choixPlage != 2) && (choixPlage != 3) && (choixPlage != 4) && (choixPlage != 5)) ;  
                switch (choixPlage){
                    // Sous-critere : Cout gratuit
                    case 1 :
                        // Affichage conditionnelle
                        for (c = 0 ; c < nbImages ; c++){
                            if (biblio["images"][c]["cout"].asDouble() == 0.0){
                                cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
                                cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                                cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                                cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                                cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                                cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                                compteur++ ;
                            }
                        }
                        cout << "Il y a " << compteur << " images gratuites." << endl << endl ;
                        break ;

                    // Sous-critere : Cout ≤ 99,99 €
                    case 2 :
                        // Affichage conditionnelle
                        for (c = 0 ; c < nbImages ; c++){
                            if (biblio["images"][c]["cout"].asDouble() <= 99.99){
                                cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
                                cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                                cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                                cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                                cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                                cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                                compteur++ ;
                            }
                        }
                        cout << "Il y a " << compteur << " images ayant le cout ≤ 99,99 €" << endl << endl ;
                        break ;  

                    // Sous-critere : 100 ≤ Cout ≤ 999,99 €
                    case 3 :
                        // Affichage conditionnelle
                        for (c = 0 ; c < nbImages ; c++){
                            if ((biblio["images"][c]["cout"].asDouble() >= 100) && (biblio["images"][c]["cout"].asDouble() <= 999.99)){
                                cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
                                cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                                cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                                cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                                cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                                cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                                compteur++ ;
                            }
                        }
                        cout << "Il y a " << compteur << " images ayant le cout entre 100 et 999,99 €" << endl << endl ;
                        break ;  

                    // Sous-critere : Cout > 1000 €
                    case 4 :
                        // Affichage conditionnelle
                        for (c = 0 ; c < nbImages ; c++){
                            if (biblio["images"][c]["cout"].asDouble() > 1000){
                                cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
                                cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                                cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                                cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                                cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                                cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                                compteur++ ;
                            }
                        }
                        cout << "Il y a " << compteur << " images ayant le cout > 1000 €" << endl << endl ;
                        break ;  

                    // Sous-critere : Plage de cout personnalisee
                    case 5 :
                        // Saisie de la plage de cout souhaitee
                        cout << "Veuillez saisir la plage de cout souhaitee : " << endl ; 
                        // Cout minimum
                        cout << "Min : " ;
                        do{
                            cin >> plageMin ;
                            if (plageMin < 0){
                                cout << "Veuillez choisir une valeur positive ou nulle." << endl ;
                            }
                        }while(plageMin < 0) ;
                        // Cout maximum
                        cout << "Max : " ;
                        do{
                            cin >> plageMax ;
                            if (plageMax < plageMin){
                                cout << "Veuillez choisir une valeur > " << plageMin << endl ;
                            }
                        }while(plageMax < plageMin) ;
                        // Affichage conditionnelle
                        for (c = 0 ; c < nbImages ; c++){
                            if ((biblio["images"][c]["cout"].asDouble() >= plageMin) && (biblio["images"][c]["cout"].asDouble() <= plageMax)){
                                cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
                                cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                                cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                                cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                                cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                                cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                                compteur++ ;
                            }
                        }
                        cout << "Il y a " << compteur << " images dans la plage de cout personnalisee" << endl << endl ;
                        break ;
                }

            }while(Continuer()) ;                

            break ;

        // Critere choisi : Source
        case 2 :
            // Creer la liste des sources
            listeSource[0] = biblio["images"][0]["source"].asString() ;
            for (c = 1 ; c < nbImages ; c++){                                               // Pourchaque element de la bibliotheque
                for(k = 0 ; k <= (int)listeSource.max_size() ; k++){                        // Pour chaque element de la liste des sources
                    if(biblio["images"][c]["source"].asString() == listeSource[k]){         // Si la source de l'element courant de la bibliotheque existe deja dans la liste
                        break ;
                    }else{                                                                  // Sinon     
                        listeSource.push_back(biblio["images"][c]["source"].asString()) ;   // Ajouter la nouvelle source
                    }
                }
            }
            // Affichage des sources existantes
            cout << "Les sources existantes dans la bibliotheque : " << endl ;
            for(c = 0 ; c < (int)listeSource.max_size() ; c++){
                cout << listeSource[c] << endl ;
            }

            // Saisie et verification de la source souhaitee
            do{
                // Saisie
                cout << "Veuillez saisir une source souhaitee : " << endl ;
                cin >> choixSource ;

                // Affichage conditionnelle
                for (c = 0 ; c < nbImages ; c++){
                    if (biblio["images"][c]["source"].asString() == choixSource){
                        cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
                        cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
                        cout << "Cout : " << biblio["images"][c]["cout"].asDouble() << "€" << endl ;
                        cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
                        cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
                        cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ; 
                        compteur++ ;
                        valideSource = true ;
                    }
                }

                // Si la source saisie est invalide
                if(valideSource == false){
                    cout << "Source invalide. Veuillez saisir une autre source." << endl ;
                }
            }while(Continuer()) ;

            cout << "Il y a " << compteur << " images correspondates a cette source." << endl << endl ;
            break ;
        default :
            break ;
    }
}

/*Trier la bibliotheque suivant une critere choisie*/
void Bibliotheque::Trier(){
    // Declaration des variables
    Json::Value biblioTrie ;                                // Bibliotheque trie
    int choix ;                                             // Choix du critere pour trier la bibliotheque

    do{
        // Choix du critere de tri
        cout << "Tri dans l'ordre decroissant" << endl ; 
        cout << "1. Cout" << endl << "2. Titre" << endl << endl ;
        cout << "Votre choix : " ; 
        do{
            // Saisie le choix
            cin >> choix ;
            // Validation du choix
            if ((choix != 1) && (choix != 2)){
                cout << "Choix invalide. Veuillez saisir '1' ou '2'." << endl ;
            }
        }while((choix != 1) && (choix != 2)) ;
        switch (choix){
            case 1 :
                cout << "Critere choisi : Cout dans l'ordre decroissant" << endl ;
                biblioTrie = TriElement("cout") ;
                break ;
            case 2 :
                cout << "Critere choisi : Titre dans l'ordre decroissant" << endl ;
                biblioTrie = TriElement("titre") ;
                break ;
            default :
                break ;
        }
    }while(Continuer()) ;
}

/*Ajouter une image*/
void Bibliotheque::AjouterImage(){ 
    Json::Value biblio = getBilbiotheque() ; 
    int nbImages = biblio["images"].size() ;                            // Nombre d'images présent dans la bibliotheque avant l'ajout d'une nouvelle image  
    int indice = nbImages ;
    bool exist ;
    char decision ;
    bool valideDate ;                                                   // Variable pour valider la date d'ajout
    string jourAjout, moisAjout, anneeAjout ;                           // Variables pour la saisie de la date d'ajout de l'image
    string jourCreation, moisCreation, anneeCreation ;                  // Variables pour la saisie de la date d'ajout de l'image
    float nbReel ;                                                      // Variable pour la saisie en nombre reel
    string texte ;                                                      // Variable pour la saisie en texte

    // Boucle de saisir
    do{
        // Saisie : Acces
        cout << "Acces (P : Publique, R : Restreint) : " ;
        do{
            cin >> texte ;
            // Verification
            if ((texte != "P") && (texte != "R")){
                cout << "Sasie incorrecte. Veuillez saisir 'P' ou 'R' : " ;
            }
        }while((texte != "P") && (texte != "R")) ;
        biblio["images"][indice]["acces"] = texte ;

        // Saisie : Chemin acces
        cout << "Chemin d'acces : ./DATA/Images/" ;
        do{
            cin >> texte ;
            texte = "./DATA/Images/" + texte ;
            // Verifier l'existance du fichier
            exist = experimental::filesystem::exists(texte) ; 
            // Si le fichier n'existe pas
            if(exist == false){
                cout << "Ce fichier n'existe pas. Veuillez saisir un nom valide : ./DATA/Images/" ;
            }
        }while (exist == false) ;
        biblio["images"][indice]["cheminAcces"] = texte ;

        // Saisie : Cout
        cout << "Cout : " ;
        cin >> nbReel ;           
        biblio["images"][indice]["cout"] = nbReel ;

        // Saisie : Date de creation
        cout << "Date de creation (dd/mm/yyyy) : " ;
        texte = SaisirDate(jourCreation, moisCreation, anneeCreation) ;
        biblio["images"][indice]["dateCreation"] = texte ;

        // Saisie : Date d'ajout
        do{  
            cout << "Date d'ajout (dd/mm/yyyy) : " ;
            texte = SaisirDate(jourAjout, moisAjout, anneeAjout) ;
            // Si la date d'ajout est superieure ou egale a la date de creation
            if((stoi(anneeAjout + moisAjout + jourAjout) - stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                cout << "La date d'ajout doit etre superieure ou egale a la date de creation. Veuillez reessayer." << endl ;
                valideDate = false ;
            }else{                      
                valideDate = true ;
            }
        }while(valideDate == false) ;
        
        biblio["images"][indice]["dateAjout"] = texte ;

        // Numero de l'image
        biblio["images"][indice]["numero"] = indice + 1 ;

        // Saisie : Source
        cout << "Source : " ;
        cin >> texte ;
        biblio["images"][indice]["source"] = texte ;

        // Saisie : Titre
        cout << "Titre : " ;
        cin >> texte ;
        biblio["images"][indice]["titre"] = texte ;
        biblio["nbImages"] = indice + 1 ;

        // Incrementation de l'indice de la boucle
        indice++ ;

    }while(Continuer()) ;

    setBilbiotheque(biblio) ;

    // Decision de sauvegarder
    cout << "Voulez-vous sauvegarder ce resultat ? [Y/N]" << endl ;
    do{
        cin >> decision ;
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N'." << endl ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;

    // Sauvegardement
    if (decision == 'Y'){
        Sauvegarder() ;
    }    
}

/*Supprimer une image bibliotheque*/
void  Bibliotheque::SupprimerImage(){
    // Declaration des variables
    Json::Value removed ;
    Json::Value biblio = getBilbiotheque() ;
    int numero ;
    int nbImages = biblio["images"].size() ;     // Nombre d'images présent dans la bibliotheque avant la suppresion d'une nouvelle image
    

    do{
        // Saisir du numéro de l'image à supprimer
        cout << "Entrez le numero de l'image a supprimer"<< endl ;
        cin >> numero ;

        // Verifier l'existance du numero saisi
        VerifierNumero(numero, getBilbiotheque()) ;
        if(VerifierNumero(numero, getBilbiotheque())){
            int indexImage = 0 ;
            for(const auto & obj : biblio["images"]) {
                if (obj["numero"] == numero) {
                    // Supprésion dans le vecteur images des élèment associer à ce numéro
                    biblio["images"].removeIndex(indexImage, &removed);
                    // Mise à Jour sur le nombre d'image.
                    biblio["nbImages"] = nbImages - 1 ;
                }
                //Incrémenter l'index Images
                indexImage++;
            }
            
            // Mise à jour de la bibliothèque
            setBilbiotheque(biblio);
        }
    }while(Continuer() && VerifierBibliotheque()) ;
}

/*Sauvegarder une bibliotheque*/
void Bibliotheque::Sauvegarder(){
    // Declaration des variables
    string nomNew ;                                                     // Nom du nouveau fichier
    bool exist ;                                                        // Variable pour verifier l'existance du fichier
    ofstream bibliotheque_new ;                                         // Objet fichier
    Json::StyledWriter styledWriter;                                    // Writer Json
    
    // Verifier l'existance ou non du fichier
    cout << "Veuillez donner un nom au fichier de resultat : " << endl ;
 
    cin >> nomNew ; 
    VerifierExtension(nomNew) ;
    nomNew = "./DATA/Bibliothèques/" + nomNew ;
    exist = experimental::filesystem::exists(nomNew) ;
    if(exist){
        cout << "Ce fichier existe deja. Le sauvegardement va ecraser le fichier existant." << endl ;
        if(Continuer()){
            bibliotheque_new.open(nomNew) ;                             // Ouvrir le fichier
            bibliotheque_new << styledWriter.write(getBilbiotheque());  // Ecrire
            bibliotheque_new.close();                                   // Fermer le fichier
        }
    }else{
        bibliotheque_new.open(nomNew) ;                                 // Ouvrir le fichier
        bibliotheque_new << styledWriter.write(getBilbiotheque());      // Ecrire
        bibliotheque_new.close();                                       // Fermer le fichier        
    }
    cout << "Bibliotheque sauvegardee." << endl ;
}

/*Saisie et validation de la date*/
string Bibliotheque::SaisirDate(string& jour, string& mois, string& annee){
    // Declaration de variable
    bool valideDate = true ;            // Validation de la date
    string date ;

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
        // Si le mois saisi est hors intervalle [1, 12]
        if((stoi(mois) < 1) || (stoi(mois) > 12)){                                                                              
            cout << "Mois invalide. Veuillez saisir une nouvelle valeur entre 1 et 12 : " ;
            valideDate = false ;
        }

        // Verification - Jour
        // Si le jour saisi est hors intervalle [1, 31]
        if((stoi(jour) > 31) || (stoi(jour) < 1)){                                                                              
            cout << "Jour invalide. Veuillez saisir une nouvelle valeur entre 1 et 31 : " ;
            valideDate = false ;
        // Mois = 2, Jour > 28
        }else if((stoi(mois) == 2) && (stoi(jour) > 28)){    
            // Mois = 2, Jour > 29 ou jour = 29 mais annee % 4 != 0                                                                   
            if((stoi(jour) > 29) || ((stoi(jour) == 29) && ((stoi(annee) % 4) != 0))){                                          
                cout << "Jour invalide. Veuillez saisir une nouvelle valeur < 29 : " ;
                valideDate = false ;
            }
        // Si Jour = 31 mais Mois = 4, 6, 9, 11
        }else if((stoi(jour) == 31) && ((stoi(mois) == 4) || (stoi(mois) == 6) || (stoi(mois) == 9) || (stoi(mois) == 11))){    
            cout << "Jour invalide. Veuillez saisir une nouvelle valeur < 31 : " ;
            valideDate = false ;
        }
    }while(valideDate == false) ;

    // Generer la date
    date = jour + "/" + mois + "/" + annee ;

    return date ;
}

/*Continuer [Y/N]*/
bool Bibliotheque::Continuer(){
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

/*Verifier l'extension ".json"*/
void Bibliotheque::VerifierExtension(string& nom){
    if (nom.length() < 6){                                          // Si la longueur du nom est < 6 (".json" = 5 caracteres)
        nom += ".json" ;                                            // Ajouter l'extension
    }else{                                                          // Sinon
        if(nom.find(".json", nom.length()-5) != nom.length()-5){    // Si ".json" n'existe pas dans le nom saisi
            nom += ".json" ;                                        // Ajouter l'extension
        }
    }    
}

/*Tri elementaire*/
Json::Value Bibliotheque::TriElement(const string critere){
    // Declaration des variables
    Json::Value biblioTrie ;                                                    // Initialiser la bibliotheque triee
    Json::Value biblioNonTrie = getBilbiotheque() ;                             // Initialiser la bibliotheque non triee
    int nbImages = biblioNonTrie["nbImages"].asInt() ;                          // Nombre d'images existantes dans la bibliotheque
    int c, k ;                                                                  // Indices
    char decision ;
    vector<string> critereTri ;                                                 // Vecteur des criteres tries
    vector<double> valNum ;                                                     // Pour convertir les chaines de caractere en valeurs numeriques
    vector<string> critereNonTri ;                                              // Vecteur des criteres non tries
    vector<int> indiceTrie ;                                                    // Vecteur des indices tries

    // Initialiser vecteur des titres
    for (c = 0 ; c < nbImages ; c++){
        critereNonTri.push_back(biblioNonTrie["images"][c][critere].asString()) ;
    }

    // Vecteur des indices du tri
    critereTri = critereNonTri ;                                                // Initialiser le vecteur des couts tries
    if(critere == "cout"){
        // Conversion de chaine de caracteres en chiffres
        transform(critereNonTri.begin(), critereNonTri.end(), back_inserter(valNum), [](const string & astr){ return stod( astr) ; } ) ;
        // Trier les couts dan l'ordre decroissant
        sort(valNum.begin(), valNum.end(), greater<double>()) ;                 
        // Conversion de chiffres en chaine de caracteres
        transform(valNum.begin(), valNum.end(), back_inserter(critereNonTri), [](const double & adbl){ return to_string( adbl) ; } ) ;
    }else{
        sort(critereTri.begin(), critereTri.end(), greater<string>()) ;         // Trier les couts dan l'ordre decroissant
    }
    
    // Initialiser la premiere valeur du vecteur des indices du tri par l'indice du cout maximum
    for (c = 0 ; c < nbImages ; c++){
        if(critereNonTri[c] == critereTri[0]){
            indiceTrie.push_back(c) ;
            break ;
        }
    }

    // Remplir le vecteur des indice du tri
    for (c = 1 ; c < nbImages ; c++){                                           // Pour chaque element du vecteur des indices du vecteur des couts trie
        for (k = 0 ; k < nbImages ; k++){                                       // Pour chaque element du vecteur des indices du vecteur des couts non trie
            if ((critereTri[c] == critereNonTri[k])){                           // Si on retrouve le meme cout dans le vecteur trie que dans le vecteur non trie     
                if ((*find(indiceTrie.begin(), indiceTrie.end(), k)) != k){     // Si l'indice correspondant n'est pas encore ecrit dans le vecteur des indices de tri                         
                    indiceTrie.push_back(k) ;                                   // Ajouter cet indice
                }
            }
        }
    }
    
    //Tri de la bibliotheque
    biblioTrie = biblioNonTrie ;                                                // Initialisation
    for (c = 0 ; c < nbImages ; c++){                                           // Remplir la bibliotheque triee
        biblioTrie["images"][c] = biblioNonTrie["images"][indiceTrie[c]] ;      
    }

    // Affichage
    setBilbiotheque(biblioTrie) ;
    AfficherDescripteurs() ;
    // Sauvegardement
    cout << "Voulez-vous sauvegarder ce resultat ? [Y/N]" << endl ;
    do{
        cin >> decision ;
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N'." << endl ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;
    if (decision == 'Y'){
        Sauvegarder() ;
    }

    // Retour
    return biblioTrie ;
}

/*Verifier l'existance d'un numero de l'image*/
bool Bibliotheque::VerifierNumero(int& numero, const Json::Value biblio){
    // Declaration des variables
    int c ;                                         // Indice
    bool exist ;                                    // Verificaiton de l'existance du numero saisi
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
     
    // Verification de l'existance du numero saisi dans la bibliotheque
    for (c = 0 ; c < nbImages ; c++){
        // Si le numero existe
        if (numero == getBilbiotheque()["images"][c]["numero"].asInt()){
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

/*Veriffier bibliotheque vide ou invalide*/
bool Bibliotheque::VerifierBibliotheque(){
    // Si la biliotheque ne contient aucune image
    if(getBilbiotheque()["nbImages"].asInt() == 0){
        cout << "Bibliotheque vide" << endl ;
        return false ;
    // Si le nombre d'images est negatif
    }else if(getBilbiotheque()["nbImages"].asInt() < 0){
        cout << "Bibliotheque invalide." << endl ;
        return false ;
    // Bibliotheque valide
    }else{
        return true ;
    }
}
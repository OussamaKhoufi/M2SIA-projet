#include "../headers/traitementImage.h"
using namespace cv ;
using namespace std ;
/*Generer une matrice zero*/
Mat ImageZero(const int nbLigne, const int nbColonne){
    // Declaration des variables
    int ligne, colonne ;        // Indices
    Size dimensionZero ;
    dimensionZero.height = nbLigne ;
    dimensionZero.width = nbColonne ;
    Mat ImageZero = Mat(dimensionZero, CV_8U) ;

    // Remplir la matrice
    for(ligne = 0 ; ligne < nbLigne ; ligne++){
        for (colonne = 0 ; colonne < nbColonne ; colonne++){
            ImageZero.at<unsigned char>(ligne, colonne) = 0 ;
        }
    }

    // Retour
    return ImageZero ;
}

/*Effet miroir*/
Mat ImageMiroir(const Mat image, const Mat filtre){
    // Declaration des variables
    int ligne, colonne, lig, col ;                                          // Indices
    int L_image, C_image, L_filtre, C_filtre, L_miroir, C_miroir  ;         // Dimensions

    // Dimensions de l'image
    L_image = image.size().height ;                                         // Nombre de lignes
    C_image = image.size().width ;                                          // Nombre de colonnes

    // Dimensions du filtre
    L_filtre = filtre.size().height ;                                       // Nombre de lignes
    C_filtre = filtre.size().width ;                                        // Nombre de colonnes

    // Initialisation de l'image resultante - Effet miroir
    L_miroir = L_image + L_filtre - 1 ;                                     // Nombre de lignes
    C_miroir = C_image + C_filtre - 1 ;                                     // Nombre de colonnes

    // Initialisation de l'image resultante
    Mat ImageMiroir = ImageZero(L_miroir, C_miroir) ;                 

    // Les bords horizontaux de l'image avec effet miroir
    // Premieres lignes 
    // Initialisation des indices
    lig = 0 ;      
    for(ligne = floor(L_filtre/2) - 1 ; ligne >= 0 ; ligne--){
        col = 0 ;
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
  
    // Dernieres lignes 
    // Initialisation des indices
    lig = L_image - floor(L_filtre/2) ; 
    for(ligne = L_miroir - 1 ; ligne >= L_miroir - floor(L_filtre/2) ; ligne--){
        col = 0 ;     
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }

    // Les bords verticaux de l'image avec effet miroir
    // Premieres colonnes 
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ; 
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
 
    // Dernieres colonnes
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - 1 ; 
        for (colonne = C_miroir - floor(C_filtre/2) ; colonne <= (C_miroir - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig++ ; 
    }

    // Les coins
    // En haut, a gauche
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = floor(C_filtre/2) ;    
        for (colonne = 0 ; colonne <= (floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig-- ; 
    }    

    // En haut, a droite
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= (C_miroir - floor(C_filtre/2)) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // En bas, a gauche
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = 0 ;    
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }       

    // En bas, a droite
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= C_miroir - floor(C_filtre/2) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // Contenu
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ;    
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }    

    return ImageMiroir ;
}

/*Produit de convolution entre deux matrices*/
Mat MatriceConvolution(const Mat image, const Mat filtre){
    // Declaration des variables
    int ligne, colonne, lig, col ;                                  // Indices
    int L_image, C_image ;                                          // Dimensions de l'image
    int L_filtre, C_filtre ;                                        // Dimensions du filtre
    int val ;                                                       // Variable intermediaire
    Mat imageConv = Mat(image.size(), CV_8U) ;                      // Image resultante
    Mat imageMiroir = ImageMiroir(image, filtre) ;                // Image avec effet miroir
    
    // Dimensions de l'image
    L_image = image.size().height ;                                 // Nombre de lignes
    C_image = image.size().width ;                                  // Nombre de colonnes

    // Dimensions du filtre
    L_filtre = filtre.size().height ;                               // Nombre de lignes
    C_filtre = filtre.size().width ;                                // Nombre de colonnes

    // Produit de convolution
    for(ligne = 0 ; ligne <= L_image - 1 ; ligne++){                // Pour chaque ligne de l'image
        for(colonne = 0 ; colonne <= C_image - 1 ; colonne++){      // Pour chaque colonne de l'image
            val = 0 ;                                               // Remise a zero la variable intermediaire
            for(lig = 0 ; lig <= L_filtre/2 + 1  ; lig++){          // Pour chaque ligne du filtre
                for(col = 0 ; col <= C_filtre/2 + 1 ; col++){       // Pour chaque colonne du filtre
                    val += imageMiroir.at<unsigned char>(ligne + lig, colonne + col)*filtre.at<double>(lig, col) ;
                }
            }
            imageConv.at<unsigned char>(ligne, colonne) = val ;
        }
    }

    // Retour
    return imageConv ;
}

/*Histogramme*/
vector<int> ImageHistogramme(const Mat image){
    // Declaration des variables
    int nbIntervalle = 100 ;                    // Nombre d'intervalles
    int c, ligne, colonne ;                     // Indices
    vector<int> occurence(nbIntervalle) ;       // Vecteur des occurences

    // Initialisation
    for(c = 0 ; c < nbIntervalle ; c++){
        occurence[c] = 0 ;
    }

    // Determiner le nombre d'occurences de chaque intervalle
    for(c = 0 ; c < nbIntervalle - 1 ; c++){
        for(ligne = 0 ; ligne < image.size().height ; ligne++){
            for(colonne = 0 ; colonne < image.size().width ; colonne++){
                if((image.at<unsigned char>(ligne, colonne) >= ((float)255/nbIntervalle*c)) && (image.at<unsigned char>(ligne, colonne) < ((float)255/nbIntervalle*(c+1)))){
                    occurence[c]++ ;
                }
            }
        }
    }

    // Retour
    return occurence ;
}

/*Produit de convolution entre deux images*/
Mat ImageConvolution(const Mat image, const Mat filtre){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageConv ;                             // Image resultante
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    vector<Mat> imageConvComposante ;           // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;
    
    // Convolution sur tous les canaux de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageConvComposante.push_back(MatriceConvolution(imageComposante[c], filtre))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageConvComposante, imageConv) ;

    // Retour
    return imageConv ;
}

/*Convertir une image en niveau de gris*/
Mat ImageNiveauGris(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageGris ;                             // Image resultante
    Mat imageDouble ;                           // Image convertie en type double

    // Convertion en double
    image.convertTo(imageDouble, CV_32FC3) ;

    // Decomposition des composantes de couleur
    split(imageDouble, imageComposante) ;

    // Initialisation
    imageGris = imageComposante[0] ;

    // Calculs
    for(c = 1 ; c < nbComposante ; c++){
        imageGris += imageComposante[c] ;
    }
    imageGris = imageGris/3 ;

    // Convertion en unsigned char
    imageGris.convertTo(imageGris, CV_8U) ;

    // Retour
    return imageGris ;
}

/*Generer les filtres*/
Mat GenererFiltre(const int typeFiltre){
    // Declaration de variable
    Mat filtre ;
    Mat filtreGradient[2] ;

    switch (typeFiltre){
    // Filtre moyenneur
    case 1 :
        filtre = (Mat_<double>(3,3) << 1, 1, 1, 1, 1, 1, 1, 1, 1) ;
        filtre = filtre/9 ;
        break ;
    // Filtre laplacien
    case 2 :
        filtre = (Mat_<double>(3,3) << -1, -1, -1, -1, 8, -1, -1, -1, -1) ;
        break ;
    // Filtre gaussien
    case 3 :
        filtre = (Mat_<double>(3,3) << 1, 2, 1, 2, 4, 2, 1, 2, 1) ;
        filtre = filtre/16 ;
        break ;
    // Filtre gradient en x (Sobel)
    case 4 :
        filtre = (Mat_<double>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1) ;
        break ;
    // Filtre gradient en y (Sobel)
    case 5 :
        filtre = (Mat_<double>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1) ;
        break ;
    default:
        cout << "Type de filtre invalide." << endl ;
        break;
    }

    // Retour
    return filtre ;
}

/*Transformée de Hough*/
Mat TransformeedeHough(const Mat imgLines){
    Mat detectImgLines;
    Mat gray_image;
    //Mat  detectImgLinescp;
    imgLines.copyTo(detectImgLines); 
   /* float rho, theta;
    Point pt1, pt2;
    double a,b;
    double x0, y0;*/
    // Niveau de gris
    gray_image = ImageNiveauGris(detectImgLines);    
    //cvtColor(detectImgLines,gray_image,COLOR_RGB2GRAY);
    //Detection des contours
    Canny(gray_image,detectImgLines,200,255);

   //cvtColor(detectImgLines,detectImgLinescp,COLOR_GRAY2BGR);
    //vector <Vec2f> lines;
    
    //Hough probabilist
    vector<Vec4i> linesP;
    HoughLinesP(detectImgLines,linesP,1,CV_PI/180,50,50,10);
    //HoughLines(detectImgLines,lines,1,CV_PI/180,150);
    for(size_t i = 0; i< linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        line(detectImgLines,Point(l[0],l[1]),Point(l[2],l[3]),(0,0,255),4,LINE_AA);
      /*  rho = lines[i][0];
        theta = lines[i][1];
        a = cos(theta);
        b = sin(theta);
        x0 = a*rho;
        y0 = b*rho;

        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( detectImgLines, pt1, pt2, (0,0,255), 8, LINE_AA);*/
    }
    
    return detectImgLines;
}

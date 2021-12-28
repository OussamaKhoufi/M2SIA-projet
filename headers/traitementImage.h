#include "image.h"
using namespace cv ;
using namespace std ;
Mat ImageZero(const int nbLigne, const int nbColonne) ; 							// Generer une matrice zero
Mat ImageMiroir(const Mat image, const Mat filtre) ;								// Effet miroir
Mat MatriceConvolution(const Mat image, const Mat filtre) ; 	                    // Produit de convolution entre deux matrices
vector<int> ImageHistogramme(const Mat image) ;										// Histogramme
Mat ImageConvolution(const Mat image, const Mat filtre) ;							// Produit de convolution entre deux images
Mat ImageNiveauGris(const Mat image) ;												// Convertir une image en niveau de gris
Mat GenererFiltre(const int typeFiltre) ;											// Generer les filtres

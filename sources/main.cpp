#include "../headers/bibliotheque.h"
#include "../headers/image.h"
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
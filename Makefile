#exec_image : main.o image.o
#	g++ -o exec_image main.o image.o -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

#main.o : main.cpp 
#	g++ -c main.cpp -W -Wall -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

#image.o : image.cpp image.h
#	g++ -c image.cpp -W -Wall -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

#exec : main.o bibliotheque.o
#	g++ -o exec main.o bibliotheque.o -ljsoncpp -lstdc++fs

#main.o : main.cpp 
#	g++ -c main.cpp -W -Wall -ljsoncpp -lstdc++fs

#bibliotheque.o : bibliotheque.cpp bibliotheque.h
#	g++ -c bibliotheque.cpp -W -Wall -ljsoncpp -lstdc++fs

binaries = main.o image.o bibliotheque.o exec_main

all: clean $(binaries)

exec_main : main.o image.o bibliotheque.o
	g++ -o exec_main main.o bibliotheque.o image.o -W -Wall -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

main.o : ./sources/main.cpp 
	g++ -c ./sources/main.cpp -W -Wall -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio 

image.o : ./sources/image.cpp ./headers/image.h
	g++ -c ./sources/image.cpp -W -Wall -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio 

bibliotheque.o : ./sources/bibliotheque.cpp ./headers/bibliotheque.h
	g++ -c ./sources/bibliotheque.cpp -W -Wall -ljsoncpp -lstdc++fs

.PHONY: clean

clean:
	rm -f $(binaries) *.o
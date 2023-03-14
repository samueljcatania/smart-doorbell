CC=g++
CFLAGS = `pkg-config --cflags opencv4` `pkg-config --cflags gtkmm-3.0` -std=c++17
LIBS = `pkg-config --libs opencv4` `pkg-config --libs gtkmm-3.0`

default:
	make all

all: Main.o Doorbell.o DisplayWindow.o VideoRecorder.o Camera.o
	$(CC) $(CFLAGS) -o group17 Main.o Doorbell.o DisplayWindow.o VideoRecorder.o Camera.o $(LIBS)

DisplayWindow.o: src/DisplayWindow.cpp include/DisplayWindow.h
	$(CC) $(CFLAGS) -c src/DisplayWindow.cpp include/DisplayWindow.h $(LIBS)

VideoRecorder.o: src/VideoRecorder.cpp include/VideoRecorder.h
	$(CC) $(CFLAGS) -c src/VideoRecorder.cpp include/VideoRecorder.h $(LIBS)

Camera.o: src/Camera.cpp include/Camera.h
	$(CC) $(CFLAGS) -c src/Camera.cpp include/Camera.h $(LIBS)

Doorbell.o: src/Doorbell.cpp include/Doorbell.h
	$(CC) $(CFLAGS) -c src/Doorbell.cpp include/Doorbell.h $(LIBS)

Main.o: src/Main.cpp
	$(CC) $(CFLAGS) -c src/Main.cpp $(LIBS)

clean:
	rm -f group17 Main.o Doorbell.o include/Doorbell.h.gch DisplayWindow.o include/DisplayWindow.h.gch VideoRecorder.o include/VideoRecorder.h.gch Camera.o include/Camera.h.gch

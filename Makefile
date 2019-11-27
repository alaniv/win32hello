main: Main.cpp
	g++ Main.cpp -o Main.exe -lcomdlg32 -mwindows -g

Main.o: Main.cpp
	g++ -c Main.o
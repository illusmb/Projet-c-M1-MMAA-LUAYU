all:
	g++ -Iinclude src/main.cpp src/hough_naive.cpp -o hough

clean:
	del hough.exe

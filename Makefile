main: src/text_moss.cpp src/assembly_moss.cpp src/test.cpp
	mkdir -p bin
	g++ src/text_moss.cpp -o bin/text_moss
	g++ src/assembly_moss.cpp -o bin/assembly_moss
	g++ src/test.cpp -o codesim
clean:
	rm -rf bin
	rm -rf codesim
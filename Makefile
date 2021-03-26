all:
	cd ./src && qmake icp.pro && $(MAKE)

run: all
	./src/icp

doxygen:
	cd ./src && doxygen doxygenconfig

pack:
	zip -r xslavk02-xuher04-100-0.zip  ./src ./examples ./doc ./README.txt ./Makefile

clean:	
	rm -rf ./doc/*
	cd ./src && make clean
	rm ./src/Makefile
	rm ./src/icp


default:
	mkdir -p bin
	cd src && make
	cd tools && make
	cd res && make

pandora:
	mkdir -p bin
	cd src && make pandora
	cd tools && make
	cd res && make pandora
	mksquashfs bin/* frozenfruits.pnd
	cat res/pandora/PXML.xml >> frozenfruits.pnd
	cat res/pandora/icon.png >> frozenfruits.pnd
	rm -Rf bin/*
	mv frozenfruits.pnd bin/


clean:
	rm -Rf bin
	cd res && make clean
	cd tools && make clean

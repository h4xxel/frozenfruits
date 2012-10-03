
default:
	mkdir -p bin
	cp res/assets_pc.list res/assets.list
	cd src && make
	cd tools && make
	cd res && make

pandora:
	mkdir -p bin
	cd src && make pandora
	cd tools && make
	cp res/assets_pandora.list res/assets.list
	cd res && make
	mksquashfs bin/* frozenfruits.pnd
	cat res/pandora/PXML.xml >> frozenfruits.pnd
	cat res/pandora/icon.png >> frozenfruits.pnd
	rm -Rf bin/*
	mv frozenfruits.pnd bin/


clean:
	rm -Rf bin
	cd res && make clean
	cd tools && make clean

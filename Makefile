
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
	cp -R res/pandora/* bin/
	mksquashfs bin/* frozenfruits.pnd
	cat res/pandora/PXML.xml >> frozenfruits.pnd
	cat res/pandora/icon.png >> frozenfruits.pnd
	rm -Rf bin/*
	mv frozenfruits.pnd bin/
	
maemo:
	mkdir -p bin
	cd src && make maemo
	cd tools && make
	cp res/assets_pc.list res/assets.list
	cd res && make


install:
	mkdir -p /usr/share
	mkdir -p /usr/share/games
	mkdir -p /usr/share/games/frozenfruits
	cp -arv bin/music /usr/share/games/frozenfruits
	cp -av bin/assets.dat /usr/share/games/frozenfruits
	mkdir -p /usr/local
	mkdir -p /usr/local/bin
	cp -v bin/frozenfruits /usr/local/bin


clean:
	rm -Rf bin
	cd res && make clean
	cd tools && make clean

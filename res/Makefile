RAWTOOL = ../tools/mkrawtexture
PACKTOOL = ../tools/mksnsbbfz

default:
	make base
	$(RAWTOOL) graphics/fruitmap.png fruitmap.raw
	$(PACKTOOL) assets.list ../bin/assets.bin
	cp -a music ../bin

base:
	$(RAWTOOL) graphics/skullimage.png skullimage.raw
	$(RAWTOOL) graphics/background.png background.raw
	$(RAWTOOL) graphics/fruitmap_pandora.png fruitmap_pandora.raw
	cp icon.bmp ../bin
	cp pandora/icon.png ../bin

clean:
	rm -Rf *.raw
	

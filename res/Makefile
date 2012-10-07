RAWTOOL = ../tools/mkrawtexture
PACKTOOL = ../tools/mksnsbbfz

default:
	make base
	$(RAWTOOL) graphics/fruitmap.png fruitmap.raw
	$(PACKTOOL) assets.list ../bin/assets.bin
	cp -a music ../bin
	rm -f assets.list

base:
	$(RAWTOOL) graphics/skullimage.png skullimage.raw
	$(RAWTOOL) graphics/background.png background.raw
	$(RAWTOOL) graphics/fruitmap_pandora.png fruitmap_pandora.raw
	cp icon.bmp ../bin
	cp pandora/icon.png ../bin
	cp icon.png ../bin/icon48.png

clean:
	rm -Rf *.raw
	

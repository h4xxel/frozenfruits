RAWTOOL = ../tools/mkrawtexture
PACKTOOL = ../tools/mksnsbbfz

default:
	make base
	$(RAWTOOL) graphics/fruitmap.png fruitmap.raw
	$(PACKTOOL) assets.list ../bin/assets.bin
	cp -a music ../bin

pandora:
	make base
	$(RAWTOOL) graphics/fruitmap_pandora.png
	$(PACKTOOL) assets_pandora.list ../bin/assets.bin

base:
	$(RAWTOOL) graphics/skullimage.png skullimage.raw
	$(RAWTOOL) graphics/background.png background.raw
	cp icon.png ../bin

clean:
	rm -Rf *.raw
	

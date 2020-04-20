all: nexuiz-tiny.zip

clean:
	rm -fr nexuiz-tiny.zip data-tiny.pk3 common-spog.pk3 nexuiz-tiny/

data-tiny.pk3: 
	cd data; zip -r ../data-tiny.zip * ; cd .. ; \
    mv data-tiny.zip data-tiny.pk3

common-spog.pk3:
	cd common-spog; zip -r ../common-spog.zip * ; cd .. ; \
    mv common-spog.zip common-spog.pk3

nexuiz-tiny.zip: data-tiny.pk3 common-spog.pk3
	mkdir nexuiz-tiny ; mkdir nexuiz-tiny/data ; \
    cp data-tiny.pk3 common-spog.pk3 nexuiz-tiny/data/ ; \
    cp bin/win32/* nexuiz-tiny ; zip -r nexuiz-tiny.zip nexuiz-tiny 

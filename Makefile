all: nexuiz-tiny.zip

clean:
	rm -fr nexuiz-tiny.zip data-tiny.pk3 common-spog.pk3 \
    aerowalk-notOpenSource.pk3 GPLv3-data.pk3 \
    quintdm3-song-notOpenSource.pk3 music-BloodPrison.pk3 \
    music-Toxic.pk3 \
    nexuiz-tiny/

data-tiny.pk3: 
	cd data; zip -r ../data-tiny.zip * ; cd .. ; \
    mv data-tiny.zip data-tiny.pk3

common-spog.pk3:
	cd common-spog; zip -r ../common-spog.zip * ; cd .. ; \
    mv common-spog.zip common-spog.pk3

aerowalk-notOpenSource.pk3:
	cd non-opensource/Aerowalk/ ; zip -r ../../aerowalk.zip * ; \
    cd ../.. ; mv aerowalk.zip aerowalk-notOpenSource.pk3 

quintdm3-song-notOpenSource.pk3:
	cd non-opensource/quintdm3/ ; zip -r ../../wisdom-song.zip * ; \
    cd ../.. ; mv wisdom-song.zip quintdm3-song-notOpenSource.pk3

music-BloodPrison.pk3:
	cd music-BloodPrison/ ; zip -r ../music-BloodPrison.zip * ; \
    cd .. ; mv music-BloodPrison.zip music-BloodPrison.pk3 

music-Toxic.pk3:
	cd music-Toxic/ ; zip -r ../music-Toxic.zip * ; \
    cd .. ; mv music-Toxic.zip music-Toxic.pk3 

GPLv3-data.pk3:
	cd GPLv3-data ; zip -r ../GPLv3-data.zip * ; cd .. ; \
    mv GPLv3-data.zip GPLv3-data.pk3

nexuiz-tiny.zip: data-tiny.pk3 common-spog.pk3 aerowalk-notOpenSource.pk3 \
    GPLv3-data.pk3 quintdm3-song-notOpenSource.pk3 music-BloodPrison.pk3 \
    music-Toxic.pk3
	mkdir nexuiz-tiny ; mkdir nexuiz-tiny/data ; \
    cp *.pk3 nexuiz-tiny/data/ ; cp LICENSE.md CHANGELOG.TXT nexuiz-tiny/ ; \
    cp bin/win32/* nexuiz-tiny ; zip -r nexuiz-tiny.zip nexuiz-tiny 

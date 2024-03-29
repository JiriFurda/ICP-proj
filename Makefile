all:
	cd ./src && qmake src.pro && $(MAKE)

run: all
	./blockeditor

doxygen:
	cd ./src && doxygen

pack: clean
	zip -r xfurda00-xhavan00.zip  ./src ./examples ./doc ./README.txt ./Makefile

clean:
	rm -r -f blockeditor doc/*
	find src/. -name '*.o' -delete
	find src/. -name 'moc_*.cpp' -delete
	find src/. -name 'ui_*.h' -delete
	find src/. -name 'qrc_*.cpp' -delete
	

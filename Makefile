all:
	cd ./src && $(MAKE)

run: all
	./blockeditor

doxygen:
	cd ./src && doxygen

pack: clean
	zip xfurda00-xhavan00 ./src/ ./examples/ ./doc/ ./README.txt ./Makefile

clean:
	rm -r -f blockeditor doc/*
	find . -name 'src/*.o' -delete
	find . -name 'src/moc_*.cpp' -delete
	find . -name 'src/ui-*.h' -delete
	find . -name 'src/qrc_*.cpp' -delete
	

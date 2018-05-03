all:
	cd ./src && $(MAKE)

run: all
	./blockeditor

doxygen:

pack: clean
	zip xfurda00-xhavan00 ./src/ ./examples/ ./doc/ ./README.txt ./Makefile

clean:
	rm -f *.o blockeditor doc/*

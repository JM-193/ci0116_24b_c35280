include ../../common/Makefile

ARGS +=

.PHONY: test
test:
	make clean release
	bin/tp2 > results.txt
	make clean debug
	bin/tp2 > results2.txt

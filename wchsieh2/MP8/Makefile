ALL: prog8 testing

HEADERS = prog8.h Makefile
SOURCES = heap.o hist.o prog8.o store.o util.o
TSTSRC  = heap.o testing.o
CFLAGS = -g -Wall
LFLAGS = -lm

%.o: %.c ${HEADERS}
	gcc -c ${CFLAGS} -o $@ $<

prog8: ${SOURCES}
	gcc ${LFLAGS} -o prog8 ${SOURCES}

testing: ${TSTSRC}
	gcc ${LFLAGS} -o testing ${TSTSRC}

clean::
	rm -f *.o *~ steady.ps onequeue.ps
	rm -f ss-short ss-longer ss-steady cent-steady

clear: clean
	rm -f prog8 testing
	rm -f steady.pdf onequeue.pdf

ss-short: prog8
	@echo "Measuring short-term behavior."
	./prog8 d 8 0.9 1.0 0 100 10000 > ss-short

ss-longer: prog8
	@echo "Measuring longer-term behavior."
	./prog8 d 8 0.9 1.0 0 10000 100 > ss-longer

ss-steady: prog8
	@echo "Measuring steady-state behavior."
	./prog8 d 8 0.9 1.0 10000 20000 100 > ss-steady

cent-steady: prog8
	@echo "Measuring steady-state behavior for centralized store."
	./prog8 c 8 0.9 1.0 10000 20000 100 > cent-steady
	
steady.ps: ss-short ss-longer ss-steady steady
	gnuplot steady

steady.pdf: steady.ps
	ps2pdf steady.ps

onequeue.ps: ss-steady cent-steady onequeue
	gnuplot onequeue

onequeue.pdf: onequeue.ps
	ps2pdf onequeue.ps


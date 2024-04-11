parser: *.c
		gcc  -o parser -g expr.c interp.c main.c scan.c tree.c

parser2: *.c
		gcc  -o parser2 -g expr2.c interp.c main.c scan.c tree.c

clean:
		rm -f parser parser2 *.o

test: parser
		-(./parser ip1; \
		 ./parser ip2; \
		 ./parser ip3; \
		 ./parser ip4; \
		 ./parser ip5)

test2: parser2
		-(./parser2 ip1; \
		 ./parser2 ip2; \
		 ./parser2 ip3; \
		 ./parser2 ip4; \
		 ./parser2 ip5)

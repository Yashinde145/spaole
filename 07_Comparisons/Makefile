SRCS= cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c
SRCN= cgn.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c

comp1: $(SRCS)
	cc -o comp1 -g $(SRCS)

compn: $(SRCN)
	cc -o compn -g $(SRCN)

clean:
	rm -f comp1 compn *.o *.s out

test: comp1 ip4
	./comp1 ip4
	cc -o out out.s
	./out

testn: compn ip4
	./compn ip4
	nasm -f elf64 out.s
	cc -no-pie -o out out.o
	./out

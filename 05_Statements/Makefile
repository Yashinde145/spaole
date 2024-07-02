comp1: *.c
		gcc -o comp1 -g cg.c expr.c gen.c misc.c main.c scan.c stmt.c tree.c

compn: *.c
		gcc -o compn -g cgn.c expr.c gen.c misc.c main.c scan.c stmt.c tree.c


clean:
		rm -rf comp1 compn *.o *.s out


test: comp1 ip1
		./comp1 ip1
		gcc -o out out.s
		./out

testn: compn ip1
		./compn ip1
		nasm -f elf64 out.s
		gcc -no-pie -o out out.o
		./out
		

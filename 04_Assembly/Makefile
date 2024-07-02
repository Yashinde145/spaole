comp1: *.c
		gcc -o comp1 -g cg.c expr.c gen.c interp.c main.c scan.c tree.c

compn: *.c
		gcc -o compn -g cgn.c expr.c gen.c interp.c main.c scan.c tree.c


clean:
		rm -rf comp1 compn *.o *.s out


test: comp1
		./comp1 ip1
		gcc -o out out.s
		./out
		./comp1 ip2
		gcc -o out out.s
		./out


testn: compn
		./compn ip1
		nasm -f elf64 out.s
		gcc -no-pie -o out out.s
		./out
		./compn ip2
		nasm -f elf64 out.s
		gcc -no-pie -o out out.o
		./out
		

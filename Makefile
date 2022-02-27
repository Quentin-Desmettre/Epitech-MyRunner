##
## EPITECH PROJECT, 2021
## B-MUL-100-LIL-1-1-myrunner-quentin.desmettre
## File description:
## Makefile
##

all:
	make -s -C src/
	mv src/a.out ./my_runner

clean:
	make -s -C src/ clean

fclean:
	rm -f my_runner
	make -s -C src/ fclean

re:
	$(MAKE) fclean
	$(MAKE) all

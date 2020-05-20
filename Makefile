

xgci : xgci_connect.o main.o \
		xgci_ddl2.o xgci_dml.o xgci_dql.o
	@gcc -o $@ $^ -lxgci2

main.o : main.c
	gcc -g -c $^

xgci_connect.o : xgci_connect.c
	gcc -g -c $^

xgci_ddl2.o : xgci_ddl2.c
	gcc -g -c $^

xgci_dml.o : xgci_dml.c
	gcc -g -c $^

xgci_dql.o : xgci_dql.c
	gcc -g -c $^

.PHONY:clean

clean : 
	rm -f *.o xgci


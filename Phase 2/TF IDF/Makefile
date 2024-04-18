hello: tf_idf.o
    g++ -o tf_idf tf_idf.o

hello.o: tf_idf.c
    g++ -o tf_idf.o -c tf_idf.c -W -Wall

main.o: tf_idf.c tf_idf.h
    g++ -o tf_idf.o -c tf_idf.c -W -Wall
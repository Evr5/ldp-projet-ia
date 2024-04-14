FLAGS=-Wall -Wextra

all: tf_idf

tf_idf: tf_idf.o tf_idf.cpp
		g++ $^ -o $@

%.o: %.cpp
		g++ $(FLAGS) -c $< -o $@

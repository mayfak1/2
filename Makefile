CC=clang
SRC=main.c  dictstruct.c atomstruct.c point3d.c fiodict.c
OUT=point_3d
FLAGS=-std=c17 -g -O3
TEST_OUT=test
SRC_T= dictstruct.c atomstruct.c point3d.c fiodict.c test.c

all: $(OUT)
$(OUT): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(OUT)	

test: $(TEST_OUT)	

$(TEST_OUT): $(TEST_SRC)
	$(CC) $(CFLAGS)  $(SRC_T) -o $@ 
clean:
	rm -f $(OUT) $(TEST_OUT)
run: $(OUT)
	 ./$(OUT)

TARGET=project
C_SOURCE=main.c ./source/*.c
I_DIR=-I ./head 
CC=arm-linux-gcc
RM=rm -rf


$(TARGET):$(C_SOURCE)
	$(CC) $^ -o $@ $(I_DIR)


.PHONY:clean
clean:
	$(RM) $(TARGET)

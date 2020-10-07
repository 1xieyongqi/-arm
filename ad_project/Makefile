TARGET=project
C_SOU=./source/*.c
IDR=-I ./head
LIB=-pthread ./library/libfont.a
GCC=arm-linux-gcc
RM=rm -rf

$(TARGET):$(C_SOU)
	$(GCC) $^ -o $@ $(IDR) $(LIB)


.PHONY:clean
clear:
	$(RM) $(TARGET)

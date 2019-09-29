# 编译环境声明
CC := /usr/bin/cc
LD := /usr/bin/gcc
GDB := /usr/bin/gdb
CFLAGS := -g
LDFLAGS := -lc 

# 项目信息
EXE := nonblocking
OBJS := main.o

.PHONY: build debug clean

build: $(OBJS)
	$(LD) $(LDFLAGS) -o $(EXE) $^

debug: build
	$(GDB) $(EXE)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)


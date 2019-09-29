# 编译环境声明
CC := /usr/bin/cc
LD := /usr/bin/gcc
CFLAGS := 
LDFLAGS := -lc 

# 项目信息
EXE := pid
OBJS := main.o

.PHONY: build debug clean

build: $(OBJS)
	$(LD) $(LDFLAGS) -o $(EXE) $^

debug: build

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
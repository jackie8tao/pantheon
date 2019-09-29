# 编译环境声明
CC := /usr/bin/cc
LD := /usr/bin/gcc
GDB := /usr/bin/gdb
CFLAGS := -g
LDFLAGS := -lc 

# 项目信息
EXE := iomutex
OBJS := main.o

.PHONY: build debug clean pipe pipe_a pipe_b

build: $(OBJS)
	$(LD) $(LDFLAGS) -o $(EXE) $^

pipe: pipe_a pipe_b

pipe_a: pipe_a.o
	$(LD) $(LDFLAGS) -o pipeA $^

pipe_b: pipe_b.o
	$(LD) $(LDFLAGS) -o pipeB $^

debug: build
	$(GDB) $(EXE)

clean:
	rm -rf pipeA pipeB
	rm -rf pipe_a.o pipe_b.o
	rm -rf *.log
	rm -rf $(EXE)
	rm -rf $(OBJS)


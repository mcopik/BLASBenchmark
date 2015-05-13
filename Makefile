BLAS_LOCATION=/usr/lib/openblas-base

CXXFLAGS =-O2 -g -L $(BLAS_LOCATION)  -std=c99
CXX = gcc
SRCS = $(wildcard src/*.c)
SRCDIR = src
OBJS = $(SRCS:$(SRCDIR)/%.c=bin/%.o)
LIBS = -lblas

TARGET = bin/benchmark
$(TARGET):      $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:    $(TARGET)

$(OBJS): bin/%.o : $(SRCDIR)/%.c
	$(CXX) $(CXXFLAGS) -c $<  -o $@
.c.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(TARGET)


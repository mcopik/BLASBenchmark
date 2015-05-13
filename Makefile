BLAS_LOCATION=

CXXFLAGS =-O2 -g -I $(BLAS_LOCATION)  -std=c99
CXX = gcc
OBJS = src/main.o
LIBS = -lblas

TARGET = bin/benchmark
$(TARGET):      $(OBJS)
	$(CXX) -g -o $(TARGET) $(OBJS) $(LIBS)

all:    $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)


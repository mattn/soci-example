SRCS = \
	main.cxx

OBJS = $(subst .cc,.o,$(subst .cxx,.o,$(subst .cpp,.o,$(SRCS))))

CXXFLAGS = -std=c++20
LIBS = -lsoci_core_4_0 -lsoci_sqlite3_4_0
TARGET = soci-example
ifeq ($(OS),Windows_NT)
TARGET := $(TARGET).exe
endif

.SUFFIXES: .cpp .cc .cxx .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	g++ -o $@ $(OBJS) $(LIBS)

.cxx.o :
	g++ -c $(CXXFLAGS) -I. $< -o $@

.cpp.o :
	g++ -c $(CXXFLAGS) -I. $< -o $@

.cc.o :
	g++ -c $(CXXFLAGS) -I. $< -o $@

clean :
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

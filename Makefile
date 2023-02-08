CXX = g++
CXXFLAGS = -Wall -g -O
PROJ = hello
OBJS = main.o controller.o model.o view.o

all: $(PROJ)

$(PROJ): $(OBJS)
	$(CXX) $(OBJS) -o $(PROJ)	

clean:
	$(RM) *.o depends

-include .depends

depend:
	$(CXX) -MM $(OBJS:.o=.cc) > depends

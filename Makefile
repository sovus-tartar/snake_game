CXX = g++
CXXFLAGS = -Wall -g -O
PROJ = hello
OBJS = main.o controller.o model.o view.o


$(PROJ): $(OBJS)
	$(CXX) $(OBJS) -o $(PROJ)	

clean:
	$(RM) *.o

-include .depends

depend:
	$(CXX) -MM $(OBJS:.o=.cc) > depends

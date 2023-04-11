CXX = g++
CXXFLAGS = -Wall -g -O0 -O -std=c++11
PROJ = snake
OBJS = main.o controller.o model.o view.o text_view.o view_fabric.o graph_view.o
HEADERS_PATH = ./headers
SOURCE_PATH = ./source


all: $(PROJ) 

$(PROJ): $(OBJS)
	$(CXX) $(OBJS) -o $(PROJ)	


clean:
	$(RM) *.o depends

-include .depends

depend:
	$(CXX) -MM $(OBJS:.o=.cc) > depends

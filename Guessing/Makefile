CXX = g++.exe
CXXFLAGS = -Wall -fmessage-length=0 -fno-tree-vectorize
LIBS = 
DBGDIR = ../bin/debug
RELDIR = ../bin/release
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
NAME = guess

.PHONY: default all debug release clean

default: debug
all: debug release

debug: CXXFLAGS += -DDEBUG -g3
debug: $(DBGDIR)/
debug: $(DBGDIR)/$(NAME)

release: CXXFLAGS += -O0 -static
release: $(RELDIR)/
release: $(RELDIR)/$(NAME)

$(DBGDIR)/%.o $(RELDIR)/%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(DBGDIR)/$(NAME): $(addprefix $(DBGDIR)/, $(OBJS) )
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(RELDIR)/$(NAME): $(addprefix $(RELDIR)/, $(OBJS) )
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(DBGDIR)/ $(RELDIR)/:
	mkdir -p $@

clean:
	rm -f $(DBGDIR)/*.o *~ core
	rm -f $(RELDIR)/*.o *~ core
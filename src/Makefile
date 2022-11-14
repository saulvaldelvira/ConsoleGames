CXX = g++.exe
CXXFLAGS = -Wall -fmessage-length=0 -fno-tree-vectorize
LIBS = 
DBGDIR = ../bin/debug
RELDIR = ../bin/release

SAME_DEST_DIR = 1 #If 0 the exes go to a specific folder for each source, else they goy to the same folder

ifeq ($(SET),Snake/)
NAME = snake.exe
SRCDIR = Snake
CXXFLAGS += -DUNICODE
endif
ifeq ($(SET),Guess/)
NAME = guess.exe
SRCDIR = Guess
else 

endif

OBJS = $(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp))

.PHONY: default all debug release clean

default: debug
all: debug release

debug: CXXFLAGS += -DDEBUG -g3
debug: $(DBGDIR)/
ifeq ($(SAME_DEST_DIR),0)
debug: $(DBGDIR)/$(SRCDIR)/
debug: $(DBGDIR)/$(SRCDIR)/$(NAME)
else
debug: $(DBGDIR)/$(NAME)
endif

release: CXXFLAGS += -O0 -static
release: $(RELDIR)/
ifeq ($(SAME_DEST_DIR),0)
release: $(RELDIR)/$(SRCDIR)/
release: $(RELDIR)/$(SRCDIR)/$(NAME)
else
release: $(RELDIR)/$(NAME)
endif

#All exes go to the same folder
ifeq ($(SAME_DEST_DIR),0)
$(DBGDIR)/$(SRCDIR)/%.o $(RELDIR)/$(SRCDIR)/%.o: $(wildcard $(SRCDIR)/*.cpp)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

$(DBGDIR)/$(SRCDIR)/$(NAME): $(addprefix $(DBGDIR)/, $(OBJS) )
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(RELDIR)/$(SRCDIR)/$(NAME): $(addprefix $(RELDIR)/, $(OBJS) )
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(DBGDIR)/$(SRCDIR)/ $(RELDIR)/$(SRCDIR)/:
	mkdir -p $@

clean:
	rm -f $(DBGDIR)/$(SRCDIR)/*.o *~ core
	rm -f $(RELDIR)/$(SRCDIR)/*.o *~ core

#The exes go to a specific folder for every source folder
else
$(DBGDIR)/%.o $(RELDIR)/%.o: $(wildcard $(SRCDIR)/*.cpp)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

$(DBGDIR)/$(NAME): $(addprefix $(DBGDIR)/, $(patsubst $(SRCDIR)/%,%,$(OBJS)))
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(RELDIR)/$(NAME): $(addprefix $(RELDIR)/, $(patsubst $(SRCDIR)/%,%,$(OBJS)))
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(DBGDIR)/*.o *~ core
	rm -f $(RELDIR)/*.o *~ core
endif

$(DBGDIR)/ $(RELDIR)/:
	mkdir -p $@
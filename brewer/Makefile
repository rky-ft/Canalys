
VPATH = src hdr

SRCDIR = src
OBJDIR = obj
BINDIR = ../bin

ROOTSYS=/usr/local/Cellar/root/6.26.06_1

TARGET = $(BINDIR)/Brew

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJS0 = $(notdir $(SOURCES:.cpp=.o))

OBJS = $(addprefix $(OBJDIR)/, $(OBJS0))

ROOTCFLAGS = $(shell root-config --cflags)
#ROOTCFLAGS  = -pthread -m64 -I$(ROOTSYSFIX)/include

ROOTLIBS = $(shell root-config --glibs)
#ROOTLIBS    = -L$(ROOTSYSFIX)/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscrsipt -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic

CPPFLAGS = -Wall -O2 -march=native -Ihdr

GXX = g++

all: $(TARGET)

$(OBJDIR)/%.o: %.cpp %.hpp
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -o $@  $^ $(ROOTLIBS) $(LIBRARIES)

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o ../bin/Brew src/*~ hdr/*~

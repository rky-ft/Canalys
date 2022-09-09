
VPATH = src hdr

SRCDIR = src
OBJDIR = obj
BINDIR = ../bin

ROOTSYS=/usr/local/Cellar/root/6.26.06_1

# For the ANAROOT library
TARTSYSFIX = $(TARTSYS)

TARGET = $(BINDIR)/Grind

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJS0 = $(notdir $(SOURCES:.cpp=.o))

OBJS = $(addprefix $(OBJDIR)/, $(OBJS0))

ROOTCFLAGS = $(shell root-config --cflags)
#ROOTCFLAGS = -pthread -m64 -I$(ROOTSYSFIX)/include -std=c++11

ROOTLIBS = $(shell root-config --glibs)
#ROOTLIBS = -L$(ROOTSYSFIX)/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic #-lCint

CPPFLAGS = -Wall -O2 -march=native -Ihdr -Ianahdr/Core -Ianahdr -I$(TARTSYSFIX)/include -L$(TARTSYSFIX)/lib #-I$(ROOTSYSFIX)/include -fopenmp

LIBRARIES = -lXMLParser -lanacore -lanabrips

GXX = g++

all: $(TARGET)

$(OBJDIR)/%.o: %.cpp %.hpp
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(GXX) $(CPPFLAGS) $(ROOTCFLAGS) -o $@  $^ $(ROOTLIBS) $(LIBRARIES)

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o ../bin/Grind src/*~ hdr/*~

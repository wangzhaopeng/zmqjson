

TARGET = req

INCLUDE		+= -I./
LDFLAG		+=

all:$(TARGET)

$(TARGET):main.o
	$(LD) -o $@ $^ $(LDFLAG) 


%.o:%.cpp
	$(CXX) -o $@ $< $(CCFLAG) $(INCLUDE)
clean:
	rm *.o *~ $(TARGET)


TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	   project/include

SRCS = \
       project/src/main.cpp \
       project/src/game.cpp \
       project/src/SparseMatrix.cpp \
	   project/src/cards.cpp \
	   project/src/gui.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf $(TARGET)

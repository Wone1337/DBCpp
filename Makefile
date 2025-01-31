# ifeq ($(OS),Windows_NT)
COMPILER = g++
# else
# COMPILER = i686-w64-mingw-cpp
# endif

TARGET_NAME = *

TARGET_NAME_FOR_EXE = test


all: $(TARGET_NAME).cpp
	 $(COMPILER) -c $(TARGET_NAME).cpp
	 $(COMPILER) $(TARGET_NAME).o -o $(TARGET_NAME_FOR_EXE) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
	 ./$(TARGET_NAME_FOR_EXE)
	 
# clean:
# 	 rm -rf $(TARGET_NAME).o $(TARGET_NAME_FOR_EXE)
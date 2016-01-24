###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = 80C51
COMPILER = "SDCC for 8051"
TARGET = Release
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
CCFLAGS=-c -mmcs51 --model-small
LDFLAGS=-mmcs51 --model-small

## Processing Tools
CC=sdcc.exe
LD=sdcc.exe
#  C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/Release.hex: TOOL=LD
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/main.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/main.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/t6963c.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/t6963c.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/STDIO-~1.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/stdio-t6963c.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/test.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/test.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/buffer.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/buffer.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/snake.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/snake.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/keyboard.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/keyboard.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/fruit.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/fruit.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/bdd.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/bdd.c
#     C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/Release/GAMEBO~1.rel: TOOL=CC
#        C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51/gameboard.c

# Build tree:
all:	Release

Release:	Release.hex
	cp "Release.hex" "C:/Users/Sebastien/CloudStation/HEIG/3eme/APM/Kata-snake/PacMan/80C51.hex"

Release.hex:	main.rel t6963c.rel STDIO-~1.rel test.rel buffer.rel snake.rel keyboard.rel fruit.rel bdd.rel GAMEBO~1.rel 
	$(LD) -Wl"-u" --out-fmt-ihx $(LDFLAGS)  -o "./Release.hex" "main.rel" "t6963c.rel" "STDIO-~1.rel" "test.rel" "buffer.rel" "snake.rel" "keyboard.rel" "fruit.rel" "bdd.rel" "GAMEBO~1.rel"

main.rel:	../main.c 
	$(CC) $(CCFLAGS)  -o "main.rel" "../main.c"

t6963c.rel:	../t6963c.c 
	$(CC) $(CCFLAGS)  -o "t6963c.rel" "../t6963c.c"

STDIO-~1.rel:	../stdio-t6963c.c 
	$(CC) $(CCFLAGS)  -o "STDIO-~1.rel" "../stdio-t6963c.c"

test.rel:	../test.c 
	$(CC) $(CCFLAGS)  -o "test.rel" "../test.c"

buffer.rel:	../buffer.c 
	$(CC) $(CCFLAGS)  -o "buffer.rel" "../buffer.c"

snake.rel:	../snake.c 
	$(CC) $(CCFLAGS)  -o "snake.rel" "../snake.c"

keyboard.rel:	../keyboard.c 
	$(CC) $(CCFLAGS)  -o "keyboard.rel" "../keyboard.c"

fruit.rel:	../fruit.c 
	$(CC) $(CCFLAGS)  -o "fruit.rel" "../fruit.c"

bdd.rel:	../bdd.c 
	$(CC) $(CCFLAGS)  -o "bdd.rel" "../bdd.c"

GAMEBO~1.rel:	../gameboard.c 
	$(CC) $(CCFLAGS)  -o "GAMEBO~1.rel" "../gameboard.c"

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf ./Release.lnk
	rm -rf ./Release.map
	rm -rf ./Release.mem
	rm -rf ./main.lst
	rm -rf ./main.rst
	rm -rf ./main.sym
	rm -rf ./main.asm
	rm -rf ./main.adb
	rm -rf ./t6963c.lst
	rm -rf ./t6963c.rst
	rm -rf ./t6963c.sym
	rm -rf ./t6963c.asm
	rm -rf ./t6963c.adb
	rm -rf ./stdio-t6963c.lst
	rm -rf ./stdio-t6963c.rst
	rm -rf ./stdio-t6963c.sym
	rm -rf ./stdio-t6963c.asm
	rm -rf ./stdio-t6963c.adb
	rm -rf ./test.lst
	rm -rf ./test.rst
	rm -rf ./test.sym
	rm -rf ./test.asm
	rm -rf ./test.adb
	rm -rf ./buffer.lst
	rm -rf ./buffer.rst
	rm -rf ./buffer.sym
	rm -rf ./buffer.asm
	rm -rf ./buffer.adb
	rm -rf ./snake.lst
	rm -rf ./snake.rst
	rm -rf ./snake.sym
	rm -rf ./snake.asm
	rm -rf ./snake.adb
	rm -rf ./keyboard.lst
	rm -rf ./keyboard.rst
	rm -rf ./keyboard.sym
	rm -rf ./keyboard.asm
	rm -rf ./keyboard.adb
	rm -rf ./fruit.lst
	rm -rf ./fruit.rst
	rm -rf ./fruit.sym
	rm -rf ./fruit.asm
	rm -rf ./fruit.adb
	rm -rf ./bdd.lst
	rm -rf ./bdd.rst
	rm -rf ./bdd.sym
	rm -rf ./bdd.asm
	rm -rf ./bdd.adb
	rm -rf ./gameboard.lst
	rm -rf ./gameboard.rst
	rm -rf ./gameboard.sym
	rm -rf ./gameboard.asm
	rm -rf ./gameboard.adb

# cleanup - delete all generated files
clean:	tidy
	rm -rf Release.hex
	rm -rf main.rel
	rm -rf t6963c.rel
	rm -rf STDIO-~1.rel
	rm -rf test.rel
	rm -rf buffer.rel
	rm -rf snake.rel
	rm -rf keyboard.rel
	rm -rf fruit.rel
	rm -rf bdd.rel
	rm -rf GAMEBO~1.rel

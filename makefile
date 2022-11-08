## Para gerar executáveis para windows a partir do linux, instale o pacote "mingw-w64" (debian/arch) ou equivalente.

## Definindo variáveis específicas para cada sistema
ifdef OS # Windows
	FixPath = $(subst /,\,$1)
	RM=del /s /F /q
	ZIP=powershell Compress-Archive -DestinationPath
else
   ifeq ($(shell uname), Linux) # Linux
      FixPath = $1
      RM=rm -rf
	  ZIP=zip
   endif
endif

## Variáveis genéricas
CC=gcc
CFLAGS=-Wall -g -lm -I$(INC)
SRC=src
OBJ=obj
INC=include
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main.exe
SUBMITNAME=projeto.zip

all: $(BIN)

forWindows: CC=x86_64-w64-mingw32-gcc
forWindows: all

release: CFLAGS=-Wall -O2 -lm -DNDEBUG -I$(INC)
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

submit:
	$(RM) $(SUBMITNAME)
	$(ZIP) $(SUBMITNAME) *

run: $(BIN)
	$(call FixPath,$(BIN))

clean:
	$(RM) $(call FixPath,$(BINDIR)/*.exe $(OBJ)/*.o $(SUBMITNAME))

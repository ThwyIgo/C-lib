BINARY=bin
CODEDIRS=.
INCDIRS=./include/
OBJDIR=./objects/

CC=gcc
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD
# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g -lm $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
# regular expression replacement
OBJECTS=$(patsubst %.c,$(OBJDIR)%.o,$(CFILES))
DEPFILES=$(patsubst %.c,$(OBJDIR)%.d,$(CFILES))

all: objdir $(BINARY)

objdir:
	@mkdir -p $(OBJDIR)

$(BINARY): $(OBJECTS)
	$(CC) -lm -g -o $@ $^

# only want the .c file dependency here, thus $< instead of $^.
$(OBJDIR)%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -r $(BINARY) $(OBJDIR) #$(DEPFILES)

# @ silences the printing of the command

# include the dependencies
-include $(DEPFILES)

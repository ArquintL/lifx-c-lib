default: app


SRC = \
	app.c \
	lifx.c

INC = \
	-I./ 

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
-include $(DEP)

CFLAGS += $(INC) -std=c99 -pedantic -pedantic-errors -Werror -g -O3 \
	-Wall -Wextra

ifeq ($(findstring clang, $(shell gcc --version)), clang)
	CFLAGS +=
else
	CFLAGS += -fno-delete-null-pointer-checks
endif

CPPFLAGS += -MMD -MP

debug: CFLAGS += -DDEBUG
debug: app

app: $(OBJ)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o app
	
clean:
	rm -f app $(OBJ) $(DEP)

.PHONY: default debug clean

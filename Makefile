TARGET  := gbamenu
SRC     := menu.c

CFLAGS ?= -O2 -Wall
LDFLAGS ?=
LDLIBS := -lncurses


.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

install:
	install -D -m 0755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

clean:
	rm -f $(TARGET)
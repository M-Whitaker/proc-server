IDIR = include
CC = g++
CFLAGS = -std=c++11 -I$(IDIR)

BDIR = bin
SRCDIR = src
PROTODIR = protofiles/build

LIBS = `pkg-config --cflags --libs protobuf`

_SRC = server.cc proc.cc
SRC = $(patsubst %,$(SRCDIR)/%,$(_SRC))

_PROTO = systeminfo.pb.cc
PROTO = $(patsubst %,$(PROTODIR)/%,$(_PROTO))

BIN = $(patsubst %,$(BDIR)/%,$@)

server: protoc $(SRC) $(PROTO)
	$(CC) -o $(BIN) $(SRC) $(PROTO) $(CFLAGS) $(LIBS)

protoc:
	cd protofiles && $(MAKE)

.PHONY: clean format

clean:
	cd protofiles && $(MAKE) clean
	rm bin/*

format:
	yapf --style google --in-place -vv examples/python/client.py

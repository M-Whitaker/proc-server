IDIR = include
CFLAGS = -std=c++11 -I$(IDIR)

BDIR = bin
SRCDIR = src
TESTDIR = test
PROTODIR = protofiles/build

LIBS = `pkg-config --cflags --libs protobuf`

_SRC = server.cc proc.cc
SRC = $(patsubst %,$(SRCDIR)/%,$(_SRC))

_TST = test.cc test_procinfo.cc
TST = $(patsubst %,$(TESTDIR)/%,$(_TST))

_PROTO = systeminfo.pb.cc
PROTO = $(patsubst %,$(PROTODIR)/%,$(_PROTO))

BIN = $(patsubst %,$(BDIR)/%,$@)

server: protoc $(SRC) $(PROTO)
	$(CXX) -o $(BIN) $(SRC) $(PROTO) $(CFLAGS) $(LIBS)

test: server $(TST)
	$(CXX) -o $(BIN) $(TST) $(CFLAGS) `pkg-config --cflags --libs gtest`
	$(BIN)

protoc:
	cd protofiles && $(MAKE)

.PHONY: clean format

clean:
	-cd protofiles && $(MAKE) clean
	-rm bin/*
	-rm cpplint-junit.xml

format:
	yapf --style google --in-place -vv examples/py/client.py
	
lint:
	@printf '\n---- CPPLINT ----\n'
	cpplint --recursive */*
	@printf '\n---- PYLINT ----\n'
	pylint examples/py/client.py 

# Proc-Server

## Pre-Requirements

- **[protoc](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md)**

## How to use

```console
$ make
...
$ ./bin/server
```

## Client Examples

Examples of code for clients is provided in examples/*. There are some examples that follow the same format in different languages. Any languages that is supported by **[protobuf](https://developers.google.com/protocol-buffers/)** can be a client.

## Code Style

### C & C++

Style tries to follow **[Google's CPP Style Guide](https://google.github.io/styleguide/cppguide.html)** as closely as possible.

### Python

Style follows **[Google Python Style Guide](https://google.github.io/styleguide/pyguide.html)** using the **[yapf](https://github.com/google/yapf/)** auto-formatter.

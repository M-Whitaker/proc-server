"""
An example script to send data with Google Protobuf over sockets
using Python.
"""
import socket  # for socket
import sys  # For command line arguments
from math import ceil
import datetime

# Python interpretation of the systeminfo.proto file.
import systeminfo_pb2  # pyright: reportMissingImports=false

PORT = 9909

_USAGE = """
Syntax: client.py
        <ipaddress> [ipaddress] ...
        <string> [message] ...
        """


def usage():
    """
    Help function to print to explain the use of the script.
    """
    print(_USAGE)


def list_attributes(system_info):
    """
    Lists the avaliable attributes to stdout.
    """
    print("Uptime", datetime.timedelta(seconds=system_info.uptime))
    print("  Total RAM:", str(ceil(system_info.totalram / 1e+9)) + "GB")


def main(argc, argv):
    """
    Entry Point
    """
    if 1 < argc < 4:
        print("Connecting to socket at  %s:%d\n" % (argv[1], PORT))
    elif argc > 3:
        print("Too many arguments supplied.\n")
        usage()
        sys.exit(-1)
    else:
        print("One argument expected.\n")
        usage()
        sys.exit(-1)

    try:
        msg = argv[2]
        msg = bytes(msg, encoding="utf-8")
    except TypeError:
        msg = b"This is a message from the client!"

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket successfully created")
    except socket.error as err:
        print("socket creation failed with error %s" % err)
        sys.exit(-1)

    try:
        host_ip = socket.gethostbyname(argv[1])
    except socket.gaierror:

        # this means could not resolve the host
        print("there was an error resolving the host")
        sys.exit(-1)

    # connecting to the server
    try:
        sock.connect((host_ip, PORT))
    except ConnectionRefusedError:
        print("ERROR *** Please start a server @ %s:%d" % (argv[1], PORT))
        sys.exit(-1)

    # sending the contents of the msg variable to the server.
    sock.sendall(msg)

    # receiving up to 1024 bytes from the server.
    data = sock.recv(1024)

    print("Received: %s" % data.__repr__())

    # serialising bytes (data) into SystemInfo class
    system_info = systeminfo_pb2.SystemInfo()
    system_info.ParseFromString(data)

    # displaying the output to console.
    list_attributes(system_info)


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)

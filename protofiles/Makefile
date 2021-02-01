.PHONY: clean

protoc_middleman:
	protoc $$PROTO_PATH --cpp_out=build --python_out=../examples/py systeminfo.proto
	@touch protoc_middleman

clean:
	-rm -rf build/*.pb.*
	-rm protoc_middleman
	-rm -f ../examples/py/systeminfo_pb2.py
	-rm -rf ../examples/py/__pycache__

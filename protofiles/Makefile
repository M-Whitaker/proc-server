.PHONY: clean

protoc_middleman:
	protoc $$PROTO_PATH --cpp_out=build --python_out=../examples/python systeminfo.proto
	@touch protoc_middleman

clean:
	rm -r build/*
	rm protoc_middleman
	rm -f ../examples/python/systeminfo_pb2.py

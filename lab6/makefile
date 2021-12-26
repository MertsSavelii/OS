CC = g++


build:
	$(CC) control_node.cpp -lzmq -pthread -o control_node -w && $(CC) calculation_node.cpp -lzmq -o calculation_node -w
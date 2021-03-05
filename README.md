Compilation 

g++ -pthread -lboost_thread -lboost_chrono -lcrypto -lssl -lboost_serialization -lboost_filesystem *.cpp -o server

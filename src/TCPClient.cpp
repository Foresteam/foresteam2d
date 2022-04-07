#include "TCPClient.h"
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")
#else
#include <arpa/inet.h>
#endif

void TCPClient::Retry(bool dInitial) {
	if (_socket)
		return;
	if (debug)
		if (dInitial)
			printf("Connecting...\n");
		else
			printf("Retrying...\n");
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	inet_pton(AF_INET, _host.c_str(), &address.sin_addr);
	connect(_socket, (struct sockaddr*)&address, sizeof(address));
}
void TCPClient::LostConnection() {
	close(_socket);
	_socket = 0;
	if (debug)
		printf("Connection lost\n");
}
char* TCPClient::ReceiveRawData(size_t* sz) {
	Retry();
	size_t bufSz;
	// receive the size first
	if (recv(_socket, reinterpret_cast<char*>(&bufSz), sizeof(size_t), 0) < 0) {
		LostConnection();
		return nullptr;
	}
	char* buf = new char[bufSz + 1];
	memset(buf, 0, bufSz + 1);
	// receive data of the actual size
	if (recv(_socket, buf, bufSz, 0) < 0) {
		LostConnection();
		return nullptr;
	}
	if (sz)
		*sz = bufSz;
	return buf;
}
std::string TCPClient::ReceiveData() {
	char* buf = ReceiveRawData();
	if (!buf)
		return "";
	std::string rs = buf;
	delete[] buf;
	return rs;
}
bool TCPClient::SendData(const char* data, size_t size) {
	Retry();
	size_t offset = 0, sent;
	while (offset < size)
		if ((sent = send(_socket, data + offset, size - offset, MSG_NOSIGNAL)) == (size_t)-1) {
			LostConnection();
			return false;
		}
		else
			offset += sent;
	return true;
}
bool TCPClient::SendData(std::string data) {
	return SendData(data.c_str(), data.length());
}

TCPClient::TCPClient(const TCPClient& other) : TCPClient(other._host, other._port, other.debug) {}
TCPClient::TCPClient(std::string host, uint16_t port, bool debug) {
	this->debug = debug;
	_socket = 0;
	_host = host;
	_port = port;
	Retry(true);
}

TCPClient::~TCPClient() {
	shutdown(_socket, 0); //Обрыв соединения сокета
	close(_socket);		 //Закрытие сокета
}

std::string TCPClient::GetHost() const { return _host; }
uint16_t TCPClient::GetPort() const { return _port; }
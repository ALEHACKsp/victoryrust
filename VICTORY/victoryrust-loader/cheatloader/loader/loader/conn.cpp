#include "conn.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#define PORT 3131
#define SERVERIP "51.195.44.191"
std::string VERSION = _xor_("1");
sockaddr_in serv_addr;

#include <sstream>
#include "md5.h"
#include "aes.hpp"



#include <iostream>
#include <string>
#include <Windows.h>
#include <random>
#include <direct.h>

#include <sstream>

template< typename ... Args >
std::string mixer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

Client::Client() {
	WSADATA data; WORD ver = MAKEWORD(2, 2);
	INT WSResult = WSAStartup(ver, &data);

	if (WSResult != 0) return;

	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET) {
		WSACleanup();
		return;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, SERVERIP, &serv_addr.sin_addr);
	connected = reconnect();

	if (connected) setup = setupEncryption();
}
Client::~Client() {
	if (m_sock != INVALID_SOCKET) {
		closesocket(m_sock);
		WSACleanup();
	}
}
bool Client::reconnect() {
	if (m_sock != INVALID_SOCKET) {
		int connResult = connect(m_sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
		if (connResult == SOCKET_ERROR) {
			closesocket(m_sock);
			WSACleanup();
		}
		else return true;
	}
	return false;
}
std::string Client::sendrecieve(const std::string& text) {
	if (m_sock != INVALID_SOCKET && connected) {
		char buf[4024];
		int sendresult = send(m_sock, text.c_str(), text.size(), 0);
		if (sendresult != SOCKET_ERROR) {
			ZeroMemory(buf, 4024);
			int bytesRec = recv(m_sock, buf, 4024, 0);
			if (bytesRec > 0) return std::string(buf, 0, bytesRec);
		}
		else if (reconnect()) return sendrecieve(text);
	}
	return "";
}

int f = 0;

bool Client::setupEncryption() {
	// Server setup
	std::string successCiv = _xor_("CIV_SUCCESS_AUTHENTICATION");
	std::string civQuery = aes_enc->decrypt(cipher_key, iv_key,
		sendrecieve(aes_enc->encrypt(cipher_key, iv_key, mixer(md5(cipher_key), _xor_(";"), md5(iv_key)))
	));
	// Cipher and iv control
	if (civQuery.size() == successCiv.size()) {		
		return true;
		
	}
	else {
		return false;
	}
}

char* Client::decyptBuffer(char* buffer, int length)
{
	std::string ss(buffer, length);
	std::string decryptedString;
	ss.clear();

	char* finalBuffer = new char[decryptedString.size()];

	std::copy(decryptedString.begin(), decryptedString.end(), finalBuffer);
	std::cout << finalBuffer;

	decryptedString.clear();
	delete[] buffer;
	return finalBuffer;
}

std::unique_ptr<Client> m_Client;
#include <stdio.h>
#include <winSock2.h> 
#include <stdlib.h> 
#include <time.h> 

class TCPServer {
private:

	WSADATA wasData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	SOCKET hClientSock;
	SOCKADDR clientAddr;


	const static int BUFSIZE = 1024;
	char message[BUFSIZE] = "";


public:
	void socketInitTMP(int port);
	void makeNewSocket();
	void socketInit(int port); 
	void ecoClientMessage();
	void socketClose();
	void playMJP();

	int messageToint(char* str);
	int MJP(char* usr);
};


void TCPServer::socketInitTMP(int port) {

	// use Winsock
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// socket 생성
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	printf("*** success making socket \n"); 
	 
	// Binding For server
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	printf("*** success binding socket \n");

	// listen : 접속자 대기
	listen(hServSock, 5);
	printf("*** listening client \n");

	int clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);

	printf("*** client in \n");
}


void TCPServer::makeNewSocket() {

	// use Winsock
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// socket 생성
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	printf("*** success making socket \n");

}


void TCPServer::socketInit(int port) {

	// Binding For server
	servAddr.sin_family = AF_INET; 
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servAddr.sin_port = htons(port);

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	printf("*** success binding socket\n");

	// listen : 접속자 대기
	listen(hServSock, 5);
	printf("*** listening client.......\n");

	int clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);

	printf("*** client in \n");
}



void TCPServer::ecoClientMessage() {

	int strLen = 0;

	while ((strLen = recv(hClientSock, message, BUFSIZE, 0)) != 0) {


		send(hClientSock, message, sizeof(message), 0);

		memset(&message, 0, sizeof(message)); // message 초기화

	}
}

void TCPServer::playMJP() {

	int strLen = 0;

	while ((strLen = recv(hClientSock, message, BUFSIZE, 0)) != 0) {

		int ret = MJP(message);
		printf("%d", ret);
		char buff[BUFSIZE];            // 변환될 int형 변수를 저장할 공간 
		sprintf_s(buff, sizeof(buff), "%d", ret);


		send(hClientSock, buff, sizeof(buff), 0);
		memset(&message, 0, sizeof(message)); // message 초기화

	}
}



void TCPServer::socketClose() {
	closesocket(hClientSock);
	WSACleanup();
}
 

int TCPServer::MJP(char* usr) {

	srand(time(NULL));
	int servTurn = rand() % 3 + 1;
	
	// ret define
	// 400 : same same -> agian 
	// 405 : input error

	int usrTurn = messageToint(usr);
	if (usrTurn == -1) return 405;
		
	// same same
	if (usrTurn==servTurn) return 400;
	
	 
	switch (usrTurn) {

	case 1 :
			if (servTurn == 2) return 102;
			if (servTurn == 3) return 103;
		break;

	case 2 :
			if (servTurn == 3) return 203;
			if (servTurn == 1) return 201;
		break;

	case 3 :
			if (servTurn == 1) return 301;
			if (servTurn == 2) return 302;
		break;

	}



}


int TCPServer::messageToint(char* str) {
	if (strcmp(str, "muk") == 0) return 1;
	if (strcmp(str, "ji") == 0) return 2;
	if (strcmp(str, "pa") == 0) return 3;
	else return -1;
}




int main() {
	 
	TCPServer *TCPtestserver = new TCPServer();
	 
	//TCPtestserver->makeNewSocket();

	while (1) {
		//TCPtestserver->socketInit(5555);
		TCPtestserver->socketInitTMP(5555);
		TCPtestserver->playMJP(); printf("\n");
		TCPtestserver->socketClose();
	}

	return 0;
}
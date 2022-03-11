#include <stdio.h>
#include <winSock2.h> 
#include <stdlib.h>


int main() {

	WSADATA wasData; // Winsock 설정
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	int clientLen;
	SOCKET hClientSock;
	SOCKADDR clientAddr;

	const int BUFSIZE = 1024;

	char message[BUFSIZE] = "";



	// use Winsock
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// make socket 
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	printf("============ socket 생성 성공.\n");

	// Binding For server  
	servAddr.sin_family = AF_INET;
	// IP 설정 : INADDR_ANY 자신의 IP 주소 획득
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Port 설정
	servAddr.sin_port = htons(5555);

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	printf("============ bind 성공.\n");

	// listen : 접속자 대기
	listen(hServSock, 5);
	printf("============ 접속 대기 중...\n");

	// accept : 접속자 받기
	clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);


	printf("============ 사용자 접속 완료");

	int strLen = 0; 

	/////////// eco test
	while ((strLen = recv(hClientSock, message, BUFSIZE, 0))!=0) { 
		 
		send(hClientSock, message, sizeof(message), 0); 
		memset(&message, 0, sizeof(message)); // message 초기화

	}


	closesocket(hClientSock);
	WSACleanup();

	return 0;
}
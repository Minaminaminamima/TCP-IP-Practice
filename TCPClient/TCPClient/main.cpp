#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

 

int main() {

	// 데이터 생성
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;


	const int BUFSIZE = 102400;

	char message[BUFSIZE] = "";

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 자신의 IP
	servAddr.sin_port = htons(5555); // server 의 포트 정보 

	// 서버 접속
	connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));

	while (1) {

		fputs("전송할 메세지를 입력하세요(q to quit) : ", stdout);
		fgets(message, BUFSIZE, stdin);


		if (!strcmp(message, "q\n")) {
			break;
		}


		int strLen = send(hSocket, message, strlen(message)-1, 0);
		// 받기 
		strLen = recv(hSocket, message, BUFSIZE - 1, 0);
		message[strLen] = 0;
		printf("서버로 부터 전송된 메세지 : %s \n", message);
	}


	closesocket(hSocket);
	WSACleanup();
	
	return 0;
}
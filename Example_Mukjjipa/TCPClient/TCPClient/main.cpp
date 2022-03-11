#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h> 
 

class TCPClient {
private: 

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	static const int BUFSIZE = 102400;
	char message[BUFSIZE] = "";

public:
	void socketInit(int port); 
	void socketClose();
	void playGame(); 

	int judgeGame(int y);
	void printRetMessage(int ret);
};
 

void TCPClient::playGame() {

	int attackTurn = -1; // -1 : first stage, 0 : usr win , 1 : server win
	int flag = 1;

	while (flag) {
		memset(&message, 0, sizeof(message)); // message 초기화
		fputs("\n*** usr : (q to quit) ", stdout);
		fgets(message, BUFSIZE, stdin);

		if (!strcmp(message, "q\n")) {
			break;
		}

		int strLen = send(hSocket, message, strlen(message) - 1, 0);
		// 받기 
		strLen = recv(hSocket, message, BUFSIZE - 1, 0);
		int ret = atoi(message);

		if (ret == 405) {
			printf("===input error===\n");
			break;
		}

		if (ret == 400) {
			if (attackTurn == -1) {
				printf("tie in the first stage! throw again\n");
				continue;
			}

			if (attackTurn == 0) {
				printf("you are win!\n");
				break;
			}

			if (attackTurn == 0) {
				printf("looooooooooooooose\n");
				break;
			}

		}


		if (ret == 102 || ret == 203 || ret == 301) { // usr win
			printRetMessage(ret);
			attackTurn = 0;
			printf("usr win! attack turn is you\n"); continue;
		}
		else if (ret == 103 || ret == 201 || ret == 302) {
			printRetMessage(ret);
			attackTurn = 1;
			printf("server win! attack turn is server\n"); continue;
		}


		
		//		message[strLen] = 0;
		//		printf("서버로 부터 전송된 메세지 : %s \n", message);
	}

}



void TCPClient::printRetMessage(int ret) {
	int tmp = ret % 10;
	if (tmp == 1) printf("*** server : muk\n");
	else if (tmp == 2) printf("*** server : ji\n");
	else if (tmp == 3) printf("*** server : pa\n");

	return;
}


int TCPClient::judgeGame(int x) {

	switch (x) {

	case 400 :
		printf("play again\n");
		return 1;

	case 401 :
		printf("usr win!");
		return 0;

	case 402 :
		printf("server win!");
		return 0;

	case 405 :
		printf("input error");
		return 1;

	}

	printf("error code :: play again");
	return 1;
}


void TCPClient::socketInit(int port) {


	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 자신의 IP
	servAddr.sin_port = htons(port); // server 의 포트 정보 

	// 서버 접속
	connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));

}



void TCPClient::socketClose() {
	closesocket(hSocket);
	WSACleanup();
	printf("Session is closed.");
}


 

int main() {

	TCPClient* TCPtestclient = new TCPClient();


	printf("======= PLAY MUK JI PA =======\n");
	printf("Throw muk or ji or pa\n\n");
	char c;

	while (1) {


		TCPtestclient->socketInit(5555);
		TCPtestclient->playGame();
		TCPtestclient->socketClose();

		 
	}



	while (1);
	return 0;
}
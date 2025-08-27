#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int	main(void)
{
	int					server_fd;
	struct sockaddr_in	address;
	const int			PORT = 8080;

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

	close(server_fd);
	return (0);
}

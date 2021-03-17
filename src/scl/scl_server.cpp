#include "scl.h"

using namespace scl;




int scl::echo_server(server* serv, int client_fd, int conn_id){
	for(;;){
		char buffer[1024] = { 0 };
		int val = read(client_fd , buffer, 1024);
		if(val <= 0){
			printf("CONNECTION '%i' CLOSED\n", conn_id);
			serv->num_of_connected_clients--;
			printf("NUMBER OF REMAINING CLIENTS: '%i'\n", serv->num_of_connected_clients);
			return -1;
		}
	    printf("%s\n",buffer );
	    val = send(client_fd, buffer, 1024, 0);
		if(val <= 0){
			printf("CONNECTION '%i' CLOSED\n", conn_id);
			serv->num_of_connected_clients--;
			printf("NUMBER OF REMAINING CLIENTS: '%i'\n", serv->num_of_connected_clients);
			return -1;
		}
	}
	return -1;
}

int scl::async_listen(server* serv){
	for(;;){
		printf("Listening!\n");

		int cli_socket;
		int address_len;


		struct sockaddr address;
		cli_socket = accept(serv->socket_fd, &address, (socklen_t*)&address_len);

		if(cli_socket == -1){
			print_errno(errno);
			return err_code::SERVER_ACCEPT_FAILED;
		}


		socklen_t len = INET_ADDRSTRLEN;
		int af = AF_INET;
		if(serv->is_ipv6){
			len = INET6_ADDRSTRLEN;
			af = AF_INET6;
		}


		char *ip;
		ip = new char[len];
		if(serv->is_ipv6){
			struct sockaddr_in *cli_addr = reinterpret_cast<struct sockaddr_in*>(&address);
			inet_ntop(af, cli_addr, ip, sizeof(char) * len);
		}
		else{
			struct sockaddr_in6 *cli_addr = reinterpret_cast<struct sockaddr_in6*>(&address);
			inet_ntop(af, cli_addr, ip, sizeof(char) * len);
		}

		printf("Got connection form: '%s'\n", ip);
		serv->num_of_connected_clients++;
		serv->connections.push_back(std::async(echo_server, serv, cli_socket, serv->connections.size()));
	}

	return 0;

}


err_code scl::server_start_to_listen(server* serv){
	if(serv == nullptr)
		return err_code::SERVER_NULLPTR;

serv->listener = std::async(async_listen, serv);
	/*if(serv->is_ipv6)
		serv->listener = std::async(async_listen_ipv6, serv);
	else
		serv->listener = std::async(async_listen_ipv4, serv);*/

	return err_code::OK;
}

err_code scl::server_create(server* serv, std::string ip, int port, bool ipv6){
	if(serv == nullptr)
		return err_code::SERVER_NULLPTR;

	if(serv->is_online)
		return err_code::SERVER_ALREADY_CREATED;


	int domain = AF_INET;
	if(ipv6){
		serv->is_ipv6 = ipv6;
		domain = AF_INET6;
	}

	if((serv->socket_fd = socket(domain, SOCK_STREAM, 0)) == -1){
		print_errno(errno);
		return err_code::SOCKET_FAILED;
	}

	int opt = 1;
	if(setsockopt(serv->socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1){
		print_errno(errno);
		return err_code::SOCKET_SET_SOCKOPT_FAILED;
	}

	if(ipv6){
		struct sockaddr_in6 address;
		memset(&address, 0, sizeof(struct sockaddr_in6));

		address.sin6_family = AF_INET6;
		inet_pton(AF_INET6, ip.c_str(), &address.sin6_addr);
		address.sin6_port = htons(port);

		if(bind(serv->socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
			print_errno(errno);
			return err_code::SOCKET_BIND_FAILED;
		}
	}
	else{
		struct sockaddr_in address;
		memset(&address, 0, sizeof(struct sockaddr_in));

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(ip.c_str());
		address.sin_port = htons(port);

		if(bind(serv->socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
			print_errno(errno);
			return err_code::SOCKET_BIND_FAILED;
		}
	}


	if(listen(serv->socket_fd, BACKLOG) == -1){
		print_errno(errno);
		return err_code::SOCKET_LISTEN_FAILED;
	}

	printf("Server created at: '%s' ip and '%i' port.\n", ip.c_str(), port);

	return err_code::OK;
}

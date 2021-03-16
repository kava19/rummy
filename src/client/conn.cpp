#include "conn.h"



static int sock = 0;

void server_disconnect(){
	close(sock);
	sock = 0;
}

int connect_to_server(short port){
	if(sock != 0){
		printf("ALREADY CONNECTED TO SERVER!\n");
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		printf("CANNOT CONNECT TO SERVER!\n");
		return -1;
	}
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)<=0)  { 
        printf("CANNOT CONNECT TO SERVER, INVAILD ADDRES!\n"); 
        return -1; 
    } 	

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) { 
        printf("CANNOT CONNECT!\n"); 
        return -1; 
    } 


	return 0;
}


std::string server_get_users_connected(){	
	char buffer[256]  = { 0 };
	read(sock, buffer, 255);
	printf("MSG FORM SERVER: '%s'\n", buffer);

//	send(sock, "JA", 2, 0);
	return std::string(buffer);
}
void server_enter_room(std::string name){
	send(sock, name.c_str(), name.size(), 0);
	
}

void server_send(std::string data){
	send(sock, data.c_str(), data.size(), 0);
}

std::string server_chck(){
	send(sock, "CHCK", 4, 0);
	char buffer[256]  = { 0 };
	read(sock, buffer, 255);
	return std::string(buffer);
}











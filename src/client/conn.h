#pragma once

#include "common.h"

#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 


void server_disconnect();
int connect_to_server(short port);
std::string server_get_users_connected();
void server_enter_room(std::string name);

void server_send(std::string data);
std::string server_chck();
















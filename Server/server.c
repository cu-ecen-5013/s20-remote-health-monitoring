#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int main()
{
	char server_py[100];

	printf("***********Starting server.py*********\n");

	snprintf(server_py,sizeof(server_py),"python2.7 /bin/MQTT_Server/Server.py");

    system(server_py); 

	return 0;
}
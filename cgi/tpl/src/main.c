#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	{
		cJSON*_str=NULL;
		cJSON*json=cJSON_CreateObject();if(json==NULL)goto fail;
		_str=cJSON_CreateString("some message");if(_str==NULL)goto fail;
		cJSON_AddItemToObject(json,"msg",_str);
		goto success;
		fail:
			printf("Content-Type: test/json\n");
			printf("\n");
			printf("{\"error\":\"Failed to create json object\"}");
			goto end;
		success:
			printf("Content-Type: application/json\n");
			printf("\n");
			char *strjsonparsed=cJSON_Print(json);
			printf("%s\n",strjsonparsed);
			goto end;
		end:
			cJSON_Delete(json);

	}
	return EXIT_SUCCESS;
}

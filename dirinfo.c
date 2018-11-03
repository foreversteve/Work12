#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

void my_ls(char *dir_name){

	printf("Statistics for directory: %s \n",dir_name);

	DIR *d;
	d = opendir(dir_name);
	if (d == NULL){
		printf("%s\n",strerror(errno));
		
		return;
	}
	struct dirent *entry;
	entry = readdir(d);

	printf("%p\n",entry);
	
	struct stat fileStat;
	int s_size = 0;
	printf("\nDirectories:\n");
	while (entry != NULL){ 
		// printf("%s ",entry->d_name);
		if (entry->d_type == DT_DIR){
			printf("%s\n",entry->d_name);
			if (strcmp(entry->d_name,".") != 0){
				if (strcmp(entry->d_name,"..") != 0){
					// char s[100];
					// strcpy(s,"/");
					// strcat(s,entry->d_name);
					// my_ls(entry->d_name);
				}
			}
		}
		stat(entry->d_name,&fileStat);
		s_size += fileStat.st_size;
		entry = readdir(d);
	}
	closedir(d);
	printf("\n");

	d = opendir(dir_name);
	entry = readdir(d);
	printf("Regular Files:\n");
	while (entry != NULL){ 
		// printf("%s\n",entry->d_name);
		if (entry->d_type == DT_REG){
			printf("%s\n",entry->d_name);
		}
		entry = readdir(d);
	}
	printf("Total Diectory Size: %d bytes \n", s_size);
	printf("\n");
	closedir(d);
}

int main(int argc, char *argv[]){
	if (argc > 1){
		my_ls(argv[1]);
	}
	else{
		my_ls(".");
	}

	return 0;
}
#include "snsbbfz-helper.h"

void showVersion() {
	printf(";;; SNSBBFz packages v.0.1\n");
	printf("Copyleft Steven Arnow 2011\n\n");
}


int main(int argc, char **argv) {
	void *handle;
	FILE *list;
	char buff[1024], *temp;
	
	if (argc <3) {
		showVersion();
		fprintf(stderr, "Usage: %s <list of datafiles> <output>\n", argv[0]);
		return -1;
	}
	
	if ((handle = snsbbfzPrepareNew()) == NULL)
		return -1;
	
	if ((list = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error: Couldn't open file %s\n", argv[1]);
		return -1;
	}
	
	do {
		*buff = 0;
		fgets(buff, 1023, list);
		if (*buff == 0 && feof(list))
			break;
		
		if ((temp = strstr(buff, "\n")) != NULL)
			*temp = 0;
		
		if ((temp = strstr(buff, ";")) != NULL) {
			*temp = 0;
			temp = &temp[1];
		}
		
		printf("Info: Adding file %s, headerpadding %s\n", buff, temp);
		
		if (snsbbfzAddFile(handle, buff, temp) < 0) {
			fprintf(stderr, "Error?\n");
			return -1;
		}
	} while (!feof(list));
	
	fprintf(stderr, "Info: Now writing out to file %s\n", argv[2]);
	snsbbfzWriteOut(handle, argv[2]);
	
	return 0;
}

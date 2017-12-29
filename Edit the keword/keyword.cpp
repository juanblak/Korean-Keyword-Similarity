#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE * fp, *fp1, *out;
	int i, j;
	int num;
	int c;
	int cat_num;
	int cc;
	char str[30];
	char cat[30] = "abc";
	char **nouns;

	fopen_s(&fp, "nouns.txt", "rt");
	fopen_s(&fp1, "cat_total.txt", "rt");
	fopen_s(&out, "cat_appear.txt", "wt");

	fscanf_s(fp, "%d %d", &num, &c);

	nouns = (char**)malloc(sizeof(char*) * num);
	for (i = 0; i < num; i++)
		nouns[i] = (char*)malloc(sizeof(char) * 30);

	for (i = 0; i < user; i++) {
		cn[i] = 0;
	}

	for (i = 0; i < num; i++) {
		if (fscanf_s(fp, "%s", nouns[i], 30) == EOF)
			break;
		//fprintf(out3, "%s\n", nouns[i]);
	}

	for (i = 0; ; i++) {
		if (fscanf_s(fp1, "%d", &cat_num) == EOF)
			break;
		fscanf_s(fp1, "%s", cat, 30);
		
		//fprintf_s(out4, "%d %s\n", cat_num, cat);
		if (strlen(cat) < 3)
			continue;
		
		puts("processing..");
		for (j = 0; j<num ;j++) {
			if (strcmp(nouns[j], cat) == 0) {
				fprintf_s(out, "%d %s\n", cat_num, cat);
				
			}
		}
		
	}
	return 0;
}
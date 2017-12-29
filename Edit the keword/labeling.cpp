#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE * fp, *out;
	int i;
	char key[30];
	char cat[30];
	char c[30] = "abc";
	int num;

	fopen_s(&fp, "label.txt", "rt");
	fopen_s(&out, "label1.txt", "wt");


	for (i = 0;; i++) {
		if (fscanf_s(fp, "%s %s", cat, 30, key, 30) == EOF)
			break;
		fprintf_s(out, "%s\n%s\n", cat, key);

	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE * fp1, *fp2, *fp3, *out1, *out2, *out3, *out4;
	int i, j;
	int vocab_size, dimension;
	int noun_num, c;
	char **str;
	double **arr;
	char nouns[30];
	int cat_num;
	char cat[30];
	int cnt=0;
	int *count;
	int user;
	
	
	fopen_s(&fp1, "nouns_3000.txt", "rt");
	fopen_s(&fp2, "cat_appear_red.txt", "rt");
	fopen_s(&fp3, "LimaFull_w2v_3000.txt", "rt");
	fopen_s(&out1, "noun_numbering.txt", "wt");
	fopen_s(&out2, "cat_appear(numbering).txt", "wt");
	fopen_s(&out3, "num_of_nouns.txt", "wt");
	fopen_s(&out4, "cat_appear_num.txt", "wt");
	
	printf("카테고리 개수 입력 : ");
	scanf("%d", &user);
	fscanf_s(fp3, "%d %d", &vocab_size, &dimension);
	fscanf_s(fp1, "%d %d", &noun_num, &c);
	
	printf("%d %d\n", vocab_size, dimension);

	count = (int*)malloc(sizeof(int)*user);
	for(i=0; i<user; i++){
		count[i] = 0;
	}
	str = (char**)malloc(sizeof(char*)*vocab_size);
	for (i = 0; i < vocab_size; i++)
		str[i] = (char*)malloc(sizeof(char) * 30);

	arr = (double**)malloc(sizeof(double*)*vocab_size);
	for (i = 0; i < vocab_size; i++)
		arr[i] = (double*)malloc(sizeof(double) * dimension);

	puts("Matrix Genarating...");
	for (i = 0; i<vocab_size; i++) {
		if (fscanf_s(fp3, "%s ", str[i], 30) == EOF)
			break;
		for (j = 0; j < dimension; j++) {
			c = fgetc(fp3);
			fscanf_s(fp3, "%lf", &arr[i][j]);
		}
	}
	
	puts("noun numbering..");
	for (i = 0; i < noun_num; i++) {
		fscanf_s(fp1, "%s", nouns, 30);

		printf("noun numbering(%d/%d)\n", i, noun_num);
		if(strlen(nouns) < 3)
			continue;
		for (j = 0; j < vocab_size; j++) {
			if (strcmp(nouns, str[j]) == 0) {
				cnt++;
				fprintf(out1, "%d\n", j);
				break;
			}
		}
	}
	fprintf(out3, "%d", cnt);
	
	puts("cat numbering..");
	for (i = 0; ; i++) {
		if (fscanf_s(fp2, "%d", &cat_num) == EOF)
			break;
		fscanf_s(fp2, "%s", cat, 30);

		//fprintf(test, "%d %s\n", cat_num, cat);

		for (j = 0; j < vocab_size; j++) {
			if (strcmp(cat, str[j]) == 0) {
				count[cat_num-1]++;
				//puts("!!");
				fprintf(out2, "%d %d\n",cat_num, j);
				break;
			}
		}
	}
	for(i=0; i<user; i++){
		fprintf(out4, "%d\n", count[i]);
	}
	return 0;
}
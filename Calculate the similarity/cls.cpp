#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	FILE * fp, *out, *out2, *cat, *catn, *n_numbering, *category, *noun, *num_of_nouns, *test;
	int vocab_size, dimension;
	char ** str;
	double ** arr;
	double distance[100];
	int *numbering;
	int i, j, k, l;
	char c, d;
	
	double tmp;
	int temp;
	int cat_num;
	int **catg;   //카테고리 단어 행렬
	int *catg_num; // 카테고리에 단어 몇개있나

	char * target = "침대"; // target!
	int nn;
	int key;
	double *dis;
	char **catg_name;
	int p;

	int cnt=0;
	int *nouns;

	int numofnouns;
	int user;
	int tnum;
	double *dd;
	int *nnn;
	
	printf("카테고리 갯수 입력 : ");
	scanf_s("%d", &user);

	//fopen_s(&test, "test.txt", "wt");
	fopen_s(&fp, "LimaFull_w2v.txt", "rt");
	fopen_s(&out, "distance(th=13).txt", "wt");
	fopen_s(&out2, "distance(no th).txt", "wt");

	//fopen_s(&noun, "nouns.txt", "rt");
	fopen_s(&n_numbering, "noun_numbering.txt", "rt");
	fopen_s(&num_of_nouns, "num_of_nouns.txt", "rt");

	fopen_s(&category, "category_small_red.txt", "rt");

	fopen_s(&cat, "cat_appear(numbering).txt", "rt"); // 카테고리 파일 오픈!
	fopen_s(&catn, "cat_appear_num.txt", "rt");

	fscanf_s(fp, "%d %d", &vocab_size, &dimension);
	
	fscanf_s(num_of_nouns, "%d", &numofnouns);
	dd = (double*)malloc(sizeof(double)*vocab_size);
	nnn = (int*)malloc(sizeof(int)*vocab_size);

	printf("%d %d\n", vocab_size, dimension);
	str = (char**)malloc(sizeof(char*)*vocab_size);
	for (i = 0; i < vocab_size; i++)
		str[i] = (char*)malloc(sizeof(char) * 30);

	arr = (double**)malloc(sizeof(double*)*vocab_size);
	for (i = 0; i < vocab_size; i++)
		arr[i] = (double*)malloc(sizeof(double) * dimension);

	nouns = (int*)malloc(sizeof(int) * numofnouns);

	catg_name = (char**)malloc(sizeof(char*) * user);
	for (i = 0; i < user; i++) {
		catg_name[i] = (char*)malloc(sizeof(char) * 100);
	}
	catg_num = (int*)malloc(sizeof(int) * user);
	numbering = (int*)malloc(sizeof(int) * user);
	dis = (double*)malloc(sizeof(double) * user);
	catg = (int**)malloc(sizeof(int*) * user);
	

	puts("Matrix Genarating...");
	for (i = 0; i<vocab_size; i++) {
		if (fscanf_s(fp, "%s ", str[i], 30) == EOF)
			break;
		for (j = 0; j < dimension; j++) {
			c = fgetc(fp);
			fscanf_s(fp, "%lf", &arr[i][j]);
			
		}
	}
	puts("Matrix Genarating Complete!");

	
	puts("category matrix generating!");
	for (i = 0; i < user; i++) { // 카테고리 행렬 만들기!
		fscanf_s(catn, "%d", &cat_num);
		catg_num[i] = cat_num;
		catg[i] = (int*)malloc(sizeof(int)*(cat_num));
	}

	for (i = 0; i < user; i++) {                //cat_appear(numbering) 행렬
		for (j = 0; j < catg_num[i]; j++) {
			fscanf_s(cat, "%d %d", &nn, &key);
			catg[i][j] = key;
		}
	}
	puts("category matrix complete!");
	puts("noun list generating!");
	for (i = 0; i < numofnouns; i++) {
		fscanf_s(n_numbering, "%d", &nouns[i]);
	}
	puts("noun list complete!");



	puts("catg naming!");
	for (i = 0; i < user; i++) {
		fscanf_s(category, "%d", &p);
		//fscanf_s(category, "%s", catg_name[i], 100);
		d = fgetc(category);
		fgets(catg_name[i], 100, category);
		catg_name[i][strlen(catg_name[i]) - 1] = '\0';
	}

	///////////////////////////////////////////////////////////////////
	/*
	for (i = 0; i < 81114; i++) {
		fscanf_s(noun, "%s", nouns, 30);

		for (j = 0; j < vocab_size; j++) {
			if (strcmp(nouns, str[j]) == 0) {
				cnt++;
				fprintf(n_numbering, "%d\n", j);
				printf("%d\n", cnt);
				break;
			}
		}
	}
	*/
	
	
	for (i = 0; i < numofnouns; i++) {
		printf("processing (%d / %d)\n", i + 1, numofnouns);

		if (strlen(str[nouns[i]]) < 2)  // 한글자보다 작은것.. 제거..
			continue;

		for (j = 0; j < user; j++) {  // 번호 매기기 !!
			numbering[j] = j;
		}

		for (j = 0; j < user; j++)  // 거리 초기화!
			dis[j] = 0;

		for (j = 0; j < user; j++) {
			if (catg_num[j] <4) {// 카테고리내 등장 단어 4보다 작은경우 패스!
				dis[j] = 100;
				continue;
			}
			for (k = 0; k < 100; k++)
				distance[k] = 100;
			for (k = 0; k < catg_num[j]; k++) {
				distance[k] = 0;
				for (l = 0; l < dimension; l++) {
					distance[k] += (arr[catg[j][k]][l] - arr[nouns[i]][l])*(arr[catg[j][k]][l] - arr[nouns[i]][l]); // 거리 계산!/
					
				}
			}
			if (catg_num[j] <= 5) {         // 5개 이하인 경우 그냥 평균 내자!
				for (k = 0; k < catg_num[j]; k++)
					dis[j] += distance[k];

				dis[j] = dis[j] / catg_num[j];
			}
			else                          //5개 초과인 경우!
			{
				for (k = 0; k < catg_num[j]-1; k++) {
					for (l = 0; l < catg_num[j] - 1 - k; l++) {
						if (distance[l] > distance[l + 1]) {
							tmp = distance[l];
							distance[l] = distance[l + 1];
							distance[l + 1] = tmp;
						}
					}
				}

				for (k = 0; k < 5; k++)
					dis[j] += distance[k];
				dis[j] = dis[j] / 5;
			}
		}
		
		
		for (j = 0; j < user-1; j++) {
			for (k = 0; k < user-1 - j; k++) {
				if (dis[k] > dis[k + 1]) {
					tmp = dis[k];
					dis[k] = dis[k + 1];
					dis[k + 1] = tmp;

					temp = numbering[k];
					numbering[k] = numbering[k + 1];
					numbering[k + 1] = temp;
				}
			}
		}
		
		if (dis[0] < 13) {  // threshold = 13
			fprintf(out, "word: %s category: ", str[nouns[i]]);
			for (j = 0; j < 5; j++) {
				fprintf_s(out, " %s %lf ", catg_name[numbering[j]], dis[j]);
			}
			fprintf(out, "\n");
		}

		/////////////no threshold///////////
		fprintf(out2, "word: %s category: ", str[nouns[i]]);
		for (j = 0; j < 5; j++) {
			fprintf_s(out2, " %s %lf ", catg_name[numbering[j]], dis[j]);
		}
		fprintf(out2, "\n");
	}
	
	return 0;
}
/*
for (i = 0; i < vocab_size; i++) {
	if (strcmp(str[i], target) == 0) {
		tnum = i;
		break;
	}
}
for (i = 0; i < vocab_size; i++) {
	dd[i] = 0;
	for (j = 0; j < dimension; j++) {
		dd[i] += ((arr[i][j] - arr[tnum][j])*(arr[i][j] - arr[tnum][j])); // 거리 계산!/
																		  //fprintf(test, "%lf ", arr[i][j]);
	}

}
for (i = 0; i < vocab_size; i++) {
	nnn[i] = i;
}
for (i = 0; i < vocab_size - 1; i++) {
	for (j = 0; j < vocab_size - 1 - i; j++) {
		if (dd[j] > dd[j + 1]) {
			temp = nnn[j];
			nnn[j] = nnn[j + 1];
			nnn[j + 1] = temp;

			tmp = dd[j];
			dd[j] = dd[j + 1];
			dd[j + 1] = tmp;
		}
	}
}
for (i = 0; i < vocab_size; i++) {
	fprintf(test, "%s : %lf\n", str[i], dd[i]);
}
printf("target = %s(%d)\n", target, tnum);
for (i = 0; i < 10; i++) {
	printf("%d\n", nnn[i]);
	printf("%s  %lf\n", str[nnn[i]], dd[i]);
}
*/

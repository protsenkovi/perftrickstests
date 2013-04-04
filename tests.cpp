#include "stdafx.h"
#include "docpu\include\DoCPUCut.h"

void dynamicArrayBoundsTest() {
	int m = 500;
	int n = 500;
	int p = 500;
	float s = 1.2; 
	float *vec = (float*)malloc(m*n*p*sizeof(float));

	srand(231);
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();
	
	A_BEGIN(0)
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			for(int k = 1; k < p; k++) {
				vec[i*n*p + j*p + k] = s*(vec[i*n*p + j*p + k] - vec[i*n*p + j*p + k - 1]);
			}
		}
	}
	A_END(0)

	//free(vec);
	int start[3], stop[3], st[3];
	start[0] = 0; stop[0] = m; st[0] = 0;
	start[1] = 0; stop[1] = n; st[1] = 0;
	start[2] = 1; stop[2] = p; st[2] = 1;

	int start_1 = start[0], start_2 = start[1], start_3 = start[2];
	int stop_1 =  stop[0],  stop_2 = stop[1],   stop_3 = stop[2];
	int st_1 =	  st[0],    st_2 = st[1],       st_3 = st[2];

	//vec = (float*)malloc(m*n*p*sizeof(float));
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(1)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++)
			for(int k = start_3; k < stop_3; k++)
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
	A_END(1)

	//free(vec);
	p = p / 4;
	m = m * 4;
	start[0] = 0; stop[0] = m; st[0] = 0;
	start[1] = 0; stop[1] = n; st[1] = 0;
	start[2] = 1; stop[2] = p; st[2] = 1;

	//vec = (float*)malloc(m*n*p*sizeof(float));
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(2)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++)
			for(int k = start_3; k < stop_3; k++)
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
	A_END(2)

	//free(vec);

	bool swaped;
	int count = 3;
	do {
		swaped = false;
		for(int i = 1; i < count; i++) {
			if (stop[i-1]>stop[i]) {
				std::swap(stop[i-1], stop[i]);
				std::swap(start[i-1], start[i]);
				std::swap(st[i-1], st[i]);
				swaped = true;
			}
		}
		count--;
	} while(swaped);

	start_1 = start[0]; start_2 = start[1]; start_3 = start[2];
	stop_1 = stop[0];	stop_2 = stop[1];	stop_3 = stop[2];
	st_1 = st[0];		st_2 = st[1];		st_3 = st[2];

	//vec = (float*)malloc(m*n*p*sizeof(float));
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(3)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++)
			for(int k = start_3; k < stop_3; k++)
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
	A_END(3)


	// with unrolling
	p = 500;
	m = 500;
	start[0] = 0; stop[0] = m; st[0] = 0;
	start[1] = 0; stop[1] = n; st[1] = 0;
	start[2] = 1; stop[2] = p; st[2] = 1;
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(4)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++) {
			for(int k = start_3; k < (stop_3 & ~7); k+=8) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+1] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+1] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+1 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+2] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+2] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+2 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+3] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+3] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+3 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+4] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+4] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+4 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+5] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+5] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+5 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+6] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+6] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+6 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+7] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+7] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+7 - st_3]);
			}
			for(int k = (stop_3 & ~7); k < stop_3; k++) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
			}
		}
	A_END(4)

	p = p / 4;
	m = m * 4;
	start[0] = 0; stop[0] = m; st[0] = 0;
	start[1] = 0; stop[1] = n; st[1] = 0;
	start[2] = 1; stop[2] = p; st[2] = 1;

	//vec = (float*)malloc(m*n*p*sizeof(float));
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(5)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++) {
			for(int k = start_3; k < (stop_3 & ~7); k+=8) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+1] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+1] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+1 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+2] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+2] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+2 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+3] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+3] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+3 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+4] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+4] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+4 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+5] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+5] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+5 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+6] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+6] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+6 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+7] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+7] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+7 - st_3]);
			}
			for(int k = (stop_3 & ~7); k < stop_3; k++) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
			}
		}
	A_END(5)

	//free(vec);
    //
	start[0] = 0; stop[0] = m; st[0] = 0;
	start[1] = 0; stop[1] = n; st[1] = 0;
	start[2] = 1; stop[2] = p; st[2] = 1;

	count = 3;
	do {
		swaped = false;
		for(int i = 1; i < count; i++) {
			if (stop[i-1]>stop[i]) {
				std::swap(stop[i-1], stop[i]);
				std::swap(start[i-1], start[i]);
				std::swap(st[i-1], st[i]);
				swaped = true;
			}
		}
		count--;
	} while(swaped);

	start_1 = start[0]; start_2 = start[1]; start_3 = start[2];
	stop_1 = stop[0];	stop_2 = stop[1];	stop_3 = stop[2];
	st_1 = st[0];		st_2 = st[1];		st_3 = st[2];


	//vec = (float*)malloc(m*n*p*sizeof(float));
	for(int i = 0; i < m*n*p; i++)
		vec[i] = rand();

	A_BEGIN(6)
	for(int i = start_1; i < stop_1; i++)
		for(int j = start_2; j < stop_2; j++) {
			for(int k = start_3; k < (stop_3 & ~7); k+=8) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+1] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+1] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+1 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+2] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+2] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+2 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+3] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+3] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+3 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+4] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+4] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+4 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+5] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+5] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+5 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+6] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+6] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+6 - st_3]);
				vec[i*stop_2*stop_3 + j*stop_3 + k+7] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k+7] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k+7 - st_3]);
			}
			for(int k = (stop_3 & ~7); k < stop_3; k++) {
				vec[i*stop_2*stop_3 + j*stop_3 + k] = s*(vec[i*stop_2*stop_3 + j*stop_3 + k] - vec[(i-st_1)*stop_2*stop_3 + (j-st_2)*stop_3 + k - st_3]);
			}
		}
	A_END(6)

	free(vec);

	FILE *file = freopen("Tests/dynamic for boundaries o2 one malloc with fill avg3.txt", "wt", stdout);
	printf("%f stencil simple\n", cpu2time(Ax_GET(0)));
	printf("%f stencil dynamic m=n=p\n", cpu2time(Ax_GET(1)));
	printf("%f stencil dynamic i > k without sort\n", cpu2time(Ax_GET(2)));
	printf("%f stencil dynamic i > k with sort\n", cpu2time(Ax_GET(3)));	
	printf("%f stencil dynamic m=n=p unroll without sort\n", cpu2time(Ax_GET(4)));
	printf("%f stencil dynamic i > k unroll without sort\n", cpu2time(Ax_GET(5)));
	printf("%f stencil dynamic i > k unroll with sort\n", cpu2time(Ax_GET(6)));
	fclose(file);
}


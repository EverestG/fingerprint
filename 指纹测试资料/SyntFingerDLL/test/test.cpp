#define _CRT_SECURE_NO_WARNINGS
#include <afx.h>
#include"afxdlgs.h"
#include <cstring> 
#include <string>
#include <vector>  
#include <io.h>   
#include<stdlib.h>
#include<Windows.h>
#include <iostream> 
using namespace std;

typedef unsigned char BYTE;
typedef _Null_terminated_ const char *LPCSTR;
#define TRUE    1

int __stdcall Add(int numa, int numb);//���Եļӷ�

int __stdcall Analyze(BYTE *lpImage, int Width, int Height, BYTE *lpFeature, int *lpSize);//��ָ��ͼ������ȡָ������

int __stdcall AnalyzeFromFile(LPCSTR lpszFileName, BYTE *lpFeature, int *lpSize);//��ָ��ͼ��BMP�ļ�����ȡָ������

int __stdcall PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore);//����ָ��������ıȶ�


int count1 = 0, Arr_score1[11476] = { 0 };

void test1(double *Arr1)//�����ϼ���
{
	char ImagePathName1[100] = "E:\\c++code\\ָ�Ʋ�������\\SyntFingerDLL\\���Է���ָ�ƿ�ͼƬ\\0.����\\1 (1).BMP";
	char ImagePathName2[100] = "E:\\c++code\\ָ�Ʋ�������\\SyntFingerDLL\\���Է���ָ�ƿ�ͼƬ\\0.����\\1 (1).BMP";

	BYTE lpFeature1[500] = { 0 };
	BYTE lpFeature2[500] = { 0 };

	int lpSize1=0, lpSize2=0, score=0;
	int iReturn = 0;

	//DWORD start_time = GetTickCount();
	for (int i = 1; i <152; i++)//ע���޸�ѭ�������ֵ
	{
		sprintf(ImagePathName1, "E:\\c++code\\ָ�Ʋ�������\\SyntFingerDLL\\���Է���ָ�ƿ�ͼƬ\\0.����\\1 (%d).BMP", i);
		for (int j = i+1; j <=152; j++)//������֤�������࣬(n-1)*n/2
		{
			sprintf(ImagePathName2, "E:\\c++code\\ָ�Ʋ�������\\SyntFingerDLL\\���Է���ָ�ƿ�ͼƬ\\0.����\\1 (%d).BMP", j);
			iReturn = AnalyzeFromFile(ImagePathName1, lpFeature1, &lpSize1);
			if (iReturn != 0)
			{
				printf("��BMP�ļ��ж�ȡͼ��%dʧ��\n", i);
				break;
			}

			iReturn = AnalyzeFromFile(ImagePathName2, lpFeature2, &lpSize2);
			if (iReturn != 0)
			{
				printf("��BMP�ļ��ж�ȡͼ��%dʧ��\n", j);
				continue;
			}

			PatternMatch(lpFeature1, lpFeature2, &score);//��ָ�ƽ��бȶ�

				Arr_score1[count1] = score;
				count1++;	
				cout << count1 <<",i=" << i << ",j=" << j << endl;
		}
		
	}
	//DWORD end_time = GetTickCount();
	
	//cout << "The run time is:" << (end_time - start_time)/23436 << "ms!" << endl;

		FILE *f; 
		f = fopen("D:\\c++code\\ָ�Ʋ�������\\�ϼ�test1\\score.txt", "w"); 
		if (f == NULL)
		{
			printf("ERROR!");
			return;
		}
		
		for (int i = 1; i <= 1000; i++)
		{
			int Y_count = 0, N_count = 0;

			for (int j = 0; j < count1; j++)
			{
				if (Arr_score1[j]>=i-1)
				{
					Y_count++;
				}
				else
				{
					N_count++;
				}
			}

			fprintf(f, "���=%d,Y_count=%d,N_count=%d,sum=%d,�ϼ���=%lf\n", i, Y_count, N_count, Y_count + N_count, Y_count*1.0 / (Y_count + N_count));
			Arr1[i - 1] = Y_count*1.0 / (Y_count + N_count);
		}

		for (int j = 0; j < count1; j++)
		{
			fprintf(f, "���=%d,score=%d\n", j + 1, Arr_score1[j]);
		}

		fclose(f);

		return ;
}


int count2 = 0;
int Arr_score2[12000] = { 0 };
void test2(double *Arr2)//���Ծ�����
{
	char ImagePathName1[100] = "D:\\c++code\\ָ�Ʋ�������\\ָ�Ʋɼ�2014.7.3-bmp\\1 (1)\\1 (1).BMP";
	char ImagePathName2[100] = "D:\\c++code\\ָ�Ʋ�������\\ָ�Ʋɼ�2014.7.3-bmp\\1 (1)\\1 (1).BMP";

	BYTE lpFeature1[500] = { 0 };
	BYTE lpFeature2[500] = { 0 };

	int lpSize1 = 0, lpSize2 = 0, score = 0;
	int iReturn = 0;
	int N=10;//�޸��ļ��з���
	
	//DWORD start_time = GetTickCount();
	for (int k =1; k <= 232; k++)
	{
		for (int i = 1; i <= N; i++)//ע���޸�ѭ�������ֵ
		{
			sprintf(ImagePathName1, "D:\\c++code\\ָ�Ʋ�������\\ָ�Ʋɼ�2014.7.3-bmp\\1 (%d)\\1 (%d).BMP", k, i);
			for (int j = i; j <= N; j++)//�����ǱȶԹ����ظ���������֤�������࣬n*(n+1)/2
			{
				//count++;
				sprintf(ImagePathName2, "D:\\c++code\\ָ�Ʋ�������\\ָ�Ʋɼ�2014.7.3-bmp\\1 (%d)\\1 (%d).BMP", k, j);
				iReturn = AnalyzeFromFile(ImagePathName1, lpFeature1, &lpSize1);
				if (iReturn != 0)
				{
					printf("��BMP�ļ��ж�ȡͼ��%dʧ��\n", i);
					break;
				}

				iReturn = AnalyzeFromFile(ImagePathName2, lpFeature2, &lpSize2);
				if (iReturn != 0)
				{
					printf("��BMP�ļ��ж�ȡͼ��%dʧ��\n", j);
					continue;
				}

				PatternMatch(lpFeature1, lpFeature2, &score);//��ָ�ƽ��бȶ�

				Arr_score2[count2] = score;
				count2++;
				cout << count2 << ",k=" << k << ",i="<<i<<",j=" << j << endl;
			}
		}
	}

	//DWORD end_time = GetTickCount();

	FILE *f; 
	f = fopen("D:\\c++code\\ָ�Ʋ�������\\����test2\\score.txt", "w"); 

	if (f == NULL) 
	{ 
		printf("ERROR!"); 
		return ; 
	} 
	
	for (int i = 1; i <= 1000; i++)
	{
		int Y_count = 0, N_count = 0;

		for (int j = 0; j < count2; j++)
		{
			if (Arr_score2[j]>=i-1)
			{
				Y_count++;
			}
			else
			{
				N_count++;
			}
		}
		fprintf(f, "score=%d,Y_count=%d,N_count=%d,sum=%d,������=%lf\n", i, Y_count, N_count, Y_count + N_count, N_count*1.0 / (Y_count + N_count));
		Arr2[i - 1] = N_count*1.0 / (Y_count + N_count);
	}

	for (int j = 0; j < count2; j++)
	{
		fprintf(f, "���=%d,score=%d\n", j + 1, Arr_score2[j]);
	}

	fclose(f);
	return ;
}


void test3()
{
	char ImagePathName1[100] = "D:\\c++code\\test\\1 (1).BMP";
	char ImagePathName2[100] = "D:\\c++code\\test\\1 (1).BMP";

	BYTE lpFeature1[500] = { 0 };
	BYTE lpFeature2[500] = { 0 };

	int lpSize1 = 0, lpSize2 = 0, score = 0;
	int iReturn = 0;
	
	sprintf(ImagePathName1, "D:\\c++code\\test\\1 (13).BMP");
	sprintf(ImagePathName2, "D:\\c++code\\test\\1 (14).BMP");
			iReturn = AnalyzeFromFile(ImagePathName1, lpFeature1, &lpSize1);
			if (iReturn != 0)
			{
				printf("��BMP�ļ��ж�ȡͼ��1ʧ��\n");
			}

			iReturn = AnalyzeFromFile(ImagePathName2, lpFeature2, &lpSize2);
	    	if (iReturn != 0)
			{
				printf("��BMP�ļ��ж�ȡͼ��2ʧ��\n");
			}

			PatternMatch(lpFeature1, lpFeature2, &score);//��ָ�ƽ��бȶ�

			if (score >35)//ԭ����60
			{
				printf("Same Fingerprint!   \n");
			}
			else
			{
				printf("Different Fingerprint!  \n");
			}
	
	return;

}

int main()
{
	double Arr1[1000] = { 0 }, Arr2[1000] = { 0 }, Arr3[1000] = { 0 };
	test2(Arr2);//���Ծ�����
	test1(Arr1);//�����ϼ���

	for (int i = 0; i < 1000; i++)
	{
		Arr3[i] = 1 - (Arr1[i] + Arr2[i]) / 2;
	}

	FILE *f;
	f = fopen("D:\\c++code\\ָ�Ʋ�������\\ʶ����1.txt", "w");
	if (f == NULL)
	{
		printf("ERROR!");
		return 0;
	}

	for (int i = 0; i <1000; i++)
	{
		fprintf(f, "score=%d,�ϼ���=%lf,������=%lf,ʶ����=%lf\n", i , Arr1[i],Arr2[i],Arr3[i]);
		printf("score=%d,�ϼ���=%lf,������=%lf,ʶ����=%lf\n", i , Arr1[i], Arr2[i], Arr3[i]);
	}
	fclose(f);

	//test3();
	system("pause");
	return 0;
}











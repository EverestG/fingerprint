#include "stdafx.h"
#include "VF_Api.h"
#include "SyntFinger.h"


int __stdcall Add(int numa, int numb)
{
	return (numa + numb);
}

// Extract: ��ָ��ͼ������ȡָ������
int __stdcall Analyze(BYTE *lpImage, int Width, int Height, BYTE *lpFeature, int *lpSize)
{
	///////////////////////////////////////////////////////////////////////
	//  Width:	[in] ָ��ͼ����
	//  Height:	[in] ָ��ͼ��߶�
	//  lpImage:    [in] ָ��ͼ������ָ��
	//  Resolution:	[in] ָ��ͼ��ֱ��ʣ�Ĭ��500
	//  lpFeature:	[out] ��ȡ��ָ����������ָ��
	//  lpSize:	[out] ָ���������ݴ�С
	///////////////////////////////////////////////////////////////////////

	// TODO: Add your implementation code here
	VF_RETURN	re;

	// ����ָ��ͼ������
	VF_ImportFinger(lpImage, Width, Height);

	// ����ָ��ͼ����ȡָ������
	re = VF_Process();
	if (re != VF_OK)
		return re;

	// ��ָ���������б���
	re = VF_FeatureEncode(&g_Feature, lpFeature, lpSize);
	if (re != VF_OK)
		return re;

	return 0;
}


// ExtractEx: ��ָ��ͼ��BMP�ļ�����ȡָ������
int __stdcall AnalyzeFromFile(LPCSTR lpszFileName, BYTE *lpFeature, int *lpSize)
{
	//  lpszFileName: [in] ָ��ͼ���ļ�·��
	//  Resolution: [in] ָ��ͼ��ֱ���
	//  lpFeature: [out] ��ȡ��ָ���������ݻ�����ָ��
	//  lpSize: [out] ��ȡ��ָ���������ݴ�С
	
	VF_RETURN	re;

	// ��ȡָ��ͼ������
	re = VF_LoadFinger(lpszFileName);
	if (re != VF_OK)
		return re;

	// ����ָ��ͼ����ȡָ������
	re = VF_Process();
	if (re != VF_OK)
		return re;

	// ��ָ���������б���
	re = VF_FeatureEncode(&g_Feature, lpFeature, lpSize);
	if (re != VF_OK)
		return re;

	return 0;
}

// VerifyMatch: ����ָ��������ıȶ�
int __stdcall PatternMatch(BYTE *lpFeature1, BYTE *lpFeature2, int *lpScore)
{
	//	lpFeature1:		[in] ��һ��ָ������
	//	lpFeature2:		[in] �ڶ���ָ������
	//	lpScore:		[out] �ȶԵ����ƶ�
	//	FastMode:		[in] �Ƿ���п���ģʽ�ȶ�
	VF_RETURN	re1,re2;
	MATCHRESULT mr;
	FEATURE		feat1, feat2;

	// ��һ��ָ�������Ľ���
	re1 = VF_FeatureDecode(lpFeature1, &feat1);
	if (re1 != VF_OK)
	{
		printf("ͼ��1����ʧ��\n");
		return 0;
		//return re1;
	}

	// �ڶ���ָ�������Ľ���
	re2 = VF_FeatureDecode(lpFeature2, &feat2);
	if (re2 != VF_OK)
	{
		printf("ͼ��2����ʧ��\n");
		return 0;
		//return re2;
	}

	*lpScore = 0;

	bool FastMode = true;

	if (FastMode)
	{
		// ����ģʽ�ıȶ�
		VF_VerifyMatch(&feat1, &feat2, &mr, VF_MATCHMODE_IDENTIFY);
	}
	else
	{
		// ��ȷģʽ�ıȶ�
		VF_VerifyMatch(&feat1, &feat2, &mr, VF_MATCHMODE_VERIFY);
	}

	// ƥ������ƶ�
	//*lpScore = mr.Similarity/10;
	*lpScore = mr.Similarity;
	/*if (mr.MMCount < 8)
	{
		*lpScore = 0;
	}
	else
	{
		*lpScore = mr.Similarity;
	}*/

	return 0;
}
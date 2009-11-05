#ifndef TANGERRDEFINE_H_
#define TANGERRDEFINE_H_



enum TTLErrState
{
	ETLErrNormal = 0,	//��ͨ
	ETLErrWarning,		//��ʾ
	ETLErrSerious ,		//�����˳�
};

enum TTLErrInfo
{
	ETLErrNone = 0,
	ETLErrLoadPicture,			//��ʼ����ȡͼƬ����.
	ETLErrLoadPicFileXml,		//��ȡͼƬ�ļ�xml����
	ETLErrLoadPicDataXml,		//��ȡͼƬ����xml����
	ETLErrLoadMenu,

	ETLWarnConfigLost,
	ETLWarnLoadPicFileNextDefault,	//��ȡͼƬ����XML�쳣,��ʼ��ȡĬ��,waring

	ETLWarnSettingInit,			//���ý����ʼ������
	ETLWarnSettingList,			//���ý����ȡ����������

	ETLWarnSaveProcess,		//������ȴ���
	ETLWarnResetProcess,	//���ý��ȴ���
	ETLWarnOpenProcess,		//�򿪽��ȴ���
	ETLWarnSaveScreen,		//��Ļ��ͼ����
};

#define LTERRFUN(a,b) STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->LTError(a,b);
#define LTERR(e,a,b) if (e!=KErrNone) STATIC_CAST(CLemonTangramAppUi*,CEikonEnv::Static()->AppUi())->LTError(a,b);
#endif /*TANGERRDEFINE_H_*/

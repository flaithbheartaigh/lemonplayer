set path="path";C:\Symbian\9.1\S60_3rd_MR\Epoc32\tools
mifconv MyTheme.mbm /hMyTheme.mbg /c12 screen_active.bmp /c12 screen_idle.bmp 
echo ����mif�ɹ�
AknSkinDescCompiler MyList.txt MyTheme
echo ����skn�ɹ�
makesis MyTheme.pkg
echo ����sis�ɹ�
signsis MyTheme.sis MyThemeSign.sis "C:\Documents and Settings\yicha\cerfile.cer" "C:\Documents and Settings\yicha\keyfile.key" janemobile.cn
echo ��������ɹ�
Pause

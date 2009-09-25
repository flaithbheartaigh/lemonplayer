set path="path";C:\Symbian\9.1\S60_3rd_MR\Epoc32\tools
mifconv MyTheme.mbm /hMyTheme.mbg /c12 screen_active.bmp /c12 screen_idle.bmp 
echo 创建mif成功
AknSkinDescCompiler MyList.txt MyTheme
echo 创建skn成功
makesis MyTheme.pkg
echo 创建sis成功
signsis MyTheme.sis MyThemeSign.sis "C:\Documents and Settings\yicha\cerfile.cer" "C:\Documents and Settings\yicha\keyfile.key" janemobile.cn
echo 创建主题成功
Pause

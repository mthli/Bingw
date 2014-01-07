#include "bingw.h"

void get_latest_image(int option)
{
	FILE *fp;
	char index[20000] = {0}, url[200] = {0};
	char command_mkdir[50] = {0}, command_wget_html[300] = {0},
		 command_wget_url[300] = {0}, command_gsettings[400] = {0},
		 command_rm[50] = {0};
	char *path, *local;
	char path_temp[50] = {0};
	char ch = '\0';
	int line = 1, i = 0;

    /*
        以下所使用的 strcat() 作用均为连接各个字符串，
        以达到形成完整路径的目的
    */
	path = getenv("HOME"); /* 调用 getenv() 获取当前用户主目录路径 */
	strcat(path, "/Bing/");
	strcat(command_mkdir, "mkdir -p "); /* 调用 mkdir -p 命令 */
	strcat(command_mkdir, path);
	system(command_mkdir);

    /* 调用 wget -O 命令抓取Bing主页 */
	strcat(command_wget_html, "wget http://cn.bing.com -O ");

	strcat(path_temp, path);
	strcat(path_temp, "index.html");
	strcat(command_wget_html, path_temp);
	system(command_wget_html);

    /* 寻找到Bing每日更新的背景图片网址，并使用 wget -O 命令抓取图片 */
	fp = fopen(path_temp, "r");
	if (fp == NULL) {
		printf("Fail to open *.html\n");
		exit(0);
	}
	while (1) {
		ch = fgetc(fp);
		if (ch == '\n'){
			line++;
			if (line == 22)
				break;
		}
	}
	fgets(index, 20000, fp);
	fclose(fp);

	strcat(command_rm, "rm ");
	strcat(command_rm, path_temp);
	system(command_rm);

	local = strstr(index, "g_img={url:");
	while (*local++ != '\'');
	while (*local != '\'') {
		url[i++] = *local;
		local++;
	}
	local = strstr(url, "/az/hprichbg/rb/");
	local += 16;
	strcat(command_wget_url, "wget ");
	strcat(command_wget_url, url);
	strcat(command_wget_url, " -O ");
	strcat(command_wget_url, path);
	strcat(command_wget_url, local);
	system(command_wget_url);
    
    /* 调用 gsettings 设置 Gnome 环境桌面壁纸 */
    if(option == 1) {
		strcat(command_gsettings, "gsettings set org.gnome.desktop.background picture-uri 'file://");
		strcat(command_gsettings, path);
		strcat(command_gsettings, local);
		strcat(command_gsettings, "\'");
		system(command_gsettings);
	}
}

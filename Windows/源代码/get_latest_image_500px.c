#include "bingw.h"

void get_latest_image_500px(Item *parents)
{
    FILE *fp = NULL;
    char original_html[20000] = {0}, image_url[200] = {0};
    char cmd_wget_image[100] = {0},
         cmd_set_image[100] = {0};
    /* 考虑是否使用这个路径 */
    char *path_html = "C:\\Bingw\\original.html",
         *path_image_jpg = "C:\\Bingw\\original.jpg",
         *path_image_bmp = "C:\\Bingw\\original.bmp",
         *find_image_url = NULL;
    char ch = 0;
    int line = 1, i = 0;
    /* 以下三个为 Windows API 所需的变量声明；
     * 考虑是否需要其他变量用来反映程序状态？*/
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    BOOL SPI_back;

    /* 获取程序路径，所有文件都放置在这个路径之下；
     * 那么安装程序之时这个文件夹路径就应该存在了。
     * 首先要移除旧文件 */
    remove(path_html);
    remove(path_image_jpg);
    remove(path_image_bmp);

    /* 抓取原始网页 */
    CreateProcess("C:\\Bingw\\wget.exe", " 500px.com -O original.html", NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);

    /* 解析原始网页 */
    if ((fp = fopen("original.html", "r")) == NULL) {
        gtk_label_set_text(GTK_LABEL((*parents).label), "404 No Found :(");
        gtk_widget_show(GTK_WIDGET((*parents).label));
    } else {
        while (1) {
            ch = fgetc(fp);
            if (ch == '\n') {
                line++;
                if (line == 43)
                break;
            }
        }
        fgets(original_html, 20000, fp);
        fclose(fp);
        find_image_url = strstr(original_html, "url(");
        while (*find_image_url++ != '\'');
        while (*find_image_url != '\'') {
            image_url[i++] = *find_image_url;
            find_image_url++;
        }

        /* 抓取原始图片 */
        strcat(cmd_wget_image, " ");
        strcat(cmd_wget_image, image_url);
        strcat(cmd_wget_image, " -O ");
        strcat(cmd_wget_image, "original.jpg");
        CreateProcess("C:\\Bingw\\wget.exe", cmd_wget_image, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);

        /* 对原始图片进行格式转换 */
        CreateProcess("C:\\Bingw\\PictureConverter.exe", " C:\\Bingw jpg bmp", NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);

        /* 开始设置背景 */
        SPI_back = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void *)path_image_bmp, 0);
        if (SPI_back == TRUE) {
            gtk_label_set_text(GTK_LABEL((*parents).label), "更换壁纸完毕 :)");
            gtk_widget_show(GTK_WIDGET((*parents).label));
        } else {
            gtk_label_set_text(GTK_LABEL((*parents).label), "更换壁纸失败 :(");
            gtk_widget_show(GTK_WIDGET((*parents).label));
        }
    }
}

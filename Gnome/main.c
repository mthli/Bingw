#include "bingw.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Wrong option! Use \"bingw -h\" to see all options.\n");
        exit(0);
    } else if (argc == 2) {
        if (strcmp(argv[1],"-c") == 0) {
            get_latest_image(1); /* change_latest_image() “获取最新Bing图片并设置为背景图片” */
        } else if (strcmp(argv[1], "-d") == 0) {
            get_latest_image(2); /* download_latest_image() “仅获取最新Bing图片” */
        } else if (strcmp(argv[1], "-h") == 0) {
            help(); /* help() “显示帮助选项” */
        } else {
            printf("Wrong option! Use \"bingw -h\" to see all options.\n");
            exit(0);
        }
    } else {
        printf("Wrong option! Use \"bingw -h\" to see all options.\n");
        exit(0);
    }
    return 0;
}

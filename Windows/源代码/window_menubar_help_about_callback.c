#include "bingw.h"

void window_menubar_help_about_callback(GtkWidget *widget, gpointer parents)
{
    GtkWidget *dialog_about;

    dialog_about = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog_about), "Bingw");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog_about), "1.0");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog_about), "遵守 GPL V3 协议");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog_about), "Bingw 是一个抓取网页图片并设置为桌面壁纸的程序");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog_about), "https://github.com/matthewlee0725/Bingw");
    gtk_dialog_run(GTK_DIALOG(dialog_about));
    gtk_widget_destroy(dialog_about);
}

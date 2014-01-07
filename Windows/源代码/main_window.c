#include "bingw.h"

void choose_latest_image(GtkWidget *widget, Item *parents);
void window_menubar_help_about_callback(GtkWidget *widget, gpointer parents);

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *window_vbox,
              *window_table;
    GtkWidget *window_menubar;
    GtkWidget *window_menu_file,
              *window_menu_help;
    GtkWidget *window_menubar_file,
              *window_menubar_file_quit;
    GtkWidget *window_menubar_help,
              *window_menubar_help_about;
    GtkWidget *window_fixed_label,
              *window_fixed_choice,
              *window_fixed_update;
    char ascii_art[10000] = {0};

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bingw");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 425, 320);
    gtk_widget_set_size_request(GTK_WIDGET(window), 425, 320);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    window_vbox = gtk_vbox_new(FALSE, 0);
    window_table = gtk_table_new(2, 2, FALSE);

    window_menubar = gtk_menu_bar_new();
    window_menu_file = gtk_menu_new();
    window_menu_help = gtk_menu_new();
    window_menubar_file = gtk_menu_item_new_with_label("文件");
    window_menubar_file_quit = gtk_menu_item_new_with_label("退出");
    window_menubar_help = gtk_menu_item_new_with_label("帮助");
    window_menubar_help_about = gtk_menu_item_new_with_label("关于");
    gtk_menu_shell_append(GTK_MENU_SHELL(window_menu_file), window_menubar_file_quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(window_menu_help), window_menubar_help_about);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(window_menubar_file), window_menu_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(window_menubar_help), window_menu_help);
    gtk_menu_shell_append(GTK_MENU_SHELL(window_menubar), window_menubar_file);
    gtk_menu_shell_append(GTK_MENU_SHELL(window_menubar), window_menubar_help);
    g_signal_connect(G_OBJECT(window_menubar_file_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window_menubar_help_about), "activate", G_CALLBACK(window_menubar_help_about_callback), window);

    window_item = (Item *)malloc(sizeof(Item));


    (*window_item).label = gtk_label_new("更换图片的时间与网络状况有关，请耐心等待 :)");
    gtk_widget_set_size_request(GTK_WIDGET((*window_item).label), 325, 100);
    (*window_item).combo_choose = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT((*window_item).combo_choose), "500px");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT((*window_item).combo_choose), "Bing");
    gtk_widget_set_size_request(GTK_WIDGET((*window_item).combo_choose), 200, 25);
    (*window_item).button_update = gtk_button_new_with_label("更新");
    gtk_widget_set_size_request(GTK_WIDGET((*window_item).button_update), 100, 25);
    window_fixed_label = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(window_fixed_label), GTK_WIDGET((*window_item).label), 50, 50);
    window_fixed_choice = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(window_fixed_choice), GTK_WIDGET((*window_item).combo_choose), 50, 50);
    window_fixed_update = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(window_fixed_update), GTK_WIDGET((*window_item).button_update), 25, 50);
    gtk_table_attach(GTK_TABLE(window_table), window_fixed_label, 0, 2, 0, 1, GTK_FILL, GTK_SHRINK, 0, 0);
    gtk_table_attach(GTK_TABLE(window_table), window_fixed_choice, 0, 1, 1, 2, GTK_FILL, GTK_SHRINK, 0, 0);
    gtk_table_attach(GTK_TABLE(window_table), window_fixed_update, 1, 2, 1, 2, GTK_FILL, GTK_SHRINK, 0, 0);

    g_signal_connect(G_OBJECT((*window_item).button_update), "clicked", G_CALLBACK(choose_latest_image), window_item);

    gtk_box_pack_start(GTK_BOX(window_vbox), GTK_WIDGET(window_menubar), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(window_vbox), GTK_WIDGET(window_table), FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), window_vbox);

    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();

    return 0;
}

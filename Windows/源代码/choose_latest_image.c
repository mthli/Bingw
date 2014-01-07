#include "bingw.h"

void get_latest_image_bing(Item *parents);
void get_latest_image_500px(Item *parents);

void choose_latest_image(GtkWidget *widget, Item *parents)
{
    gchar *get_active_text;

    get_active_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT((*parents).combo_choose));
    if (g_strcmp0(get_active_text, "Bing") == 0) {
        get_latest_image_bing(parents);
    }
    if (g_strcmp0(get_active_text, "500px") == 0) {
        get_latest_image_500px(parents);
    }
}

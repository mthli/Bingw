#ifndef __BINGW
#define __BINGW

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
    GtkWidget *label;
    GtkWidget *combo_choose;
    GtkWidget *button_update;
} Item;
Item *window_item;

#endif

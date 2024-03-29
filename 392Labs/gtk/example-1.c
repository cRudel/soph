#include <gtk/gtk.h>
#include <stdlib.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
	srand(time(NULL));
	int n = (int) random();
	if(n % 2 == 0)
		n = 0;
	else n=1;
	g_print("%i\n", n);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
	GtkWidget *window;
	GtkWidget *close;
	GtkWidget *button_box;
	GtkWidget *flip;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Coin Flip");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

	button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), button_box);

	close = gtk_button_new_with_label ("Close");
	g_signal_connect (close, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped (close, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_container_add (GTK_CONTAINER (button_box), close);

	gtk_widget_show_all (window);
}

int main (int argc,  char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}

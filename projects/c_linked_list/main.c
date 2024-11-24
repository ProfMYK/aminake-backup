#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client Client;
struct Client {
    int x, y, w, h;
    char title[256];
    int win; // Unique in all clients
    Client *next;
};

Client *new_client(int x, int y, int w, int h, char *title) {
    Client *new = malloc(sizeof(Client));
    new->x = x;
    new->y = y;
    new->w = w;
    new->h = h;
    strcpy(new->title, title); 

    return new;
}

void add_client(Client *clients, Client *new) {
    Client *c;
    for (c = clients; c->next != NULL; c = c->next);

    c->next = new;
}

void free_clients(Client *clients) {
    if(clients->next != NULL)
        free_clients(clients->next);
    free(clients);
}

void display_clients(Client *clients) {
    Client *c;
    for (c = clients; c->next != NULL; c = c->next) {
        printf("[%i,%i,%i,%i,\"%s\"] -> ", c->x, c->y, c->w, c->h, c->title);
    } printf("[%i,%i,%i,%i,\"%s\"]\n", c->x, c->y, c->w, c->h, c->title);
}

int main() {
    Client *clients = new_client(0, 0, 200, 200, "Test Title");

    Client *new_window = new_client(50, 50, 300, 250, "New Window!");
    add_client(clients, new_window);

    Client *new_window1 = new_client(20, 20, 400, 550, "Another one bites the dust!");
    add_client(clients, new_window1);

    Client *new_window2 = new_client(34, 54, 300, 450, "Oyun");
    add_client(clients, new_window2);

    display_clients(clients);

    free_clients(clients);

    return 0;
}

#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <X11/Xlib.h>

typedef struct Client Client;
typedef struct Client Monitor;
struct Client {
    char title[256];
    int x, y, w, h;
    Client *next;
    Window window;
};

Display *dpy;
Window root;

void ERROR(char *msg) {
    printf("\033[31mERROR: \033[0m%s\n", msg);
    exit(0);
};

void WARNING(char *msg) {
    printf("\033[36mWARNING: \033[0m%s\n", msg);
    exit(0);
};

void onCirculateNotify(XCirculateEvent e);
void onConfigureNotify(XConfigureEvent e);
void onCreateNotify(XCreateWindowEvent e);
void onDestroyNotify(XDestroyWindowEvent e);
void onGravityNotify(XGravityEvent e);
void onMapNotify(XMapEvent e);
void onReparentNotify(XReparentEvent e);
void onUnmapNotify(XUnmapEvent e);
void onCirculateRequest(XCirculateRequestEvent e);
void onConfigureRequest(XConfigureRequestEvent e);
void onMapRequest(XMapRequestEvent e);
void onClientMessage(XClientMessageEvent e);
void onMappingNotify(XMappingEvent e);
void onSelectionClear(XSelectionClearEvent e);
void onSelectionNotify(XSelectionEvent e);
void onSelectionRequest(XSelectionRequestEvent e);

Client *clients;
int cur;

void init() {
    cur = 0;
}

int main() {
    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        ERROR("Display could not be created.");
    }

    root = DefaultRootWindow(dpy);

    
    XSelectInput(dpy, root, SubstructureNotifyMask | SubstructureRedirectMask);
    XSync(dpy, 0);

    init();

    XEvent e;
    for(;;) {
        XNextEvent(dpy, &e);
        switch (e.type) {
            case CirculateNotify:
                onCirculateNotify(e.xcirculate);
                break;
            case ConfigureNotify:
                onConfigureNotify(e.xconfigure);
                break;
            case CreateNotify:
                onCreateNotify(e.xcreatewindow);
                break;
            case DestroyNotify:
                onDestroyNotify(e.xdestroywindow);
                break;
            case GravityNotify:
                onGravityNotify(e.xgravity);
                break;
            case MapNotify:
                onMapNotify(e.xmap);
                break;
            case ReparentNotify:
                onReparentNotify(e.xreparent);
                break;
            case UnmapNotify:
                onUnmapNotify(e.xunmap);
                break;
            case CirculateRequest:
                onCirculateRequest(e.xcirculaterequest);
                break;
            case ConfigureRequest:
                onConfigureRequest(e.xconfigurerequest);
                break;
            case MapRequest:
                onMapRequest(e.xmaprequest);
                break;
            case ClientMessage:
                onClientMessage(e.xclient);
                break;
            case MappingNotify:
                onMappingNotify(e.xmapping);
                break;
            case SelectionClear:
                onSelectionClear(e.xselectionclear);
                break;
            case SelectionNotify:
                onSelectionNotify(e.xselection);
                break;
            case SelectionRequest:
                onSelectionRequest(e.xselectionrequest);
                break;
            default:
                WARNING("Got an unexpected event type.");
                break;
        }

        XSync(dpy, 0);
    }
    

    XCloseDisplay(dpy);

    return 0;
}


void onCirculateNotify(XCirculateEvent e) {
}

void onConfigureNotify(XConfigureEvent e) {
}

void onCreateNotify(XCreateWindowEvent e) {
    WARNING("Got a craeted window ay");
}

void onDestroyNotify(XDestroyWindowEvent e) {
}

void onGravityNotify(XGravityEvent e) {
}

void onMapNotify(XMapEvent e) {
}

void onReparentNotify(XReparentEvent e) {
}

void onUnmapNotify(XUnmapEvent e) {
}

void onCirculateRequest(XCirculateRequestEvent e) {
}

void onConfigureRequest(XConfigureRequestEvent e) {
    XWindowChanges changes;
    changes.x = e.x;
    changes.y = e.y;
    changes.width = e.width;
    changes.height = e.height;
    changes.border_width = e.border_width;
    XConfigureWindow(dpy, e.window, e.value_mask, &changes);
}

void onMapRequest(XMapRequestEvent e) {
    Client *c;
    XWindowAttributes wa;
    XGetWindowAttributes(dpy, e.window, &wa);

    c->window = e.window;

    c->x = wa.x;
    c->x = wa.x;
    c->w = wa.width;
    c->h = wa.height;

    if (cur == 0) {
        clients = c;
        cur++;
    } else {
        clients->next = c;
        clients = clients->next;
        cur++;
    }
}

void onClientMessage(XClientMessageEvent e) {
}

void onMappingNotify(XMappingEvent e) {
}

void onSelectionClear(XSelectionClearEvent e) {
}

void onSelectionNotify(XSelectionEvent e) {
}

void onSelectionRequest(XSelectionRequestEvent e) {
}


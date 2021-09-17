#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glad/glad.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLFW/glfw3.h>

Window create_x11_window(Display *display, int x, int y, int width, int height);

int main(void)
{
    // connect to the X server
    Display *display = XOpenDisplay(NULL);
    if(display == NULL)
    {
        fprintf(stderr, "Could not connect to the X server\n");
        exit(EXIT_FAILURE);
    }
    // obtain information about the display
    int screen = DefaultScreen(display);
    printf("screen: %d\n", screen);

    int depth = 32;
    XVisualInfo visual_info;
    if(XMatchVisualInfo(display, screen, depth, TrueColor, &visual_info) == 0)
    {
        fprintf(stderr, "Could not find visual\n");
        exit(EXIT_FAILURE);
    }

    Window parent_window = DefaultRootWindow(display);
    XSetWindowAttributes attrs;

    unsigned long valuemask = CWBackPixel | CWColormap | CWBorderPixel |
                              CWEventMask;
    attrs.colormap = XCreateColormap(display, parent_window, visual_info.visual,
                                     AllocNone);
    attrs.background_pixel = 0x00000000;
    attrs.border_pixel = BlackPixel(display, screen);
    attrs.event_mask = ButtonPressMask;

    int x = 0, y = 0;
    int width = 780, height = 780;
    int border_width = 0;
    Window window = XCreateWindow(display, parent_window, x, y,
                                  width, height, border_width,
                                  visual_info.depth, InputOutput,
                                  visual_info.visual, valuemask, &attrs);

    XMapWindow(display, window);
    printf("mapped window\n");

    // event loop
    XEvent event;
    int quit = 0;
    while(!quit)
    {
        XNextEvent(display, &event);
        switch(event.type)
        {
            case ButtonPress:
                quit = 1;
                break;
        }
    }

    // clean up and disconnect from the X server
    XUnmapWindow(display, window);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}

/* Window create_x11_window(Display *display, int x, int y, int width, int height) */
/* { */
/* } */

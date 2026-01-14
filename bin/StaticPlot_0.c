#include <signal.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <panels.h>

#include "../lib/debug.h"


static
void catcher(int sig) {

    ASSERT(0, "caught signal number %d", sig);
}

static const double tMax = 20 * M_PI;

static double a;

static double x(double t) {

    return a * cos(t);
}

static double y(double t) {

    return a * sin(t);
}


bool Plotter(struct PnWidget *g, struct PnPlot *p, void *userData,
        double xMin, double xMax, double yMin, double yMax) {

    for(double t = 0.0; t <= 2*tMax + 10; t += 0.1) {
        a = 1.0 - t/tMax;
        pnPlot_drawPoint(p, x(t), y(t));
    }
    return false;
}

static void StaticPlot(struct PnWidget *g) {

    struct PnPlot *p = pnStaticPlot_create(g, Plotter, catcher);
    ASSERT(p);
    // This plot, p, is owned by the graph, w.
    pnPlot_setLineColor(p, 0xFFFF0000);
    pnPlot_setPointColor(p, 0xFF00FFFF);
    pnPlot_setLineWidth(p, 3.2);
    pnPlot_setPointSize(p, 4.5);
}

static void Graph(struct PnWidget *parent) {

    struct PnWidget *g = pnGraph_create(
            parent,
            90/*width*/, 70/*height*/, 0/*align*/,
            PnExpand_HV/*expand*/);
    ASSERT(g);
    //                  Color Bytes:  A R G B
    pnWidget_setBackgroundColor(g, 0xA0101010, 0);
    pnGraph_setView(g, -1.05, 1.05, -1.05, 1.05);

    StaticPlot(g);
}

static void GraphHContainer(struct PnWidget *parent) {

    Graph(parent);
    Graph(parent);
}

static void WindowVContainer(struct PnWidget *win) {

    // TODO: Add other widgets like menus, button bar, graph tabs, and
    // status bar.

    GraphHContainer(win);
}

static struct PnWidget *Window(void) {

    struct PnWidget *win = pnWindow_create(0, 8, 8,
            0/*x*/, 0/*y*/, PnLayout_TB/*layout*/, 0,
            PnExpand_HV);
    ASSERT(win);
    pnWindow_setPreferredSize(win, 1100, 900);

    WindowVContainer(win);

    return win;
}


int main(void) {

    ASSERT(SIG_ERR != signal(SIGSEGV, catcher));

    struct PnWidget *win = Window();

    pnWindow_show(win);

    pnDisplay_run();

    return 0;
}

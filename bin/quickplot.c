#include <signal.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <panels.h>

#include "../include/quickplot.h"

#include "../lib/debug.h"

#include "findGrapher.h"


static
void catcher(int sig) {

    ASSERT(0, "caught signal number %d", sig);
}

struct Quickplot_Preferences {

    struct PnWidget (*Window)(void);

};


static double t1 = 0.0;
static double t2 = 0.0;

static
bool ScopePlotter1(struct PnWidget *g, struct PnPlot *p, void *userData,
double xMin, double xMax, double yMin, double yMax) {

    for(uint32_t n = 100; n; t1 += 0.06, n--) {
        double a = cos(0.34 + t1/(1540.2 * M_PI));
        pnPlot_drawPoint(p, a * cos(t1), a * sin(2.01*t1));
    }
    pnWidget_queueDraw(g, 0);
    return false;
}

static
bool ScopePlotter2(struct PnWidget *g, struct PnPlot *p, void *userData,
double xMin, double xMax, double yMin, double yMax) {

    for(uint32_t n = 100; n; t2 += 0.06, n--) {
        double a = cos(0.34 + t2/(1540.2 * M_PI));
        pnPlot_drawPoint(p, a * cos(t2), a * sin(2.01*t2));
    }
    pnWidget_queueDraw(g, 0);
    return false;
}

static int count = 0;

static void ScopePlot(struct PnWidget *g) {

    struct PnPlot *p;
if(!(count++)) {
    p = pnScopePlot_create(g, ScopePlotter1, catcher);
    ASSERT(p);
    pnPlot_setLineColor(p, 0xFF0000FF);
    pnPlot_setPointColor(p, 0xFFFF00FF);
    pnPlot_setLineWidth(p, 4.2);
    pnPlot_setPointSize(p, 4.5);

} else {
    p = pnScopePlot_create(g, ScopePlotter2, catcher);
    ASSERT(p);
    pnPlot_setLineColor(p, 0xFF00FFFF);
    pnPlot_setPointColor(p, 0xFFF0F0F0);
    pnPlot_setLineWidth(p, 4.2);
    pnPlot_setPointSize(p, 4.5);
}
}


static const double tMax = 20 * M_PI;

static double a;

static double x(double t) {

    return a * cos(t);
}

static double y(double t) {

    return a * sin(t);
}

static
bool StaticPlotter(struct PnWidget *g, struct PnPlot *p, void *userData,
        double xMin, double xMax, double yMin, double yMax) {

    for(double t = 0.0; t <= 2*tMax + 10; t += 0.1) {
        a = 1.0 - t/tMax;
        pnPlot_drawPoint(p, x(t), y(t));
    }
    return false;
}

static void StaticPlot(struct PnWidget *g) {

    struct PnPlot *p = pnStaticPlot_create(g, StaticPlotter, catcher);
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
    //fprintf(stderr, "StaticPlot=%p\n", StaticPlot);
    ScopePlot(g);
}

// Return true on error.
static bool GraphHContainer(struct PnWidget *parent) {

    struct PnWidget *w = pnWidget_create(parent, 6, 6,
            PnLayout_LR/*layout*/, 0/*align*/,
            PnExpand_HV, 0/*size*/);
    ASSERT(w);
    //                  Color Bytes:  A R G B
    pnWidget_setBackgroundColor(w, 0xFFE060F0, 0);

    int ret = findGrapher(w);
    if(ret < 0)
        return true;
    else if(ret)
        return false;

    Graph(w);
    Graph(w);
    return false;
}

// Return true on error.
static bool WindowVContainer(struct PnWidget *win) {

    // Reuse win:
    struct PnWidget *w = pnWidget_create(win, 2, 2,
            PnLayout_TB/*layout*/, 0/*align*/,
            PnExpand_HV, 0/*size*/);
    ASSERT(w);
    //                  Color Bytes:  A R G B
    pnWidget_setBackgroundColor(w, 0xFF00F030, 0);

    // TODO: Add other widgets like menus, button bar, and graph tabs.

    return GraphHContainer(w);

    // TODO: Add status bar last.
}

struct PnWidget *win;

// Return true on error.
static bool Window(void) {

    win = pnWindow_create(0, 8, 8,
            0/*x*/, 0/*y*/, PnLayout_TB/*layout*/, 0,
            PnExpand_HV);
    ASSERT(win);
    pnWindow_setPreferredSize(win, 1100, 900);

    return WindowVContainer(win);
}


int main(void) {

    ASSERT(SIG_ERR != signal(SIGSEGV, catcher));

    if(Window())
        return 3; // error

    pnWindow_show(win);

    pnDisplay_run();

    cleanupGrapher();

    return 0;
}

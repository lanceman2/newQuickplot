#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <panels.h>

#include "../../include/quickplot.h"

#include "../../lib/debug.h"


// Next x (X) as function of current x.
static inline double X(double x) {

    return 1.02 * x;
}

static
bool StaticPlotter(struct PnWidget *g, struct PnPlot *p, void *userData,
        double xMin, double xMax, double yMin, double yMax) {

    double x = 100.0;

    for(int i=0; i<100; ++i) {
        pnPlot_drawPoint(p, i, x);
        x = X(x);
    }
    return false;
}

static void StaticPlot(struct PnWidget *g) {

    struct PnPlot *p = pnStaticPlot_create(g, StaticPlotter, 0);
    ASSERT(p);
    // This plot, p, is owned by the graph, w.
    pnPlot_setLineColor(p, 0xFFFF0000);
    pnPlot_setPointColor(p, 0xFF00FFFF);
    pnPlot_setLineWidth(p, 3.2);
    pnPlot_setPointSize(p, 4.5);
}

// This is called by ../../bin/quickplot using dlsym().
//
void qp_graph(struct PnWidget *parent) {

    struct PnWidget *g = pnGraph_create(
            parent,
            90/*width*/, 70/*height*/, 0/*align*/,
            PnExpand_HV/*expand*/);
    ASSERT(g);
    //                  Color Bytes:  A R G B
    pnWidget_setBackgroundColor(g, 0xA0101010, 0);
    pnGraph_setView(g, -6.05, 105.0, -6.0, 800);

    StaticPlot(g);
}


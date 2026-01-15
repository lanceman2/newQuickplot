#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <sys/stat.h>

#include <panels.h>

#include "../include/quickplot.h"

#include "../lib/debug.h"

#include "findGrapher.h"

#define QP_PREFIX   "./qp_graph"
#define FUNC_NAME   "qp_graph"


void *dlhandle = 0;


void cleanupGrapher(void) {

    if(dlhandle) {
        dlclose(dlhandle);
        dlhandle = 0;
    }
}

// Return true on success.
static inline bool RunDso(struct PnWidget *parent,
        const char *dsoPath) {

    DASSERT(!dlhandle);

    dlhandle = dlopen(dsoPath, RTLD_NOW|RTLD_LOCAL);

    if(!dlhandle) {
        NOTICE("dlopen(\"%s\",) failed: dlerror()=\"%s\"",
                dsoPath, dlerror());
        return false;
    }

    void (*Graph)(struct PnWidget *parent);

    Graph = dlsym(dlhandle, FUNC_NAME);

    if(!Graph) {
        ERROR("dlsym(\"%s\",) failed: dlerror()=\"%s\"",
                FUNC_NAME, dlerror());
        cleanupGrapher();
        return false;
    }

    Graph(parent);

    // cleanupGrapher() is called later so we may keep any state that may
    // have been created by loading and running Graph() from dsoPath.

    return true; // success
}


static inline bool
Compile(const char *cPath, const char *dsoPath) {

    const size_t Len = 128;
    char run[Len];

    snprintf(run, Len,
            "gcc -Wall -Werror -fPIC -shared -o %s %s -ldl -lm",
            dsoPath, cPath);

    errno = 0;
    INFO("running: %s", run);

    if(system(run) == 0)
        return true; // success

    WARN("Failed to compile %s", cPath);
    return false; // failure
}

// Return true if we need to compile.
static inline bool
CheckDates(const struct stat *c, const struct stat *dso) {

    // struct timespec  st_atim;  /* Time of last access */
    // struct timespec  st_mtim;  /* Time of last modification */
    // struct timespec  st_ctim;  /* Time of last status change */

    const struct timespec *c_t = &c->st_ctim;
    const struct timespec *dso_t = &dso->st_ctim;

    if(c_t->tv_sec > dso_t->tv_sec || (
            c_t->tv_sec == dso_t->tv_sec &&
            c_t->tv_nsec > dso_t->tv_nsec))
        return true;
    return false;
}


int findGrapher(struct PnWidget *parent) {

    const char *cPath = QP_PREFIX ".c";
    const char *dsoPath = QP_PREFIX ".so";
    struct stat cStatbuf;
    struct stat dsoStatbuf;

    int cStat = stat(cPath, &cStatbuf);
    int dsoStat = stat(dsoPath, &dsoStatbuf);

    if(cStat) {
        if(!dsoStat)
            // We have no C file and a DSO.   
            return (RunDso(parent, dsoPath)?1:-1);
        // We have no C file and no DSO.
        return 0; // not creating grpahs.
    }

    // We have a C file.
    if(dsoStat) {
        // We don't have a DSO
        if(Compile(cPath, dsoPath))
            return (RunDso(parent, dsoPath)?1:-2);
        return -3; // not creating graphs.
    }
    // We have a C file and a DSO.
    if(CheckDates(&cStatbuf, &dsoStatbuf)) {
        if(Compile(cPath, dsoPath))
            return (RunDso(parent, dsoPath)?1:-4);
        else
            // Compiling failed.
            return -5; // not creating graphs.
    }

    // We have a C file and an up to date DSO.
    return (RunDso(parent, dsoPath)?1:-6);
}


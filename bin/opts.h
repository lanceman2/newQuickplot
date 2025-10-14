struct opts {
    const char *longOpt;
    int shortOpt; // char code like 'c'
};

extern int getOpt(int argc, const char * const *argv, int i,
        const struct opts *options/*array of options*/,
        const char **command);

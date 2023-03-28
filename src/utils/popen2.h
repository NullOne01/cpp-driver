#ifndef CMAKE_TESTS_POPEN2_H
#define CMAKE_TESTS_POPEN2_H


struct popen2 {
    size_t child_pid;
    int   from_child, to_child;
};

int popen2(const char *cmdline, struct popen2 *childinfo);

#endif //CMAKE_TESTS_POPEN2_H

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_WARN_DEPRECATED
#include "nob.h"

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Cmd cmd = {0};
    Procs procs = {0};

    if (!mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    // Spawn three async processes collecting them to procs dynamic array
    nob_cc(&cmd);
    nob_cc_flags(&cmd);
    nob_cc_output(&cmd, BUILD_FOLDER"foo");
    nob_cc_inputs(&cmd, SRC_FOLDER"foo.c");
    if (!cmd_run(&cmd, .async = &procs)) return 1;

    nob_cc(&cmd);
    nob_cc_flags(&cmd);
    nob_cc_output(&cmd, BUILD_FOLDER"bar");
    nob_cc_inputs(&cmd, SRC_FOLDER"bar.c");
    if (!cmd_run(&cmd, .async = &procs)) return 1;

    nob_cc(&cmd);
    nob_cc_flags(&cmd);
    nob_cc_output(&cmd, BUILD_FOLDER"baz");
    nob_cc_inputs(&cmd, SRC_FOLDER"baz.c");
    if (!cmd_run(&cmd, .async = &procs)) return 1;

    // Wait on all the async processes to finish and reset procs dynamic array to 0
    if (!procs_flush(&procs)) return 1;

    // TODO: add some examples with .max_procs

    return 0;
}

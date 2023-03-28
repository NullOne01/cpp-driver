#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <printf.h>
#include <assert.h>

#include <string>
#include "model/MyCPU.h"

static struct options {
    int units;
    int show_help;
} options;

std::unique_ptr<MyCPU> myCpu;

#define OPTION(t, p)                           \
    { t, offsetof(struct options, p), 1 }

static const struct fuse_opt option_spec[] = {
        OPTION("--units=%d", units),
        OPTION("-h", show_help),
        OPTION("--help", show_help),
        FUSE_OPT_END
};

static int getattr_callback(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    if (strcmp(path, "/ctrl") == 0) {
        stbuf->st_mode = S_IFREG | 0777;
        stbuf->st_nlink = 1;
        stbuf->st_size = 10;
        return 0;
    }

    for (int i = 0; i < options.units; ++i) {
        auto &unit = myCpu->units[i];
        std::string unit_path("/unit" + std::to_string(i));

        if (strcmp(path, unit_path.c_str()) == 0) {
            stbuf->st_mode = S_IFDIR | 0755;
            stbuf->st_nlink = 2;
            return 0;
        }

        std::string lram_unit_path(unit_path + "/lram");
        if (strcmp(path, lram_unit_path.c_str()) == 0) {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = unit->lram->text.size();
            return 0;
        }

        std::string pram_unit_path(unit_path + "/pram");
        if (strcmp(path, pram_unit_path.c_str()) == 0) {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = unit->pram->text.size();
            return 0;
        }
    }

    return -ENOENT;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    filler(buf, "ctrl", NULL, 0);

    for (int i = 0; i < options.units; ++i) {
        auto &unit = myCpu->units[i];
        std::string unit_path("unit" + std::to_string(i) + "/");
        filler(buf, unit_path.c_str(), NULL, 0);

        std::string lram_unit_path(unit_path + "lram/");
        filler(buf, lram_unit_path.c_str(), NULL, 0);

        std::string pram_unit_path(unit_path + "pram/");
        filler(buf, pram_unit_path.c_str(), NULL, 0);

        if (strcmp(path, unit_path.c_str()) == 0) {
            filler(buf, "lram", NULL, 0);
            filler(buf, "pram", NULL, 0);
        }
    }

    return 0;
}

static int open_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
                         struct fuse_file_info *fi) {

    if (strcmp(path, "/ctrl") == 0) {
        myCpu->makeWork();
        std::string str("CPU with : " + std::to_string(options.units) + " units did some work");
        size_t len = str.size();
        if (offset >= len) {
            return 0;
        }

        if (offset + size > len) {
            memcpy(buf, str.c_str() + offset, len - offset);
            return len - offset;
        }

        memcpy(buf, str.c_str() + offset, size);
        return size;
    }

    return -ENOENT;
}

static struct fuse_operations fuse_example_operations = {
        .getattr = getattr_callback,
        .open = open_callback,
        .read = read_callback,
        .readdir = readdir_callback,
};

static void show_help(const char *progname)
{
    printf("usage: %s [options] <mountpoint>\n\n", progname);
    printf("File-system specific options:\n"
           "    --units=<d>          Number of units \n"
           "                        (default: 2)\n"
           "\n");
}

int main(int argc, char *argv[]) {
    int ret;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    options.units = 2;

    // Parse options
    if (fuse_opt_parse(&args, &options, option_spec, NULL) == -1)
        return 1;

    if (options.show_help) {
        show_help(argv[0]);
        assert(fuse_opt_add_arg(&args, "--help") == 0);
        args.argv[0][0] = '\0';
    }

    myCpu = std::make_unique<MyCPU>(options.units);

    ret = fuse_main(args.argc, args.argv, &fuse_example_operations, NULL);
    fuse_opt_free_args(&args);
    return ret;
}

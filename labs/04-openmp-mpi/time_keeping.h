#ifndef TIME_KEEPING_H_INCLUDED
#define TIME_KEEPING_H_INCLUDED

#define RUNTIMES_SIZE 32

typedef struct TimeRange {
    double t1;
    double t2;
} TimeRange;

TimeRange time_ranges[RUNTIMES_SIZE] = {[0 ... RUNTIMES_SIZE - 1] = {0, 0}};

double runtimes[RUNTIMES_SIZE] = {[0 ... RUNTIMES_SIZE - 1] = 0};

void register_time(int rank, double t1, double t2) {
    runtimes[rank] = t2 - t1;
    time_ranges[rank] = (TimeRange){t1, t2};
}

double get_max_runtime(int nprocs) {
    double max_runtime = -1;

    for (int i = 0; i < nprocs; i++) {
        // printf("Rank %d t1 %.2f t2 %.2f dt %.2f\n",
        //        i,
        //        time_ranges[i].t1, time_ranges[i].t2,
        //        runtimes[i]);

        if (runtimes[i] > max_runtime)
            max_runtime = runtimes[i];
    }

    return max_runtime;
}

#endif // TIME_KEEPING_H_INCLUDED
export CPUPROFILE=/Users/darren/cppcode/perf/testperf.prof
export LD_PRELOAD=/usr/local/lib/libprofiler.dylib
g++ perf.cpp -o testperf
./testperf

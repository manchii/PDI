#!/bin/bash


echo "Starting regression run"
echo "ltilib::maximumFilter running"
make -C ../seq/
../seq/seq ../seq/cat-test-1.jpg > lti-perf.csv
make -C ../dokladal/
../dokladal/dokladal ../dokladal/cat-test-1.jpg > dokladal-perf.csv
make -C ../vectorized/
../vectorized/vectorized ../vectorized/cat-test-1.jpg > vectorized-perf.csv
paste -d " " lti-perf.csv dokladal-perf.csv vectorized-perf.csv > resume-perf.csv
echo "plotting"
./plot_time_comparation.py resume-perf.csv

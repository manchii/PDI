#!/bin/bash


echo "Starting regression run"
echo "ltilib::maximumFilter running"
make -C ../seq/
../seq/seq ../seq/cat-test.jpg > lti-perf.csv
make -C ../dokladal/
../dokladal/dokladal ../dokladal/cat-test.jpg > dokladal-perf.csv
paste -d " " lti-perf.csv dokladal-perf.csv > resume-perf.csv
echo "plotting"
./plot_time_comparation.py resume-perf.csv

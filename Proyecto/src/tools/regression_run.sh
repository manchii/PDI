#!/bin/bash


echo "Starting regression run"
echo "ltilib::maximumFilter running"
echo "Sample cat-test-1.jpg  cat-test.jpg  elsa-y-elmar_o.jpg  profile.jpeg  zedbrain.jpg"

make -C ../seq/
echo "pixels , time(ms) , stdvar(ms)" > lti-perf.csv
../seq/seq ../sample_img/profile.jpeg >> lti-perf.csv
../seq/seq ../sample_img/elsa-y-elmar_o.jpg >> lti-perf.csv
../seq/seq ../sample_img/cat-test-1.jpg >> lti-perf.csv
../seq/seq ../sample_img/cat-test.jpg >> lti-perf.csv
../seq/seq ../sample_img/zedbrain.jpg >> lti-perf.csv

make -C ../dokladal/
echo "pixels , time(ms) , stdvar(ms)" > dokladal-perf.csv
../dokladal/dokladal ../sample_img/profile.jpeg >> dokladal-perf.csv
../dokladal/dokladal ../sample_img/elsa-y-elmar_o.jpg >> dokladal-perf.csv
../dokladal/dokladal ../sample_img/cat-test-1.jpg >> dokladal-perf.csv
../dokladal/dokladal ../sample_img/cat-test.jpg >> dokladal-perf.csv
../dokladal/dokladal ../sample_img/zedbrain.jpg >> dokladal-perf.csv


make -C ../vectorized/
 echo "pixels , time(ms) , stdvar(ms)" > vectorized-perf.csv
../vectorized/vectorized ../sample_img/profile.jpeg >> vectorized-perf.csv
../vectorized/vectorized ../sample_img/elsa-y-elmar_o.jpg >> vectorized-perf.csv
../vectorized/vectorized ../sample_img/cat-test-1.jpg >> vectorized-perf.csv
../vectorized/vectorized ../sample_img/cat-test.jpg >> vectorized-perf.csv
../vectorized/vectorized ../sample_img/zedbrain.jpg >> vectorized-perf.csv


make -C ../opencv/
echo "pixels , time(ms) , stdvar(ms)" > opencv-perf.csv
../opencv/filter-opencv ../sample_img/profile.jpeg >> opencv-perf.csv
../opencv/filter-opencv ../sample_img/elsa-y-elmar_o.jpg >> opencv-perf.csv
../opencv/filter-opencv ../sample_img/cat-test-1.jpg >> opencv-perf.csv
../opencv/filter-opencv ../sample_img/cat-test.jpg >> opencv-perf.csv
../opencv/filter-opencv ../sample_img/zedbrain.jpg >> opencv-perf.csv



# echo "plotting"
# ./plot_time_comparation.py resume-perf.csv

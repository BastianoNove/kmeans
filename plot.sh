#!/bin/bash

gnuplot -e "unset colorbox; plot(\"$1\") with points pointtype 5 palette notitle; pause -1"

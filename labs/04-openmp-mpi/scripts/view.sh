run_command=$1

killall -q -9 eog; rm -f out_julia_normal.bmp; $run_command | sort; eog out_julia_normal.bmp &
open_project MeatNet-project
set_top MeatNet
add_files MeatNet.cpp
add_files -tb MeatNet-tb-fp-selection.cpp
open_solution "solution1" -reset
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
csim_design
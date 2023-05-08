# cosyn_automation

1. Put `build_vrun_script.cpp` and `vrun_reduction_unique_arrays.sh` in the `vrun` folder of `cape-experiment-scripts
`.
2. Compile: `g++ build_vrun_script.cpp -o build_vrun_script`

3. Run: `./a.out [base_path/codelet_name]` or `./build_vrun_script [codelet_name]` with default base_path = `compiler-evaluation-experiments/LoopGen`. for example, to run [recurrence-chained-20220730](https://github.com/amchiclet/compiler-evaluation-experiments/tree/experiments/LoopGen/recurrence-chained-20220730), we can run either `./build_vrun_script recurrence-chained-20220730` or `./a.out compiler-evaluation-experiments/LoopGen/recurrence-chained-20220730`, the generated scripts should be the same.

4. The generated vrun script will be `vrun_new.sh`.

Notice that the current `vrun_new.sh` does not have customized codelet input parameters. We didn't modify the `parameter_set_decoding()` function and the `fill_codelet_maps` command at line 136 of our reference vrun script.
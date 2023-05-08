# cosyn_automation

1. Put `build_vrun_script.cpp` and `vrun_reduction_unique_arrays.sh` in the `vrun` folder of `cape-experiment-scripts
`.
2. Compile: `g++ build_vrun_script.cpp -o build_vrun_script`

3. Run: `./a.out [base path/codelet path]` or `./build_vrun_script [codelet name]` with default base_path = `compiler-evaluation-experiments/LoopGen/`. for example, to run [recurrence-chained-20220730](https://github.com/amchiclet/compiler-evaluation-experiments/tree/experiments/LoopGen/recurrence-chained-20220730), we can run either `./build_vrun_script recurrence-chained-20220730` or `./a.out compiler-evaluation-experiments/LoopGen/recurrence-chained-20220730`, the generated script should be the same.

4. The generated vrun script will be `vrun_new.sh`.

# cosyn_automation

1. Put `build_vrun_script.cpp` and `vrun_reduction_unique_arrays.sh` in the `vrun` folder of `cape-experiment-scripts
`.
2. Compile: `g++ build_vrun_script.cpp -o build_vrun_script`

3. Run: `./build_vrun_script [codelet name]` for example, to run [recurrence-chained-20220730](https://github.com/amchiclet/compiler-evaluation-experiments/tree/experiments/LoopGen/recurrence-chained-20220730), `[codelet name]=recurrence-chained-20220730`.

4. The generated vrun script will be `vrun_new.sh`.

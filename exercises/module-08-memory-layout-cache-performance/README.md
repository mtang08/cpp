# Module 8 — Memory Layout and Performance Measurement

Status: specified, not started. Prerequisites: Modules 1–7; proceed in sequence.

## New learning

Alignment/padding, locality, working sets, AoS/SoA, optimized builds, profiling and benchmark validity.

## Exercise: Profile and compare event layouts

Build an aggregation workload over events with a mixture of frequently and rarely used fields. Produce a simple correct baseline and compare one alternative data layout. Both versions must calculate identical results from identical input. Use several working-set sizes and at least two data distributions; describe the workload and keep it reproducible.

Measure the processing kernel separately from input generation/layout conversion, and also report total cost including conversion. Use an optimized build, observable results and repeated runs. Profile the baseline with an available local tool before choosing the change. Use macOS tools locally; Linux-only tools are not prerequisites.

## Verification and review

Report compiler/options, machine, workload sizes/seeds, repetitions, variability, memory/storage cost and output equivalence. Explain a speedup, slowdown or inconclusive result. A small results table and concise explanation are sufficient.

Follow the build/review workflow in [the curriculum](../../curriculum.md). Write the implementation and tests independently, then request review. Briefly explain key design choices; a long report is not required.

## Scope boundary

Out of scope: An arbitrary speedup target, SIMD, hardware tuning, custom pools and false-sharing experiments before concurrency.

Capstone connection: Reproducible evidence for later optimization.

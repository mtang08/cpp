# Module 8 — Memory Layout and Performance Measurement

## For you

### Goal

Profile and compare event layouts.

### Steps

1. Implement the requirements and run the checks below.
2. Say **“review”**; fix required findings. The teacher handles correctness and C++ quality checks.
3. Complete the debugging challenge, then the short quiz (or skip it). Say **“continue”** to move forward.

You do not need to name skills. Say **“wrap up”** to save your place at any time.

### Build

Build an aggregation workload over events with a mixture of frequently and rarely used fields. Produce a simple correct baseline and compare one alternative data layout. Both versions must calculate identical results from identical input. Use several working-set sizes and at least two data distributions; describe the workload and keep it reproducible.

Measure the processing kernel separately from input generation/layout conversion, and also report total cost including conversion. Use an optimized build, observable results and repeated runs. Profile the baseline with an available local tool before choosing the change. Use macOS tools locally; Linux-only tools are not prerequisites.

### Check

Report compiler/options, machine, workload sizes/seeds, repetitions, variability, memory/storage cost and output equivalence. Explain a speedup, slowdown or inconclusive result. A small results table and concise explanation are sufficient.

Use the [shared build rules](../../curriculum.md#build-rules). Brief explanations of design choices are enough.

### Scope

Out of scope: An arbitrary speedup target, SIMD, hardware tuning, custom pools and false-sharing experiments before concurrency.

## For the teacher

<details>
<summary>Scope, sequencing, and handoff notes</summary>

Prerequisites: Modules 1–7.

Teaching focus: Alignment/padding, locality, working sets, AoS/SoA, optimized builds, profiling and benchmark validity.

Project connection: Reproducible evidence for later optimization.

Read [the teacher workflow](../../context/teaching-workflow.md) for skill routing. Current phase, evidence, exceptions and next action belong in [progress](../../progress.md), not in this specification.

</details>

# Learning Goals and Background

Last updated: 2026-10-03.

This is the durable source of learner goals, background, and sequencing preferences. Read it before proposing curriculum changes or preparing future exercises. [AGENTS.md](../AGENTS.md) defines teaching rules, [curriculum.md](../curriculum.md) defines the module plan, and [progress.md](../progress.md) records exercise state and evidence. The July [curriculum critique](../curriculum_critique.md) is historical advice, not an additional assignment list.

## Primary motivation

Become an excellent software systems engineer, with strong practical C++ skills and the ability to independently design, implement, test, debug, measure, and evolve a substantial software system. Quant SWE roles are a motivating application of those skills.

Reliable infrastructure ownership is especially appealing: exchange integration, market-data correctness, order handling, disconnects, recovery, and behavior under load. Working directly with traders and being close to trading outcomes also appeals; keep that direction open.

## Role interests

The learner supplied these HRT role descriptions as examples of appealing work:

- **Core Markets Engineer — Live Trading / Platform / C++:** exchange-specific order entry and market-data connectivity across asset classes, plus the underlying platform and frameworks. This is the stronger current preference.
- **Options Trading Accel Engineer — Live Trading / Accel / C++:** exchange protocols, latency/scaling in the live trading path, and strategy/execution logic. This remains an appealing alternative.

These are learner-provided reference descriptions, not a claim that particular vacancies are currently available. Both directions motivate a shared foundation in C++, systems, networking, concurrency, correctness, and performance. Specialization can come later.

The learner is more interested in application/system behavior at millisecond scales than nanosecond tuning, but this is an interest preference, not a hard performance budget or a claim about these roles. C++ systems fundamentals remain important. Hardware interfaces, kernel programming, and extreme low-latency tuning are optional future directions; the learner is open to them but does not currently want them to drive the curriculum.

## Background and reading

- New grad SWE; professional experience with Go and React. Intermediate C++: comfortable with classes, pointers, and basic STL; developing fluency in modern C++ and engineering practice. Keep explanations C++-native.
- Has already read the **virtualization and concurrency portions of OSTEP**. Do not infer that the entire book is complete or that C++ concurrency implementation has been mastered.
- Previously took a networking course using **Computer Networking: A Top-Down Approach**, did well, and plans to revisit its **first five chapters**. This review is planned, not completed.
- After finishing the initial C++ modules, intends to read **Effective Modern C++ for a couple of hours per week**, applying relevant lessons to the project as continued learning. This supersedes the earlier plan to read it alongside the initial modules. Apply techniques where appropriate rather than forcing every pattern into the project.

## Agreed learning sequence

1. Finish the initial C++ foundations before making networking and concurrency major implementation topics. Continue one module at a time; Module 4 is currently active.
2. Build a **single-threaded order-book replay application** as the initial capstone, integrating module learning into a real project. Start with one instrument and a small documented event format. Recorded executions are inputs; a matching engine is a separate potential extension.
3. Continue evolving that project into a larger software system. Introduce networking and concurrency gradually when the project creates a concrete need for them.
4. Read Effective Modern C++ alongside continued project work after the initial modules.

**Keep Python outside the curriculum for now.** Interest in C++/Python job descriptions does not authorize adding Python exercises, tooling, or a parallel study track.

## Planning direction and boundaries

The initial capstone choice is settled. Potential subsequent extensions discussed include simulated exchange/feed connectivity, market-data and order-entry services, recovery, and measured scaling. Their exact order and contracts remain to be specified; these are not current assignments.

The detailed curriculum and Modules 4–15 specifications were revised on 2026-10-03 after this goals discussion. The learner wants to work through them efficiently to build momentum. Follow the planned progression, avoid adding drills or duplicate ownership/container work without a new learning objective, and gradually give the learner more API and design ownership. Future networking/concurrency milestones remain a roadmap to specify when reached.

Success means independent engineering judgment supported by tests, debugging, and measurements. Do not turn preparation into an ever-growing prerequisite list or equate curriculum completion with guaranteed hiring readiness.

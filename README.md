# A Testbed Framework for STM32 Board Verification

This repository contains code for easy and fast setup of testing code for newly designed/assembled STM32 boards. The main purpose is to verify the correctness the hardware design and check each peripheral module of the STM32 board works as expected. Once this step is done, you can continue working with your board for whatever applications, likely with a totally differnt firmware development structure. As a result, performance and high-level features are not the main concerns of this project. The focus will be on providing verified driver modules for the most commonly used STM32 peripherals so that you can verify your hardware with minimal efforts on writing testing code.

## Development environment

* OS: Ubuntu 20.04
* Compiler: gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux
* Editor: VSCode

The project should also compile with a similar environment setup.


.. _ibex_demo_system:

Ibex Demo System
###################

Overview
********

The Ibex Demo System is one of the official project examples of the `Ibex Core`_,
a parametrizable 32 bit RISC-V CPU core maintained by lowRISC. The Ibex Demo System 
project is targeted at FPGA implementation (Arty-A7) and contains several peripherals.

Hardware
********

- RV32IMC RISC-V "Ibex" core
- 64kB main SRAM
- 1 x GPIO
- 1 x UART
- 1 x PWM
- 1 x Timer
- 1 x SPI
- 1 x PULP RISC-V Debug Module

Detailed specification is on the `Ibex Demo System Repository`_.

Supported Features
==================

+-----------+------------+-------------------------------------+
| Interface | Controller | Driver/Component                    |
+===========+============+=====================================+
| NVIC      | on-chip    | nested vector interrupt controller  |
+-----------+------------+-------------------------------------+
| Timer     | on-chip    | RISC-V Machine Timer                |
+-----------+------------+-------------------------------------+
| UART      | on-chip    | serial port-polling                 |
+-----------+------------+-------------------------------------+

Other hardware features are not yet supported on Zephyr porting.

Simulation, Programming and Debugging
*************************************

Detailed instructions are provided on the `Ibex Demo System Repository`_.

Building
========

Here is an example for building the :ref:`hello_world` application. 

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :board: ibex_demo_system
   :goals: build

Simulation
==========

The Demo System simulator binary can be built via FuseSoC:

.. code-block:: console

   fusesoc --cores-root=. run --target=sim --tool=verilator --setup --build lowrisc:ibex:demo_system

The following command can be used to load the zephyr image:

.. code-block:: console

   ./build/lowrisc_ibex_demo_system_0/sim-verilator/Vtop_verilator --meminit=ram,$ZEPHYR_PATH/build/zephyr/zephyr.elf

UART output:

.. code-block:: console

   cat uart0.log
    *** Booting Zephyr OS build v3.6.0-665-gad7086a2dfe6 ***
    Hello World! ibex_demo_system

Running on FPGA
================

Run the FPGA build for the Arty-A7:

.. code-block:: console

   fusesoc --cores-root=. run --target=synth --setup --build lowrisc:ibex:demo_system

and program the bitstream on the board:

.. code-block:: console

   make -C ./build/lowrisc_ibex_demo_system_0/synth-vivado/ pgm

The following command can be used to run the zephyr image:

.. code-block:: console

   ./util/load_demo_system.sh run $ZEPHYR_PATH/build/zephyr/zephyr.bin

UART output:

.. code-block:: console

   cat uart0.log
    *** Booting Zephyr OS build v3.6.0-665-gad7086a2dfe6 ***
    Hello World! ibex_demo_system

Debugging on FPGA
================

To debug the application, load and halt:

.. code-block:: console

   ./util/load_demo_system.sh halt $ZEPHYR_PATH/build/zephyr/zephyr.bin

and run GDB:

.. code-block:: console

    riscv32-unknown-elf-gdb ./sw/c/build/demo/hello_world/demo
    (gdb) target extended-remote localhost:3333


References
**********

.. target-notes::

.. _Ibex Demo System Repository: https://github.com/lowRISC/ibex-demo-system

.. _Ibex Core: https://ibex-core.readthedocs.io/en/latest/

## How to use it
To use the driver, you need to implement the platform specific functions.
An example is provided in the iqs266_bsp.c. The **driver** pointer will be referred in the iqs266.c file as an extern variable, through which the platform-specific functions can be accessed.

So to use the driver, you simply need to:
1. Write your own platform specific functions according to **iqs266_driver_t** struct in iqs266.h.
2. Create an instance of the **iqs266_driver_t**, and then assign all of the function pointers.
3. Have a **iqs266_driver_t** pointer named **driver** and assign the address of the driver instance in step 2.

The iqs266_bsp.c provides examples of the required functions. This is the implementation for STM32G474QE.
# About CMSIS-DSP 
CMSIS-DSP library is the component that provides an extensive suite of functions ranging from basic math to advanced filtering, all of which take advantage of the Cortex-M4's extended instruction set.

CMSIS-DSP is widely used in the industry, and enables optimized C code generation from various third-party tools. Arm has recently added new functions to the CMSIS-DSP library for classical ML, including Support Vector Machine (SVM), naive gaussian Bayes classifier and distances for clustering.


Arm’s Cortex-M4 (which is utilized by the PSoC 6), Cortex-M7, Cortex-M33, and Cortex-M35P processors all include additional instructions not found on the Cortex-M0(+) or Cortex-M3. These are the Single Instruction Multiple Data (SIMD) and Multiply and Accumulate (MAC) instructions, which allow for the efficient execution of computationally intensive DSP functions and algorithms. To take full advantage of these instructions would require a great deal of DSP and embedded programming expertise were it not for the CMSIS-DSP library. The library's source code is written mostly in C (utilizing several idioms and intrinsics) and a bit of assembly language to fully optimize it for the higher-end cores. ***Note that the CMSIS-DSP library will function correctly on the lower-end Cortex-M0(+) and Cortex-M3 cores, but not nearly as efficiently***. The library contains over 60 functions that operate on several data types. The library is divided into a number of modules each covering a specific category:
* **Basic math functions**
    > Vector Absolute Value
    
    > Vector Addition
    
    > Vector Dot Product
    
    > Vector Multiplication
    
    > Vector Negate
    
    > Vector Offset
    
    > Vector Scale
    
    > Vector Shift
    
    > Vector Subtraction

* **Fast math functions**
    > Cosine
    
    > Sine
    
    > Square Root
* **Complex math functions**
    > Complex Conjugate
    
    > Complex Dot Product
    
    > Complex Magnitude
    
    > Complex Magnitude Squared
    
    > Complex-by-Complex Multiplication
    
    > Complex-by-Real Multiplication
* **Filters**
    >   Biquad Cascade IIR Filters Using Direct Form I Structure
    
    >    Biquad Cascade IIR Filters Using a Direct Form II Transposed Structure
    
    >    High Precision Q31 Biquad Cascade Filter
    
    >   Convolution
    
    >    Partial Convolution
    
    >    Correlation
    
    >    Finite Impulse Response (FIR) Decimator
    
    >    Finite Impulse Response (FIR) Filters
    
    >    Finite Impulse Response (FIR) Lattice Filters
    
    >    Finite Impulse Response (FIR) Sparse Filters
    
    >    Infinite Impulse Response (IIR) Lattice Filters
    
    >    Least Mean Square (LMS) Filters
    
    >    Normalized LMS Filters
    
    >    Normalized LMS Filters
    
    >    Normalized LMS Filters
    
    >    Normalized LMS Filters
    
    >    Finite Impulse Response (FIR) Interpolator
* **Matrix functions**
    >   Matrix Addition
    
    >   Matrix Initialization
    
    >    Matrix Inverse
    
    >    Matrix Multiplication
    
    >    Matrix Scale
    
    >    Matrix Subtraction
    
    >    Matrix Transpose
*   **Transforms**
    >   Complex FFT Functions
    
    >    DCT Type IV Functions
    
    >   Real FFT Functions
* **Motor control functions**
    >   Sine Cosine
    
    >    PID Motor Control
    
    >    Vector Clarke Transform
    
    >    Vector Inverse Clarke Transform
    
    >    Vector Park Transform
    
    >    Vector Inverse Park transform
* **Statistical functions**
* **Support functions**
* **Interpolation functions**
    >    Linear Interpolation
    
    >    Bilinear Interpolation

The library has separate functions for operating on 8-bit integers, 16-bit integers, 32-bit integers, and 32-bit floating-point
values.

***The library functions are declared in the public file arm_math.h which is placed in the Include folder. Simply include this file and link the appropriate library in the application and begin calling the library functions.***

## Refrence
 *  [CMSIS_DSP](https://arm-software.github.io/CMSIS_5/DSP/html/index.html)
 
 

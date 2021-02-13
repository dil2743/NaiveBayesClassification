# NaiveBayesClassification



## Objective 



> On ***Cortex M0+*** microcontroller perform a ***Naive Bayes classification*** using ***CMSIS-DSP***, every 10ms. Any data can be taken for this.

The firmware should be written to exhibit minimal power consumption without performance loss.



## [Project Implimentation](https://github.com/dil2743/NaiveBayesClassification/tree/CubeIde/BayesianEstimator)
>	* The project is developed on **CubeIDE** Version: 1.5.1 can be found [here](https://github.com/dil2743/NaiveBayesClassification/tree/CubeIde/BayesianEstimator)


## Microcontroller selection 

> Stm has a good line of low power controllers, according to  requirement the MCU should be on Cortex M0+ and must consume list power with desired performance.

> **Stm32 CubeIde** provides a nice interface for selecting the MCU, as can be seen from below image that with the help of available filters such as **Core**, **Series**, **Line** and **Package** it become quite easy to narrow down the list.

Stm32L071CBTx is selected from available options after analysing various available options on the basis of available RAM, Flash, power consumption and DMIPS.

![Stm32L071CBTx](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/Images/Design/TargetSelection.PNG)



# [Exploring CMSIS-DSP Library](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/CMSIS-DSP.md)



# [Exploring Low Power Mode](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/LowPowerDesign.md)



# [Understanding NaiveBayes classifier](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/Naive-BayesClassifier.md)



# [Training Model and Collecting Parameters](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/TrannigModel.md)

> The Python script can be found [here](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/ModelTranning/BayesianClassiferTrain.py) which can be used to train NaiveBayes classifier and to generate required parameters. 



## Writing Firmware 



> ### ***Low Power Mode*** 



* RTC is configured at 10ms for generating interrupt which will be used as source for waking the controller from Stop mode.

```



	if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x20, RTC_WAKEUPCLOCK_RTCCLK_DIV16)

			!= HAL_OK) {

		Error_Handler();

	}

```

* Also **sleep on exit** is enabled so that the controller wakes up, executes the sub-routine and  automataclly went to Stop mode as soon as the sub-routine exits.

```

HAL_PWR_EnableSleepOnExit();

```

* **Stop mode** is used as low power mode and the analysis about the same can be found below

![Power Consumption](https://github.com/dil2743/NaiveBayesClassification/blob/CubeIde/Images/Design/ConsumptionPofile.PNG)

> ### The clock is configured at 32 Mhz as the subroutine execution takes about 26000 DWT cycle which is approx 0.1ms time on core and it can be seen from above analysis that the Run mode is only consuming 7.5 mAmps of current while stop mode is consuming approx 750nAmps leading to average consumption of approx. 73 micro-AMps.


> ### Flow Design



 * 			The controller is configured in Stop mode with SleepOnExit feature

 * 			As soon as it receives a INT it will wake up and

 * 			execute the sub-routine, once the sub-routine is completed it will go again into Stop mode.



* Wakeup Sub-routine 

```

/*

 * @info : Callback function for RTC - this routine will be executed every time the controller wakes from low power mode

 *

 */



void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {

	SystemClock_Config();

	HAL_ResumeTick();

	my_test_task();

}

```

* Test Function 

```

/*

 * @info : test function - this function will execute at a every 10ms and will use the @func my_pridictor(x,y) to

 * 			Predict the output based on the given input

 * 			Here the test a pseudo test. A more random test can be generated using ADC for generating Random numbers

 * @input : None

 * @output : None

 */

void my_test_task(void) {

	uint32_t output_cluster_index = my_pridictor(

			input_test_array[index_counter],

			input_test_array[index_counter + 1]);

	if (index_counter > 9) {

		index_counter = 0;

	} else {

		index_counter += 2;

	}

}

```

* Classifier Sub-routine

```

/*

 * @info Naive_Bayes Predictor : This function will predict the class/index with which the given inputs should belong

 * @input : float x : first feature of the object

 * @input : float y : second feature of the object

 * @output : returns the index with which the object belongs based on its features and trained model data

 */

uint32_t my_pridictor(float x, float y) {

	/* Array of input data */



	float32_t in[2];



	/* Result of the classifier */

	float32_t result[NB_OF_CLASSES];

	float32_t maxProba;

	uint32_t index;



	S.vectorDimension = VECTOR_DIMENSION;

	S.numberOfClasses = NB_OF_CLASSES;

	S.theta = theta;

	S.sigma = sigma;

	S.classPriors = classPriors;

	S.epsilon = 4.328939296523643e-09f;



	in[0] = x;

	in[1] = y;



	arm_gaussian_naive_bayes_predict_f32(&S, in, result);



	arm_max_f32(result, NB_OF_CLASSES, &maxProba, &index);



	return index;

}

```


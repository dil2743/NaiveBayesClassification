/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "arm_math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
uint32_t my_pridictor(float x, float y);

arm_gaussian_naive_bayes_instance_f32 S;

#define NB_OF_CLASSES 3
#define VECTOR_DIMENSION 2

const float32_t theta[NB_OF_CLASSES * VECTOR_DIMENSION] = { 1.4539529436590528f,
		0.8722776016801852f, -1.5267934452462473f, 0.903204577814203f,
		-0.15338006360932258f, -2.9997913665803964f }; /**< Mean values for the Gaussians */

const float32_t sigma[NB_OF_CLASSES * VECTOR_DIMENSION] = { 1.0063470889514925f,
		0.9038018246524426f, 1.0224479953244736f, 0.7768764290432544f,
		1.1217662403241206f, 1.2303890106020325f }; /**< Variances for the Gaussians */

const float32_t classPriors[NB_OF_CLASSES] = { 0.3333333333333333f,
		0.3333333333333333f, 0.3333333333333333f }; /**< Class prior probabilities */
int index_counter = 0; // to iterate on test array
float input_test_array[10] = { -0.001, -3.000, 1.551, 0.570, -1.601, 0.980,
		-1.158, -3.110, 2.5158, 1.910

};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_RTC_Init();
	/* USER CODE BEGIN 2 */
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
		/* USER CODE END WHILE */

		/*
		 * @TODO :
		 * 			1: wake up periodically at an interval of 10ms.
		 * 			2: execute the Naive-Bayes Classifier
		 * 			3: Go to low Power mode
		 * @Design :
		 * 			The controller is configured in Stop mode with SleepOnExit feature
		 * 			So the will go into Stop mode and as soon as it receives a INT it will wake up and
		 * 			execute the sub-routine. Once the sub-routine is completed it will go again into Stop mode.
		 *
		 */

		/*
		 Configure the Wake up timer
		 RTC Wake-up Interrupt Generation:
		 Wake-up Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSI))
		 ==> WakeUpCounter = Wake-up Time / Wake-up Time Base

		 To configure the wake up timer to 20s the WakeUpCounter is set to 0xA017:
		 RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16
		 Wake-up Time Base = 16 /(32KHz) = 0.0005 seconds
		 ==> WakeUpCounter = ~10ms/0.0005s = 20 = 0x14
		 */

		if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 20, RTC_WAKEUPCLOCK_RTCCLK_DIV16)
				!= HAL_OK) {
			Error_Handler();
		}

		/****** Suspend the Ticks before entering the STOP mode or else this can wake the device up **********/
		HAL_SuspendTick();

		HAL_PWR_EnableSleepOnExit(); // enable Sleep on Exit : it will put the controller into sleep after completing the sub-routine

		/* Enter Stop Mode */
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
		/* Enter Stop Mode */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI
			| RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void) {

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */
	/** Initialize RTC Only
	 */
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&hrtc) != HAL_OK) {
		Error_Handler();
	}
	/** Enable the WakeUp
	 */
	if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 20, RTC_WAKEUPCLOCK_RTCCLK_DIV16)
			!= HAL_OK) {
		Error_Handler();
	}
	/** Enable Calibrartion
	 */
	if (HAL_RTCEx_SetCalibrationOutPut(&hrtc, RTC_CALIBOUTPUT_1HZ) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
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

/*
 * @info : Callback function for RTC - this routine will be executed every time the controller wakes from low power mode
 *
 */

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
	SystemClock_Config();
	HAL_ResumeTick();
	my_test_task();
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

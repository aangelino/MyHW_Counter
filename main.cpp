#include "mbed.h"
#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
long count=0;
long count2=0;

static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);

int main(void)
{
  /* GPIO Ports Clock Enable /Enable the AHB1 peripheral clock. */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  printf("\n\r MX_TIM1_Init \r\n");
  MX_TIM1_Init();
  printf("\n\r MX_TIM2_Init \r\n");
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
  printf("\n\r HAL_TIM_Base_Start(&htim1) \r\n");
  HAL_TIM_Base_Start(&htim1);    //Start TIM2 without interrupt
  printf("\n\r HAL_TIM_Base_Start(&htim2) \r\n");
  HAL_TIM_Base_Start(&htim2);    //Start TIM2 without interrupt
  printf("\n\r srtart run \r\n");
  while (1)
  {

	  count = __HAL_TIM_GetCounter(&htim1);    //read TIM2 counter value
    printf("\n\r count=%d\n\r",count);
    count2 = __HAL_TIM_GetCounter(&htim2);    //read TIM2 counter value
    printf("\n\r count2=%d\n\r",count2);

    //printf("\n\r status =%d\n\r",__HAL_TIM_GET_ITSTATUS(&htim1));
    //printf("\n\r clear =%d\n\r",TIM_GET_CLEAR_IT(&htim1));
    //printf("\n\r itstatus =%d\n\r",__HAL_TIM_GET_ITSTATUS(&htim1));
    //printf("\n\r status =%d\n\r",__HAL_TIM_GET_ITSTATUS(&htim1));


    wait(1);

  }


}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{
  printf("\n\r into MX_TIM1_Init \n\r");
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  printf("\n\r HAL_TIM_Base_Init(&htim1)\n\r");
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 15;
  printf("\n\r HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig)\n\r");
  if (HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;//TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;//TIM_MASTERSLAVEMODE_DISABLE;
  printf("\n\r HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)\n\r");
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

}

/* TIM1 init function */
static void MX_TIM2_Init(void)
{

  printf("\n\r into MX_TIM2_Init \n\r");
  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.RepetitionCounter = 0;

  printf("\n\r HAL_TIM_Base_Init(&htim2)\n\r");
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_GATED;
  sSlaveConfig.InputTrigger = TIM_TS_ITR1;//TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  printf("\n\r HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig)\n\r");
  if (HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  //sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;//TIM_TRGO_RESET;
  //sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;//TIM_MASTERSLAVEMODE_DISABLE;

  /*if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }*/

}

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // 42 MHz max Timer i�in 84Mhz max

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;; // STMCUBEMX den de bak�labilir. Elektrik t�ketimi ile alakal�d�r.
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_RepetitionCounter = 0; // 1 ta�ma sonucunda bayra�� kald�r diyoruz. yaz�lan de�er +1 olur.
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Yukar� do�ru say diyoruz.

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	// E�er TIM ile beraber bir interrupt kullanacaksak timer ile interrupt� birbirine ba�lamal�y�z.
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn; // NVIC in y�netece�i interrupt� belirtir
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	// hatt� aktif ettik
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; // bas�a interrupt yok �nceli�e gerek yok.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;

	NVIC_Init(&NVIC_InitStruct);
}

void TIM4_IRQHandler()
{
	// bayrak kalkt�ktan sonra yap�lacak i�lem
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	// bayra�� tekrar indirmeliyiz bayra��n tekrar kalkmas� i�in
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}

int main(void)
{
	config();
  while (1)
  {

  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}

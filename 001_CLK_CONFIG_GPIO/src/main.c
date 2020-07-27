#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStructure;

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Delay(uint32_t time)
{
	while(time > 0)
		time -= 1;
	// while(time--); �eklinde ifade edilirse bir i�lem 8 cycle da tamamlan�yor.
	/*
	 * Tam bir saniye elde edebilmek i�in time de�eri
	 * time = 168000000 / 8 = 21000000 yaz�lmal�.
	 */
	//	while(time > 0)time-=1; �eklinde ifade edilirse bir i�lem 12 cycle da tamamlan�yor.
	/*
	 * Tam bir saniye elde edebilmek i�in time de�eri
	 * time = 168000000 / 12 = 14000000 olmal�
	 */
}

int main(void)
{
 	config();

  while (1)
  {
	  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  Delay(14000000);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	  Delay(14000000);
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

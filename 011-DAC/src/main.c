#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i;

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

void delay(uint32_t time)
{
	while(time--)
	{

	}
}

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None; 	// sinyal �retilecekse tetiklenmesi laz�m bu sebeple tetik yok
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None; // sinyal �retmeyece�im
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable; // Buffer g�r�lt�y� engeller aktif etmek gerekir.

	DAC_Init(DAC_Channel_1, &DAC_InitStruct);

	// DAC bir �evre birimi oldu�u i�in ve her �evre birimini aktif etti�imiz gibi DAC � da aktif etmemiz gerekir.
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

int main(void)
{
 	config();
  while (1)
  {
	  for(i = 0; i<4096; i++)
	  {
		  DAC_SetChannel1Data(DAC_Align_12b_R, i); // DAC align (y�n) olarak sa�a m� sola m� olaca��n� g�nderece�imiz k�s�md�r.
		  delay(10000);
	  }

	  i = 0;
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

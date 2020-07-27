#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIM_OCInitStruct; // OC: Output Channel

void config()
{
	/*
	 * Bu projede TIM4 timer�n� kullanaca��z. Ledlerimizin �zerinde bulundu�u pinlerde mevcut.
	 * Bu sayede farkl� bir komponent kullanmadan direkt olarak yapt���m�z ayar� board �zerinde g�rece�iz.
	*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// AF � belirtti�imiz yer
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
	// Hangi pin hangi fonksiyon i�in tan�mlanacaksa onu se�meliyiz.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // ��k�� elde edece�iz ancak pwm �zerinden ��k�� verece�iz bu
	// sebeple alternate function oldu�unu belli etmemiz laz�m. AF olarak s�yledik ve pwm ��k�� elde edece�iz
	// e�er AF olarak bir fonksiyon tan�mlad�ysak kesinlikle AF �n �zerinde belirtmemiz gerekir.
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

	TIM_Cmd(TIM4, ENABLE);

	// T�mer PWM Konfigurasyonu

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;  // 1. Modu kullanaca��m�z� s�yledik
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // ��k�� almay� aktif ettik
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // HIGH ve LOW olma durumu
}

int main(void)
{
	config();
  while (1)
  {
	  /*
	   * Doluluk oran� a�a��daki formul ile hesaplan�r:
	   *
	   * pulse_length = ((TIM_period + 1) * DutyCycle) / 100 - 1
	   *
	   * �rne�in
	   *
	   * 	%25  duty cycle: pulse_length = ((9999 + 1) *  25) / 100 -1 = 2499
	   * 	%50  duty cycle: pulse_length = ((9999 + 1) *  50) / 100 -1 = 4999
	   * 	%75  duty cycle: pulse_length = ((9999 + 1) *  75) / 100 -1 = 7499
	   * 	%100 duty cycle: pulse_length = ((9999 + 1) * 100) / 100 -1 = 9999
	   */
	  // PD12
	  TIM_OCInitStruct.TIM_Pulse = 2499;	// %25 duty cycle ile �al��t�r�yoruz.
	  TIM_OC1Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);	// TIM OC nin 1.kanal�n� aktif ettik

	  // PD13
	  TIM_OCInitStruct.TIM_Pulse = 4999;	// %50 duty cycle ile �al��t�r�yoruz.
	  TIM_OC2Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);	// TIM OC nin 2. kanal�n� aktif ettik

	  // PD14
	  TIM_OCInitStruct.TIM_Pulse = 7499;	// %75 duty cycle ile �al��t�r�yoruz.
	  TIM_OC3Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);	// TIM OC 3. nin kanal�n� aktif ettik

	  // PD15
	  TIM_OCInitStruct.TIM_Pulse = 9999;	// %100 duty cycle ile �al��t�r�yoruz.
	  TIM_OC4Init(TIM4, &TIM_OCInitStruct);
	  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);	// TIM OC nin 4. kanal�n� aktif ettik
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

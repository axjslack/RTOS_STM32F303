#ifndef _ACC_C_
#define _ACC_C_
 
#define LSM_Acc_Sensitivity_2g     (float)     1.0f            /*!< accelerometer sensitivity with 2 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_4g     (float)     0.5f            /*!< accelerometer sensitivity with 4 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_8g     (float)     0.25f           /*!< accelerometer sensitivity with 8 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_16g    (float)     0.0834f         /*!< accelerometer sensitivity with 12 g full scale [LSB/mg] */
 
#include "Accelerometer.h"
#include "stm32f3_discovery_lsm303dlhc.h"
/**
  * @brief  Configure the Mems to Accelerometer MEMS.
  * @param  None
  * @retval None
  */
void Acc_Config(void)
{
  LSM303DLHCAcc_InitTypeDef LSM303DLHCAcc_InitStructure;
  LSM303DLHCAcc_FilterConfigTypeDef LSM303DLHCFilter_InitStructure;
     
   /* Fill the accelerometer structure */
  LSM303DLHCAcc_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
  LSM303DLHCAcc_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
  LSM303DLHCAcc_InitStructure.Axes_Enable= LSM303DLHC_AXES_ENABLE;
  LSM303DLHCAcc_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
  LSM303DLHCAcc_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
  LSM303DLHCAcc_InitStructure.Endianness=LSM303DLHC_BLE_LSB;
  LSM303DLHCAcc_InitStructure.High_Resolution=LSM303DLHC_HR_ENABLE;
  /* Configure the accelerometer main parameters */
  LSM303DLHC_AccInit(&LSM303DLHCAcc_InitStructure);
   
  /* Fill the accelerometer LPF structure */
  LSM303DLHCFilter_InitStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
  LSM303DLHCFilter_InitStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
  LSM303DLHCFilter_InitStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
  LSM303DLHCFilter_InitStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;
 
  /* Configure the accelerometer LPF main parameters */
  LSM303DLHC_AccFilterConfig(&LSM303DLHCFilter_InitStructure);
}
 
/**
* @brief Read LSM303DLHC output register, and calculate the acceleration ACC=(1/SENSITIVITY)* (out_h*256+out_l)/16 (12 bit rappresentation)
* @param pnData: pointer to float buffer where to store data
* @retval None
*/
void Acc_ReadData(float* pfData)
{
  int16_t pnRawData[3];
  uint8_t ctrlx[2];
  float LSM_Acc_Sensitivity = LSM_Acc_Sensitivity_2g;
  uint8_t buffer[6], cDivider;
  uint8_t i = 0;
   
  /* Read the register content */
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, ctrlx,2);
  LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A, buffer, 6);
  
   
  if(ctrlx[1]&0x40)
    cDivider=64;
  else
    cDivider=16;
 
  /* check in the control register4 the data alignment*/
  if(!(ctrlx[0] & 0x40) || (ctrlx[1] & 0x40)) /* Little Endian Mode or FIFO mode */
  {
    for(i=0; i<3 data-blogger-escaped-0x30="" data-blogger-escaped-8="" data-blogger-escaped-all="" data-blogger-escaped-and="" data-blogger-escaped-axis="" data-blogger-escaped-basic="" data-blogger-escaped-big="" data-blogger-escaped-block="" data-blogger-escaped-break="" data-blogger-escaped-brief="" data-blogger-escaped-buffer="" data-blogger-escaped-case="" data-blogger-escaped-cc_sensitivity="" data-blogger-escaped-cdivider="" data-blogger-escaped-communication="" data-blogger-escaped-content="" data-blogger-escaped-crtl4="" data-blogger-escaped-ctrlx="" data-blogger-escaped-else="" data-blogger-escaped-endian="" data-blogger-escaped-endif="" data-blogger-escaped-fifo="" data-blogger-escaped-float="" data-blogger-escaped-for="" data-blogger-escaped-i="" data-blogger-escaped-if="" data-blogger-escaped-in="" data-blogger-escaped-int16_t="" data-blogger-escaped-lsm303dlhc_ctrl_reg4_a="" data-blogger-escaped-lsm303dlhc_fullscale_16g:="" data-blogger-escaped-lsm303dlhc_fullscale_2g:="" data-blogger-escaped-lsm303dlhc_fullscale_4g:="" data-blogger-escaped-lsm303dlhc_fullscale_8g:="" data-blogger-escaped-lsm303dlhc_read="" data-blogger-escaped-lsm303dlhc_timeout_usercallback="" data-blogger-escaped-lsm_acc_sensitivity="LSM_Acc_Sensitivity_16g;" data-blogger-escaped-management="" data-blogger-escaped-mg="" data-blogger-escaped-mode="" data-blogger-escaped-none.="" data-blogger-escaped-normal="" data-blogger-escaped-obtain="" data-blogger-escaped-of="" data-blogger-escaped-param="" data-blogger-escaped-pfdata="" data-blogger-escaped-pnrawdata="" data-blogger-escaped-pre="" data-blogger-escaped-processes="" data-blogger-escaped-read="" data-blogger-escaped-register="" data-blogger-escaped-retval="" data-blogger-escaped-sensitivity="" data-blogger-escaped-set="" data-blogger-escaped-situation.="" data-blogger-escaped-switch="" data-blogger-escaped-the="" data-blogger-escaped-three="" data-blogger-escaped-timeout="" data-blogger-escaped-uint16_t="" data-blogger-escaped-uint32_t="" data-blogger-escaped-value="" data-blogger-escaped-void="" data-blogger-escaped-while="" data-blogger-escaped-x40="">
Gyro.c
 
 
 
#ifndef _GYRO_C_
#define _GYRO_C_
 
#define L3G_Sensitivity_250dps     (float)   114.285f         /*!< gyroscope sensitivity with 250 dps full scale [LSB/dps] */
#define L3G_Sensitivity_500dps     (float)    57.1429f        /*!< gyroscope sensitivity with 500 dps full scale [LSB/dps] */
#define L3G_Sensitivity_2000dps    (float)    14.285f       /*!< gyroscope sensitivity with 2000 dps full scale [LSB/dps] */
 
#include "Gyro.h"
#include "stm32f3_discovery_l3gd20.h"
 
/**
  * @brief  Configure the Mems to gyroscope application.
  * @param  None
  * @retval None
  */
void GyroConfig(void)
{
  L3GD20_InitTypeDef L3GD20_InitStructure;
  L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;
   
  /* Configure Mems L3GD20 */
  L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
  L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1;
  L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
  L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4;
  L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
  L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
  L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500;
  L3GD20_Init(&L3GD20_InitStructure);
    
  L3GD20_FilterStructure.HighPassFilter_Mode_Selection =L3GD20_HPM_NORMAL_MODE_RES;
  L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;
  L3GD20_FilterConfig(&L3GD20_FilterStructure) ;
   
  L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);
}
 
/**
  * @brief  Calculate the angular Data rate Gyroscope.
  * @param  pfData : Data out pointer
  * @retval None
  */
void GyroReadAngRate (float* pfData)
{
  uint8_t tmpbuffer[6] ={0};
  int16_t RawData[3] = {0};
  uint8_t tmpreg = 0;
  float sensitivity = 0;
  int i =0;
 
  L3GD20_Read(&tmpreg,L3GD20_CTRL_REG4_ADDR,1);
   
  L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);
   
  /* check in the control register 4 the data alignment (Big Endian or Little Endian)*/
  if(!(tmpreg & 0x40))
  {
    for(i=0; i<3 data-blogger-escaped-0="" data-blogger-escaped-0x00:="" data-blogger-escaped-0x10:="" data-blogger-escaped-0x20:="" data-blogger-escaped-0x30="" data-blogger-escaped-8="" data-blogger-escaped-awdata="" data-blogger-escaped-basic="" data-blogger-escaped-break="" data-blogger-escaped-brief="" data-blogger-escaped-by="" data-blogger-escaped-case="" data-blogger-escaped-crtl4="" data-blogger-escaped-divide="" data-blogger-escaped-else="" data-blogger-escaped-endif="" data-blogger-escaped-float="" data-blogger-escaped-for="" data-blogger-escaped-i="" data-blogger-escaped-in="" data-blogger-escaped-int16_t="" data-blogger-escaped-l3gd20_timeout_usercallback="" data-blogger-escaped-management="" data-blogger-escaped-none.="" data-blogger-escaped-of="" data-blogger-escaped-param="" data-blogger-escaped-pfdata="" data-blogger-escaped-pre="" data-blogger-escaped-rawdata="" data-blogger-escaped-return="" data-blogger-escaped-retval="" data-blogger-escaped-sensitivity="" data-blogger-escaped-set="" data-blogger-escaped-situation.="" data-blogger-escaped-switch="" data-blogger-escaped-the="" data-blogger-escaped-timeout="" data-blogger-escaped-tmpbuffer="" data-blogger-escaped-tmpreg="" data-blogger-escaped-uint16_t="" data-blogger-escaped-uint32_t="" data-blogger-escaped-value="" data-blogger-escaped-void=""></pre>
main.c
 
 
 
 
 
/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Virtual Com Port Demo main file
  ******************************************************************************
  * @attention
  *
  **
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
 
 
/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "Accelerometer.h"
#include "Gyro.h"
#include <stdio .h="">
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
float AccData[3];
float GyroData[3];
char data[9];
 int i =0;
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
 
/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
// data[0] = 'K';
 
  Set_System();
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
  Acc_Config();
  GyroConfig();
  while (1)
  {
   Acc_ReadData(AccData);
   GyroReadAngRate(GyroData);
   sprintf(data,"%F",AccData[0]);
   sprintf(data+3,"%F",AccData[1]);
   sprintf(data+6,"%F",AccData[2]);
    UserToPMABufferCopy((uint8_t*)data,ENDP1_TXADDR,9);
      SetEPTxCount(ENDP1, 9);
      SetEPTxValid(ENDP1);
   sprintf(data,"%F",GyroData[0]);
   sprintf(data+3,"%F",GyroData[1]);
   sprintf(data+6,"%F",GyroData[2]);
    UserToPMABufferCopy((uint8_t*)data,ENDP1_TXADDR,9);
      SetEPTxCount(ENDP1, 9);
      SetEPTxValid(ENDP1);
    
  // printf("%s\n",AccData);
  }
}
#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
 
  /* Infinite loop */
  while (1)
  {}
}
#endif
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 
</stdio></pre>
<!--3-->

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
//QDtech-OLEDҺ������ for STM32
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/8/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
// OLEDģ��               STM32��Ƭ��
//   VCC         ��       DC 5V/3.3V      //OLED����Դ��
//   GND         ��          GND          //OLED����Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������Ϊ4����SPI
// OLEDģ��               STM32��Ƭ��
//   D1          ��          PB15        //OLED��SPIд�ź�
//=======================================Һ���������߽���==========================================//
// OLEDģ��               STM32��Ƭ��
//   CS          ��          PB11        //OLED��Ƭѡ�����ź�
//   RES         ��          PB12        //OLED����λ�����ź�
//   DC          ��          PB10        //OLED������/����ѡ������ź�
//   D0          ��          PB13        //OLED��SPIʱ���ź�
//=========================================����������=========================================//
//��ģ�鲻���������ܣ����Բ���Ҫ����������
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/		
#ifndef __GUI_H__
#define __GUI_H__

#include "stm32f1xx_hal.h"
#include "stdint.h"

/*****************************************************************************
 * @name       :void GUI_DrawPoint(uint8_t x, uint8_t y, uint8_t color)
 * @date       :��
 * @function   :��ָ���������һ����
 * @parameters :x:��� x ����
                y:��� y ����
                color:�����ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawPoint(uint8_t x, uint8_t y, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color)
 * @date       :��
 * @function   :���ָ������
 * @parameters :sx:��ʼ x ����
                sy:��ʼ y ����
                ex:���� x ����
                ey:���� y ����
                color:�����ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :��
 * @function   :����һ��ֱ��
 * @parameters :x1:��ʼ��� x ����
                y1:��ʼ��� y ����
                x2:������� x ����
                y2:������� y ����
                color:������ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :��
 * @function   :����һ�����α߿�
 * @parameters :x1:���Ͻǵ� x ����
                y1:���Ͻǵ� y ����
                x2:���½ǵ� x ����
                y2:���½ǵ� y ����
                color:���α߿���ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :��
 * @function   :���һ������
 * @parameters :x1:���Ͻǵ� x ����
                y1:���Ͻǵ� y ����
                x2:���½ǵ� x ����
                y2:���½ǵ� y ����
                color:�����ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :��
 * @function   :����һ��Բ�ı߿�
 * @parameters :xc:Բ�ĵ� x ����
                yc:Բ�ĵ� y ����
                color:Բ�ı߿���ɫ
                r:Բ�İ뾶
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r);

/*****************************************************************************
 * @name       :void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :��
 * @function   :���һ��Բ
 * @parameters :xc:Բ�ĵ� x ����
                yc:Բ�ĵ� y ����
                color:�����ɫ
                r:Բ�İ뾶
 * @retvalue   :��
******************************************************************************/ 
void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r);

/*****************************************************************************
 * @name       :void GUI_DrawTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :��
 * @function   :����һ�������εı߿�
 * @parameters :x0:��һ������� x ����
                y0:��һ������� y ����
                x1:�ڶ�������� x ����
                y1:�ڶ�������� y ����
                x2:����������� x ����
                y2:����������� y ����
                color:�����α߿���ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_FillTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :��
 * @function   :���һ��������
 * @parameters :x0:��һ������� x ����
                y0:��һ������� y ����
                x1:�ڶ�������� x ����
                y1:�ڶ�������� y ����
                x2:����������� x ����
                y2:����������� y ����
                color:�����ɫ
 * @retvalue   :��
******************************************************************************/ 
void GUI_FillTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t mode)
 * @date       :��
 * @function   :��ʾ�����ַ�
 * @parameters :x:�ַ���ʾ��ʼλ�õ� x ����
                y:�ַ���ʾ��ʼλ�õ� y ����
                chr:Ҫ��ʾ���ַ�
                Char_Size:�ַ���С
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode)
 * @date       :��
 * @function   :��ʾ����
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                num:Ҫ��ʾ������
                len:��ʾ��λ��
                Size:���ֵĴ�С
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode)
 * @date       :��
 * @function   :��ʾ�ַ���
 * @parameters :x:�ַ�����ʾ��ʼλ�õ� x ����
                y:�ַ�����ʾ��ʼλ�õ� y ����
                chr:Ҫ��ʾ���ַ���
                Char_Size:�ַ���С
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont16(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :��
 * @function   :��ʾ���� 16x16 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont16(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont24(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :��
 * @function   :��ʾ���� 24x24 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont24(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont32(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :��
 * @function   :��ʾ���� 32x32 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont32(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode)
 * @date       :��
 * @function   :��ʾ�����ַ���
 * @parameters :x:�����ַ�����ʾ��ʼλ�õ� x ����
                y:�����ַ�����ʾ��ʼλ�õ� y ����
                hsize:���ִ�С
                str:�����ַ�������ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_DrawBMP(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
 * @date       :��
 * @function   :��ʾ��ɫ BMP ͼƬ
 * @parameters :x:ͼƬ��ʾ��ʼλ�õ� x ����
                y:ͼƬ��ʾ��ʼλ�õ� y ����
                width:ͼƬ���
                height:ͼƬ�߶�
                BMP:ͼƬ���ݵ���ʼ��ַ
                mode:0-�׵׺�ͼ
                      1-�ڵװ�ͼ
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawBMP(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode);

#endif


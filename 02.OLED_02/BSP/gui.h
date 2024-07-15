//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-OLED液晶驱动 for STM32
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/8/27
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
// OLED模块               STM32单片机
//   VCC         接       DC 5V/3.3V      //OLED屏电源正
//   GND         接          GND          //OLED屏电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI
// OLED模块               STM32单片机
//   D1          接          PB15        //OLED屏SPI写信号
//=======================================液晶屏控制线接线==========================================//
// OLED模块               STM32单片机
//   CS          接          PB11        //OLED屏片选控制信号
//   RES         接          PB12        //OLED屏复位控制信号
//   DC          接          PB10        //OLED屏数据/命令选择控制信号
//   D0          接          PB13        //OLED屏SPI时钟信号
//=========================================触摸屏接线=========================================//
//本模块不带触摸功能，所以不需要触摸屏接线
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
 * @date       :无
 * @function   :在指定坐标绘制一个点
 * @parameters :x:点的 x 坐标
                y:点的 y 坐标
                color:点的颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawPoint(uint8_t x, uint8_t y, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color)
 * @date       :无
 * @function   :填充指定区域
 * @parameters :sx:起始 x 坐标
                sy:起始 y 坐标
                ex:结束 x 坐标
                ey:结束 y 坐标
                color:填充颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_Fill(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :无
 * @function   :绘制一条直线
 * @parameters :x1:起始点的 x 坐标
                y1:起始点的 y 坐标
                x2:结束点的 x 坐标
                y2:结束点的 y 坐标
                color:线条颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :无
 * @function   :绘制一个矩形边框
 * @parameters :x1:左上角的 x 坐标
                y1:左上角的 y 坐标
                x2:右下角的 x 坐标
                y2:右下角的 y 坐标
                color:矩形边框颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :无
 * @function   :填充一个矩形
 * @parameters :x1:左上角的 x 坐标
                y1:左上角的 y 坐标
                x2:右下角的 x 坐标
                y2:右下角的 y 坐标
                color:填充颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :无
 * @function   :绘制一个圆的边框
 * @parameters :xc:圆心的 x 坐标
                yc:圆心的 y 坐标
                color:圆的边框颜色
                r:圆的半径
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r);

/*****************************************************************************
 * @name       :void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :无
 * @function   :填充一个圆
 * @parameters :xc:圆心的 x 坐标
                yc:圆心的 y 坐标
                color:填充颜色
                r:圆的半径
 * @retvalue   :无
******************************************************************************/ 
void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r);

/*****************************************************************************
 * @name       :void GUI_DrawTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :无
 * @function   :绘制一个三角形的边框
 * @parameters :x0:第一个顶点的 x 坐标
                y0:第一个顶点的 y 坐标
                x1:第二个顶点的 x 坐标
                y1:第二个顶点的 y 坐标
                x2:第三个顶点的 x 坐标
                y2:第三个顶点的 y 坐标
                color:三角形边框颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_FillTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color)
 * @date       :无
 * @function   :填充一个三角形
 * @parameters :x0:第一个顶点的 x 坐标
                y0:第一个顶点的 y 坐标
                x1:第二个顶点的 x 坐标
                y1:第二个顶点的 y 坐标
                x2:第三个顶点的 x 坐标
                y2:第三个顶点的 y 坐标
                color:填充颜色
 * @retvalue   :无
******************************************************************************/ 
void GUI_FillTriangel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

/*****************************************************************************
 * @name       :void GUI_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t mode)
 * @date       :无
 * @function   :显示单个字符
 * @parameters :x:字符显示起始位置的 x 坐标
                y:字符显示起始位置的 y 坐标
                chr:要显示的字符
                Char_Size:字符大小
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode)
 * @date       :无
 * @function   :显示数字
 * @parameters :x:数字显示起始位置的 x 坐标
                y:数字显示起始位置的 y 坐标
                num:要显示的数字
                len:显示的位数
                Size:数字的大小
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode)
 * @date       :无
 * @function   :显示字符串
 * @parameters :x:字符串显示起始位置的 x 坐标
                y:字符串显示起始位置的 y 坐标
                chr:要显示的字符串
                Char_Size:字符大小
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont16(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :无
 * @function   :显示单个 16x16 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont16(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont24(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :无
 * @function   :显示单个 24x24 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont24(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowFont32(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode)
 * @date       :无
 * @function   :显示单个 32x32 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont32(uint8_t x, uint8_t y, uint8_t *s, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode)
 * @date       :无
 * @function   :显示汉字字符串
 * @parameters :x:汉字字符串显示起始位置的 x 坐标
                y:汉字字符串显示起始位置的 y 坐标
                hsize:汉字大小
                str:汉字字符串的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode);

/*****************************************************************************
 * @name       :void GUI_DrawBMP(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
 * @date       :无
 * @function   :显示单色 BMP 图片
 * @parameters :x:图片显示起始位置的 x 坐标
                y:图片显示起始位置的 y 坐标
                width:图片宽度
                height:图片高度
                BMP:图片数据的起始地址
                mode:0-白底黑图
                      1-黑底白图
 * @retvalue   :无
******************************************************************************/ 
void GUI_DrawBMP(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode);

#endif


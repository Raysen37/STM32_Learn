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
#include "oled.h"
#include "string.h"
#include "oledfont.h" 
//#include "delay.h"
#include "gui.h"
/*******************************************************************
 * @name       :void GUI_DrawPoint(uint8_t x,uint8_t y,uint8_t color)
 * @date       :2018-08-27
 * @function   :��LCD��Ļ�ϻ���һ����
 * @parameters :x:���x����
                y:���y����
                color:�����ɫֵ
                      1-��ɫ
                      0-��ɫ
 * @retvalue   :��
********************************************************************/
void GUI_DrawPoint(uint8_t x,uint8_t y,uint8_t color)
{
    OLED_Set_Pixel(x,y,color); // ����ָ����������ص���ɫ
    OLED_Display(); // ������ʾ
}

/*******************************************************************
 * @name       :void GUI_Fill(uint8_t sx,uint8_t sy,uint8_t ex,uint8_t ey,uint8_t color)
 * @date       :2018-08-27 
 * @function   :���ָ������
 * @parameters :sx:ָ���������ʼx����
                sy:ָ���������ʼy����
                ex:ָ������Ľ���x����
                ey:ָ������Ľ���y����
                color:�������ɫֵ
                      1-��ɫ
                      0-��ɫ
 * @retvalue   :��
********************************************************************/
void GUI_Fill(uint8_t sx,uint8_t sy,uint8_t ex,uint8_t ey,uint8_t color)
{  
    uint8_t i,j;            
    uint8_t width = ex - sx + 1; // �������Ŀ��
    uint8_t height = ey - sy + 1; // �������ĸ߶�
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            OLED_Set_Pixel(sx + j, sy + i, color); // ����ÿ�����ص���ɫ
        }       
    }
    OLED_Display(); // ������ʾ
}

/*******************************************************************
 * @name       :void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :������֮�����һ����
 * @parameters :x1:�ߵ���ʼx����
                y1:�ߵ���ʼy����
                x2:�ߵĽ���x����
                y2:�ߵĽ���y����
                color:�ߵ���ɫֵ
                      1-��ɫ
                      0-��ɫ
 * @retvalue   :��
********************************************************************/
void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    uint16_t t; 
    int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
    int incx, incy, uRow, uCol; 

    delta_x = x2 - x1; // ������������ 
    delta_y = y2 - y1; 
    uRow = x1; 
    uCol = y1; 

    // ���õ�������
    if(delta_x > 0) incx = 1; 
    else if(delta_x == 0) incx = 0; // ��ֱ�� 
    else { incx = -1; delta_x = -delta_x; } 

    if(delta_y > 0) incy = 1; 
    else if(delta_y == 0) incy = 0; // ˮƽ�� 
    else { incy = -1; delta_y = -delta_y; } 

    // ѡȡ��������������
    distance = (delta_x > delta_y) ? delta_x : delta_y; 

    for(t = 0; t <= distance + 1; t++) // ������� 
    { 
        OLED_Set_Pixel(uRow, uCol, color); // ���õ�ǰ�����ɫ
        xerr += delta_x; 
        yerr += delta_y; 
        if(xerr > distance) 
        { 
            xerr -= distance; 
            uRow += incx; 
        } 
        if(yerr > distance) 
        { 
            yerr -= distance; 
            uCol += incy; 
        } 
    }  
    OLED_Display(); // ������ʾ
} 

/*****************************************************************************
 * @name       :void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :���ƾ���
 * @parameters :x1:���ε���ʼx����
                y1:���ε���ʼy����
                x2:���εĽ���x����
                y2:���εĽ���y����
                color:���ε���ɫֵ
                      1-��ɫ
                      0-��ɫ
 * @retvalue   :��
******************************************************************************/
void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    GUI_DrawLine(x1, y1, x2, y1, color); // �ϱ�
    GUI_DrawLine(x1, y1, x1, y2, color); // ���
    GUI_DrawLine(x1, y2, x2, y2, color); // �±�
    GUI_DrawLine(x2, y1, x2, y2, color); // �ұ�
}  

/*****************************************************************************
 * @name       :void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27
 * @function   :������
 * @parameters :x1:�����ε���ʼx����
                y1:�����ε���ʼy����
                x2:�����εĽ���x����
                y2:�����εĽ���y����
                color:���ε���ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
******************************************************************************/  
void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    GUI_Fill(x1, y1, x2, y2, color); // ������亯��
}
 
/*****************************************************************************
 * @name       :static void _draw_circle_8(uint8_t xc, uint8_t yc, uint8_t x, uint8_t y, uint8_t color)
 * @date       :2018-08-27 
 * @function   :����8�Գ�Բ���ڲ����ã�
 * @parameters :xc:Բ�ĵ�x���� 
                yc:Բ�ĵ�y���� 
                x:���Բ�ĵ�x���� 
                y:���Բ�ĵ�y���� 
                color:Բ����ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
******************************************************************************/  
static void _draw_circle_8(uint8_t xc, uint8_t yc, uint8_t x, uint8_t y, uint8_t color)
{
    OLED_Set_Pixel(xc + x, yc + y, color); // ���ư˸��ԳƵ�
    OLED_Set_Pixel(xc - x, yc + y, color);
    OLED_Set_Pixel(xc + x, yc - y, color);
    OLED_Set_Pixel(xc - x, yc - y, color);
    OLED_Set_Pixel(xc + y, yc + x, color);
    OLED_Set_Pixel(xc - y, yc + x, color);
    OLED_Set_Pixel(xc + y, yc - x, color);
    OLED_Set_Pixel(xc - y, yc - x, color);
}

/*****************************************************************************
 * @name       :void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :2018-08-27
 * @function   :��ָ��λ�û���ָ����С��Բ
 * @parameters :xc:Բ�ĵ�x���� 
                yc:Բ�ĵ�y���� 
                r:Բ�İ뾶
                color:Բ����ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
******************************************************************************/  
void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
{
    int x = 0, y = r, d;
    d = 3 - 2 * r; // ��ʼ���߱���
    while (x <= y) 
    {
        _draw_circle_8(xc, yc, x, y, color); // ����Բ�ĶԳƵ�
        if (d < 0) 
        {
            d = d + 4 * x + 6; // ���¾��߱���
        }
        else 
        {
            d = d + 4 * (x - y) + 10;
            y--; // �뾶��С
        }
        x++; // x����
    }
    OLED_Display(); // ������ʾ
}

/*****************************************************************************
 * @name       :void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :2018-08-27
 * @function   :���ָ����С��Բ
 * @parameters :xc:Բ�ĵ�x���� 
                yc:Բ�ĵ�y���� 
                r:Բ�İ뾶
                color:Բ����ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
******************************************************************************/  
void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
{
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r; // ��ʼ���߱���
    while (x <= y) 
    {
        for (yi = x; yi <= y; yi++)
        {
            _draw_circle_8(xc, yc, x, yi, color); // �������ĶԳƵ�
        }
        if (d < 0) 
        {
            d = d + 4 * x + 6; // ���¾��߱���
        } 
        else 
        {
            d = d + 4 * (x - y) + 10;
            y--; // �뾶��С
        }
        x++; // x����
    }
    OLED_Display(); // ������ʾ
}

/**********************************************************************************
 * @name       :void GUI_DrawTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :��ָ��λ�û���һ��������
 * @parameters :x0:�����α�Ե����ʼx���� 
                y0:�����α�Ե����ʼy���� 
                x1:�����ζ����x����
                y1:�����ζ����y����
                x2:�����α�Ե�Ľ���x���� 
                y2:�����α�Ե�Ľ���y���� 
                color:�����ε���ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
***********************************************************************************/ 
void GUI_DrawTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    GUI_DrawLine(x0, y0, x1, y1, color); // ���������εı�
    GUI_DrawLine(x1, y1, x2, y2, color);
    GUI_DrawLine(x2, y2, x0, y0, color);
}

/*****************************************************************************
 * @name       :static void _swap(uint8_t *a, uint8_t *b)
 * @date       :2018-08-27
 * @function   :�������������ڲ����ã�
 * @parameters :a:��һ�����ĵ�ַ 
                b:�ڶ������ĵ�ַ
 * @retvalue   :��
******************************************************************************/  
static void _swap(uint8_t *a, uint8_t *b)
{
    uint16_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp; // ����ֵ
}

/*****************************************************************************
 * @name       :static void _draw_h_line(uint8_t x0,uint8_t x1,uint8_t y,uint8_t color)
 * @date       :2018-08-27
 * @function   :��RAM�л���ˮƽ�ߣ��ڲ����ã�
 * @parameters :x0:ˮƽ�ߵ���ʼx����
                x1:ˮƽ�ߵĽ���x����
                y:ˮƽ�ߵ�y����
                color:ˮƽ�ߵ���ɫֵ
                      1-��ɫ
                      0-��ɫ	
 * @retvalue   :��
******************************************************************************/
static void _draw_h_line(uint8_t x0,uint8_t x1,uint8_t y,uint8_t color)
{
    uint8_t i = 0;
    for(i = x0; i <= x1; i++)
    {
        OLED_Set_Pixel(i, y, color); // ����ˮƽ��ÿ�������ɫ
    }
}

/*****************************************************************************
 * @name       :void GUI_FillTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :��ָ��λ�����������
 * @parameters :x0:�����α�Ե��ʼ��� x ���� 
                y0:�����α�Ե��ʼ��� y ���� 
                x1:�����ζ���� x ���� 
                y1:�����ζ���� y ���� 
                x2:�����α�Ե������� x ���� 
                y2:�����α�Ե������� y ���� 
                color:�����ɫֵ��1-��ɫ��0-��ɫ�� 
 * @retvalue   :��
******************************************************************************/ 
void GUI_FillTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    uint8_t a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0; // ��01���ۼ���
    long sb = 0; // ��02���ۼ���

    // ȷ�� y0 <= y1 <= y2
    if (y0 > y1) 
    {
        _swap(&y0, &y1); 
        _swap(&x0, &x1);
    }
    if (y1 > y2) 
    {
        _swap(&y2, &y1); 
        _swap(&x2, &x1);
    }
    if (y0 > y1) 
    {
        _swap(&y0, &y1); 
        _swap(&x0, &x1);
    }

    // ����ƽ���� x ������
    if (y0 == y2) 
    { 
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        _draw_h_line(a, b, y0, color); // ����ˮƽ��
        return;
    }

    // ����ߵ�����
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    // ȷ�����һ�е� y ֵ
    if (y1 == y2)
    {
        last = y1; 
    }
    else
    {
        last = y1 - 1; 
    }

    // �� y0 �� last ���������ε��ϰ벿��
    for (y = y0; y <= last; y++) 
    {
        a = x0 + sa / dy01; // ���� x ����
        b = x0 + sb / dy02; // ���� x ����
        sa += dx01; // �����ۼ���
        sb += dx02; // �����ۼ���
        if (a > b)
        {
            _swap(&a, &b); // ȷ�� a <= b
        }
        _draw_h_line(a, b, y, color); // ����ˮƽ��
    }

    sa = dx12 * (y - y1); // ��ʼ���ۼ���
    sb = dx02 * (y - y0); // ��ʼ���ۼ���

    // �� last+1 �� y2 ���������ε��°벿��
    for (; y <= y2; y++) 
    {
        a = x1 + sa / dy12; // ���� x ����
        b = x0 + sb / dy02; // ���� x ����
        sa += dx12; // �����ۼ���
        sb += dx02; // �����ۼ���
        if (a > b)
        {
            _swap(&a, &b); // ȷ�� a <= b
        }
        _draw_h_line(a, b, y, color); // ����ˮƽ��
    }

    OLED_Display(); // ˢ����ʾ
}

/*****************************************************************************
 * @name       :void GUI_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ����Ӣ���ַ�
 * @parameters :x:�ַ���ʾλ�õ� x ����
                y:�ַ���ʾλ�õ� y ����
                chr:Ҫ��ʾ���ַ��� ASCII �루0~94��
                Char_Size:�ַ�����ʾ��С��8 �� 16��
                mode:��ʾģʽ��0-�׵׺��֣�1-�ڵװ��֣�
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
{      	
    unsigned char c = 0, i = 0, tmp, j = 0;	
    c = chr - ' '; // ����ƫ��ֵ
    if (x > WIDTH - 1) { x = 0; y = y + 2; } // �����߽紦��

    if (Char_Size == 16)
    {
        for (i = 0; i < 16; i++)
        {
            // ����ģʽѡ���ַ�����ɫ
            if (mode) {
                tmp = F8X16[c * 16 + i];
            } else {
                tmp = ~(F8X16[c * 16 + i]);
            }
            for (j = 0; j < 8; j++)
            {
                // �������ص�
                if (tmp & (0x80 >> j))
                {
                    OLED_Set_Pixel(x + j, y + i, 1); // ����Ϊ��ɫ
                }
                else
                {
                    OLED_Set_Pixel(x + j, y + i, 0); // ����Ϊ��ɫ
                }
            }
        }
    }
    else if (Char_Size == 8)
    {	
        for (i = 0; i < 8; i++)
        {
            if (mode) {
                tmp = F6x8[c][i];
            } else {
                tmp = ~(F6x8[c][i]);
            }
            for (j = 0; j < 8; j++)
            {
                if (tmp & (0x80 >> j))
                {
                    OLED_Set_Pixel(x + j, y + i, 1); // ����Ϊ��ɫ
                }
                else
                {
                    OLED_Set_Pixel(x + j, y + i, 0); // ����Ϊ��ɫ
                }
            }
        }
    }
    else
    {
        return; // ��Ч�ַ���С����
    }
    OLED_Display(); // ˢ����ʾ
}

/*****************************************************************************
 * @name       :void GUI_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾӢ���ַ���
 * @parameters :x:�ַ�����ʼλ�õ� x ����
                y:�ַ�����ʼλ�õ� y ����
                chr:�ַ�������ʼ��ַ
                Char_Size:�ַ�����ʾ��С
                mode:��ʾģʽ
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode)
{
    unsigned char j = 0, csize;
    if (Char_Size == 16)
    {
        csize = Char_Size / 2; // ÿ���ַ��Ŀ��
    }
    else if (Char_Size == 8)
    {
        csize = Char_Size / 2 + 2; // ÿ���ַ��Ŀ��
    }
    else
    {
        return; // ��Ч�ַ���С����
    }

    // ѭ����ʾ�ַ����е�ÿ���ַ�
    while (chr[j] != '\0')
    {		
        GUI_ShowChar(x, y, chr[j], Char_Size, mode);
        x += csize; // ���� x ����
        if (x > 120) // �����߽紦��
        {
            x = 0; // ����
            y += Char_Size;
        }
        j++;
    }
}

/*****************************************************************************
 * @name       :u32 mypow(uint8_t m,uint8_t n)
 * @date       :2018-08-27 
 * @function   :���� m �� n �η����ڲ����ã�
 * @parameters :m:����
                n:ָ��
 * @retvalue   :m �� n �η�ֵ
******************************************************************************/ 
static uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;	 
    while (n--) result *= m; // ������
    return result; // ���ؽ��
}

/*****************************************************************************
 * @name       :void GUI_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ����
 * @parameters :x:������ʾλ�õ� x ����
                y:������ʾλ�õ� y ����
                num:Ҫ��ʾ�����֣�0~4294967295��
                len:��ʾ���ֵĳ���
                Size:��ʾ���ֵĴ�С
                mode:��ʾģʽ��0-�׵׺��֣�1-�ڵװ��֣�
 * @retvalue   :��
******************************************************************************/  			 
void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode)
{         	
    uint8_t t, temp;
    uint8_t enshow = 0, csize;
    if (Size == 16)
    {
        csize = Size / 2; // ÿ�����ֵĿ��
    }
    else if (Size == 8)
    {
        csize = Size / 2 + 2; // ÿ�����ֵĿ��
    } 	
    else
    {
        return; // ��Ч���ִ�С����
    }

    // ѭ����ʾÿһλ����
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10; // ȡ��ǰλ������
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                GUI_ShowChar(x + csize * t, y, ' ', Size, mode); // ��ʾ�ո�
                continue;
            } 
            else enshow = 1; // ��ʼ��ʾ����
        }
        GUI_ShowChar(x + csize * t, y, temp + '0', Size, mode); // ��ʾ��ǰ����
    }
}  
/*****************************************************************************
 * @name       :void GUI_ShowFont16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ���� 16x16 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont16) / sizeof(typFNT_GB16); // ��ȡ�����ֿ��С
    
    for (i = 0; i < num; i++)
    {
        // ����Ƿ��ҵ��˶�Ӧ�ĺ���
        if ((cfont16[i].Index[0] == *s) && (cfont16[i].Index[1] == *(s + 1)))
        {
            // �������ε�ÿһ��
            for (j = 0; j < 32; j++)
            {
                // ����ģʽѡ����ɫ
                if (mode)
                {
                    tmp = cfont16[i].Msk[j]; // ֱ��ȡ����
                }
                else
                {
                    tmp = ~(cfont16[i].Msk[j]); // ��ɫ����
                }
                // �������ε�ÿһ��
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2, 1); // ����Ϊ��ɫ
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2, 0); // ����Ϊ��ɫ
                    }
                }
            }
            break; // �ҵ����ֺ��˳�ѭ��
        }
    }
    OLED_Display(); // ˢ����ʾ
}

/*****************************************************************************
 * @name       :void GUI_ShowFont24(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ���� 24x24 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont24(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont24) / sizeof(typFNT_GB24); // ��ȡ�����ֿ��С
    
    for (i = 0; i < num; i++)
    {
        // ����Ƿ��ҵ��˶�Ӧ�ĺ���
        if ((cfont24[i].Index[0] == *s) && (cfont24[i].Index[1] == *(s + 1)))
        {
            // �������ε�ÿһ��
            for (j = 0; j < 72; j++)
            {
                if (mode)
                {
                    tmp = cfont24[i].Msk[j]; // ֱ��ȡ����
                }
                else
                {
                    tmp = ~(cfont24[i].Msk[j]); // ��ɫ����
                }
                // �������ε�ÿһ��
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 3) * 8 + k, y + j / 3, 1); // ����Ϊ��ɫ
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 3) * 8 + k, y + j / 3, 0); // ����Ϊ��ɫ
                    }
                }
            }
            break; // �ҵ����ֺ��˳�ѭ��
        }
    }
    OLED_Display(); // ˢ����ʾ
}

/*****************************************************************************
 * @name       :void GUI_ShowFont32(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ���� 32x32 �ĺ���
 * @parameters :x:������ʾ��ʼλ�õ� x ����
                y:������ʾ��ʼλ�õ� y ����
                s:���ֵ���ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_ShowFont32(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont32) / sizeof(typFNT_GB32); // ��ȡ�����ֿ��С
    
    for (i = 0; i < num; i++)
    {
        // ����Ƿ��ҵ��˶�Ӧ�ĺ���
        if ((cfont32[i].Index[0] == *s) && (cfont32[i].Index[1] == *(s + 1)))
        {
            // �������ε�ÿһ��
            for (j = 0; j < 128; j++)
            {
                if (mode)
                {
                    tmp = cfont32[i].Msk[j]; // ֱ��ȡ����
                }
                else
                {
                    tmp = ~(cfont32[i].Msk[j]); // ��ɫ����
                }
                // �������ε�ÿһ��
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 4) * 8 + k, y + j / 4, 1); // ����Ϊ��ɫ
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 4) * 8 + k, y + j / 4, 0); // ����Ϊ��ɫ
                    }
                }
            }
            break; // �ҵ����ֺ��˳�ѭ��
        }
    }
    OLED_Display(); // ˢ����ʾ
}

/*****************************************************************************
 * @name       :void GUI_ShowCHinese(uint8_t x,uint8_t y,uint8_t hsize,uint8_t *str,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ�����ַ���
 * @parameters :x:�����ַ�����ʼλ�õ� x ����
                y:�����ַ�����ʼλ�õ� y ����
                hsize:���ֵĴ�С
                str:�����ַ�������ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/   
void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode)
{
    while (*str != '\0') // ֱ���ַ�������
    {
        // ���ݴ�Сѡ����Ӧ����ʾ����
        if (hsize == 16)
        {
            GUI_ShowFont16(x, y, str, mode);
        }
        else if (hsize == 24)
        {
            GUI_ShowFont24(x, y, str, mode);
        }
        else if (hsize == 32)
        {
            GUI_ShowFont32(x, y, str, mode);
        }
        else
        {
            return; // ��Ч��С����
        }
        x += hsize; // ���� x ����
        if (x > WIDTH - hsize) // �����߽紦��
        {
            x = 0; // ����
            y += hsize;
        }
        str += 2; // �ƶ�����һ������
    }
}

/*****************************************************************************
 * @name       :void GUI_DrawBMP(uint8_t x,uint8_t y,uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
 * @date       :2018-08-27 
 * @function   :��ʾ BMP ��ɫͼƬ
 * @parameters :x:��ɫͼƬ��ʾ��ʼλ�õ� x ����
                y:��ɫͼƬ��ʾ��ʼλ�õ� y ����
                width:��ɫͼƬ�Ŀ��
                height:��ɫͼƬ�ĸ߶�
                BMP:��ɫͼƬ�������ʼ��ַ
                mode:0-�׵׺���
                      1-�ڵװ���
 * @retvalue   :��
******************************************************************************/ 
void GUI_DrawBMP(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
{
    uint8_t i, j, k;
    uint8_t tmp;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < (width + 7) / 8; j++)
        {
            if (mode)
            {
                tmp = BMP[i * ((width + 7) / 8) + j]; // ֱ��ȡ����
            }
            else
            {
                tmp = ~BMP[i * ((width + 7) / 8) + j]; // ��ɫ����
            }
            for (k = 0; k < 8; k++)
            {
                if (tmp & (0x80 >> k))
                {
                    OLED_Set_Pixel(x + j * 8 + k, y + i, 1); // ����Ϊ��ɫ
                }
                else
                {
                    OLED_Set_Pixel(x + j * 8 + k, y + i, 0); // ����Ϊ��ɫ
                }
            }
        }
    }
    OLED_Display(); // ˢ����ʾ
}

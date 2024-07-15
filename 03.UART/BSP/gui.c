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
#include "oled.h"
#include "string.h"
#include "oledfont.h" 
//#include "delay.h"
#include "gui.h"
/*******************************************************************
 * @name       :void GUI_DrawPoint(uint8_t x,uint8_t y,uint8_t color)
 * @date       :2018-08-27
 * @function   :在LCD屏幕上绘制一个点
 * @parameters :x:点的x坐标
                y:点的y坐标
                color:点的颜色值
                      1-白色
                      0-黑色
 * @retvalue   :无
********************************************************************/
void GUI_DrawPoint(uint8_t x,uint8_t y,uint8_t color)
{
    OLED_Set_Pixel(x,y,color); // 设置指定坐标的像素点颜色
    OLED_Display(); // 更新显示
}

/*******************************************************************
 * @name       :void GUI_Fill(uint8_t sx,uint8_t sy,uint8_t ex,uint8_t ey,uint8_t color)
 * @date       :2018-08-27 
 * @function   :填充指定区域
 * @parameters :sx:指定区域的起始x坐标
                sy:指定区域的起始y坐标
                ex:指定区域的结束x坐标
                ey:指定区域的结束y坐标
                color:区域的颜色值
                      1-白色
                      0-黑色
 * @retvalue   :无
********************************************************************/
void GUI_Fill(uint8_t sx,uint8_t sy,uint8_t ex,uint8_t ey,uint8_t color)
{  
    uint8_t i,j;            
    uint8_t width = ex - sx + 1; // 计算填充的宽度
    uint8_t height = ey - sy + 1; // 计算填充的高度
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            OLED_Set_Pixel(sx + j, sy + i, color); // 设置每个像素的颜色
        }       
    }
    OLED_Display(); // 更新显示
}

/*******************************************************************
 * @name       :void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :在两点之间绘制一条线
 * @parameters :x1:线的起始x坐标
                y1:线的起始y坐标
                x2:线的结束x坐标
                y2:线的结束y坐标
                color:线的颜色值
                      1-白色
                      0-黑色
 * @retvalue   :无
********************************************************************/
void GUI_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    uint16_t t; 
    int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
    int incx, incy, uRow, uCol; 

    delta_x = x2 - x1; // 计算坐标增量 
    delta_y = y2 - y1; 
    uRow = x1; 
    uCol = y1; 

    // 设置单步方向
    if(delta_x > 0) incx = 1; 
    else if(delta_x == 0) incx = 0; // 垂直线 
    else { incx = -1; delta_x = -delta_x; } 

    if(delta_y > 0) incy = 1; 
    else if(delta_y == 0) incy = 0; // 水平线 
    else { incy = -1; delta_y = -delta_y; } 

    // 选取基本增量坐标轴
    distance = (delta_x > delta_y) ? delta_x : delta_y; 

    for(t = 0; t <= distance + 1; t++) // 画线输出 
    { 
        OLED_Set_Pixel(uRow, uCol, color); // 设置当前点的颜色
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
    OLED_Display(); // 更新显示
} 

/*****************************************************************************
 * @name       :void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :绘制矩形
 * @parameters :x1:矩形的起始x坐标
                y1:矩形的起始y坐标
                x2:矩形的结束x坐标
                y2:矩形的结束y坐标
                color:矩形的颜色值
                      1-白色
                      0-黑色
 * @retvalue   :无
******************************************************************************/
void GUI_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    GUI_DrawLine(x1, y1, x2, y1, color); // 上边
    GUI_DrawLine(x1, y1, x1, y2, color); // 左边
    GUI_DrawLine(x1, y2, x2, y2, color); // 下边
    GUI_DrawLine(x2, y1, x2, y2, color); // 右边
}  

/*****************************************************************************
 * @name       :void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
 * @date       :2018-08-27
 * @function   :填充矩形
 * @parameters :x1:填充矩形的起始x坐标
                y1:填充矩形的起始y坐标
                x2:填充矩形的结束x坐标
                y2:填充矩形的结束y坐标
                color:矩形的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
******************************************************************************/  
void GUI_FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
    GUI_Fill(x1, y1, x2, y2, color); // 调用填充函数
}
 
/*****************************************************************************
 * @name       :static void _draw_circle_8(uint8_t xc, uint8_t yc, uint8_t x, uint8_t y, uint8_t color)
 * @date       :2018-08-27 
 * @function   :绘制8对称圆（内部调用）
 * @parameters :xc:圆心的x坐标 
                yc:圆心的y坐标 
                x:相对圆心的x坐标 
                y:相对圆心的y坐标 
                color:圆的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
******************************************************************************/  
static void _draw_circle_8(uint8_t xc, uint8_t yc, uint8_t x, uint8_t y, uint8_t color)
{
    OLED_Set_Pixel(xc + x, yc + y, color); // 绘制八个对称点
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
 * @function   :在指定位置绘制指定大小的圆
 * @parameters :xc:圆心的x坐标 
                yc:圆心的y坐标 
                r:圆的半径
                color:圆的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
******************************************************************************/  
void GUI_DrawCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
{
    int x = 0, y = r, d;
    d = 3 - 2 * r; // 初始决策变量
    while (x <= y) 
    {
        _draw_circle_8(xc, yc, x, y, color); // 绘制圆的对称点
        if (d < 0) 
        {
            d = d + 4 * x + 6; // 更新决策变量
        }
        else 
        {
            d = d + 4 * (x - y) + 10;
            y--; // 半径减小
        }
        x++; // x增大
    }
    OLED_Display(); // 更新显示
}

/*****************************************************************************
 * @name       :void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
 * @date       :2018-08-27
 * @function   :填充指定大小的圆
 * @parameters :xc:圆心的x坐标 
                yc:圆心的y坐标 
                r:圆的半径
                color:圆的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
******************************************************************************/  
void GUI_FillCircle(uint8_t xc, uint8_t yc, uint8_t color, uint8_t r)
{
    int x = 0, y = r, yi, d;
    d = 3 - 2 * r; // 初始决策变量
    while (x <= y) 
    {
        for (yi = x; yi <= y; yi++)
        {
            _draw_circle_8(xc, yc, x, yi, color); // 绘制填充的对称点
        }
        if (d < 0) 
        {
            d = d + 4 * x + 6; // 更新决策变量
        } 
        else 
        {
            d = d + 4 * (x - y) + 10;
            y--; // 半径减小
        }
        x++; // x增大
    }
    OLED_Display(); // 更新显示
}

/**********************************************************************************
 * @name       :void GUI_DrawTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :在指定位置绘制一个三角形
 * @parameters :x0:三角形边缘的起始x坐标 
                y0:三角形边缘的起始y坐标 
                x1:三角形顶点的x坐标
                y1:三角形顶点的y坐标
                x2:三角形边缘的结束x坐标 
                y2:三角形边缘的结束y坐标 
                color:三角形的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
***********************************************************************************/ 
void GUI_DrawTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    GUI_DrawLine(x0, y0, x1, y1, color); // 绘制三角形的边
    GUI_DrawLine(x1, y1, x2, y2, color);
    GUI_DrawLine(x2, y2, x0, y0, color);
}

/*****************************************************************************
 * @name       :static void _swap(uint8_t *a, uint8_t *b)
 * @date       :2018-08-27
 * @function   :交换两个数（内部调用）
 * @parameters :a:第一个数的地址 
                b:第二个数的地址
 * @retvalue   :无
******************************************************************************/  
static void _swap(uint8_t *a, uint8_t *b)
{
    uint16_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp; // 交换值
}

/*****************************************************************************
 * @name       :static void _draw_h_line(uint8_t x0,uint8_t x1,uint8_t y,uint8_t color)
 * @date       :2018-08-27
 * @function   :在RAM中绘制水平线（内部调用）
 * @parameters :x0:水平线的起始x坐标
                x1:水平线的结束x坐标
                y:水平线的y坐标
                color:水平线的颜色值
                      1-白色
                      0-黑色	
 * @retvalue   :无
******************************************************************************/
static void _draw_h_line(uint8_t x0,uint8_t x1,uint8_t y,uint8_t color)
{
    uint8_t i = 0;
    for(i = x0; i <= x1; i++)
    {
        OLED_Set_Pixel(i, y, color); // 设置水平线每个点的颜色
    }
}

/*****************************************************************************
 * @name       :void GUI_FillTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
 * @date       :2018-08-27 
 * @function   :在指定位置填充三角形
 * @parameters :x0:三角形边缘起始点的 x 坐标 
                y0:三角形边缘起始点的 y 坐标 
                x1:三角形顶点的 x 坐标 
                y1:三角形顶点的 y 坐标 
                x2:三角形边缘结束点的 x 坐标 
                y2:三角形边缘结束点的 y 坐标 
                color:填充颜色值（1-白色，0-黑色） 
 * @retvalue   :无
******************************************************************************/ 
void GUI_FillTriangel(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
    uint8_t a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0; // 边01的累加器
    long sb = 0; // 边02的累加器

    // 确保 y0 <= y1 <= y2
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

    // 处理平行于 x 轴的情况
    if (y0 == y2) 
    { 
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        _draw_h_line(a, b, y0, color); // 绘制水平线
        return;
    }

    // 计算边的增量
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    // 确定最后一行的 y 值
    if (y1 == y2)
    {
        last = y1; 
    }
    else
    {
        last = y1 - 1; 
    }

    // 从 y0 到 last 绘制三角形的上半部分
    for (y = y0; y <= last; y++) 
    {
        a = x0 + sa / dy01; // 计算 x 坐标
        b = x0 + sb / dy02; // 计算 x 坐标
        sa += dx01; // 更新累加器
        sb += dx02; // 更新累加器
        if (a > b)
        {
            _swap(&a, &b); // 确保 a <= b
        }
        _draw_h_line(a, b, y, color); // 绘制水平线
    }

    sa = dx12 * (y - y1); // 初始化累加器
    sb = dx02 * (y - y0); // 初始化累加器

    // 从 last+1 到 y2 绘制三角形的下半部分
    for (; y <= y2; y++) 
    {
        a = x1 + sa / dy12; // 计算 x 坐标
        b = x0 + sb / dy02; // 计算 x 坐标
        sa += dx12; // 更新累加器
        sb += dx02; // 更新累加器
        if (a > b)
        {
            _swap(&a, &b); // 确保 a <= b
        }
        _draw_h_line(a, b, y, color); // 绘制水平线
    }

    OLED_Display(); // 刷新显示
}

/*****************************************************************************
 * @name       :void GUI_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示单个英文字符
 * @parameters :x:字符显示位置的 x 坐标
                y:字符显示位置的 y 坐标
                chr:要显示的字符的 ASCII 码（0~94）
                Char_Size:字符的显示大小（8 或 16）
                mode:显示模式（0-白底黑字，1-黑底白字）
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode)
{      	
    unsigned char c = 0, i = 0, tmp, j = 0;	
    c = chr - ' '; // 计算偏移值
    if (x > WIDTH - 1) { x = 0; y = y + 2; } // 超出边界处理

    if (Char_Size == 16)
    {
        for (i = 0; i < 16; i++)
        {
            // 根据模式选择字符的颜色
            if (mode) {
                tmp = F8X16[c * 16 + i];
            } else {
                tmp = ~(F8X16[c * 16 + i]);
            }
            for (j = 0; j < 8; j++)
            {
                // 设置像素点
                if (tmp & (0x80 >> j))
                {
                    OLED_Set_Pixel(x + j, y + i, 1); // 设置为白色
                }
                else
                {
                    OLED_Set_Pixel(x + j, y + i, 0); // 设置为黑色
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
                    OLED_Set_Pixel(x + j, y + i, 1); // 设置为白色
                }
                else
                {
                    OLED_Set_Pixel(x + j, y + i, 0); // 设置为黑色
                }
            }
        }
    }
    else
    {
        return; // 无效字符大小处理
    }
    OLED_Display(); // 刷新显示
}

/*****************************************************************************
 * @name       :void GUI_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示英文字符串
 * @parameters :x:字符串起始位置的 x 坐标
                y:字符串起始位置的 y 坐标
                chr:字符串的起始地址
                Char_Size:字符的显示大小
                mode:显示模式
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size, uint8_t mode)
{
    unsigned char j = 0, csize;
    if (Char_Size == 16)
    {
        csize = Char_Size / 2; // 每个字符的宽度
    }
    else if (Char_Size == 8)
    {
        csize = Char_Size / 2 + 2; // 每个字符的宽度
    }
    else
    {
        return; // 无效字符大小处理
    }

    // 循环显示字符串中的每个字符
    while (chr[j] != '\0')
    {		
        GUI_ShowChar(x, y, chr[j], Char_Size, mode);
        x += csize; // 更新 x 坐标
        if (x > 120) // 超出边界处理
        {
            x = 0; // 换行
            y += Char_Size;
        }
        j++;
    }
}

/*****************************************************************************
 * @name       :u32 mypow(uint8_t m,uint8_t n)
 * @date       :2018-08-27 
 * @function   :计算 m 的 n 次方（内部调用）
 * @parameters :m:基数
                n:指数
 * @retvalue   :m 的 n 次方值
******************************************************************************/ 
static uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;	 
    while (n--) result *= m; // 计算幂
    return result; // 返回结果
}

/*****************************************************************************
 * @name       :void GUI_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t Size,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示数字
 * @parameters :x:数字显示位置的 x 坐标
                y:数字显示位置的 y 坐标
                num:要显示的数字（0~4294967295）
                len:显示数字的长度
                Size:显示数字的大小
                mode:显示模式（0-白底黑字，1-黑底白字）
 * @retvalue   :无
******************************************************************************/  			 
void GUI_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t Size, uint8_t mode)
{         	
    uint8_t t, temp;
    uint8_t enshow = 0, csize;
    if (Size == 16)
    {
        csize = Size / 2; // 每个数字的宽度
    }
    else if (Size == 8)
    {
        csize = Size / 2 + 2; // 每个数字的宽度
    } 	
    else
    {
        return; // 无效数字大小处理
    }

    // 循环显示每一位数字
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10; // 取当前位的数字
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                GUI_ShowChar(x + csize * t, y, ' ', Size, mode); // 显示空格
                continue;
            } 
            else enshow = 1; // 开始显示数字
        }
        GUI_ShowChar(x + csize * t, y, temp + '0', Size, mode); // 显示当前数字
    }
}  
/*****************************************************************************
 * @name       :void GUI_ShowFont16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示单个 16x16 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont16(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont16) / sizeof(typFNT_GB16); // 获取汉字字库大小
    
    for (i = 0; i < num; i++)
    {
        // 检查是否找到了对应的汉字
        if ((cfont16[i].Index[0] == *s) && (cfont16[i].Index[1] == *(s + 1)))
        {
            // 遍历字形的每一行
            for (j = 0; j < 32; j++)
            {
                // 根据模式选择颜色
                if (mode)
                {
                    tmp = cfont16[i].Msk[j]; // 直接取字形
                }
                else
                {
                    tmp = ~(cfont16[i].Msk[j]); // 反色处理
                }
                // 遍历字形的每一列
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2, 1); // 设置为白色
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 2) * 8 + k, y + j / 2, 0); // 设置为黑色
                    }
                }
            }
            break; // 找到汉字后退出循环
        }
    }
    OLED_Display(); // 刷新显示
}

/*****************************************************************************
 * @name       :void GUI_ShowFont24(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示单个 24x24 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont24(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont24) / sizeof(typFNT_GB24); // 获取汉字字库大小
    
    for (i = 0; i < num; i++)
    {
        // 检查是否找到了对应的汉字
        if ((cfont24[i].Index[0] == *s) && (cfont24[i].Index[1] == *(s + 1)))
        {
            // 遍历字形的每一行
            for (j = 0; j < 72; j++)
            {
                if (mode)
                {
                    tmp = cfont24[i].Msk[j]; // 直接取字形
                }
                else
                {
                    tmp = ~(cfont24[i].Msk[j]); // 反色处理
                }
                // 遍历字形的每一列
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 3) * 8 + k, y + j / 3, 1); // 设置为白色
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 3) * 8 + k, y + j / 3, 0); // 设置为黑色
                    }
                }
            }
            break; // 找到汉字后退出循环
        }
    }
    OLED_Display(); // 刷新显示
}

/*****************************************************************************
 * @name       :void GUI_ShowFont32(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示单个 32x32 的汉字
 * @parameters :x:汉字显示起始位置的 x 坐标
                y:汉字显示起始位置的 y 坐标
                s:汉字的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/ 
void GUI_ShowFont32(uint8_t x,uint8_t y,uint8_t *s,uint8_t mode)
{
    uint8_t i, j, k, tmp;
    uint16_t num;
    num = sizeof(cfont32) / sizeof(typFNT_GB32); // 获取汉字字库大小
    
    for (i = 0; i < num; i++)
    {
        // 检查是否找到了对应的汉字
        if ((cfont32[i].Index[0] == *s) && (cfont32[i].Index[1] == *(s + 1)))
        {
            // 遍历字形的每一行
            for (j = 0; j < 128; j++)
            {
                if (mode)
                {
                    tmp = cfont32[i].Msk[j]; // 直接取字形
                }
                else
                {
                    tmp = ~(cfont32[i].Msk[j]); // 反色处理
                }
                // 遍历字形的每一列
                for (k = 0; k < 8; k++)
                {
                    if (tmp & (0x80 >> k))
                    {
                        OLED_Set_Pixel(x + (j % 4) * 8 + k, y + j / 4, 1); // 设置为白色
                    }
                    else
                    {
                        OLED_Set_Pixel(x + (j % 4) * 8 + k, y + j / 4, 0); // 设置为黑色
                    }
                }
            }
            break; // 找到汉字后退出循环
        }
    }
    OLED_Display(); // 刷新显示
}

/*****************************************************************************
 * @name       :void GUI_ShowCHinese(uint8_t x,uint8_t y,uint8_t hsize,uint8_t *str,uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示汉字字符串
 * @parameters :x:汉字字符串起始位置的 x 坐标
                y:汉字字符串起始位置的 y 坐标
                hsize:汉字的大小
                str:汉字字符串的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
******************************************************************************/   
void GUI_ShowCHinese(uint8_t x, uint8_t y, uint8_t hsize, uint8_t *str, uint8_t mode)
{
    while (*str != '\0') // 直到字符串结束
    {
        // 根据大小选择相应的显示函数
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
            return; // 无效大小处理
        }
        x += hsize; // 更新 x 坐标
        if (x > WIDTH - hsize) // 超出边界处理
        {
            x = 0; // 换行
            y += hsize;
        }
        str += 2; // 移动到下一个汉字
    }
}

/*****************************************************************************
 * @name       :void GUI_DrawBMP(uint8_t x,uint8_t y,uint8_t width, uint8_t height, uint8_t BMP[], uint8_t mode)
 * @date       :2018-08-27 
 * @function   :显示 BMP 单色图片
 * @parameters :x:单色图片显示起始位置的 x 坐标
                y:单色图片显示起始位置的 y 坐标
                width:单色图片的宽度
                height:单色图片的高度
                BMP:单色图片数组的起始地址
                mode:0-白底黑字
                      1-黑底白字
 * @retvalue   :无
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
                tmp = BMP[i * ((width + 7) / 8) + j]; // 直接取像素
            }
            else
            {
                tmp = ~BMP[i * ((width + 7) / 8) + j]; // 反色处理
            }
            for (k = 0; k < 8; k++)
            {
                if (tmp & (0x80 >> k))
                {
                    OLED_Set_Pixel(x + j * 8 + k, y + i, 1); // 设置为白色
                }
                else
                {
                    OLED_Set_Pixel(x + j * 8 + k, y + i, 0); // 设置为黑色
                }
            }
        }
    }
    OLED_Display(); // 刷新显示
}

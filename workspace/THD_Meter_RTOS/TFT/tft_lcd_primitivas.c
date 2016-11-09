/*
 * lcd_primitivas.c
 *
 *  Created on: 04/10/2014
 *      Author: fede
 */


#include "header.h"
#include "tft_header_priv.h"



void tft_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	tft_SendCommand_priv(ILI9341_COLUMN_ADDR);
	tft_SendData_priv(x1 >> 8);
	tft_SendData_priv(x1 & 0xFF);
	tft_SendData_priv(x2 >> 8);
	tft_SendData_priv(x2 & 0xFF);

	tft_SendCommand_priv(ILI9341_PAGE_ADDR);
	tft_SendData_priv(y1 >> 8);
	tft_SendData_priv(y1 & 0xFF);
	tft_SendData_priv(y2 >> 8);
	tft_SendData_priv(y2 & 0xFF);
}

void tft_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	tft_SetCursorPosition(x, y, x, y);

	tft_SendCommand_priv(ILI9341_GRAM);
	tft_SendData_priv(color);
}

void tft_Fill(uint16_t color)
{
	tft_SetCursorPosition(0, 0, tft_Opts.width - 1, tft_Opts.height - 1);

	tft_SendCommand_priv(ILI9341_GRAM);

	for (int n = 0; n < TFT_PIXEL; n++)
	{
		tft_SendData_priv(color);
	}
}


void tft_Rotate(tft_Orientation orientation)
{
	tft_SendCommand_priv(ILI9341_MAC);

	if (orientation == TFT_ORIENTATION_PORTRAIT_1)
	{
		tft_SendData_priv(0x58);
	}
	else if (orientation == TFT_ORIENTATION_PORTRAIT_2)
	{
		tft_SendData_priv(0x88);
	}
	else if (orientation == TFT_ORIENTATION_LANDSCAPE_1)
	{
		tft_SendData_priv(0x28);
	}
	else if (orientation == TFT_ORIENTATION_LANDSCAPE_2)
	{
		tft_SendData_priv(0xE8);
	}

	if (orientation == TFT_ORIENTATION_PORTRAIT_1 || orientation == TFT_ORIENTATION_PORTRAIT_2)
	{
		tft_Opts.width = TFT_WIDTH;
		tft_Opts.height = TFT_HEIGHT;
		tft_Opts.orientation = TFT_ORIENTATION_PORTRAIT;
	}
	else
	{
		tft_Opts.width = TFT_HEIGHT;
		tft_Opts.height = TFT_WIDTH;
		tft_Opts.orientation = TFT_ORIENTATION_LANDSCAPE;
	}
}

static void tft_Putc(uint16_t x, uint16_t y, char c, tft_font_t *font, uint16_t foreground, uint16_t background)
{
	uint32_t i, b, j;

		// Set coordinates
	tft_x = x;
	tft_y = y;

	if ((tft_x + font->FontWidth) > tft_Opts.width)
	{
		//If at the end of a line of display, go to new line and set x to 0 position
		tft_y += font->FontHeight;
		tft_x = 0;
	}
	for (i = 0; i < font->FontHeight; i++)
	{
		b = font->data[(c - 32) * font->FontHeight + i];
		for (j = 0; j < font->FontWidth; j++)
		{
			if ((b << j) & 0x8000)
			{
				tft_DrawPixel(tft_x + j, (tft_y + i), foreground);
			}
			else
			{
				tft_DrawPixel(tft_x + j, (tft_y + i), background);
			}
		}
	}
	tft_x += font->FontWidth;
}

void tft_Puts(uint16_t x, uint16_t y, char *str, tft_font_t *font, uint16_t foreground, uint16_t background)
{
		// Set X and Y coordinates
	tft_x = x;
	tft_y = y;

	while (*str)
	{
		//New line
		/*
		if (*str == '\n')
		{
			tft_y += font->FontHeight + 1;
			//if after \n is also \r, than go to the left of the screen
			if (*(str + 1) == '\r')
			{
				tft_x = 0;
				str++;
			}
			else
			{
				tft_x = startX;
			}
			str++;
			continue;
		}
		else if (*str == '\r')
		{
			str++;
			continue;
		}
		*/

		tft_Putc(tft_x, tft_y, *str++, font, foreground, background);
	}
}

void tft_GetStringSize(char *str, tft_font_t *font, uint16_t *width, uint16_t *height)
{
	uint16_t w = 0;

	*height = font->FontHeight;

	while (*str++)
	{
		w += font->FontWidth;
	}

	*width = w;
}


void tft_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx, dy, sx, sy, err, e2;


	if (x0 >= tft_Opts.width)
	{
		x0 = tft_Opts.width - 1;
	}
	if (x1 >= tft_Opts.width)
	{
		x1 = tft_Opts.width - 1;
	}
	if (y0 >= tft_Opts.height)
	{
		y0 = tft_Opts.height - 1;
	}
	if (y1 >= tft_Opts.height)
	{
		y1 = tft_Opts.height - 1;
	}

	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	while (1)
	{
		tft_DrawPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1)
		{
			break;
		}
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void tft_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	tft_DrawLine(x0, y0, x1, y0, color); //Top
	tft_DrawLine(x0, y0, x0, y1, color);//Left
	tft_DrawLine(x1, y0, x1, y1, color);//Right
	tft_DrawLine(x0, y1, x1, y1, color);//Bottom
}

void tft_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	for (; y0 < y1; y0++) {
		tft_DrawLine(x0, y0, x1, y0, color);
	}
}

void tft_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    tft_DrawPixel(x0, y0 + r, color);
    tft_DrawPixel(x0, y0 - r, color);
    tft_DrawPixel(x0 + r, y0, color);
    tft_DrawPixel(x0 - r, y0, color);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        tft_DrawPixel(x0 + x, y0 + y, color);
        tft_DrawPixel(x0 - x, y0 + y, color);
        tft_DrawPixel(x0 + x, y0 - y, color);
        tft_DrawPixel(x0 - x, y0 - y, color);

        tft_DrawPixel(x0 + y, y0 + x, color);
        tft_DrawPixel(x0 - y, y0 + x, color);
        tft_DrawPixel(x0 + y, y0 - x, color);
        tft_DrawPixel(x0 - y, y0 - x, color);
    }
}

void tft_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    tft_DrawPixel(x0, y0 + r, color);
    tft_DrawPixel(x0, y0 - r, color);
    tft_DrawPixel(x0 + r, y0, color);
    tft_DrawPixel(x0 - r, y0, color);
    tft_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        tft_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        tft_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        tft_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        tft_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
}

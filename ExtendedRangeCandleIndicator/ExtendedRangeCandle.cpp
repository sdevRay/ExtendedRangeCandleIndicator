//---------------------------------------------------------------------------
// Extended Range Candle indicator
// Ray Hancock 2020
//---------------------------------------------------------------------------

#include <windows.h>
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"

//// External variables
bool EnableIndicator;

//// Buffers
TIndexBuffer
ERCup1, ERCup2, ERCup3, ERCup4,
ERCdown1, ERCdown2, ERCdown3, ERCdown4;

//---------------------------------------------------------------------------
// Initialize indicator
//---------------------------------------------------------------------------
EXPORT void __stdcall Init()
{
	// define properties
	IndicatorShortName("Extended Range Candle indicator");
	SetOutputWindow(ow_ChartWindow);
	SetEmptyValue(-1);

	ERCup1 = CreateIndexBuffer();
	ERCup2 = CreateIndexBuffer();
	ERCup3 = CreateIndexBuffer();
	ERCup4 = CreateIndexBuffer();

	ERCdown1 = CreateIndexBuffer();
	ERCdown2 = CreateIndexBuffer();
	ERCdown3 = CreateIndexBuffer();
	ERCdown4 = CreateIndexBuffer();

	IndicatorBuffers(8);

	RegOption("Enable indicator", ot_Boolean, &EnableIndicator);
	EnableIndicator = true;

	AddSeparator("Up Bar");

	SetIndexBuffer(0, ERCup1);
	SetIndexStyle(0, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(0, "up wick");

	SetIndexBuffer(1, ERCup2);
	SetIndexStyle(1, ds_None, psSolid, 1, clDarkGreen);
	SetIndexLabel(1, "up filler");

	SetIndexBuffer(2, ERCup3);
	SetIndexStyle(2, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(2, "down wick");

	SetIndexBuffer(3, ERCup4);
	SetIndexStyle(3, ds_ColoredCandles, psSolid, 1, clDarkGreen);
	SetIndexLabel(3, "down filler");

	AddSeparator("Down Bar");

	SetIndexBuffer(4, ERCdown1);
	SetIndexStyle(4, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(4, "up wick");

	SetIndexBuffer(5, ERCdown2);
	SetIndexStyle(5, ds_None, psSolid, 1, clDarkRed);
	SetIndexLabel(5, "up filler");

	SetIndexBuffer(6, ERCdown3);
	SetIndexStyle(6, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(6, "down wick");

	SetIndexBuffer(7, ERCdown4);
	SetIndexStyle(7, ds_ColoredCandles, psSolid, 1, clDarkRed);
	SetIndexLabel(7, "down filler");
}

EXPORT void __stdcall OnParamsChange()
{
}

//---------------------------------------------------------------------------
// Calculate requested bar
//---------------------------------------------------------------------------
EXPORT void __stdcall Calculate(int index)
{
	double open, close, high, low, candle, eightPercent, hlEightyPercent;
	int emptyValue;

	open = Open(index);
	high = High(index);
	low = Low(index);
	close = Close(index);

	eightPercent = 0.8;
	emptyValue = -1;

	hlEightyPercent = abs(high - low) * eightPercent;
	candle = abs(open - close);

	if (hlEightyPercent < candle && EnableIndicator)
	{
		if (close > open)
		{
			ERCup1[index] = open;
			ERCup2[index] = high;
			ERCup3[index] = low;
			ERCup4[index] = close;
		}
		else
		{
			ERCup1[index] = emptyValue;
			ERCup2[index] = emptyValue;
			ERCup3[index] = emptyValue;
			ERCup4[index] = emptyValue;
		}

		if (open > close)
		{
			ERCdown1[index] = open;
			ERCdown2[index] = high;
			ERCdown3[index] = low;
			ERCdown4[index] = close;
		}
		else 
		{
			ERCdown1[index] = emptyValue;
			ERCdown2[index] = emptyValue;
			ERCdown3[index] = emptyValue;
			ERCdown4[index] = emptyValue;
		}
	}
	else
	{
		ERCup1[index] = emptyValue;
		ERCup2[index] = emptyValue;
		ERCup3[index] = emptyValue;
		ERCup4[index] = emptyValue;

		ERCdown1[index] = emptyValue;
		ERCdown2[index] = emptyValue;
		ERCdown3[index] = emptyValue;
		ERCdown4[index] = emptyValue;
	}
}

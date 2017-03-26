#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(unsigned & width, unsigned & height, unsigned newWidth, unsigned newHeight)
	: m_width(width)
	, m_height(height)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	SwapUnsigned(m_width, m_newWidth);
	SwapUnsigned(m_height, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	SwapUnsigned(m_width, m_newWidth);
	SwapUnsigned(m_height, m_newHeight);
}

void CResizeImageCommand::SwapUnsigned(unsigned & val1, unsigned & val2)
{
	unsigned tmpVal = val1;
	val1 = val2;
	val2 = tmpVal;
}


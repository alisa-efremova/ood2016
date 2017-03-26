#pragma once
#include "AbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(unsigned & width, unsigned & height, unsigned newWidth, unsigned newHeight);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	void SwapUnsigned(unsigned & val1, unsigned & val2);

	unsigned & m_width;
	unsigned & m_height;
	unsigned m_newWidth;
	unsigned m_newHeight;
};


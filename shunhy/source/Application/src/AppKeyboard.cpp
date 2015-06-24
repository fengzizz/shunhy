#include "AppKeyboard.h"
#include "Memory.h"
namespace Shh
{
	AppKeyboard::AppKeyboard()
	{
		_Reset();
	}
	AppKeyboard::~AppKeyboard()
	{

	}
	void AppKeyboard::_Reset()
	{
		Memory::Zero(mKeyInfo, sizeof(mKeyInfo));
	}

	void AppKeyboard::_SetKeyPress(EKeys key)
	{
		size_t x = (size_t)key;
		KeyStates& state = getKeyStates(x);

		size_t move = x & KeyStateMark;
		KeyStates mark = 1 << move;
		state |= mark;
	}
	void AppKeyboard::_SetKeyUp(EKeys key)
	{
		size_t x = (size_t)key;
		KeyStates& state = getKeyStates(x);

		size_t move = x & KeyStateMark;
		KeyStates mark = 1 << move;
		state &= (~mark);
	}
}
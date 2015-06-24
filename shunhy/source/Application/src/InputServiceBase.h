#ifndef __INPUTSERVICEBASE_H__
#define __INPUTSERVICEBASE_H__
#include "Singleton.h"
#include "InputListener.h"
#include <vector>
namespace Shh
{
	template<typename T>
	class InputServerBase : public Singleton<T>
	{
	public:
		void SetSelect(bool select);
		void AddListener(InputListener* listener);
		void RemoveListener(InputListener* listener);
		static bool CheckSelect();
	protected:
		InputServerBase();
		~InputServerBase();
		void _setKey(EKeys key, EKeyState state);
		void _setMouse(EKeys key, EKeyState state, int x, int y);
		void _setMouseMove( int x, int y);
		void _addWheel(int roll);
		typedef std::vector<InputListener*> Listeners;
		Listeners mListeners;
		bool mSelect;
	};
	template<typename T>
	InputServerBase<T>::InputServerBase()
		:mSelect(false)
	{

	}
	template<typename T>
	InputServerBase<T>::~InputServerBase()
	{

	}
	template<typename T>
	void InputServerBase<T>::AddListener(InputListener* listener)
	{
		const InputListener::Priority priority = listener->GetPriority();
		Listeners::const_iterator it = mListeners.begin();
		Listeners::const_iterator end = mListeners.end();
		while(it != end)
		{
			if ((*it)->GetPriority() >= priority)
			{
				mListeners.insert(it, listener);
				return;
			}
		}
		mListeners.push_back(listener);
	}
	template<typename T>
	void InputServerBase<T>::RemoveListener(InputListener* listener)
	{
		mListeners.erase(listener);
	}

	template<typename T>
	inline void InputServerBase<T>::SetSelect(bool select)
	{
		mSelect = select;
	}

	template<typename T>
	inline bool InputServerBase<T>::CheckSelect()
	{
		return (ms_Singleton != nullptr && ms_Singleton->mSelect);
	}

	template<typename T>
	void InputServerBase<T>::_setKey(EKeys key, EKeyState state)
	{
		Listeners::const_iterator it = mListeners.begin();
		Listeners::const_iterator end = mListeners.end();
		while(it != end)
		{
			(*it)->SetKeyEvent(key, state);
			++it;
		}
	}
	template<typename T>
	void InputServerBase<T>::_setMouse(EKeys key, EKeyState state, int x, int y)
	{
		Listeners::const_iterator it = mListeners.begin();
		Listeners::const_iterator end = mListeners.end();
		while(it != end)
		{
			(*it)->SetMouseEvent(key, state, x, y);
			++it;
		}
	}

	template<typename T>
	void InputServerBase<T>::_setMouseMove(int x, int y)
	{
		Listeners::const_iterator it = mListeners.begin();
		Listeners::const_iterator end = mListeners.end();
		while(it != end)
		{
			(*it)->SetMouseMove(x, y);
			++it;
		}
	}

	template<typename T>
	void InputServerBase<T>::_addWheel(int roll)
	{
		Listeners::const_iterator it = mListeners.begin();
		Listeners::const_iterator end = mListeners.end();
		while(it != end)
		{
			(*it)->AddWheel(roll);
			++it;
		}
	}

}

#endif //__INPUTSERVICEBASE_H__
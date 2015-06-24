#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "Core/CoreDef.h"
namespace Shh
{
	template <typename T>
	class _Shh_Export_Tmpl Singleton
	{
	public:		
		~Singleton();
		static T* GetSingletonPtr();
		static T& GetSingleton();
	protected:
		static T* ms_Singleton;
		Singleton();
	private:		
		Singleton(const Singleton<T> &);	
		Singleton& operator=(const Singleton<T> &);
	};
#define SingletonInstancePtr(T) template<> ##T * Singleton< ##T >::ms_Singleton = nullptr


	template<typename T>
	Singleton<T>::Singleton()
	{
		shh_assert(nullptr == ms_Singleton);
		ms_Singleton = static_cast<T*>(this);
	}
	template<typename T>
	Singleton<T>::~Singleton()
	{
		  shh_assert(ms_Singleton); 
		  ms_Singleton = nullptr;  
	}
	template <typename T>
	T* Singleton<T>::GetSingletonPtr()
	{
		return ms_Singleton;
	}
	template <typename T>
	T& Singleton<T>::GetSingleton()
	{	
		shh_assert( nullptr != ms_Singleton );  
		return ( *ms_Singleton ); 
	}
}
#endif //__SINGLETON_H__

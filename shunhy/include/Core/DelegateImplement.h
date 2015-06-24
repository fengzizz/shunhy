
namespace delegates
{

#define SHH_COMBINE(a, b)		SHH_COMBINE1(a, b)
#define SHH_COMBINE1(a, b)		a##b

#define SHH_I_DELEGATE			SHH_COMBINE(IDelegate, SHH_SUFFIX)

#define SHH_C_STATIC_DELEGATE	SHH_COMBINE(CStaticDelegate, SHH_SUFFIX)
#define SHH_C_METHOD_DELEGATE	SHH_COMBINE(CMethodDelegate, SHH_SUFFIX)

#define SHH_C_DELEGATE			SHH_COMBINE(CDelegate, SHH_SUFFIX)
#define SHH_C_MULTI_DELEGATE	SHH_COMBINE(CMultiDelegate, SHH_SUFFIX)

	SHH_TEMPLATE   SHH_TEMPLATE_PARAMS
	class SHH_I_DELEGATE
	{
	public:
		virtual ~SHH_I_DELEGATE() { }
		virtual bool isType( const std::type_info& _type) = 0;
		virtual void invoke( SHH_PARAMS ) = 0;
		virtual bool compare(  SHH_I_DELEGATE SHH_TEMPLATE_ARGS* _delegate) const = 0;
		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return false;
		}
	};


	SHH_TEMPLATE   SHH_TEMPLATE_PARAMS
	class SHH_C_STATIC_DELEGATE : public  SHH_I_DELEGATE SHH_TEMPLATE_ARGS
	{
	public:
		typedef void (*Func)( SHH_PARAMS );

		SHH_C_STATIC_DELEGATE (Func _func) : mFunc(_func) { }

		virtual bool isType( const std::type_info& _type)
		{
			return typeid( SHH_C_STATIC_DELEGATE SHH_TEMPLATE_ARGS ) == _type;
		}

		virtual void invoke( SHH_PARAMS )
		{
			mFunc( SHH_ARGS );
		}

		virtual bool compare(  SHH_I_DELEGATE SHH_TEMPLATE_ARGS* _delegate) const
		{

			SHH_C_STATIC_DELEGATE SHH_TEMPLATE_ARGS* cast = dynamic_cast<SHH_C_STATIC_DELEGATE SHH_TEMPLATE_ARGS*>(_delegate);
			if (nullptr == cast) 
				return false;
			return cast->mFunc == mFunc;
		}
		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return false;
		}

	private:
		Func mFunc;
	};


	template SHH_T_TEMPLATE_PARAMS
	class SHH_C_METHOD_DELEGATE : public  SHH_I_DELEGATE SHH_TEMPLATE_ARGS
	{
	public:
		typedef void (T::*Method)( SHH_PARAMS );

		SHH_C_METHOD_DELEGATE(IDelegateUnlink* _unlink, T* _object, Method _method) : mUnlink(_unlink), mObject(_object), mMethod(_method) { }

		virtual bool isType( const std::type_info& _type)
		{
			return typeid( SHH_C_METHOD_DELEGATE SHH_T_TEMPLATE_ARGS ) == _type;
		}

		virtual void invoke( SHH_PARAMS )
		{
			(mObject->*mMethod)( SHH_ARGS );
		}

		virtual bool compare(  SHH_I_DELEGATE SHH_TEMPLATE_ARGS* _delegate) const
		{

			SHH_C_METHOD_DELEGATE SHH_T_TEMPLATE_ARGS* cast = dynamic_cast<  SHH_C_METHOD_DELEGATE SHH_T_TEMPLATE_ARGS* >(_delegate);
			if (nullptr == cast) 
				return false;
			return cast->mObject == mObject && cast->mMethod == mMethod;
		}

		virtual bool compare(IDelegateUnlink* _unlink) const
		{
			return mUnlink == _unlink;
		}

	private:
		IDelegateUnlink* mUnlink;
		T* mObject;
		Method mMethod;
	};

}

// newDelegate(funk_name);
// newDelegate(class_name::static_method_name);
SHH_TEMPLATE   SHH_TEMPLATE_PARAMS
	inline  delegates::SHH_I_DELEGATE SHH_TEMPLATE_ARGS* newDelegate( void (*_func)( SHH_PARAMS ) )
{
	return shh_new delegates::SHH_C_STATIC_DELEGATE SHH_TEMPLATE_ARGS  (_func);
}


//newDelegate(&object_name, &class_name::method_name);
template SHH_T_TEMPLATE_PARAMS
	inline  delegates::SHH_I_DELEGATE SHH_TEMPLATE_ARGS* newDelegate( T* _object, void (T::*_method)( SHH_PARAMS ) )
{
	return shh_new delegates::SHH_C_METHOD_DELEGATE  SHH_T_TEMPLATE_ARGS  (delegates::GetDelegateUnlink(_object), _object, _method);
}

namespace delegates
{
	SHH_TEMPLATE   SHH_TEMPLATE_PARAMS
	class SHH_C_DELEGATE
	{
	public:
		typedef  SHH_I_DELEGATE SHH_TEMPLATE_ARGS  IDelegate;

		SHH_C_DELEGATE () : mDelegate(nullptr) { }
		SHH_C_DELEGATE (const SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& _event) : mDelegate(nullptr)
		{
			IDelegate* del = _event.mDelegate;
			const_cast< SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& >(_event).mDelegate = nullptr;

			if (mDelegate != nullptr && !mDelegate->compare(del))
				shh_delete mDelegate;

			mDelegate = del;
		}
		~SHH_C_DELEGATE ()
		{
			clear();
		}

		bool empty() const
		{
			return mDelegate == nullptr;
		}

		void clear()
		{
			if (mDelegate)
			{
				shh_delete mDelegate;
				mDelegate = nullptr;
			}
		}

		SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& operator=(IDelegate* _delegate)
		{
			shh_delete mDelegate;
			mDelegate = _delegate;
			return *this;
		}

		SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& operator=(const SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& _event)
		{
			IDelegate* del = _event.mDelegate;
			const_cast< SHH_C_DELEGATE  SHH_TEMPLATE_ARGS& >(_event).mDelegate = nullptr;

			if (mDelegate != nullptr && !mDelegate->compare(del))
				shh_delete mDelegate;

			mDelegate = del;

			return *this;
		}

		void operator()( SHH_PARAMS )
		{
			if (mDelegate == nullptr) return;
			mDelegate->invoke( SHH_ARGS );
		}

	private:
		IDelegate* mDelegate;
	};


	SHH_TEMPLATE   SHH_TEMPLATE_PARAMS
	class SHH_C_MULTI_DELEGATE
	{
	public:
		typedef  SHH_I_DELEGATE SHH_TEMPLATE_ARGS  IDelegate;
		typedef SHH_TYPENAME std::list<IDelegate* /*, Allocator<IDelegate*>*/ > ListDelegate;
		typedef SHH_TYPENAME ListDelegate::iterator ListDelegateIterator;
		typedef SHH_TYPENAME ListDelegate::const_iterator ConstListDelegateIterator;

		SHH_C_MULTI_DELEGATE () { }
		~SHH_C_MULTI_DELEGATE ()
		{
			clear();
		}

		bool empty() const
		{
			for (ConstListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter) return false;
			}
			return true;
		}

		void clear()
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter)
				{
					shh_delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

		void clear(IDelegateUnlink* _unlink)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_unlink))
				{
					shh_delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

		SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& operator+=(IDelegate* _delegate)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_delegate))
				{
					shh_assert(0);
				}
			}
			mListDelegates.push_back(_delegate);
			return *this;
		}

		SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& operator-=(IDelegate* _delegate)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_delegate))
				{
					if ((*iter) != _delegate) shh_delete (*iter);
					(*iter) = nullptr;
					break;
				}
			}
			shh_delete _delegate;
			return *this;
		}

		void operator()( SHH_PARAMS )
		{
			ListDelegateIterator iter = mListDelegates.begin();
			while (iter != mListDelegates.end())
			{
				if (nullptr == (*iter))
				{
					iter = mListDelegates.erase(iter);
				}
				else
				{
					(*iter)->invoke( SHH_ARGS );
					++iter;
				}
			}
		}

		SHH_C_MULTI_DELEGATE (const SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& _event)
		{
			// 蟹邪斜懈褉邪械屑 褋械斜械 胁谢邪写械薪懈械
			ListDelegate del = _event.mListDelegates;
			const_cast< SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& >(_event).mListDelegates.clear();

			safe_clear(del);

			mListDelegates = del;
		}

		SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& operator=(const SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& _event)
		{
			ListDelegate del = _event.mListDelegates;
			const_cast< SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& >(_event).mListDelegates.clear();

			safe_clear(del);

			mListDelegates = del;

			return *this;
		}

		SHH_C_MULTI_DELEGATE  SHH_TEMPLATE_ARGS& operator=(IDelegate* _delegate)
		{
			clear();
			*this += _delegate;
			return *this;
		}

	private:
		void safe_clear(ListDelegate& _delegates)
		{
			for (ListDelegateIterator iter = mListDelegates.begin(); iter != mListDelegates.end(); ++iter)
			{
				if (*iter)
				{
					IDelegate* del = (*iter);
					(*iter) = nullptr;
					delete_is_not_found(del, _delegates);
				}
			}
		}

		void delete_is_not_found(IDelegate* _del, ListDelegate& _delegates)
		{
			for (ListDelegateIterator iter = _delegates.begin(); iter != _delegates.end(); ++iter)
			{
				if ((*iter) && (*iter)->compare(_del))
				{
					return;
				}
			}

			shh_delete _del;
		}

	private:
		ListDelegate mListDelegates;
	};


#undef SHH_COMBINE
#undef SHH_COMBINE1

#undef SHH_I_DELEGATE

#undef SHH_C_STATIC_DELEGATE
#undef SHH_C_METHOD_DELEGATE

#undef SHH_C_DELEGATE
#undef SHH_C_MULTI_DELEGATE

#undef SHH_SUFFIX
#undef SHH_TEMPLATE
#undef SHH_TEMPLATE_PARAMS
#undef SHH_TEMPLATE_ARGS
#undef SHH_T_TEMPLATE_PARAMS
#undef SHH_T_TEMPLATE_ARGS
#undef SHH_PARAMS
#undef SHH_ARGS
#undef SHH_TYPENAME

} // namespace delegates

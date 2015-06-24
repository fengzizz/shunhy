#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include <exception>
#include "Core/CoreDef.h"

namespace Shh
{
	#define BASE_EXCEPT(desc, src) throw Exception(desc, src, __FILE__, __LINE__)

	class _Shh_Export Exception : public std::exception
	{
	public:
		enum ExceptionType
		{
			EXT_UNDEF_TYPE = 0,
			EXT_SERIALIZE_ERROR = 1,
			EXT_FORMAT_ERROR = 2,
			EXT_SHADER_ERROR = 3,
			EXT_MEMORY_ERROR = 4,
			//EXT_FILE_READ_FALSE,
			//EXT_FILE_WRITE_FALSE,
			//EXT_FILE_NOT_FOUND,
			//EXT_ITEM_NOT_FOUND,
			//EXT_SYSTEM_ERROR,
			EXT_CUSTOM_BEGIN = 1000,
		};

		/** Default constructor.
        */

        Exception(const String& description_, const String& source_);
		Exception(const String& description_, const String& source_, const char* file_, long line_);

        /** Copy constructor.
        */
        Exception(const Exception& rhs);

		/// Needed for  compatibility with std::exception
		virtual ~Exception() throw();

        /** Assignment operator.
        */
        void operator = (const Exception& rhs);

        virtual const String& GetFullDescription() const;

        /** Gets the error code.
        */
        virtual int GetType(void) const throw();

        /** Gets the source function.
        */
        virtual const String &GetSource() const;

        /** Gets source file name.
        */
        virtual const String &GetFile() const;

        /** Gets line number.
        */
        virtual long GetLine() const;

		/** Returns a string with only the 'description' field of this exception. Use 
			GetFullDescriptionto get a full description of the error including line number,
			error number and what function threw the exception.
        */
		virtual const String &GetDescription(void) const;

		/// Override std::exception::what
		const char* what() const throw();

	protected:

		/** Advanced constructor.
        */
        Exception(int type_, const String& description_, const String& source_, const char* tile_, const char* file_, long line_);

		long line;
		int type;
		String title;
		String description;
		String source;
		String file;
		mutable String fullDesc;
	};
}

#endif
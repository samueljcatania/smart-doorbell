#ifndef _GLIBMM_CONFIG_H
#define _GLIBMM_CONFIG_H

/* Define to omit deprecated API from the library. */
/* #undef GLIBMM_DISABLE_DEPRECATED */

/* Major version number of glibmm. */
#define GLIBMM_MAJOR_VERSION 2

/* Minor version number of glibmm. */
#define GLIBMM_MINOR_VERSION 66

/* Micro version number of glibmm. */
#define GLIBMM_MICRO_VERSION 2

/* Define if glibmm is built as a static library */
/* #undef GLIBMM_STATIC_LIB */

/* The size of wchar_t, as computed by sizeof. */
#define GLIBMM_SIZEOF_WCHAR_T 4

/* Defined when the -Ddebug-refcounting configure argument was given */
/* #undef GLIBMM_DEBUG_REFCOUNTING */

/* This is always set. This is only for backwards compatibility. */
#define GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED 1

/* This is always set. This is only for backwards compatibility. */
#define GLIBMM_EXCEPTIONS_ENABLED 1

/* This is always set. This is only for backwards compatibility. */
#define GLIBMM_VFUNCS_ENABLED 1

/* This is always set. This is only for backwards compatibility. */
#define GLIBMM_PROPERTIES_ENABLED 1

/* This is always set. This is only for backwards compatibility.
 * All acceptable C++ compilers have namespace std. */
#define GLIBMM_HAVE_NAMESPACE_STD 1

/* Dummy macro definition for compatibility with old code that expects
 * it to be defined. */
#define GLIBMM_USING_STD(Symbol)

#ifdef _WIN32
  /* Win32 compilers have a lot of varation */
# if defined(_MSC_VER)
#  define GLIBMM_MSC 1
#  define GLIBMM_WIN32 1
#  define GLIBMM_DLL 1
# elif defined(__CYGWIN__)
#  define GLIBMM_CONFIGURE 1
# elif defined(__MINGW32__)
#  define GLIBMM_WIN32 1
#  define GLIBMM_CONFIGURE 1
# else
   /* AIX clR compiler complains about this even though it doesn't get this far */
#  error "Unknown architecture (send me gcc --dumpspecs or equiv)"
# endif
#else
# define GLIBMM_CONFIGURE 1
#endif /* _WIN32 */

#ifdef GLIBMM_CONFIGURE

/* Define only on Mac OS, COCOA */
/* #undef GLIBMM_OS_COCOA */

/* Define if extern "C" and extern "C++" function pointers are compatible. */
#define GLIBMM_CAN_ASSIGN_NON_EXTERN_C_FUNCTIONS_TO_EXTERN_C_CALLBACKS 1

/* Define if non-instantiated templates may dynamic_cast<> to an undefined
   type. */
#define GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION 1

/* Define if the compiler honors namespaces inside extern "C" blocks. */
#define GLIBMM_CAN_USE_NAMESPACES_INSIDE_EXTERNC 1

/* Defined when the SUN Forte C++ compiler is being used. */
/* #undef GLIBMM_COMPILER_SUN_FORTE */

/* Defined if a static member variable may be initialized inline to
   std::string::npos */
#define GLIBMM_HAVE_ALLOWS_STATIC_INLINE_NPOS 1

/* Defined when time_t is not equivalent to gint32, meaning that it can be
   used for a method overload */
#define GLIBMM_HAVE_C_STD_TIME_T_IS_NOT_INT32 1

/* Define if the compiler disambiguates template specializations for const and
   non-const types. */
#define GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS 1

/* Defined if std::iterator_traits<> is standard-conforming */
#define GLIBMM_HAVE_STD_ITERATOR_TRAITS 1

/* Defined if std::reverse_iterator is in Sun libCstd style */
/* #undef GLIBMM_HAVE_SUN_REVERSE_ITERATOR */

/* Defined if the STL containers have templated sequence ctors */
#define GLIBMM_HAVE_TEMPLATE_SEQUENCE_CTORS 1

/* Define to 1 if wide stream is available. */
#define GLIBMM_HAVE_WIDE_STREAM 1

/* Define if C++ member functions may refer to member templates. */
#define GLIBMM_MEMBER_FUNCTIONS_MEMBER_TEMPLATES 1

/* Define if the thread_local keyword is supported. */
#define GLIBMM_CAN_USE_THREAD_LOCAL 1

#endif /* GLIBMM_CONFIGURE */

#ifdef GLIBMM_MSC
# define GLIBMM_HAVE_STD_ITERATOR_TRAITS 1
# define GLIBMM_HAVE_TEMPLATE_SEQUENCE_CTORS 1
# define GLIBMM_HAVE_WIDE_STREAM 1
# define GLIBMM_HAVE_DISAMBIGUOUS_CONST_TEMPLATE_SPECIALIZATIONS 1
# define GLIBMM_HAVE_C_STD_TIME_T_IS_NOT_INT32 1
# define GLIBMM_CAN_USE_DYNAMIC_CAST_IN_UNUSED_TEMPLATE_WITHOUT_DEFINITION 1
# define GLIBMM_CAN_USE_THREAD_LOCAL 1
# define GLIBMM_CAN_ASSIGN_NON_EXTERN_C_FUNCTIONS_TO_EXTERN_C_CALLBACKS 1
# define GLIBMM_CAN_USE_NAMESPACES_INSIDE_EXTERNC 1
# pragma warning (disable: 4786 4355 4800 4181)

/* We have GLIBMM_HAVE_ALLOWS_STATIC_INLINE_NPOS for Visual Studio 2017+ */
#if (_MSC_VER >= 1910)
#define GLIBMM_HAVE_ALLOWS_STATIC_INLINE_NPOS 1
#endif

#endif /* GLIBMM_MSC */

/* Enable DLL-specific stuff only when not building a static library */
#if !defined(__CYGWIN__) && defined(__MINGW32__) && !defined(GLIBMM_STATIC_LIB)
# define GLIBMM_DLL 1
#endif

#ifdef GLIBMM_DLL
# if defined(GLIBMM_BUILD)
#  define GLIBMM_API __declspec(dllexport)
# elif !defined (__GNUC__)
#  define GLIBMM_API __declspec(dllimport)
# else /* don't dllimport classes/methods on GCC/MinGW */
#  define GLIBMM_API
# endif /* GLIBMM_BUILD - _WINDLL */
#else
/* Build a static library or a non-native-Windows library */
# define GLIBMM_API
#endif /* GLIBMM_DLL */

#endif /* _GLIBMM_CONFIG_H */

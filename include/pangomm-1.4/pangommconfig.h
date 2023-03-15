/* This file is part of pangomm. */
#ifndef PANGOMM_PANGOMMCONFIG_H_INCLUDED
#define PANGOMM_PANGOMMCONFIG_H_INCLUDED

#include <glibmmconfig.h>

/* Define to omit deprecated API from the library. */
/* #undef PANGOMM_DISABLE_DEPRECATED */

/* Major version number of pangomm. */
#define PANGOMM_MAJOR_VERSION 2

/* Minor version number of pangomm. */
#define PANGOMM_MINOR_VERSION 46

/* Micro version number of pangomm. */
#define PANGOMM_MICRO_VERSION 2

/* Enable DLL-specific stuff only when not building a static library */
#if !defined(__CYGWIN__) && (defined(__MINGW32__) || defined (_MSC_VER)) && !defined(PANGOMM_STATIC_LIB) && !defined (PANGOMM_USE_GENDEF)
# define PANGOMM_DLL 1
#endif

#ifdef PANGOMM_DLL
# if defined(PANGOMM_BUILD)
#  define PANGOMM_API __declspec(dllexport)
# elif !defined (__GNUC__)
#  define PANGOMM_API __declspec(dllimport)
# else /* don't dllimport classes/methods on GCC/MinGW */
#  define PANGOMM_API
# endif /* PANGOMM_BUILD - _WINDLL */
#else
/* Build a static library or a non-native-Windows library */
# define PANGOMM_API
#endif /* PANGOMM_DLL */

#endif /* !PANGOMM_PANGOMMCONFIG_H_INCLUDED */

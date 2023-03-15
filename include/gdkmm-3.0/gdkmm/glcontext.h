// Generated by gmmproc 2.66.0 -- DO NOT MODIFY!
#ifndef _GDKMM_GLCONTEXT_H
#define _GDKMM_GLCONTEXT_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* Copyright (C) 2015 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <gdkmmconfig.h>
#include <gdkmm/display.h>
#include <gdkmm/window.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
using GdkGLContext = struct _GdkGLContext;
using GdkGLContextClass = struct _GdkGLContextClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Gdk
{ class GDKMM_API GLContext_Class; } // namespace Gdk
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace Gdk
{

/**  @newin{3,18}
 */
class GDKMM_API GLError : public Glib::Error
{
public:
  /**  @var Code NOT_AVAILABLE
   * OpenGL support is not available.
   * 
   *  @var Code UNSUPPORTED_FORMAT
   * The requested visual format is not supported.
   * 
   *  @var Code UNSUPPORTED_PROFILE
   * The requested profile is not supported.
   * 
   *  @enum Code
   * 
   * Error enumeration for Gdk::GLContext.
   * 
   * @newin{3,18}
   */
  enum Code
  {
    NOT_AVAILABLE,
    UNSUPPORTED_FORMAT,
    UNSUPPORTED_PROFILE
  };

  GLError(Code error_code, const Glib::ustring& error_message);
  explicit GLError(GError* gobject);
  Code code() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:

  static void throw_func(GError* gobject);

  friend GDKMM_API void wrap_init(); // uses throw_func()

  #endif //DOXYGEN_SHOULD_SKIP_THIS
};

} // namespace Gdk

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class GDKMM_API Value<Gdk::GLError::Code> : public Glib::Value_Enum<Gdk::GLError::Code>
{
public:
  static GType value_type() G_GNUC_CONST;
};

} // namespace Glib
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace Gdk
{


/** A Gdk::GLContext is an OpenGL context abstraction. It's a low-level object, used to implement high-level objects such
 * as Gtk::GLArea on the GTK+ level.
 * @newin{3,18}
 */

class GDKMM_API GLContext : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  using CppObjectType = GLContext;
  using CppClassType = GLContext_Class;
  using BaseObjectType = GdkGLContext;
  using BaseClassType = GdkGLContextClass;

  // noncopyable
  GLContext(const GLContext&) = delete;
  GLContext& operator=(const GLContext&) = delete;

private:  friend class GLContext_Class;
  static CppClassType glcontext_class_;

protected:
  explicit GLContext(const Glib::ConstructParams& construct_params);
  explicit GLContext(GdkGLContext* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:

  GLContext(GLContext&& src) noexcept;
  GLContext& operator=(GLContext&& src) noexcept;

  ~GLContext() noexcept override;

  /** Get the GType for this class, for use with the underlying GObject type system.
   */
  static GType get_type()      G_GNUC_CONST;

#ifndef DOXYGEN_SHOULD_SKIP_THIS


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GdkGLContext*       gobj()       { return reinterpret_cast<GdkGLContext*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GdkGLContext* gobj() const { return reinterpret_cast<GdkGLContext*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GdkGLContext* gobj_copy();

private:


protected:
  GLContext();

public:
  
  /** Retrieves the Gdk::Display the @a context is created for
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::Display or <tt>nullptr</tt>.
   */
  Glib::RefPtr<Display> get_display();
  
  /** Retrieves the Gdk::Display the @a context is created for
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::Display or <tt>nullptr</tt>.
   */
  Glib::RefPtr<const Display> get_display() const;
  
  /** Retrieves the Gdk::Window used by the @a context.
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::Window or <tt>nullptr</tt>.
   */
  Glib::RefPtr<Window> get_window();
  
  /** Retrieves the Gdk::Window used by the @a context.
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::Window or <tt>nullptr</tt>.
   */
  Glib::RefPtr<const Window> get_window() const;
  
  /** Retrieves the Gdk::GLContext that this @a context share data with.
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::GLContext or <tt>nullptr</tt>.
   */
  Glib::RefPtr<GLContext> get_shared_context();
  
  /** Retrieves the Gdk::GLContext that this @a context share data with.
   * 
   * @newin{3,18}
   * 
   * @return A Gdk::GLContext or <tt>nullptr</tt>.
   */
  Glib::RefPtr<const GLContext> get_shared_context() const;
  
  /** Retrieves the OpenGL version of the @a context.
   * 
   * The @a context must be realized prior to calling this function.
   * 
   * @newin{3,18}
   * 
   * @param major Return location for the major version.
   * @param minor Return location for the minor version.
   */
  void get_version(int& major, int& minor) const;
  
  /** Whether the Gdk::GLContext is in legacy mode or not.
   * 
   * The Gdk::GLContext must be realized before calling this function.
   * 
   * When realizing a GL context, GDK will try to use the OpenGL 3.2 core
   * profile; this profile removes all the OpenGL API that was deprecated
   * prior to the 3.2 version of the specification. If the realization is
   * successful, this function will return <tt>false</tt>.
   * 
   * If the underlying OpenGL implementation does not support core profiles,
   * GDK will fall back to a pre-3.2 compatibility profile, and this function
   * will return <tt>true</tt>.
   * 
   * You can use the value returned by this function to decide which kind
   * of OpenGL API to use, or whether to do extension discovery, or what
   * kind of shader programs to load.
   * 
   * @newin{3,20}
   * 
   * @return <tt>true</tt> if the GL context is in legacy mode.
   */
  bool is_legacy() const;
  
  /** Retrieves the major and minor version requested by calling
   * gdk_gl_context_set_required_version().
   * 
   * @newin{3,18}
   * 
   * @param major Return location for the major version to request.
   * @param minor Return location for the minor version to request.
   */
  void get_required_version(int& major, int& minor) const;
  
  /** Sets the major and minor version of OpenGL to request.
   * 
   * Setting @a major and @a minor to zero will use the default values.
   * 
   * The Gdk::GLContext must not be realized or made current prior to calling
   * this function.
   * 
   * @newin{3,18}
   * 
   * @param major The major version to request.
   * @param minor The minor version to request.
   */
  void set_required_version(int major, int minor);
  
  /** Retrieves the value set using gdk_gl_context_set_debug_enabled().
   * 
   * @newin{3,18}
   * 
   * @return <tt>true</tt> if debugging is enabled.
   */
  bool get_debug_enabled() const;
  
  /** Sets whether the Gdk::GLContext should perform extra validations and
   * run time checking. This is useful during development, but has
   * additional overhead.
   * 
   * The Gdk::GLContext must not be realized or made current prior to
   * calling this function.
   * 
   * @newin{3,18}
   * 
   * @param enabled Whether to enable debugging in the context.
   */
  void set_debug_enabled(bool enabled =  true);
  
  /** Retrieves the value set using gdk_gl_context_set_forward_compatible().
   * 
   * @newin{3,18}
   * 
   * @return <tt>true</tt> if the context should be forward compatible.
   */
  bool get_forward_compatible() const;
  
  /** Sets whether the Gdk::GLContext should be forward compatible.
   * 
   * Forward compatibile contexts must not support OpenGL functionality that
   * has been marked as deprecated in the requested version; non-forward
   * compatible contexts, on the other hand, must support both deprecated and
   * non deprecated functionality.
   * 
   * The Gdk::GLContext must not be realized or made current prior to calling
   * this function.
   * 
   * @newin{3,18}
   * 
   * @param compatible Whether the context should be forward compatible.
   */
  void set_forward_compatible(bool compatible =  true);

  
  /** Requests that GDK create an OpenGL ES context instead of an OpenGL one,
   * if the platform and windowing system allows it.
   *
   * The %GLContext must not have been realized.
   *
   * By default, GDK will attempt to automatically detect whether the
   * underlying GL implementation is OpenGL or OpenGL ES once the %GLContext
   * is realized.
   *
   * You should check the return value of get_use_es() after
   * calling realize() to decide whether to use the OpenGL or
   * OpenGL ES API, extensions, or shaders.
   *
   * @newin{3,22}
   *
   * @param use_es Whether the context should use OpenGL ES instead of OpenGL.
   */
  void set_use_es(bool use_es =  true);

  /** Undo a previous call to set_use_es().
   *
   * GDK will attempt to automatically detect whether the underlying
   * GL implementation is OpenGL or OpenGL ES once the %GLContext is realized.
   *
   * @newin{3,24}
   */
  void unset_use_es();

  
  /** Checks whether the @a context is using an OpenGL or OpenGL ES profile.
   * 
   * @newin{3,22}
   * 
   * @return <tt>true</tt> if the Gdk::GLContext is using an OpenGL ES profile.
   */
  bool get_use_es() const;
  
  /** Realizes the given Gdk::GLContext.
   * 
   * It is safe to call this function on a realized Gdk::GLContext.
   * 
   * @newin{3,18}
   * 
   * @return <tt>true</tt> if the context is realized.
   * 
   * @throws Glib::Error
   */
  bool realize();
  
  /** Makes the @a context the current one.
   * 
   * @newin{3,18}
   */
  void make_current();
  
  /** Retrieves the current Gdk::GLContext.
   * 
   * @newin{3,18}
   * 
   * @return The current Gdk::GLContext, or <tt>nullptr</tt>.
   */
  static Glib::RefPtr<GLContext> get_current();
  
  /** Clears the current Gdk::GLContext.
   * 
   * Any OpenGL call after this function returns will be ignored
   * until gdk_gl_context_make_current() is called.
   * 
   * @newin{3,18}
   */
  static void clear_current();

  /** The Gdk::Display used to create the Gdk::GLContext.
   * 
   * @newin{3,18}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Display> > property_display() const;


  /** The Gdk::GLContext that this context is sharing data with, or <tt>nullptr</tt>
   * 
   * @newin{3,18}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<GLContext> > property_shared_context() const;


  /** The Gdk::Window the gl context is bound to.
   * 
   * @newin{3,18}
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Window> > property_window() const;


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


};

} // namespace Gdk


namespace Glib
{
  /** A Glib::wrap() method for this object.
   *
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gdk::GLContext
   */
  GDKMM_API
  Glib::RefPtr<Gdk::GLContext> wrap(GdkGLContext* object, bool take_copy = false);
}


#endif /* _GDKMM_GLCONTEXT_H */

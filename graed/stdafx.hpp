/***********************************************************************//**
	@file
***************************************************************************/
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#define GRAED_PLATFORM "mac"
#define GRAED_PLATFORM_MAC

#else
#error "not support platform"
#endif
/***********************************************************************//**
	@brief 
***************************************************************************/
#if defined(GRAED_PLATFORM_MAC)
#define _FILE_OFFSET_BITS 64
#define __WXMAC__
#define __WXOSX__
#define __WXOSX_COCOA__
#endif

#include <wx/wx.h>
#include <wx/aui/aui.h>
/***********************************************************************//**
	@brief 
***************************************************************************/
namespace graed {
class Application;
class Canvas;
class MainFrame;
}
/***********************************************************************//**
	$Id$
***************************************************************************/

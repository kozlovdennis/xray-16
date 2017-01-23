#pragma once

#include "Common/Platform.hpp"

#ifdef XRSCRIPTENGINE_EXPORTS
#define XRSCRIPTENGINE_API XR_EXPORT
#else
#define XRSCRIPTENGINE_API XR_IMPORT
#endif

#pragma warning(disable : 4244)
#pragma warning(disable : 4995)
#pragma warning(disable : 4267)
#pragma warning(disable : 4100) // unreferenced formal parameter

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4456) // declaration of 'x' hides previous local declaration
#pragma warning(disable : 4458) // declaration of 'x' hides class member
#pragma warning(disable : 4459) // declaration of 'x' hides global declaration
#pragma warning(disable : 4913) // user defined binary operator 'x' exists but no overload could convert all operands
#pragma warning(disable : 4297) // function assumed not to throw exception but does
// XXX: define LUABIND_DYNAMIC_LINK in engine config header
#include <luabind/adopt_policy.hpp>
#include <luabind/class.hpp>
#include <luabind/iterator_policy.hpp>
#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <luabind/operator.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>

#pragma warning(default : 4127)
#pragma warning(default : 4456)
#pragma warning(default : 4458)
#pragma warning(default : 4459)
#pragma warning(default : 4913)
#pragma warning(default : 4297)

#pragma warning(default : 4244)
#pragma warning(default : 4995)
#pragma warning(default : 4267)
#pragma warning(default : 4100)

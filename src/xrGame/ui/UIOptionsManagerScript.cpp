#include "UIOptionsManagerScript.h"
#include "UIOptionsItem.h"
#include "pch_script.h"
#include "xrScriptEngine/ScriptExporter.hpp"

using namespace luabind;

void CUIOptionsManagerScript::SetCurrentValues(const char* group)
{
    CUIOptionsItem::GetOptionsManager()->SetCurrentValues(group);
}

void CUIOptionsManagerScript::SaveBackupValues(const char* group)
{
    CUIOptionsItem::GetOptionsManager()->SaveBackupValues(group);
}

void CUIOptionsManagerScript::SaveValues(const char* group)
{
    CUIOptionsItem::GetOptionsManager()->SaveValues(group);
}

void CUIOptionsManagerScript::UndoGroup(const char* group)
{
    CUIOptionsItem::GetOptionsManager()->UndoGroup(group);
}

void CUIOptionsManagerScript::OptionsPostAccept()
{
    CUIOptionsItem::GetOptionsManager()->OptionsPostAccept();
}

void CUIOptionsManagerScript::SendMessage2Group(const char* group, const char* message)
{
    CUIOptionsItem::GetOptionsManager()->SendMessage2Group(group, message);
}

bool CUIOptionsManagerScript::NeedSystemRestart()
{
    return CUIOptionsItem::GetOptionsManager()->NeedSystemRestart();
}
bool CUIOptionsManagerScript::NeedVidRestart()
{
    return CUIOptionsItem::GetOptionsManager()->NeedVidRestart();
}

SCRIPT_EXPORT(CUIOptionsManagerScript, (), {
    module(luaState)[class_<CUIOptionsManagerScript>("COptionsManager")
                         .def(constructor<>())
                         .def("SaveBackupValues", &CUIOptionsManagerScript::SaveBackupValues)
                         .def("SetCurrentValues", &CUIOptionsManagerScript::SetCurrentValues)
                         .def("SaveValues", &CUIOptionsManagerScript::SaveValues)
                         .def("UndoGroup", &CUIOptionsManagerScript::UndoGroup)
                         .def("OptionsPostAccept", &CUIOptionsManagerScript::OptionsPostAccept)
                         .def("SendMessage2Group", &CUIOptionsManagerScript::SendMessage2Group)
                         .def("NeedSystemRestart", &CUIOptionsManagerScript::NeedSystemRestart)
                         .def("NeedVidRestart", &CUIOptionsManagerScript::NeedVidRestart)];
});

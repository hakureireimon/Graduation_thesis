local M = UnLua.Class()
local BindKey = UnLua.Input.BindKey
BindKey(M, "F", "Pressed", UE.AUGCItemFrameworkCharacter.OnFPressed)

return M
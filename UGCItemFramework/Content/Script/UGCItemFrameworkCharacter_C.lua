local M = UnLua.Class()
local BindKey = UnLua.Input.BindKey

BindKey(M, "F", "Pressed", UE.AUGCItemFrameworkCharacter.OnFPressed)
BindKey(M, "B", "Pressed", UE.AUGCItemFrameworkCharacter.ShowOrHideBag)

function M:ReceiveBeginPlay()
    self.OnGenerateItem:Add(self, self.test)
end

function M:test()
    print('UnLua bind delegate success')
end

return M
local M = UnLua.Class()

function M:ReceiveBeginPlay()
    print('CPP->Lua Success')
    self:TestUnLua()
end

function M:TestUnLua()
    self.Overridden.TestUnLua(self)
    print('Override Success')
end

function M:ReceiveEndPlay()
    self:ClearMap()
end

return M
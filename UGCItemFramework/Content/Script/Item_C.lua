local M = UnLua.Class()

function M:ReceiveBeginPlay()
    self.EventOnItemPickedUp:Add(self, self.ItemPickedUp)
end

function M:ItemPickedUp()
    print('overlap bind success')
end

return M
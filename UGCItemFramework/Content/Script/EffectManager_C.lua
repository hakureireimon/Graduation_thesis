local M = UnLua.Class()

function M:ReceiveBeginPlay()
    self.ConditionAndEffectMap = {}
end

function M:ReceiveEndPlay()
    self:ClearMap()
end

function M:RegisterItem(item)
    if item then
        local Properties = item:GetUGCProperty()
        for _, effect in pairs(Properties.Effects) do
            if not self.ConditionAndEffectMap[Properties.Condition] then
                self.ConditionAndEffectMap[Properties.Condition] = {}
            end
            table.insert(self.ConditionAndEffectMap[Properties.Condition], effect)
        end
    else
        print("RegisterItem: item is nil")
    end
end

function M:ApplyEffect(effect, params)
    print('ApplyEffect:' .. effect, params)
end

function M:SendSignal(signal, ...)
    local params = {...}

    coroutine.resume(coroutine.create(function(WorldContextObject, duration)
        UE.UKismetSystemLibrary.Delay(WorldContextObject, duration)
        if next(self.ConditionAndEffectMap) ~= nil then
            for condition, effects in pairs(self.ConditionAndEffectMap) do
                if condition == signal then
                    for _, effect in ipairs(effects) do
                        self:ApplyEffect(effect, params)
                    end
                end
            end
        else
            print("SendSignal: ConditionAndEffectMap is empty")
        end
    end), self, 0.016)
end

return M
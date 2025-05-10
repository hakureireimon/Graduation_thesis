local M = UnLua.Class()

require("LuaPanda").start("127.0.0.1", 8818);

function M:ReceiveBeginPlay()
    -- self.ConditionAndEffectMap = {}
    self.ItemEffectMap = {}
end

function M:ReceiveEndPlay()
    self:ClearMap()
end

function M:RegisterItem(item)
    if item then
        local Properties = item:GetUGCProperty()
        local Effects = Properties.Effects
        local PackedEffects = {}
        for i=1, Effects:Length() do
            table.insert(PackedEffects, Effects[i])
        end
        table.insert(self.ItemEffectMap, {
            Id = Properties.Id,
            Condition = Properties.Condition,
            Effects = PackedEffects
        })
    else
        print("RegisterItem: item is nil")
    end
end

local function split(str, delimiter)
    local result = {}
    for match in (str .. delimiter):gmatch("([^" .. delimiter .. "]+)") do
        table.insert(result, match)
    end
    return result
end

local function parseParams(paramStrs)
    local params = {}
    for _, paramStr in ipairs(paramStrs) do
        local keyValue = split(paramStr, ":")
        if #keyValue == 2 then
            local key = keyValue[1]
            local value = keyValue[2]
            params[key] = value
        end
    end
    return params
end

local function mergeTables(t1, t2)
    local merged = {}
    for k, v in pairs(t1) do
        merged[k] = v
    end
    for k, v in pairs(t2) do
        merged[k] = v
    end
    return merged
end

function M:ApplyEffect(effect, params)
    print('ApplyEffect: ' .. effect, params)

    local EffectLibrary = require("EffectLibrary_C")

    local parts = split(effect, "-")

    local effectFunctionName = table.remove(parts, 1)
    local effectParams = parseParams(parts)
    params = parseParams(params)
    local effectFunction = EffectLibrary[effectFunctionName]
    local finalParams = mergeTables(effectParams, params or {})
    finalParams["character"] = UE.UGameplayStatics.GetPlayerCharacter(self:GetWorld(), 0)

    if effectFunction then
        effectFunction(finalParams)
    else
        print("Effect not found: " .. effectFunctionName)
    end
end

function M:ExecuteItemEffects(effects, params)
    if effects then
        coroutine.resume(coroutine.create(function()
            for _, effect in ipairs(effects) do
                self:ApplyEffect(effect, params)
            end
        end))
    else
        print("ExecuteItemEffects: Item data is nil")
    end
end

function M:SendSignal(signal, ...)
    local params = {...}
    coroutine.resume(coroutine.create(function(WorldContextObject, duration)
        UE.UKismetSystemLibrary.Delay(WorldContextObject, duration)
        for _, itemData in ipairs(self.ItemEffectMap) do
            if itemData.Condition == signal then
                self:ExecuteItemEffects(itemData.Effects, params)
            end
        end
    end), self, 0.016)
end

return M
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type JsonDeserializer_C
local M = UnLua.Class()
local rapidjson = require("rapidjson")

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

local RelativePath = debug.getinfo(1, "S").source
local TargetPath = string.gsub(RelativePath, "Script/JsonDeserializer_C.lua", "UGCItemFramework/Configuration.json")

local EffectsList = {}
local ItemPool = {}

function AddItemToPool(Id, Name, Type, Description, Icon, Effects, Charge, Condition)
    local Item = {}
    Item.Id = Id
    Item.Name = Name
    Item.Type = Type
    Item.Description = Description
    Item.Icon = Icon
    Item.Effects = Effects
    Item.Charge = Charge
    Item.Condition = Condition
    ItemPool[Id] = Item
end

function M:ReceiveBeginPlay()
    local JsonData = io.open(TargetPath, "r")
    if JsonData then
        local JsonString = JsonData:read("*a")
        JsonData:close()

        local data, err = rapidjson.decode(JsonString)
        if err then
            print("Error:", err)
            return
        end

        if data.Items and #data.Items > 0 then
            for _, Item in ipairs(data.Items) do
                local Id = Item.Id
                local Name = Item.Name
                local Type = Item.Type
                local Description = Item.Description
                local Icon = Item.Icon
                local Effects = Item.Effects
                local Charge = Item.Charge
                local Condition = Item.Condition
                AddItemToPool(Id, Name, Type, Description, Icon, Effects, Charge, Condition)
                for _, value in pairs(Effects) do
                    if not EffectsList[value] then
                        table.insert(EffectsList, value)
                    end
                end
            end
        end
    end

    if not _G._UGC then
        _G._UGC = {}
        _G._UGC.EffectsList = EffectsList
        _G._UGC.ItemPool = ItemPool
        _G._UGC.isConfigLoaded = true
    else
        _G._UGC.EffectsList = EffectsList
        _G._UGC.ItemPool = ItemPool
        _G._UGC.isConfigLoaded = true
    end
end

-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

return M

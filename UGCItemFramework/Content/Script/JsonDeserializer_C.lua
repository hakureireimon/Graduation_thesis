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
local ConditionList = {}
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

local itemManagerClass = UE.AItemManager

function M:OnItemManagerCreated()
    local World = self:GetWorld()
    local itemManagerInstance = UE.UGameplayStatics.GetActorOfClass(World, itemManagerClass)
    if itemManagerInstance then
        print("Found AItemManager instance: ", itemManagerInstance)

        for _, Effect in pairs(EffectsList) do
            print("Adding Effect: ", Effect)
            itemManagerInstance:AddEffect(Effect)
        end
        for _, Condition in pairs(ConditionList) do
            print("Adding Condition: ", Condition)
            itemManagerInstance:AddCondition(Condition)
        end
    else
        print("AItemManager instance not found")
        self:DelayFunc(0.1)
    end
end

function M:CheckForItemManager()
    self:OnItemManagerCreated()
end

function M:DelayFunc(duration)
    coroutine.resume(coroutine.create(
        function(WorldContextObject, duration)
            UE.UKismetSystemLibrary.Delay(WorldContextObject, duration)
            WorldContextObject:CheckForItemManager()
        end
    ), self, duration)
end

function M:ReceiveBeginPlay()
    self:CheckForItemManager()

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
                if not ConditionList[Condition] then
                    table.insert(ConditionList, Condition)
                end
            end
        end
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

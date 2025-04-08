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
require("LuaPanda").start("127.0.0.1", 8818);

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

local RelativePath = debug.getinfo(1, "S").source
local TargetPath = string.gsub(RelativePath, "Script/JsonDeserializer_C.lua", "UGCItemFramework/Configuration.json")

local EffectsList = {}
local ConditionList = {}
local ItemPool = {}

function AddItemToPool(Id, Name, Description, Icon, Effects, Condition)
    local Item = {}
    Item.Id = Id
    Item.Name = Name
    Item.Description = Description
    Item.Icon = Icon
    Item.Effects = Effects
    Item.Condition = Condition
    ItemPool[#ItemPool+1] = Item
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
        for i=1, #ItemPool do
            local Item = ItemPool[i]
            local Id = Item.Id
            local Name = Item.Name
            local Description = Item.Description
            local Icon = Item.Icon
            local Effects = Item.Effects
            local Condition = Item.Condition
            print("Adding Item: ", Id, Name, Description, Icon, Effects, Condition)
            itemManagerInstance:AddItemToPool(Id, Name, Description, Icon, Effects, Condition)
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
                local Description = Item.Description
                local Icon = Item.Icon
                local Effects = Item.Effects
                local Condition = Item.Condition
                AddItemToPool(Id, Name, Description, Icon, Effects, Condition)
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

    TargetPath = string.gsub(RelativePath, "Content/Script/JsonDeserializer_C.lua", "Module/UserConfig.json")
    local UserJsonData = io.open(TargetPath, "r")
    if UserJsonData then
        local UserJsonString = UserJsonData:read("*a")
        UserJsonData:close()

        local userData, err = rapidjson.decode(UserJsonString)
        if err then
            print("Error parsing user JSON:", err)
            return
        end

        if userData.Items and #userData.Items > 0 then
            for _, Item in ipairs(userData.Items) do
                Item.Id = "99" .. Item.Id
            end

            for _, Item in ipairs(userData.Items) do
                local Id = Item.Id
                local Name = Item.Name
                local Description = Item.Description
                local Icon = Item.Icon
                local Effects = Item.Effects
                local Condition = Item.Condition
                AddItemToPool(Id, Name, Description, Icon, Effects, Condition)
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

    self:CheckForItemManager()
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

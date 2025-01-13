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

local OnConfigurationLoaded = UE.SimpleMulticastDelegate()

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

local RelativePath = debug.getinfo(1, "S").source
local TargetPath = string.gsub(RelativePath, "Script/JsonDeserializer_C.lua", "UGCItemFramework/Configuration.json")

local EffectsList = {}

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
                local EffectData = Item.Effects
                for _, value in pairs(EffectData) do
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
        _G._UGC.isConfigLoaded = true
    else
        _G._UGC.EffectsList = EffectsList
        _G._UGC.isConfigLoaded = true
    end

    OnConfigurationLoaded:Broadcast()
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

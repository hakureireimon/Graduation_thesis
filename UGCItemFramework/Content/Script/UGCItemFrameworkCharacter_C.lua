local M = UnLua.Class()
local BindKey = UnLua.Input.BindKey
require("LuaPanda").start("127.0.0.1", 8818);

BindKey(M, "F", "Pressed", UE.AUGCItemFrameworkCharacter.OnFPressed)
BindKey(M, "B", "Pressed", UE.AUGCItemFrameworkCharacter.ShowOrHideBag)
BindKey(M, "E", "Pressed", function(self)
    local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
    EffectManager:SendSignal('EPressed', "extra:666")
end)
BindKey(M, "R", "Pressed", function(self)
    local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
    EffectManager:SendSignal('RPressed', "extra:666")
end)

local ReversedLocation = UE.FVector(0, 0, 0)

function M:ReceiveBeginPlay()
    self.OnGenerateItem:Add(self, self.test)
    self.PositionRecord = {}
    self.AccumulateTime = 0
end

function M:test()
    local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
    EffectManager:SendSignal('ItemGenerated', "extra:666")
end

function M:ReceiveTick(DeltaSeconds)
    self.Overridden.ReceiveTick(self, DeltaSeconds)
    self.AccumulateTime = self.AccumulateTime + DeltaSeconds
    if(self.AccumulateTime > 1) then
        self.AccumulateTime = 0
        local pos = self:K2_GetActorLocation()
        table.insert(self.PositionRecord, pos)
        if (#self.PositionRecord > 4) then
            table.remove(self.PositionRecord, 1)
        end
        ReversedLocation = self.PositionRecord[1]
    end
end

function M:GetReversedPosition()
    return ReversedLocation
end

return M
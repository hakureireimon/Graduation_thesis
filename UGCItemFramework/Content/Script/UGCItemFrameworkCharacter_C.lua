local M = UnLua.Class()
local BindKey = UnLua.Input.BindKey

BindKey(M, "F", "Pressed", UE.AUGCItemFrameworkCharacter.OnFPressed)
BindKey(M, "B", "Pressed", UE.AUGCItemFrameworkCharacter.ShowOrHideBag)

function M:ReceiveBeginPlay()
    self.OnGenerateItem:Add(self, self.test)
end

function M:test()
    local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
    EffectManager:SendSignal('ItemGenerated', "extra:666")
end

function M:OnEPressed()
    local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
    EffectManager:SendSignal('EPressed', "extra:666")
end

return M
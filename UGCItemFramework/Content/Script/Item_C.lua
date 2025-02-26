local M = UnLua.Class()

function M:ReceiveBeginPlay()
    self.EventOnItemPickedUp:Add(self, self.ItemPickedUp)
end

function M:ItemPickedUp(OtherActor)
    if not OtherActor then
        print('OtherActor is nil')
        return
    end
    local Character = OtherActor:Cast(UE.AUGCItemFrameworkCharacter)
    if Character then
        Character:AddItemToInventory(self)

        local EffectManager = UE.UGameplayStatics.GetActorOfClass(self:GetWorld(), UE.AEffectManager)
        if EffectManager then
            EffectManager:RegisterItem(self)
        else
            print('EffectManager is nil')
        end

        self:K2_DestroyActor()
    else
        print('not character')
    end
end

return M
local M = UnLua.Class()

function M.Test(params)
    if params["origin"] then
        print(params["origin"])
    end
    if params["extra"] then
        print(params["extra"])
    end
end

function M.Flash(params)
    if params["character"] and params["distance"] then
        local Character = params["character"]
        local FollowCamera = Character.FollowCamera
        if not FollowCamera then
            print("Follow Camera not found!")
            return
        end
        local CurrentLocation = Character:K2_GetActorLocation()
        local ForwardVector = FollowCamera:GetForwardVector()
        local Distance = tonumber(params["distance"])
        local NewLocation = CurrentLocation + ForwardVector * Distance

        Character:K2_SetActorLocation(NewLocation, false, nil, true)
        local EffectManager = UE.UGameplayStatics.GetActorOfClass(Character:GetWorld(), UE.AEffectManager)
        EffectManager:SendSignal('PositionChanged', "extra:666")
    end
end

function M.Reverse(params)
    if params["character"] then
        local Character = params["character"]
        local LuaCharacter = require("UGCItemFrameworkCharacter_C")
        local Location = LuaCharacter:GetReversedPosition()

        Character:K2_SetActorLocation(Location, false, nil, true)
        local EffectManager = UE.UGameplayStatics.GetActorOfClass(Character:GetWorld(), UE.AEffectManager)
        EffectManager:SendSignal('PositionChanged', "extra:666")
    end
end

function M.Chaos(params)
    if params["character"] and params["angle"] then
        local Character = params["character"]
        local Angle = params["angle"]

        local CurrentRotation = Character:K2_GetActorRotation()

        local NewRotation = UE.FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + Angle, CurrentRotation.Roll)

        Character:K2_SetActorRotation(NewRotation, false)
        local EffectManager = UE.UGameplayStatics.GetActorOfClass(Character:GetWorld(), UE.AEffectManager)
        EffectManager:SendSignal('AngleChanged', "extra:666")
    end
end

function M.Delay(params)
    if params["character"] and params["duration"] then
        local Character = params["character"]
        local Duration = tonumber(params["duration"])
        if Duration then
            UE.UKismetSystemLibrary.Delay(Character, Duration)
        end
    end
end

return M
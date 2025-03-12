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
    end
end

function M.Reverse(params)
    if params["character"] then
        local Character = params["character"]
        local LuaCharacter = require("UGCItemFrameworkCharacter_C")
        local Location = LuaCharacter:GetReversedPosition()

        Character:K2_SetActorLocation(Location, false, nil, true)
    end
end

return M
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
    if params["character"] and params["X"] and params["Y"] and params["Z"] then

        local Character = params["character"]
        local CurrentLocation = Character:K2_GetActorLocation()
        local NewLocation = CurrentLocation + UE.FVector(params["X"], params["Y"], params["Z"])

        Character:K2_SetActorLocation(NewLocation, false, nil, true)
    end
end

return M
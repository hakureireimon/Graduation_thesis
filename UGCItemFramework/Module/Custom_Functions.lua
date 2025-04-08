return {
    CustomFunction = function(params)
        if params["message"] then
            print("CustomFunction says: " .. params["message"])
        else
            print("CustomFunction was called without a message")
        end
    end
}
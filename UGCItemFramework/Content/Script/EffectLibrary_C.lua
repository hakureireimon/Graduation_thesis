local M = UnLua.Class()

function M.Test(params)
    if params["origin"] then
        print(params["origin"])
    end
    if params["extra"] then
        print(params["extra"])
    end
end

return M
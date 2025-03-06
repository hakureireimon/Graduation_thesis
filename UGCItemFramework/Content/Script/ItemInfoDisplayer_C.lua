--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
local M = UnLua.Class()

function M:Initialize()
    self.TextBlocks = {
        self:FindWidget("ItemName"),
        self:FindWidget("ItemDescription"),
        self:FindWidget("ItemCondition"),
        self:FindWidget("ItemEffects"),
    }
end

function M:ShowTextBlocks()
    for _, TextBlock in ipairs(self.TextBlocks) do
        if TextBlock then
            TextBlock:SetVisibility(UE.ESlateVisibility.Visible)
        end
    end
end

function M:HideTextBlocks()
    for _, TextBlock in ipairs(self.TextBlocks) do
        if TextBlock then
            TextBlock:SetVisibility(UE.ESlateVisibility.Hidden)
        end
    end
end

function M:SetText(ItemInfo)
    self.TextBlocks[1]:SetText(ItemInfo.Name)
    self.TextBlocks[2]:SetText(ItemInfo.Description)
    self.TextBlocks[3]:SetText(ItemInfo.Condition)
    self.TextBlocks[4]:SetText(ItemInfo.Effects)
end

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M

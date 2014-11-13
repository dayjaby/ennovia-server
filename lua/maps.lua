maps = {TestMap = 1}
testmap = Map(maps.TestMap,"tree_scene.3ds","",27,27)






class 'Chest' (Locatable)
function Chest:__init(pos)
  print(pos.x * pos.y)
  Locatable.__init(self,pos,"Chest","treasure_chest.obj","treasure_chest.jpg")
end

function Chest:getOptionList(player)
  ol = Locatable.getOptionList(self,player)
  ol:add(CustomOption("Count Money",
    function(performer)
        print("100g in there!")
    end
  ))
  return ol
end

Chest(Position(2,2,testmap))

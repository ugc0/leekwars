global chests;

global chest_dangerous_area = [];

function update_chest_danger_area() {
	chests = arrayFilter(getEnemies(),function(x){return (isAlive(x) and getType(x)==ENTITY_CHEST);});
	for (var chest in chests) {
		debugC(getName(chest), COLOR_BLUE);
		var center = getCell(chest);
		var chips = arrayFilter(getChips(chest),function(x){
			var effects = getChipEffects(x);
			for (var effect in effects) {
				if (effect[0]==EFFECT_DAMAGE) return true;
			}
			return false;
		});
		
		for (var cp in chips) {
			var mini=999;
			var maxi=0;
			debugC(getChipName(cp), COLOR_BLUE);
			var new_mini = getChipMinRange(cp);
			var new_maxi = getChipMaxRange(cp);
			var zonearea = getChipArea(cp);
			if (zonearea==AREA_CIRCLE_1) {
				new_maxi++;
				if (new_mini>=1) new_mini--;
			} else if (zonearea==AREA_CIRCLE_2) {
				new_maxi+=2;
				if (new_mini>=2) new_mini-=2;
			} else if (zonearea==AREA_CIRCLE_3) {
				new_maxi+=3;
				if (new_mini>=3) new_mini-=3;
			}
			debugC(new_mini+":"+new_maxi, COLOR_BLUE);
			if (new_maxi>maxi) maxi = new_maxi;
			if (new_mini<mini) mini = new_mini;
			debugC(mini+":"+maxi, COLOR_BLUE);
			if (mini==999 or maxi==0) {
				push(chest_dangerous_area,[]);
			} else {
				push(chest_dangerous_area,getZone(center,mini,maxi,chipNeedLos(cp)))
			}
		}
	}
	
	if (count(chests)>0) {
		chest_dangerous_area = arrayUnique(arrayFlatten(chest_dangerous_area));
		mark(chest_dangerous_area,COLOR_RED);
	} else {
		debugC("No chests found",COLOR_RED);
	}
}

if (getTurn()==1) {
	update_chest_danger_area();
}



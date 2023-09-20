global __CPS__ = getChips();

global __CP_HEAL__ = [];
global __CP_BUFF__ = [];
global __CP_NO_LOS__ = [];
global __CP_DAMAGE__ = [];

if (getTurn()==1) {
	for (var cp in __CPS__) {
		var effects = getChipEffects(cp)[0];
		var los = chipNeedLos(cp);
		debugC(getChipName(cp)+effects, COLOR_GREEN);
		if (effects[0]==EFFECT_HEAL) {
			push(__CP_HEAL__,cp)
		} else if (inArray([EFFECT_BUFF_AGILITY,EFFECT_BUFF_STRENGTH,EFFECT_BUFF_RESISTANCE,EFFECT_RAW_BUFF_AGILITY,EFFECT_RAW_BUFF_RESISTANCE,EFFECT_RAW_BUFF_STRENGTH], effects[0])) {
			push(__CP_BUFF__,cp)
		} else if (effects[0]==EFFECT_DAMAGE) {
			if (los) {
				push(__CP_DAMAGE__,cp);
			} else {
				push(__CP_NO_LOS__,cp);
			}
		} 
	}
	
	__CP_HEAL__=arraySort(__CP_HEAL__,function(cp1,cp2) {
		var e1 = getChipEffects(cp1)[0];
		var e2 = getChipEffects(cp2)[0];
		var c1 = getChipCost(cp1); if (c1==0) c1=1;
		var c2 = getChipCost(cp2); if (c2==0) c2=1;
		var p1 = (e1[1]+e1[2])/c1;
		var p2 = (e2[1]+e2[2])/c2;
		return p2-p1;
	});

	__CP_BUFF__=arraySort(__CP_BUFF__,function(cp1,cp2) {
		var e1 = getChipEffects(cp1)[0];
		var e2 = getChipEffects(cp2)[0];
		var c1 = getChipCost(cp1); if (c1==0) c1=1;
		var c2 = getChipCost(cp2); if (c2==0) c2=1;
		var p1 = (e1[1]+e1[2])/c1;
		var p2 = (e2[1]+e2[2])/c2;
		return p2-p1;
	});

	__CP_NO_LOS__=arraySort(__CP_NO_LOS__,function(cp1,cp2) {
		var e1 = getChipEffects(cp1)[0];
		var e2 = getChipEffects(cp2)[0];
		var c1 = getChipCost(cp1); if (c1==0) c1=1;
		var c2 = getChipCost(cp2); if (c2==0) c2=1;
		var p1 = (e1[1]+e1[2])/c1;
		var p2 = (e2[1]+e2[2])/c2;
		return p2-p1;
	});
	
	__CP_DAMAGE__=arraySort(__CP_DAMAGE__,function(cp1,cp2) {
		var e1 = getChipEffects(cp1)[0];
		var e2 = getChipEffects(cp2)[0];
		var c1 = getChipCost(cp1); if (c1==0) c1=1;
		var c2 = getChipCost(cp2); if (c2==0) c2=1;
		var p1 = (e1[1]+e1[2])/c1;
		var p2 = (e2[1]+e2[2])/c2;
		return p2-p1;
	});
	
	debugC("Heal chips : "+__CP_HEAL__, COLOR_GREEN);
	debugC("Buff chips : "+__CP_BUFF__, COLOR_BLUE);
	debugC("Flipendo chips : "+__CP_NO_LOS__, COLOR_RED);
	debugC("Incendio chips : "+__CP_DAMAGE__, COLOR_RED);
	
}

function HEAL() {
	if (count(__CP_HEAL__)==0) return false;
	debugC("HEALING "+__CP_HEAL__, COLOR_GREEN);
	for (var cp in __CP_HEAL__) while (useChip(cp)>=USE_SUCCESS);
	return true;
}

function BUFF() {
	if (count(__CP_BUFF__)==0) return false;
	debugC("BUFFING "+__CP_BUFF__, COLOR_BLUE);
	for (var cp in __CP_BUFF__) while (useChip(cp)>=USE_SUCCESS);
	return true;
}

function FLIPENDO(target) {
	if (count(__CP_NO_LOS__)==0) return false;
	debugC("FLIPENDO "+__CP_NO_LOS__, COLOR_RED);
	for (var cp in __CP_NO_LOS__) while (useChip(cp,target)>=USE_SUCCESS);
	return true;
}

function INCENDIO(target) {
	if (count(__CP_DAMAGE__)==0) return false;
	debugC("INCENDIO "+__CP_DAMAGE__, COLOR_RED);
	for (var cp in __CP_DAMAGE__) {
		if (useChip(cp, target)>=USE_SUCCESS) return true;
	}
	return false;
}
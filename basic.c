include("include/cells.h");
include("include/history.h");
include("include/chest.h");
include("include/chip.h");

if (count(chests)>0) __LAST_CHANCE__=45;

global __MODE__;

//if (getFightContext()==FIGHT_CONTEXT_TEST) return;

var T = getTurn();

if (T>=__LAST_CHANCE__) __TIMER__=0;

var max_MP = getMP();

var enemy = arraySort(arrayFilter(getEnemies(),function(x){return isAlive(x)}), function(e1, e2) {
	if (getType(e1)==ENTITY_LEEK) return -1; else return 1;
})[0];

if (__MODE__==MODE_NEW_ENEMY) {
	__MODE__=MODE_BARBARIAN;
	update_chest_danger_area();
}

if (getAIName(enemy)==null) {
	if (count(chests)>0 and T<__LAST_CHANCE__) {
		for (var chest in chests) {
			if (isAlive(chest)) {
				enemy = chest; break;
			}
		}
	} else if (count(chests)==0) {
		debugC("ENEMY HAS NO AI > RUSHING", COLOR_PURPLE);
		moveToward(enemy);
	}
}

var enemy_type=getType(enemy);

global my_max_HP = getTotalLife();
global enemy_max_HP = getTotalLife(enemy);

if (T == 1) {
	say("Hello, " + getName(enemy) + ". I see you're using the " + getAIName(enemy) + " AI...")
	setWeapon(WEAPON_PISTOL);
	__MODE__ = MODE_BARBARIAN;
}

global WP = getWeapon();
global WP_cost = getWeaponCost(WP);

var pos = getCell();
var target = getCell(enemy);

push(enemy_positions, target);
push(my_positions, pos);
push(enemy_hp, (100 * getLife(enemy)) / enemy_max_HP);
push(my_hp, (100 * getLife()) / my_max_HP);

var my_path = getRange(pos, getMP());
var enemy_path = getRange(target, getMP(enemy));
var offensive_zone = getZone(target, 0,7, true);

mark(offensive_zone, COLOR_PINK);

boolean hit = false;
global stuck = false;
global step = null;
global lock = false;
global new_target = 0;
global nexus = null;

var utility_cells = getSafeDangerCells(my_path, enemy_path);
var safe_cells = utility_cells[0];
var danger_cells = utility_cells[1];

if (enemy_type==ENTITY_CHEST or T>=__LAST_CHANCE__) {
	safe_cells = my_path;
	danger_cells = []; pushAll(danger_cells, chest_dangerous_area);
} else {
	pushAll(danger_cells, chest_dangerous_area);
}
safe_cells = arrayDelta(safe_cells, chest_dangerous_area);

debugC(danger_cells, COLOR_RED);
debugC(safe_cells, COLOR_GREEN);

safe_cells = sortNearest(safe_cells, target);
offensive_zone = sortNearest(offensive_zone, target);

if (T>=__LAST_CHANCE__ and count(chests)==0) {
	debugC("Let's end this !!", COLOR_ORANGE);
	moveToward(enemy);
}

if (T >= 3) {
	lock = enemy_positions[T] == enemy_positions[T - 1] or(enemy_positions[T] == enemy_positions[T - 2] and enemy_positions[T - 1] == enemy_positions[T - 3]);
	if (__MODE__ == MODE_AMBUSH and! lock) {
		__MODE__ = MODE_BARBARIAN;
	}
}

mark(danger_cells, COLOR_RED, 1);
mark(safe_cells, COLOR_GREEN, 1);

//POSITIONNING

boolean positionned = false;

for (var c in my_path) {
	if (inArray(offensive_zone, c)) {
		if (inArray(chest_dangerous_area,c)) {
			if (getPathLength(pos, c)>1) {
				debugC("I could move in to attack on cell "+c+" but that seems to be a the danger zone of a chest and i'm afraid...", COLOR_RED);
				continue;
			} else {
				debugC("LURKING ON CHEST",COLOR_PURPLE);
				moveTowardCell(c);
				break;
			}
		}
		debugC("POSITIONNING", COLOR_PURPLE);
		moveTowardCell(c); positionned = true; break;
	}
}

//FLIPENDO

if (!positionned and count(__CP_NO_LOS__)>0) {
	var flipendo_zone = getCellsToUseChipOnCell(__CP_NO_LOS__[0], target);
	for (var c in my_path) {
		if (inArray(flipendo_zone, c)) {
			FLIPENDO(target);
			break;
		}
	}
}

//HITTING 1

if (getLife()!=my_max_HP) INCENDIO(target);

if (canUseWeaponOnCell(target)) {
	while (WP_cost < getTP()) {
		if (useWeapon(enemy) <= 0) break;
		else hit = true;
	}
}

if (isDead(enemy)) {
	debugC("JUST KILLED AN ENEMY", COLOR_PURPLE);
	__MODE__=MODE_NEW_ENEMY;
	return;
}

if (inArray(danger_cells, pos)) {
	debugC("I AM IN DANGER AND THERE'S AN ACCESSIBLE SAFE CELL", COLOR_PURPLE);
	if (count(safe_cells) > 0) moveTowardCell(safe_cells[0]);
}

pos = getCell();

var warpath = getPath(pos, target);
if (__MODE__ == MODE_AMBUSH) warpath = nexus;
var warpath_length = 0;
if (warpath!=null) warpath_length = count(warpath);
 
mark(warpath, COLOR_BLUE, 1);
debugC("Warpath : " + warpath, COLOR_BLUE);

//RETREATING

if (__MODE__ == MODE_RETREAT) {
	debugC("Retreating step " + __TIMER__, COLOR_RED);
	if (__TIMER__ > 0) {
		if (count(danger_cells) > 0) {
			if (moveAwayFromCells(danger_cells)==0) {
				if (count(safe_cells)>0) {
					moveTowardCell(safe_cells[count(safe_cells)-1]);
				}
			}
		} else {
			moveTowardCell(306);
		}
		__TIMER__--;
	}
	if (__TIMER__ == 0) __MODE__ = MODE_BARBARIAN;
}

//REPLACING

if (__MODE__ == MODE_BARBARIAN) {
	debug("I'M A BARBARIAN IN A BARBAR WORLD !");
} else if (__MODE__ == MODE_AMBUSH) {
	debug("SWIFT AND SILENT AS SHADOWS WE MUST BE...");
	debugC(warpath, COLOR_PURPLE);
} else if (__MODE__ == MODE_RETREAT) {
	debug("FLY, YOU FOOL !");
}

var my_mp = getMP();
var my_tp = getTP();
debugC("I have " + my_mp + " MP", COLOR_ORANGE);
var move = 0;
while (my_mp > 0) {
	boolean moved = false;
	if (warpath_length > TOO_FAR_GONE) {
		debugC("I have time", COLOR_ORANGE);
		for (var m = my_mp; m > 0; m--) {
			debugC("Checking move cell : " + warpath[m + move - 1], COLOR_ORANGE);
			if (inArray(safe_cells, warpath[m + move - 1])) {
				debugC("I can move safely to " + warpath[m + move - 1] + " (" + (m) + ")", COLOR_PURPLE);
				moveTowardCell(warpath[m + move - 1], m);
				my_mp -= m;
				moved = true;
				move += m;
				if (nexus != null and __MODE__ == MODE_AMBUSH and count(nexus) > m)
					for (var i = 0; i < m; i++) shift(nexus);
				break;
			}
		}
	} else {
		debugC("I'm too far gone", COLOR_PURPLE);
		if (moveToward(enemy) == 0) break;
		moved = true;
	}
	if (!moved) break;
}

//HITTING 2

if (getLife()!=my_max_HP) INCENDIO(target);

if (canUseWeaponOnCell(target)) {
	while (WP_cost < getTP()) {
		if (useWeapon(enemy) <= 0) break;
		else hit = true;
	}
}

if (isDead(enemy)) {
	debugC("JUST KILLED AN ENEMY", COLOR_PURPLE);
	__MODE__=MODE_NEW_ENEMY;
	return;
}

//RETREATING

if (inArray(danger_cells, getCell()) and count(safe_cells)>0) {
	debugC("Let's take cover (" + getMP() + ")", COLOR_PURPLE);
	moveTowardCell(safe_cells[0]);
}

if (T >= 3) {
	stuck = (((getMP() == max_MP) or (my_positions[T] == my_positions[T - 2] and my_positions[T - 1] == my_positions[T - 3])) and !hit);
}

if (stuck) {
	if (T<__LAST_CHANCE__) {
		my_path = getRange(pos, 6 * max_MP);
	} else {
		my_path = getRange(pos, 8 * max_MP);
	}
	my_path = sortNearest(my_path, target);
	if (T<__LAST_CHANCE__) my_path = arrayChunk(my_path, count(my_path) / 2)[0];
	utility_cells = getSafeDangerCells(my_path, enemy_path);
	safe_cells = utility_cells[0];
	danger_cells = utility_cells[1];

	var border = sortNearest(borderZone(danger_cells), target);
	
	if (enemy_type==ENTITY_CHEST or T>=__LAST_CHANCE__) {
		safe_cells = my_path;
		danger_cells = []; pushAll(danger_cells, chest_dangerous_area);
	} else {
		pushAll(danger_cells, chest_dangerous_area);
	}
	safe_cells = arrayDelta(safe_cells, chest_dangerous_area);
	
	mark(safe_cells, COLOR_GREEN);
	debugC(safe_cells, COLOR_GREEN);
	mark(danger_cells, COLOR_RED);
	debugC(danger_cells, COLOR_RED);
	mark(offensive_zone, COLOR_PINK);
	debugC(offensive_zone, COLOR_PINK);
	mark(border, COLOR_CYAN);
	debugC(border, COLOR_CYAN);

	var opti_cells = [];

	for (var b in border) {
		for (var o in offensive_zone) {
			var l = getPathLength(b, o);
			if ((enemy_type==ENTITY_LEEK and l <= max_MP) or (enemy_type==ENTITY_CHEST and l <= 1)) {
				push(opti_cells, {
					from: b,
					to: o,
					d: l
				})
			}
		}
	}

	__MODE__ = MODE_RETREAT;
	if (count(opti_cells) > 1) {
		opti_cells = arraySort(opti_cells, function(c1, c2) {
			return c1.d - c2.d;
		})
	}

	debugC(opti_cells, COLOR_CYAN);
	var opti_cells_considered = 0;
	for (var oc in opti_cells) {
		if (opti_cells_considered>20) break;
		opti_cells_considered++;
		if (oc.d==null) continue;
		var optipath=null;
		if (pos!=oc.from) optipath = newPath(pos, oc.from, danger_cells, max_MP - 1);
		if (optipath == null) continue;
		var remaining_path_1 = getPath(oc.from, oc.to);
		var remaining_path_2 = getPath(oc.to, target);
		pushAll(optipath, remaining_path_1);
		pushAll(optipath, remaining_path_2);
		nexus = optipath;
		mark(nexus, COLOR_PURPLE);
		__MODE__ = MODE_AMBUSH;
		break;
	}

	if (__MODE__ == MODE_RETREAT) __TIMER__ = __DEFAULT_TIMER__;
}

//BOUCLAGE > RETREAT
if (T >= 10 and !hit) {
	if (my_positions[T] == my_positions[T - 2] and my_positions[T - 1] == my_positions[T - 3] and my_positions[T - 2] == my_positions[T - 4] and my_positions[T - 3] == my_positions[T - 5] and enemy_positions[T] == enemy_positions[T - 2] and enemy_positions[T - 1] == enemy_positions[T - 3] and enemy_positions[T - 2] == enemy_positions[T - 4] and enemy_positions[T - 3] == enemy_positions[T - 5]) {
		debugC("REPETITION SCHEMA DOUBLE", COLOR_ORANGE);
		__MODE__ = MODE_RETREAT;
		__TIMER__ = __DEFAULT_TIMER__;
	}
	if (my_positions[T] == my_positions[T - 3] and my_positions[T - 1] == my_positions[T - 4] and my_positions[T - 2] == my_positions[T - 5] and my_positions[T - 3] == my_positions[T - 6] and enemy_positions[T] == enemy_positions[T - 3] and enemy_positions[T - 1] == enemy_positions[T - 4] and enemy_positions[T - 2] == enemy_positions[T - 5] and enemy_positions[T - 3] == enemy_positions[T - 6]) {
		debugC("REPETITION SCHEMA TRIPLE", COLOR_ORANGE);
		__MODE__ = MODE_RETREAT;
		__TIMER__ = __DEFAULT_TIMER__;
	}
	if (my_positions[T] == my_positions[T - 4] and my_positions[T - 1] == my_positions[T - 5] and my_positions[T - 2] == my_positions[T - 6] and my_positions[T - 3] == my_positions[T - 7] and enemy_positions[T] == enemy_positions[T - 4] and enemy_positions[T - 1] == enemy_positions[T - 5] and enemy_positions[T - 2] == enemy_positions[T - 6] and enemy_positions[T - 3] == enemy_positions[T - 7]) {
		debugC("REPETITION SCHEMA QUADRUPLE", COLOR_ORANGE);
		__MODE__ = MODE_RETREAT;
		__TIMER__ = __DEFAULT_TIMER__;
	}
}
debugC(my_hp, COLOR_RED);
debugC(enemy_hp, COLOR_RED);
debugC(average(my_hp), COLOR_RED);
debugC(average(enemy_hp), COLOR_RED);

debugC("Le tour est terminé, j'ai dépensé : " + (100 * getOperations()) / OPERATIONS_LIMIT + " % des opérations disponibles.", COLOR_CYAN);

if (__MODE__ == MODE_BARBARIAN) {
	debug("FOR FROTON !");
} else if (__MODE__ == MODE_AMBUSH) {
	debug("I'LL BE RIGHT BACK !");
} else if (__MODE__ == MODE_RETREAT) {
	debug("MUSTN'T GO THAT WAY !");
}



if (getLife()<my_max_HP) {
	HEAL();
}

if (enemy_type!=ENTITY_CHEST) {
	var my_new_path = getRange(pos, getMP());
	for (var c in my_new_path) {
		if (inArray(offensive_zone, c)) {
			BUFF();
		}
	}
}
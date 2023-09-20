include("colors.h");

function arrayDelta(array1,array2) {
	var result = []+array1;
	var offset = 0;
	for(var key:var val in array1) {
		if (inArray(array2, val)) {remove(result, key-offset); offset++;}
	}
	return result;
}

function arrayCommon(array1,array2) {
	var P = arrayUnique(array1+array2);
	for (var c in P) {
		if (!inArray(array1, c) or !inArray(array2,c)) removeElement(P, c); 
	}
}

function affinePath(path) {
	debugC(path, COLOR_ORANGE);
	for (var i:var c in path) {
		var n = search(path,c,i+1);
		if (n>0) {
			for (var j=n-1;j>=i;j--) {
				remove(path, j);
			}
			return affinePath(path);
		}
	}
	return path;
}

function getSafeDangerCells(my_path,enemy_path) {
	var safe_cells = [];
	var danger_cells = [];
	for (var my_cell in my_path) {
		boolean safe = true;
		for (var enemy_cell in enemy_path) {
			if (getCellDistance(enemy_cell, my_cell) <= 7 and lineOfSight(enemy_cell, my_cell)) {
				safe = false;
				break;
			}
		}
		if (safe) push(safe_cells, my_cell);
		else push(danger_cells, my_cell);
	}
	return [safe_cells,danger_cells];
}

function sortNearest(array,cell) {
	return arraySort(array, function(c1, c2) {
		return getCellDistance(cell, c1) - getCellDistance(cell, c2);
	});
}

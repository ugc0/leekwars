include("utils.h");
include("colors.h");
include("param.h");

global __N__ = [
	612: [594],
	611: [593, 594],
	610: [592, 593],
	609: [591, 592],
	608: [590, 591],
	607: [589, 590],
	606: [588, 589],
	605: [587, 588],
	604: [586, 587],
	603: [585, 586],
	602: [584, 585],
	601: [583, 584],
	600: [582, 583],
	599: [581, 582],
	598: [580, 581],
	597: [579, 580],
	596: [578, 579],
	595: [578],
	577: [559, 594],
	560: [578, 543],
	542: [524, 559],
	525: [543, 508],
	507: [489, 524],
	490: [508, 473],
	472: [454, 489],
	455: [473, 438],
	437: [419, 454],
	420: [438, 403],
	402: [384, 419],
	385: [403, 368],
	367: [349, 384],
	350: [368, 333],
	332: [314, 349],
	315: [333, 298],
	297: [279, 314],
	280: [298, 263],
	262: [244, 279],
	245: [263, 228],
	227: [209, 244],
	210: [228, 193],
	192: [174, 209],
	175: [193, 158],
	157: [139, 174],
	140: [158, 123],
	122: [104, 139],
	105: [123, 88],
	87: [69, 104],
	70: [88, 53],
	52: [34, 69],
	35: [53, 18],
	17: [34],
	16: [33,34],
	15: [32,33],
	14: [31,32],
	13: [30,31],
	12: [29,30],
	11: [28,29],
	10: [27,28],
	9: [26,27],
	8: [25,26],
	7: [24,25],
	6: [23,24],
	5: [22,23],
	4: [21,22],
	3: [20,21],
	2: [19,20],
	1: [18,19],
	0: [18],
];

global __C__ = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574, 575, 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 606, 607, 608, 609, 610, 611, 612];

if (getTurn()==1) {
	for (var c in __C__) {
		if (__N__[c]==null) __N__[c]=[c-18,c-17,c+17,c+18];
	}
}

global __O__ = arrayFilter(__C__, function(x) {
	return isObstacle(x);
})

__C__ = arrayDelta(__C__, __O__);

global __Nstrict__ = mapMap(__N__, function(x) {
	return arrayDelta(x, __O__)
});

function getZone(center,r1,r2,los) {
	var P = [];
	var root = [center];
	var l = 0;
	var visited = [];
	while (count(root) > 0) {
		var new_root = [];
		root = arrayUnique(root);
		pushAll(visited, root);
		if (l>=r1) {
			for (var r in root) {
				if (!isObstacle(r)) push(P, r);
			}
			 
		}
		for (var r in root) {
			for (var n in __N__[r]) {
				if (!inArray(visited, n) and (!los or lineOfSight(center, n))) push(new_root, n);
			}
		}
		root = new_root;
		l++;
		if (l > r2) break;
	}
	return P;
}

function getRange(center, radius) {
	var P = [];
	var root = [center];
	var l = 0;
	var visited = [];
	while (count(root) > 0) {
		var new_root = [];
		root = arrayUnique(root);
		pushAll(P, root);
		pushAll(visited, root);
		for (var r in root) {
			for (var n in __Nstrict__[r]) {
				if (!inArray(visited, n)) push(new_root, n);
			}
		}
		root = new_root;
		l++;
		if (l > radius) break;
	}
	return P;
}

function newPath(start, end, avoid,leap) {
	if (isObstacle(start)) return null;
	if (isObstacle(end)) return null;
	var ancestors = new Map();
	var root = [[start]];
	for (var i=1;i<=leap;i++) {
		push(root,[]);
	}
	var visited = [];
	var iter = 0;
	boolean found = false;
	while (!found) {
		if (isEmpty(arrayFlatten(root))) break;
		iter++;
		if (iter > MAX_PATH_ITER) break;
		var new_root = [[]];
		for(var i=0;i<=leap;i++) {
			root[i]=arrayUnique(root[i]);
			pushAll(visited, root[i]);
			if (i>0) push(new_root,[]);
		}
		for(var i=leap;i>=0;i--) {
			for (var r in root[i]) {
				for (var n in __Nstrict__[r]) {
					if (!inArray(visited, n)) {
						if (!inArray(avoid,n)) {
							ancestors[n] = r;
							if (n == end) found = true;
							push(new_root[0], n);
						} else {
							if (i<leap) {
								ancestors[n] = r;
								push(new_root[i+1],n);
							}
						}
					}
				}
			}
		}
		root = new_root;
	}

	if (found) {
		var new_path = [end];
		var c = end;
		while (c != start) {
			c = ancestors[c];
			push(new_path, c)
		}
		clearMarks();
		mark(new_path,COLOR_PURPLE);
		pop(new_path);
		reverse(new_path);
		debugC(start+" > "+end+" : "+new_path, COLOR_PINK);
		return new_path;
	} else return null;
}

function borderZone(zone) {
	var border = [];
	for(var c in zone) {
		if (__Nstrict__[c]==null) continue
		for (var n in __Nstrict__[c]) {
			if (!inArray(zone, n) and !inArray(border, n)) push(border,n);
		}
	}
	return border;
}
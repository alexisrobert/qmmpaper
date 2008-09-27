print("Music paper script");
print("Copyright (c) 2007 Alexis ROBERT");
print("Bundled with QMMPaper v0.2.5, under GPL2");

var color = [0,0,0]; // Music paper lines are "all blacks" !

function draw() {
	mm = paper.getDpm();
	width = paper.getWidth();
	height = paper.getHeight();

	between_margin = 2;
	score_margin = 10;

	y = score_margin*mm;
	while (y+(5*between_margin*mm)+score_margin < height) {
		for (i = 0; i < 5; i++) {
			wrapper.addLine(0,y,width,y,color);
			y = y+(between_margin*mm);
		}
		y = y+(score_margin*mm);
	}
}

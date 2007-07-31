print("Millimetered paper script");
print("Copyright (c) 2007 Alexis ROBERT");
print("Bundled with QMMPaper v0.2, under GPL2");

var mm = 0;
var width = 0;
var height = 0;

var round_width = 0;
var round_height = 0;

function drawLine(lineno, horizontal) {
	color = 2;

	if (lineno % 10 == 0)
		color = 1;
	else if (lineno % 5 == 0)
		color = 3;

	z = 0;
	if (lineno % 10 == 0)
		z = 3;
	else if (lineno % 5 == 0)
		z = 2;

	if (horizontal == true)
		wrapper.addLine(lineno*mm,0,lineno*mm,round_height,color,z);
	else
		wrapper.addLine(0,lineno*mm,round_width,lineno*mm,color,z);
}

function draw() {
	mm = paper.getDpm();
	width = paper.getWidth();
	height = paper.getHeight();

	round_width = width - (width%mm);
	round_height = height - (height%mm);

	for (i = 0; i*mm < width; i++)
		drawLine(i, true);

	for (i = 0; i*mm < height; i++)
		drawLine(i, false);
}

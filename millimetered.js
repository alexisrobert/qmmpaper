print("Millimetered paper script");
print("Copyright (c) 2007 Alexis ROBERT");
print("Bundled with QMMPaper v0.2, under GPL2");

var colors = {'Black && &White': [[127,127,127],[208,208,208],[173,173,173]],
		'&Orange': [[255,144,0],[255,207,77],[255,184,29]],
		'&Blue': [[79,121,255],[156,198,255],[144,153,255]]};

var mm = 0;
var width = 0;
var height = 0;

var round_width = 0;
var round_height = 0;

function drawLine(lineno, horizontal) {
	color = 1;

	if (lineno % 10 == 0)
		color = 0;
	else if (lineno % 5 == 0)
		color = 2;

	z = 0;
	if (lineno % 10 == 0)
		z = 3;
	else if (lineno % 5 == 0)
		z = 2;

	if (horizontal == true)
		wrapper.addLine(lineno*mm,0,lineno*mm,height,current_color[color],z);
	else
		wrapper.addLine(0,lineno*mm,width,lineno*mm,current_color[color],z);
}

function draw() {
	mm = paper.getDpm();
	width = paper.getWidth();
	height = paper.getHeight();

	round_width = width;
	round_height = height;

	for (i = 0; i*mm < width; i++)
		drawLine(i, true);

	for (i = 0; i*mm < height; i++)
		drawLine(i, false);
}

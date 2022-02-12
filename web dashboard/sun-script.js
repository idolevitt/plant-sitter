var params = define();
main();

function main() {
	// main function, kicks off the functions
	params['sky'].onload = run;
	params['sky'].src = 'bg-sun-01.jpg';
}

function define() {
	// defines the context in the canvas, gradient and sky returned as an object
	var context = document.getElementById('sky-canvas').getContext('2d'),
			grad = context.createLinearGradient(0, 0, 0, context.canvas.height),
			sky = new Image();
	// add colours
	grad.addColorStop(0, '#F4E9BE');
	grad.addColorStop(0.75, '#F4E9BE');
	grad.addColorStop(1, '#E5AF67');
	context.shadowColor = '#ffffff';
	return {context: context, grad: grad, sky: sky}
}

function run() {
	// runs the main functions and main loop
	var context = params['context'];
	var grad = params['grad'];
	var sky = params['sky'];

	// init position vars
	var arc_centre = context.canvas.width * 0.8,
			arc_bottom = context.canvas.height * 1.1, //+ 15,
			vert_radius = context.canvas.height * 0.8, //* 0.8,
			horit_radius = context.canvas.width * 0.5; //* 0.50;

	var time = getRealTime(); // gets real time from function
	var timeMoon = (getRealTime() + 12.0) % 24.00;
	var sunrise = 7;          // default, but will obtain from Yahoo Weather API
	var sunset = 18;          // default, but will obtain from Yahoo Weather API

	mainloop();

	function mainloop() {
		// main loop that creates the animation
		// var time = getDemoTime();
		// var angleSun = getAngle(time);
		// var horitSun = arc_centre + horit_radius * Math.cos(angleSun);
		// var vertSun = arc_bottom + vert_radius * Math.sin(angleSun);
		//
		// var timeMoon = (getDemoTimeMoon() + 12) % 23.60;
		// var angleMoon = getAngle(timeMoon);
		// var horitMoon = arc_centre + horit_radius * Math.cos(angleMoon);
		// var vertMoon = arc_bottom + vert_radius * Math.sin(angleMoon);

		var time = getRealTime();
		var angleSun = getAngle(time + 12);
		var horitSun = arc_centre + horit_radius * Math.cos(angleSun);
		var vertSun = arc_bottom + vert_radius * Math.sin(angleSun);

		var timeMoon = (getRealTime() + 12.0) % 24.00;
		var angleMoon = Math.PI * timeMoon;
		var horitMoon = arc_centre + horit_radius * Math.cos(angleMoon);
		var vertMoon = arc_bottom + vert_radius * Math.sin(angleMoon);



		generateSky((time + 14) % 24);
		upldateSunLocation(horitSun, vertSun);
		upldateMoonLocation(horitMoon, vertMoon);
		requestAnimationFrame(mainloop);

		setInterval(function() {
			window.location.reload();
		}, 5000);
	}

	function getRealTime() {
		// returns real time as a number
		var date = new Date();
		return Number(date.getHours() + '.' + Math.round(date.getMinutes()*1.66));
	}

	function getDemoTime() {
		// returns a demo time that passes fast
		time += 0.033;
		if (time > 23.59) time = 0;
		return (time - sunrise) / (sunset - sunrise);
	}

	function getDemoTimeMoon() {
		// returns a demo time that passes fast
		timeMoon += 0.033;
		if (timeMoon > 23.59) timeMoon = 0;
		return (timeMoon - sunrise) / (sunset - sunrise);
	}

	function getAngle(time) {
		// returns angle for sun position
		return Math.PI + Math.PI * time;
	}

	function generateSky(time) {
		// generates the background
		time = Math.max(0, Math.min(1, time));
		context.drawImage(sky, (60 + (sky.width - 120) * time), 0, 1, sky.height, 0, 0, context.canvas.width, context.canvas.height);
	}

	function upldateSunLocation(h, v) {
		var img = document.getElementById('sun');
	 	img.style.left = 3 * h + "px";
		img.style.top = 4.5 * v + "px";
		// document.getElementById('body').appendChild(img);
	}

	function upldateMoonLocation(h, v) {
		var img = document.getElementById('moon');
		img.style.left = 3 * h + "px";
		img.style.top = 4.5  * v + "px";
		// document.getElementById('body').appendChild(img);
	}

}

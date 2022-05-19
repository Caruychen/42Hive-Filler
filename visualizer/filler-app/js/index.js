let play_result; 

function overlay_off() {
	document.getElementsByClassName("overlay")[0].style.display = "none";	
}

function set_loading() {
	document.getElementById("run").style.display = "none";
	document.getElementById("loading").style.display = "block";
}

function init_grid() {
	let grid = document.getElementsByClassName("grid-container")[0];
	for (let i = 0; i < 10000; i++) {
		let item = document.createElement("div");
		item.classList.add("grid-item");
		item.setAttribute("id", "item-1");
		grid.appendChild(item);
	}
}

function run_game() {
	set_loading();
	$.ajax({
		url: "run",
		success: function(data, status, xhr) {
			overlay_off();
			run_replay(data);
		}
	});
}

function run_replay(data) {
	const array = JSON.parse(data);
	let grid = $("div.grid-item");
	_set_state(grid, array[2]);
}

function _set_state(grid, state) {
	let indices = [];
	let indexFrom = 0;
	let index = 0;
	state.forEach((line, lnIndex) => {
		indices = [];
		indexFrom = 0;
		do {
			index = line.indexOf('O', indexFrom);
			if (index >= 0)
			{
				indices.push(index);
				indexFrom = index + 1;
			}
		} while (index >= 0);
	})
}

window.onload = init_grid;

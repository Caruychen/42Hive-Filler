let play_result; 

function overlay_off() {
	document.getElementsByClassName("overlay")[0].style.display = "none";	
}

function init_grid() {
	let grid = document.getElementsByClassName("grid-container")[0];
	for (let i = 0; i < 10000; i++) {
		let item = document.createElement("div");
		item.classList.add("grid-item");
		item.classList.add("item" + i);
		grid.appendChild(item);
	}
}

function run_game() {
	overlay_off();
}

window.onload = init_grid;

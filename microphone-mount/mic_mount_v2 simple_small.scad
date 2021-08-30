use <threads.scad>;
use <boxes.scad>;

module mic_mount() {

columns = 1000;
tube_len = 50;
b_len = 2;
b_len = 0;
b_peg_len = 2;
b_peg_len = 2;
t_peg_len = 3;
b_peg_r = 2.5;
t_peg_r = 1.65;

translate([0,0,12]) {
difference(){
		english_thread(5/8, 27, 0.55);
		cylinder(h = tube_len, r1 = 5.5,  r2 = 5.5, $fn = columns);
	}
}
//translate([0,0,25]) {
//difference(){
		//cylinder(h = b_len, r1 = 8,  r2 = 10, $fn = columns);
		//cylinder(h = b_len, r1 = 5.5,  r2 = 5.5, $fn = columns);
	//}
//}

difference(){
translate([0,0,25+b_len]) {
difference(){
		cylinder(h = 20, r1 = 8,  r2 =20, $fn = columns);
		cylinder(h = 20, r1 = 5.5,  r2 = 10, $fn = columns);
	}
	
}

translate([10,0,42]) {
		//roundedBox([12, 13, 15], 0, true, columns);
		roundedBox([7, 13, 7], 0, true, columns);
}



translate([0,0,35]) {
		rotate ([0,90,15]) {scale([1.0,0.5,1.0]){cylinder (h = 40, r=7, center = true, $fn=100);}}
	}
translate([0,0,35]) {
		rotate ([0,90,60]) {scale([1.0,0.5,1.0]){cylinder (h = 40, r=7, center = true, $fn=100);}}
	}

translate([0,0,35]) {
		rotate ([0,90,105]) {scale([1.0,0.5,1.0]){cylinder (h = 40, r=7, center = true, $fn=100);}}
	}
translate([0,0,35]) {
		rotate ([0,90,-30]) {scale([1.0,0.5,1.0]){cylinder (h = 40, r=7, center = true, $fn=100);}}
	}
}

difference(){
translate([0,0,45+b_len]) {
difference(){
		cylinder(h = 30, r1 = 20,  r2 = 10, $fn = columns);
		cylinder(h = 30, r1 = 16,  r2 = 10, $fn = columns);
	}
}

translate([10,0,42]) {
	roundedBox([50, 50, 70], 0, true, columns);
	//roundedBox([7, 13, 7], 0, true, columns);
}

}


difference(){

translate([0,0,50]) {
difference(){
		//cylinder(h = b_len, r1 = 20,  r2 = 20, $fn = columns);
		//cylinder(h = b_len, r1 = 14,  r2 = 9, $fn = columns);
	}
}



}



translate([9.5,9.5,45+b_len]) {
	cylinder(h = b_peg_len, r1 = b_peg_r,  r2 = b_peg_r, $fn = columns);
}

translate([9.5,9.5,45+b_len+b_peg_len]) {
	//english_thread(0.1120, 40, 0.11811);
	cylinder(h = t_peg_len, r1 = t_peg_r,  r2 = t_peg_r, $fn = columns);
}




translate([-9.5,-9.5,45+b_len]) {
	cylinder(h = b_peg_len, r1 = b_peg_r,  r2 = b_peg_r, $fn = columns);
}

translate([-9.5,-9.5,45+b_len+b_peg_len]) {
	//english_thread(0.1120, 40, 0.11811);
	cylinder(h = t_peg_len, r1 = t_peg_r,  r2 = t_peg_r, $fn = columns);
}



translate([-9.5,9.5,45+b_len]) {
	cylinder(h = b_peg_len, r1 = b_peg_r,  r2 = b_peg_r, $fn = columns);
}

translate([-9.5,9.5,45+b_len+b_peg_len]) {
	//english_thread(0.1120, 40, 0.11811);
	cylinder(h = t_peg_len, r1 = t_peg_r,  r2 = t_peg_r, $fn = columns);
}



translate([9.5,-9.5,45+b_len]) {
	cylinder(h = b_peg_len, r1 = b_peg_r,  r2 = b_peg_r, $fn = columns);
}

translate([9.5,-9.5,45+b_len+b_peg_len]) {
	//english_thread(0.1120, 40, 0.11811);
	cylinder(h = t_peg_len, r1 = t_peg_r,  r2 = t_peg_r, $fn = columns);
}

}

mic_mount();
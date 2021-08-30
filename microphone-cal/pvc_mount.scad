use <boxes.scad>;

module pvc_mount() {

	columns = 1000;
	tube_len = 105; //105 = final (peak at 1kHz)
	driver_mount = 18;
	inner_d_sm = 12;
	inner_d_la = 35;
	tube_wall_th = 6; //6 = final
	sensor_mnt_h = 5;
	mountplate_d = 35;
	screw_sep = 19;
	screw_d = 3.5;

	corner_r = 5;

	cap_len = 18; //18 = final
	cap_d = 14;

	port_d = 2;

	screw_r = screw_d/2;
	
	inner_r_sm = inner_d_sm/2;
	inner_r_la = inner_d_la/2;

	cap_r = cap_d/2;

	port_r = port_d/2;
	
	////////Combined adaptor mount
	difference() {

			translate([0,0,sensor_mnt_h/2]) { roundedBox([mountplate_d, mountplate_d, sensor_mnt_h], corner_r, true, columns); }
			
		union() {
			cylinder(60,inner_r_sm+tube_wall_th/2,inner_r_sm+tube_wall_th/2, $fn = columns);

			translate([screw_sep/2,screw_sep/2,-1]) {
				cylinder(sensor_mnt_h+1,screw_r,screw_r, $fn = columns);
			}
			translate([-screw_sep/2,-screw_sep/2,-1]) {
				cylinder(sensor_mnt_h+1,screw_r,screw_r, $fn = columns);
			}

			translate([-screw_sep/2,screw_sep/2,-1]) {
				cylinder(sensor_mnt_h+1,screw_r,screw_r, $fn = columns);
			}

			translate([screw_sep/2,-screw_sep/2,-1]) {
				cylinder(sensor_mnt_h+1,screw_r,screw_r, $fn = columns);
			}
			
		}
	}

	difference(){
	difference(){
		cylinder(h = tube_len, r1 = inner_r_sm+tube_wall_th/2, r2 = inner_r_la+tube_wall_th/2, $fn = columns);
		cylinder(h = tube_len, r1 = inner_r_sm,   r2 = inner_r_la, $fn = columns);
	}
	translate([0,0,tube_len - port_r]) {
		rotate ([90,0,0]) {cylinder (h = 100, r=port_r, center = true, $fn=100);}
		rotate ([0,90,0]) {cylinder (h = 100, r=port_r, center = true, $fn=100);}
	}
}

	translate([0,0,tube_len]) {
				difference(){
					cylinder(h = driver_mount, r1 = inner_r_la+tube_wall_th/2, r2 = inner_r_la+tube_wall_th/2, $fn = columns);
					cylinder(h = driver_mount, r1 = inner_r_la, r2 = inner_r_la, $fn = columns);
				}
				translate([inner_r_la+2,0]) {cylinder(h = driver_mount, r1 = 1, r2 = 2, $fn = columns);}
				translate([-inner_r_la-2,0]) {cylinder(h = driver_mount, r1 = 1, r2 = 2, $fn = columns);}
				translate([0,inner_r_la+2]) {cylinder(h = driver_mount, r1 = 1, r2 = 2, $fn = columns);}
				translate([0,-inner_r_la-2]) {cylinder(h = driver_mount, r1 = 1, r2 = 2, $fn = columns);}
			}

	

	////SLM block plate
//	translate([50,0,0]) {
//		difference() {
//					translate([0,0,sensor_mnt_h/2]) { roundedBox([mountplate_d, mountplate_d, sensor_mnt_h], corner_r, true, columns); }
//					
//				
//				union() {
//					cylinder(60,cap_r,cap_r, $fn = columns);
//		
//					translate([screw_sep/2,screw_sep/2,-1]) {
//						cylinder(cap_len+1,screw_r,screw_r, $fn = columns);
//					}
//					translate([-screw_sep/2,-screw_sep/2,-1]) {
//						cylinder(cap_len+1,screw_r,screw_r, $fn = columns);
//					}
//		
//					translate([-screw_sep/2,screw_sep/2,-1]) {
//						cylinder(cap_len+1,screw_r,screw_r, $fn = columns);
//					}
//		
//					translate([screw_sep/2,-screw_sep/2,-1]) {
//						cylinder(cap_len+1,screw_r,screw_r, $fn = columns);
//					}
//					
//				}
//			}
//	}
	
	////Driver mount check
//	translate([100,0,0]) {
//				difference(){
//					cylinder(h = driver_mount, r1 = inner_r_la+tube_wall_th/2, r2 = inner_r_la+tube_wall_th/2, $fn = columns);
//					cylinder(h = driver_mount, r1 = inner_r_la, r2 = inner_r_la, $fn = columns);
//					//english_thread(inner_d_la, 18, driver_mount, internal=true);
//				}
//			}

}

pvc_mount();
$fn=20;

epsParoie = 1.5;
epsParoie2 = 2*epsParoie;


piece1();

piece2();



module piece2(){
    color("silver")difference(){
        minkowski() {
            backBox();
            sphere(epsParoie);
        }
        union(){
            translate([0,0,0]) backBox();
            translate([-3,-3,14]) cube([125,65,4]);
            translate([117,4,20]) rotate([-10,0,90]) cube([10.5,7,10]);
        }
    }
}
module backBox(){
    difference(){
    union(){
            translate([0,0,17]) cube([115+epsParoie2,55+epsParoie2,17]);  
        }
        translate([-3,-3,20]) rotate([0,-18,0]) cube([60,65,16]); 
        translate([65,-3,38]) rotate([0,18,0]) cube([60,65,16]); 
        
        translate([-3,-3,18.2]) rotate([40,0,0]) cube([130,65,16]); 
        translate([-3,35,54]) rotate([-55,0,0]) cube([130,65,16]); 
    }
}


module piece1(){
    color("silver")difference(){
            minkowski() {
                              
                fontBox();
                sphere(epsParoie);
            }
             

    union(){
        translate([0,0,0]) fontBox();
        translate([17,epsParoie+3.5,-2]) cube([80,48,8]);
        translate([-10, -10,18]) cube([140,80,10]);  
        connecter();
        }
        
    }
    difference(){
        translate([0,0,16]) cube([115+epsParoie2,55+epsParoie2,4]); 
        union(){
            connecter();
            translate([epsParoie,epsParoie,15]) cube([115,55,6]); 
        }
    }
}
         
module connecter(){
    translate([-5, 10,8]) cube([10,12.5,12.1]);
}    
module fontBox(){
    
    difference(){
        union(){
            translate([0,0,0]) cube([115+epsParoie2,55+epsParoie2,20]);             
        }
        union(){            
            translate([-8, -1,-1]) rotate([0,25,0]) cube([25,55+5,10]);  
            translate([102, -1,-10]) rotate([0,-22,0]) cube([25,55+5,10]); 
        }
    }
    difference(){
        union(){
            translate([-12, 0,10+epsParoie]) rotate([0,25,0]) translate([10, 0,0]) cube([20,55+epsParoie2,epsParoie]);  
            translate([102, 0,epsParoie-0.8]) rotate([0,-22,0]) translate([-5, 0,0]) cube([25,55+epsParoie2,epsParoie]);  
        }
        union(){
            translate([10, -1,-2]) cube([100,60,2]);
            translate([-5, -1,0]) cube([5,60,20]);
            translate([115+epsParoie2, -1,0]) cube([5,60,20]);
        }
    }
}
#include <pebble.h>
#include "goal.h"	
#include "game.h"	

public bool point_in_rect(Vector2 _v, Rect _r){
	if(_v.x>_r.pos.x){
		if(_v.y>_r.pos.y){
			if(_v.x<_r.pos.x+_r.size.x){
				if(_v.y<_r.pos.y+_r.size.y){
					return true;
				}
			}
		}
	}
	return false;
}	 

// checks if a Rect overlaps another Rect
public bool r_intersects(Rect _r1, Rect _r2){
	if(point_in_rect(_r1.pos, _r2)||
		 point_in_rect(_r2.pos, _r1)||
		 point_in_rect((Vector2){_r1.pos.x+_r1.size.x,_r1.pos.y+_r1.size.y}, _r2)||
		 point_in_rect((Vector2){_r2.pos.x+_r2.size.x,_r2.pos.y+_r2.size.y}, _r1)||
		 point_in_rect((Vector2){_r1.pos.x+_r1.size.x,_r1.pos.y}, _r2)||
		 point_in_rect((Vector2){_r2.pos.x+_r2.size.x,_r2.pos.y}, _r1)||
		 point_in_rect((Vector2){_r1.pos.x,_r1.pos.y+_r1.size.y}, _r2)||
		 point_in_rect((Vector2){_r2.pos.x,_r2.pos.y+_r2.size.y}, _r1)){
		return true;
	}
		 
	return false;
}	

// returns the next location of the Goal Object in a different quandrant than the current quadrant
public Vector2 get_next_pos(Goal* g){
	Rect _r1 = (Rect) { // 1st Quadrant
		(Vector2) {20,0},
		(Vector2) {20,20}
	};
	Rect _r2 = (Rect) { // 2nd Quadrant
		(Vector2) {0,0},
		(Vector2) {20,20}
	};
	Rect _r3 = (Rect) { // 3rd Quadrant
		(Vector2) {0,20},
		(Vector2) {20,20}
	};
	Rect _r4 = (Rect) { // 4th Quadrant
		(Vector2) {20,20},
		(Vector2) {20,20}
	};
	
	// Iterate through all possible Rect sections and pick the possible Rects to use
	int i = 0;
	Rect* _a_rects = new Rect[3]; // available Rects to be used for next Goal Point
	
	if(!point_in_rect(g->rect->pos,_r1)){
		_a_rects[i] = _r1;
		i++;
	}
	if(!point_in_rect(g->rect->pos,_r2)){
		_a_rects[i] = _r2;
		i++;
	}
	if(!point_in_rect(g->rect->pos,_r3)){
		_a_rects[i] = _r3;
		i++;
	}
	if(!point_in_rect(g->rect->pos,_r1)){
		if(i<3){
			_a_rects[i] = _r4;
			i++;
		}
	}
	
	double _x = (((double)rand()%180)/10) + 1;
	double _y = (((double)rand()%180)/10) + 1;
	
	int index = rand()%3;
	g->rect->pos = (Vector2) {_a_rects[index].pos.x+_x,_a_rects[index].pos.y+_y};
	// INCREASE POINTS HERE!
	return (Vector2) {_a_rects[index].pos.x+_x,_a_rects[index].pos.y+_y};
}
///ui_rect(screen_x, screen_y, screen_x2, screen_y2, col, alpha)
/*
    draw rectangle in screen units [0...1]
*/

var _absx1 = argument0 * WIN_WID, _absy1 = argument1 * WIN_HEI;
var _absx2 = argument2 * WIN_WID, _absy2 = argument3 * WIN_HEI;

iui_rect_alpha(_absx1, _absy1, _absx2, _absy2, argument4, argument5);

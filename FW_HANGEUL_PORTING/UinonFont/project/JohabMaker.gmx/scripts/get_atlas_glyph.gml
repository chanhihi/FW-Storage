///get_atlas_glyph(sprite, glyphindex, surface)
/*
    Blits part from glyph atlas to given surface
    pass -1 into surface argument to only store the result to glyphTemp variable
*/

var _atlas = argument0, _idx = argument1, _surf = argument2;
var _atlaswid, _atlashei;

// check sprite
if (!sprite_exists(_atlas))
{
    return _surf;
    show_debug_message("ATLAS_GET] ERROR : NO SPRITE!!");
}

// check surface
/*
if (!surface_exists(glyphTemp))
{
    surface_free(glyphTemp);
    glyphTemp = surface_create(charWid, charHei);
    show_debug_message("CREATED GLYPH TEMP");
}
else
    surface_resize(glyphTemp, charWid, charHei);
*/
var _temp = surface_create(charWid, charHei);
    
surface_set_target(_temp);
var _u = charWid * (_idx % gridWid);
var _v = charHei * (_idx div gridWid);

// get surface
draw_clear_alpha(0, 0);
draw_sprite_part(_atlas, 0, _u, _v, charWid, charHei, 0, 0);

surface_reset_target();

// set surface
if (_surf != -1) // copy to tohe rsurface
{
    if (!surface_exists(_surf))
    {
        _surf = surface_create(charWid, charHei);
        show_debug_message("ATLAS_GET] ERROR : GIVEN SURFACE DOES NOT EXIST!!");
    }
    // surface_set_target(_surf);
    // draw_surface(glyphTemp, 0, 0);
    // surface_reset_target();
    surface_copy(_surf, 0, 0, _temp);
    surface_free(_temp);
    return _surf;
}
else // user only wants to get data on glyphTemp surface
{
    if (!surface_exists(glyphTemp))
    {
        surface_free(glyphTemp);
        glyphTemp = surface_create(charWid, charHei);
        show_debug_message("CREATED GLYPH TEMP");
    }
    else
        surface_resize(glyphTemp, charWid, charHei);

    surface_copy(glyphTemp, 0, 0, _temp);
    surface_free(_temp);
    return true;
}

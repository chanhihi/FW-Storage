function slide(Id, interval, to)
{
    var obj = document.getElementById(Id);
    var H, step = 10;

    if (obj == null) return;
    if (to == undefined) { // user clicking
        if (obj._slideStart == true) return;
        if (obj._expand == true) {
            to = 0;
            obj.style.overflow = "hidden";
        } else {
            slide.addId(Id);
            for(var i=0; i < slide.objects.length; i++) {
                if (slide.objects[i].id != Id && slide.objects[i]._expand == true) {
                    slide(slide.objects[i].id);
                }
            }

            obj.style.height = "";
            obj.style.overflow = "";
            obj.style.display = "block";
            to = obj.offsetHeight;
            obj.style.overflow = "hidden";
            obj.style.height = "3px";
        }
        obj._slideStart = true;
    }
    
    step            = ((to > 0) ? 1:-1) * step;
    interval        = ((interval==undefined)?1:interval);
    obj.style.height = (H=((H=(isNaN(H=parseInt(obj.style.height))?0:H))+step<0)?0:H+step)+"px";

    if (H <= 0) {
        obj.style.display = "none";
        obj.style.overflow = "hidden";
        obj._expand = false;
        obj._slideStart = false;
		document.getElementById('category_on').style.display='block';
		document.getElementById('category_off').style.display='none';
    } else if (to > 0 && H >= to) {
        obj.style.display = "block";
        obj.style.overflow = "visible";
        obj.style.height = H + "px";
        obj._expand = true;
        obj._slideStart = false;
		document.getElementById('category_on').style.display='none';
		document.getElementById('category_off').style.display='block';
    } else {
        setTimeout("slide('"+Id+"' , "+interval+", "+to+");", interval);
    }
}
slide.objects = new Array();
slide.addId = function(Id)
{
    for (var i=0; i < slide.objects.length; i++) {
        if (slide.objects[i].id == Id) return true;
    }
    slide.objects[slide.objects.length] = document.getElementById(Id);
}

var prevOnmousemove = document.body.onmousemove;
document.body.onmousemove = function (event) {
	if(prevOnmousemove) { prevOnmousemove(); }
	if (document.getElementById('category_on')) {
		try {
			event = event || window.event;
			var clicked = (event.srcElement || event.target);
			var clickedID = (clicked.id || '');
			if (clicked && clicked.parentNode.className != 'span_sub'  && (clickedID == '' || (clickedID.indexOf('category_') == -1)) && clicked.className != 'span_sub' && clicked.parentNode.nodeName != 'A')
			{	
				if (document.getElementById('category_sub1').offsetHeight > 0) {
					slide('category_sub1');
				}
			}
		} catch (e) {}
	}
}
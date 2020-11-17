#ifndef PAGE_ADMIN_H
#define PAGE_ADMIN_H

//<a href="color.html"   style="width:250px"  class="btn btn--m btn--grey" >Colour settings</a><br>
//
//  HTML PAGE
//

const char PAGE_AdminMainPage[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<link rel='stylesheet' href='style.css' type='text/css' />
<body>
<strong>Ring Clock</strong><br>

<hr>
<a href="config.html" style="width:250px" class="btn btn--m btn--grey" >Network Configuration</a><br>
<a href="info.html" style="width:250px"  class="btn btn--m btn--grey" >Network Information</a><br>
<a href="ntp.html" style="width:250px"  class="btn btn--m btn--grey" >System Settings</a><br>
<a href="time.html" style="width:250px"  class="btn btn--m btn--grey" >Manual time setting</a><br>
<hr>
<strong>by BorgMcz - <a href="http://www.dccmm.cz/index.php/dcc-modely/neopixelclockring" target="_blank" >www.dccmm.cz</a></strong>
</body>


)=====";

#endif


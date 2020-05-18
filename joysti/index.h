const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
  <head>
    <title>Joy</title>
    <meta charset="utf-8">
  </head>
  <body>
      <div class="columnLateral">
        <div id="joy1Div" style="width:600px;height:600px;margin:200px"></div>
        Posizione X:<input id="joy1PosizioneX" type="text" /><br />
        Posizione Y:<input id="joy1PosizioneY" type="text" /><br />
        X :<input id="joy1X" type="text" /></br>
        Y :<input id="joy1Y" type="text" />
      </div>
    <script type="text/javascript">
     
var JoyStick = (function(container, parameters) {
  parameters = parameters || {};
  var title = (undefined === parameters.title ? 'joystick' : parameters.title),
    width = (undefined === parameters.width ? 0 : parameters.width),
    height = (undefined === parameters.height ? 0 : parameters.height),
    internalFillColor = (undefined === parameters.internalFillColor ? '#00AA00' : parameters.internalFillColor),
    internalLineWidth = (undefined === parameters.internalLineWidth ? 2 : parameters.internalLineWidth),
    internalStrokeColor = (undefined === parameters.internalStrokeColor ? '#003300' : parameters.internalStrokeColor),
    externalLineWidth = (undefined === parameters.externalLineWidth ? 2 : parameters.externalLineWidth),
    externalStrokeColor = (undefined === parameters.externalStrokeColor ? '#008000' : parameters.externalStrokeColor),
    autoReturnToCenter = (undefined === parameters.autoReturnToCenter ? true : parameters.autoReturnToCenter);
  
  var objContainer = document.getElementById(container);
  var canvas = document.createElement('canvas');
  canvas.id = title;
  if(width === 0) width = objContainer.clientWidth;
  if(height === 0) height = objContainer.clientHeight;
  canvas.width = width;
  canvas.height = height;
  objContainer.appendChild(canvas);
  var context=canvas.getContext('2d');
  
  var pressed = 0;
    var circumference = 2 * Math.PI;
    var internalRadius = (canvas.width-((canvas.width/2)+10))/2;
  var maxMoveStick = internalRadius + 5;
  var externalRadius = internalRadius + 30;
  var centerX = canvas.width / 2;
  var centerY = canvas.height / 2;
  var directionHorizontalLimitPos = canvas.width / 10;
  var directionHorizontalLimitNeg = directionHorizontalLimitPos * -1;
  var directionVerticalLimitPos = canvas.height / 10;
  var directionVerticalLimitNeg = directionVerticalLimitPos * -1;
  var movedX=centerX;
  var movedY=centerY;
  if("ontouchstart" in document.documentElement)
  {
    canvas.addEventListener('touchstart', onTouchStart, false);
    canvas.addEventListener('touchmove', onTouchMove, false);
    canvas.addEventListener('touchend', onTouchEnd, false);
  }
  else
  {
    canvas.addEventListener('mousedown', onMouseDown, false);
    canvas.addEventListener('mousemove', onMouseMove, false);
    canvas.addEventListener('mouseup', onMouseUp, false);
  }
  drawExternal();
  drawInternal();
  function drawExternal()
  {
    context.beginPath();
    context.arc(centerX, centerY, externalRadius, 0, circumference, false);
    context.lineWidth = externalLineWidth;
    context.strokeStyle = externalStrokeColor;
    context.stroke();
  }
  function drawInternal()
  {
    context.beginPath();
    if(movedX<internalRadius) movedX=maxMoveStick;
    if((movedX+internalRadius) > canvas.width) movedX = canvas.width-(maxMoveStick);
    if(movedY<internalRadius) movedY=maxMoveStick;
    if((movedY+internalRadius) > canvas.height) movedY = canvas.height-(maxMoveStick);
    context.arc(movedX, movedY, internalRadius, 0, circumference, false);
    var grd = context.createRadialGradient(centerX, centerY, 5, centerX, centerY, 200);
    grd.addColorStop(0, internalFillColor);
    grd.addColorStop(1, internalStrokeColor);
    context.fillStyle = grd;
    context.fill();
    context.lineWidth = internalLineWidth;
    context.strokeStyle = internalStrokeColor;
    context.stroke();
  }

  function onTouchStart(event) 
  {
    pressed = 1;
  }
  function onTouchMove(event)
  {
    event.preventDefault();
    if(pressed === 1 && event.targetTouches[0].target === canvas)
    {
      movedX = event.targetTouches[0].pageX;
      movedY = event.targetTouches[0].pageY;
      movedX -= canvas.offsetLeft;
      movedY -= canvas.offsetTop;
      context.clearRect(0, 0, canvas.width, canvas.height);
      drawExternal();
      drawInternal();
    }
  } 
  function onTouchEnd(event) 
  {
    pressed = 0;
    if(autoReturnToCenter)
    {
      movedX = centerX;
      movedY = centerY;
    }
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawExternal();
    drawInternal();
  }
  function onMouseDown(event) 
  {
    pressed = 1;
  }
  function onMouseMove(event) 
  {
    if(pressed === 1)
    {
      movedX = event.pageX;
      movedY = event.pageY;
      movedX -= canvas.offsetLeft;
      movedY -= canvas.offsetTop;
      context.clearRect(0, 0, canvas.width, canvas.height);
      drawExternal();
      drawInternal();
    }
  }
  function onMouseUp(event) 
  {
    pressed = 0;
    if(autoReturnToCenter)
    {
      movedX = centerX;
      movedY = centerY;
    }
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawExternal();
    drawInternal();
  }

  this.GetWidth = function () 
  {
    return canvas.width;
  };
  
  this.GetHeight = function () 
  {
    return canvas.height;
  };
  
  this.GetPosX = function ()
  {
    return movedX;
  };
  
  this.GetPosY = function ()
  {
    return movedY;
  };
  
  this.GetX = function ()
  {
    return (100*((movedX - centerX)/maxMoveStick)).toFixed();
  };

  this.GetY = function ()
  {
    return ((100*((movedY - centerY)/maxMoveStick))*-1).toFixed();
  };
  
  this.GetDir = function()
  {
    var result = "";
    var orizontal = movedX - centerX;
    var vertical = movedY - centerY;
    
    if(vertical >= directionVerticalLimitNeg && vertical <= directionVerticalLimitPos)
    {
      result = "C";
    }
    if(vertical < directionVerticalLimitNeg)
    {
      result = "N";
    }
    if(vertical > directionVerticalLimitPos)
    {
      result = "S";
    }
    
    if(orizontal < directionHorizontalLimitNeg)
    {
      if(result === "C")
      { 
        result = "W";
      }
      else
      {
        result += "W";
      }
    }
    if(orizontal > directionHorizontalLimitPos)
    {
      if(result === "C")
      { 
        result = "E";
      }
      else
      {
        result += "E";
      }
    }
    
    return result;
  };
});

var JoyStick=function(t,e){var i=void 0===(e=e||{}).title?"joystick":e.title,n=void 0===e.width?0:e.width,o=void 0===e.height?0:e.height,r=void 0===e.internalFillColor?"#00AA00":e.internalFillColor,h=void 0===e.internalLineWidth?2:e.internalLineWidth,d=void 0===e.internalStrokeColor?"#003300":e.internalStrokeColor,a=void 0===e.externalLineWidth?2:e.externalLineWidth,l=void 0===e.externalStrokeColor?"#008000":e.externalStrokeColor,c=void 0===e.autoReturnToCenter||e.autoReturnToCenter,u=document.getElementById(t),s=document.createElement("canvas");s.id=i,0==n&&(n=u.clientWidth),0==o&&(o=u.clientHeight),s.width=n,s.height=o,u.appendChild(s);var f=s.getContext("2d"),g=0,v=2*Math.PI,w=(s.width-(s.width/2+10))/2,C=w+5,m=w+30,p=s.width/2,L=s.height/2,E=s.width/10,S=-1*E,k=s.height/10,W=-1*k,G=p,x=L;function R(){f.beginPath(),f.arc(p,L,m,0,v,!1),f.lineWidth=a,f.strokeStyle=l,f.stroke()}function T(){f.beginPath(),G<w&&(G=C),G+w>s.width&&(G=s.width-C),x<w&&(x=C),x+w>s.height&&(x=s.height-C),f.arc(G,x,w,0,v,!1);var t=f.createRadialGradient(p,L,5,p,L,200);t.addColorStop(0,r),t.addColorStop(1,d),f.fillStyle=t,f.fill(),f.lineWidth=h,f.strokeStyle=d,f.stroke()}"ontouchstart"in document.documentElement?(s.addEventListener("touchstart",function(t){g=1},!1),s.addEventListener("touchmove",function(t){t.preventDefault(),1==g&&t.targetTouches[0].target==s&&(G=t.targetTouches[0].pageX,x=t.targetTouches[0].pageY,G-=s.offsetLeft,x-=s.offsetTop,f.clearRect(0,0,s.width,s.height),R(),T())},!1),s.addEventListener("touchend",function(t){g=0,c&&(G=p,x=L);f.clearRect(0,0,s.width,s.height),R(),T()},!1)):(s.addEventListener("mousedown",function(t){g=1},!1),s.addEventListener("mousemove",function(t){1==g&&(G=t.pageX,x=t.pageY,G-=s.offsetLeft,x-=s.offsetTop,f.clearRect(0,0,s.width,s.height),R(),T())},!1),s.addEventListener("mouseup",function(t){g=0,c&&(G=p,x=L);f.clearRect(0,0,s.width,s.height),R(),T()},!1)),R(),T(),this.GetWidth=function(){return s.width},this.GetHeight=function(){return s.height},this.GetPosX=function(){return G},this.GetPosY=function(){return x},this.GetX=function(){return((G-p)/C*100).toFixed()},this.GetY=function(){return((x-L)/C*100*-1).toFixed()},this.GetDir=function(){var t="",e=G-p,i=x-L;return i>=W&&i<=k&&(t="C"),i<W&&(t="N"),i>k&&(t="S"),e<S&&("C"==t?t="W":t+="W"),e>E&&("C"==t?t="E":t+="E"),t}};
var Joy1 = new JoyStick('joy1Div');

var joy1IinputPosX = document.getElementById("joy1PosizioneX");
var joy1InputPosY = document.getElementById("joy1PosizioneY");
var joy1Direzione = document.getElementById("joy1Direzione");
var joy1X = document.getElementById("joy1X");
var joy1Y = document.getElementById("joy1Y");

setInterval(function(){ joy1IinputPosX.value=Joy1.GetPosX(); }, 50);
setInterval(function(){ joy1InputPosY.value=Joy1.GetPosY(); }, 50);
setInterval(function(){ joy1Direzione.value=Joy1.GetDir(); }, 50);
setInterval(function(){ joy1X.value=Joy1.GetX(); }, 50);
setInterval(function(){ joy1Y.value=Joy1.GetY(); }, 50);
    </script>
  </body>
</html>
)=====";

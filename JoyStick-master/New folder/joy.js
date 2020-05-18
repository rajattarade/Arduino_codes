/*
 * Name          : joy.js
 * @author       : Roberto D'Amico (Bobboteck)
 * Last modified : 07.01.2020
 * Revision      : 1.1.4
 *
 * Modification History:
 * Date         Version     Modified By		Description
 * 2020-04-20	1.1.5		Roberto D'Amico	Correct: Two sticks in a row, thanks to @liamw9534 for the suggestion
 * 2020-04-03               Roberto D'Amico Correct: InternalRadius when change the size of canvas, thanks to @vanslipon for the suggestion
 * 2020-01-07	1.1.4		Roberto D'Amico Close #6 by implementing a new parameter to set the functionality of auto-return to 0 position
 * 2019-11-18	1.1.3		Roberto D'Amico	Close #5 correct indication of East direction
 * 2019-11-12   1.1.2       Roberto D'Amico Removed Fix #4 incorrectly introduced and restored operation with touch devices
 * 2019-11-12   1.1.1       Roberto D'Amico Fixed Issue #4 - Now JoyStick work in any position in the page, not only at 0,0
 * 
 * The MIT License (MIT)
 *
 *  This file is part of the JoyStick Project (https://github.com/bobboteck/JoyStick).
 *	Copyright (c) 2015 Roberto D'Amico (Bobboteck).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
/**
 * @desc Principal object that draw a joystick, you only need to initialize the object and suggest the HTML container
 * @costructor
 * @param container {String} - HTML object that contains the Joystick
 * @param parameters (optional) - object with following keys:
 *	title {String} (optional) - The ID of canvas (Default value is 'joystick')
 * 	width {Int} (optional) - The width of canvas, if not specified is setted at width of container object (Default value is the width of container object)
 * 	height {Int} (optional) - The height of canvas, if not specified is setted at height of container object (Default value is the height of container object)
 * 	internalFillColor {String} (optional) - Internal color of Stick (Default value is '#00AA00')
 * 	internalLineWidth {Int} (optional) - Border width of Stick (Default value is 2)
 * 	internalStrokeColor {String}(optional) - Border color of Stick (Default value is '#003300')
 * 	externalLineWidth {Int} (optional) - External reference circonference width (Default value is 2)
 * 	externalStrokeColor {String} (optional) - External reference circonference color (Default value is '#008000')
 * 	autoReturnToCenter {Bool} (optional) - Sets the behavior of the stick, whether or not, it should return to zero position when released (Default value is True and return to zero)
 */
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
	
	// Create Canvas element and add it in the Container object
	var objContainer = document.getElementById(container);
	var canvas = document.createElement('canvas');
	canvas.id = title;
	if(width === 0) width = objContainer.clientWidth;
	if(height === 0) height = objContainer.clientHeight;
	canvas.width = width;
	canvas.height = height;
	objContainer.appendChild(canvas);
	var context=canvas.getContext('2d');
	
	var pressed = 0; // Bool - 1=Yes - 0=No
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
	// Used to save current position of stick
	var movedX=centerX;
	var movedY=centerY;
		
	// Check if the device support the touch or not
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
	// Draw the object
	drawExternal();
	drawInternal();
	/******************************************************
	 * Private methods
	 *****************************************************/
	/**
	 * @desc Draw the external circle used as reference position
	 */
	function drawExternal()
	{
		context.beginPath();
		context.arc(centerX, centerY, externalRadius, 0, circumference, false);
		context.lineWidth = externalLineWidth;
		context.strokeStyle = externalStrokeColor;
		context.stroke();
	}
	/**
	 * @desc Draw the internal stick in the current position the user have moved it
	 */
	function drawInternal()
	{
		context.beginPath();
		if(movedX<internalRadius) movedX=maxMoveStick;
		if((movedX+internalRadius) > canvas.width) movedX = canvas.width-(maxMoveStick);
		if(movedY<internalRadius) movedY=maxMoveStick;
		if((movedY+internalRadius) > canvas.height) movedY = canvas.height-(maxMoveStick);
		context.arc(movedX, movedY, internalRadius, 0, circumference, false);
		// create radial gradient
		var grd = context.createRadialGradient(centerX, centerY, 5, centerX, centerY, 200);
		// Light color
		grd.addColorStop(0, internalFillColor);
		// Dark color
		grd.addColorStop(1, internalStrokeColor);
		context.fillStyle = grd;
		context.fill();
		context.lineWidth = internalLineWidth;
		context.strokeStyle = internalStrokeColor;
		context.stroke();
	}
	
	/**
	 * @desc Events for manage touch
	 */
	function onTouchStart(event) 
	{
		pressed = 1;
	}
	function onTouchMove(event)
	{
		// Prevent the browser from doing its default thing (scroll, zoom)
		event.preventDefault();
		if(pressed === 1 && event.targetTouches[0].target === canvas)
		{
			movedX = event.targetTouches[0].pageX;
			movedY = event.targetTouches[0].pageY;
			// Manage offset
			movedX -= canvas.offsetLeft;
			movedY -= canvas.offsetTop;
			// Delete canvas
			context.clearRect(0, 0, canvas.width, canvas.height);
			// Redraw object
			drawExternal();
			drawInternal();
		}
	} 
	function onTouchEnd(event) 
	{
		pressed = 0;
		// If required reset position store variable
		if(autoReturnToCenter)
		{
			movedX = centerX;
			movedY = centerY;
		}
		// Delete canvas
		context.clearRect(0, 0, canvas.width, canvas.height);
		// Redraw object
		drawExternal();
		drawInternal();
		//canvas.unbind('touchmove');
	}
	/**
	 * @desc Events for manage mouse
	 */
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
			// Manage offset
			movedX -= canvas.offsetLeft;
			movedY -= canvas.offsetTop;
			// Delete canvas
			context.clearRect(0, 0, canvas.width, canvas.height);
			// Redraw object
			drawExternal();
			drawInternal();
		}
	}
	function onMouseUp(event) 
	{
		pressed = 0;
		// If required reset position store variable
		if(autoReturnToCenter)
		{
			movedX = centerX;
			movedY = centerY;
		}
		// Delete canvas
		context.clearRect(0, 0, canvas.width, canvas.height);
		// Redraw object
		drawExternal();
		drawInternal();
		//canvas.unbind('mousemove');
	}
	/******************************************************
	 * Public methods
	 *****************************************************/
	/**
	 * @desc The width of canvas
	 * @return Number of pixel width 
	 */
	this.GetWidth = function () 
	{
		return canvas.width;
	};
	
	/**
	 * @desc The height of canvas
	 * @return Number of pixel height
	 */
	this.GetHeight = function () 
	{
		return canvas.height;
	};
	
	/**
	 * @desc The X position of the cursor relative to the canvas that contains it and to its dimensions
	 * @return Number that indicate relative position
	 */
	this.GetPosX = function ()
	{
		return movedX;
	};
	
	/**
	 * @desc The Y position of the cursor relative to the canvas that contains it and to its dimensions
	 * @return Number that indicate relative position
	 */
	this.GetPosY = function ()
	{
		return movedY;
	};
	
	/**
	 * @desc Normalizzed value of X move of stick
	 * @return Integer from -100 to +100
	 */
	this.GetX = function ()
	{
		return (100*((movedX - centerX)/maxMoveStick)).toFixed();
	};

	/**
	 * @desc Normalizzed value of Y move of stick
	 * @return Integer from -100 to +100
	 */
	this.GetY = function ()
	{
		return ((100*((movedY - centerY)/maxMoveStick))*-1).toFixed();
	};
	
	/**
	 * @desc Get the direction of the cursor as a string that indicates the cardinal points where this is oriented
	 * @return String of cardinal point N, NE, E, SE, S, SW, W, NW and C when it is placed in the center
	 */
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

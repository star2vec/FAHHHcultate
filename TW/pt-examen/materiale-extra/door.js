window.onload = function() {
   const canvas = document.getElementById("canvdoor");
    const ctx = canvas.getContext("2d");

   const doorCoords = [
     {x: 70, y: 70},   // stânga sus        
     {x: 70, y: 300},  // stânga jos
      {x: 200, y: 350}, // dreapta jos
      {x: 200, y: 40}   // dreapta sus
   ];

   let doorColor = "red";

   draw();
             
   function draw() {
      ctx.fillStyle = "red";
      ctx.fillRect(50, 50, 200, 250);

      ctx.fillStyle = "white";
      ctx.fillRect(60, 60, 180, 240);


      ctx.fillStyle = doorColor;
      ctx.beginPath();
      ctx.moveTo(doorCoords[0].x, doorCoords[0].y);
      ctx.lineTo(doorCoords[1].x, doorCoords[1].y);
      ctx.lineTo(doorCoords[2].x, doorCoords[2].y);
      ctx.lineTo(doorCoords[3].x, doorCoords[3].y);
      ctx.closePath();
      ctx.fill();

      ctx.fillStyle = "white";
      ctx.beginPath();
      ctx.ellipse(
         180, 200, 
         5, 10, 
         0,      
         0,        
         Math.PI * 2 
      );
      ctx.fill();
   }          
             
    function colorBlue(x, y) {
        ctx.beginPath();
        ctx.moveTo(doorCoords[0].x, doorCoords[0].y);
        ctx.lineTo(doorCoords[1].x, doorCoords[1].y);
        ctx.lineTo(doorCoords[2].x, doorCoords[2].y);
        ctx.lineTo(doorCoords[3].x, doorCoords[3].y);
        ctx.closePath();

        if (ctx.isPointInPath(x, y)) {
            doorColor = "blue";
            draw();
        }
    }

    canvas.addEventListener("click", function(event) {
        const rect = canvas.getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;

        colorBlue(x, y);
    });
}   
        
       
      

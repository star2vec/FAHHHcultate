window.onload = function() {
  const canvas = document.getElementById("canvas");
  const ctx = canvas.getContext("2d");
  var starttime = Date.now();
           
  const foodStart = { x: 280, y: 150 }; // puțin în fața gurii lui Pac-Man
  const pacmanCenter = { x: 150, y: 150 };
  const foodRadius = 10; // raza discului

  function draw() {
    let nowtime = Date.now();
    let elapsed = (nowtime - starttime)/1000; // diferența în milisecunde (pentru animație ulterior)

        
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    const mouthMax = 0.15; // unghi maxim în π radiani
    const mouthAngle = (Math.sin(elapsed * 5) + 1) / 2 * mouthMax; 
    const endAngle = mouthAngle * Math.PI;
    const startAngle = (2 - mouthAngle) * Math.PI;


    ctx.fillStyle = "yellow";
    ctx.beginPath();
    ctx.arc(150, 150, 80, 0, Math.PI * 2);
    ctx.fill();

    ctx.fillStyle = "black";
    ctx.beginPath();
    ctx.arc(150, 150, 80, startAngle, endAngle); 
    ctx.lineTo(150, 150);
    ctx.closePath();
    ctx.fill();

    ctx.fillStyle = "black";
    ctx.beginPath();
    ctx.arc(180, 100, 7, 0, Math.PI * 2); 
    ctx.fill();


    const cycleDuration = 2; // în secunde
    const t = (elapsed % cycleDuration) / cycleDuration;
    const foodX = foodStart.x + (pacmanCenter.x - foodStart.x) * t;
    const foodY = foodStart.y + (pacmanCenter.y - foodStart.y) * t;
    const opacity = 1 - t; // dispare pe măsură ce ajunge la Pac-Man

    ctx.fillStyle = `rgba(255,255,255,${opacity})`;
    ctx.beginPath();
    ctx.arc(foodX, foodY, foodRadius, 0, Math.PI * 2);
    ctx.fill();


    requestAnimationFrame(draw);
  } 

  draw();
}       
